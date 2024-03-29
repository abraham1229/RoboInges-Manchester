// Se incluyen las librerias necesarias.
#include <micro_ros_arduino.h>
#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/float32.h>
#include "driver/adc.h"
#include "driver/ledc.h"
#include <math.h>



// Definiciones de pines
#define In1 27 //Pin1 del motor
#define In2 33 // Pin2 del motor
#define PWM_PIN 12 // Pin que otorga el PWM necesario
#define EncA  25 // GPIO para señal A del encoder
#define EncB  26 // GPIO para señal B del encoder

//Definicion del PWM
#define freq 5000//Frecuencia de PWM
#define resolution 8 //Resolución de PWM 2^8 = 256
#define PWM1_Ch 0 // Canal de PWM

//Definicion del pid
#define Umax 14 
#define Umin 0
#define T 0.01 // sampling time
#define pi M_PI

//Variables para el encoder
int32_t tiempo_act = 0, tiempo_ant = 0, delta_tiempo = 2e9; //Variables para calcular velocidad
int pwmValue = 0;        // valor de salida al PWM
float posicion=0, posactual = 0, posanterior = 0, velocidad = 0; //Variables entregadas del encoder
float resolucion = 0.065;  //Definir resolución del encoder
int pulsos = 5500;      //Número de pulsos a la salida del motorreductor
int32_t contador = 0, contaux = 0, revoluciones;
volatile bool BSet = 0;
volatile bool ASet = 0;
volatile bool encoderDirection = false;

//Variables del PID (ecuación característica obtenida heurísticamente)
const double p1 = -0.000009;
const double p2 = 0.0049;
const double p3 = -0.7601;
const double p4 = 34.24;
//Se declaran las variables de la velocidad
double valorEncoderRpm = 0;
double valorEncoderRpm_anterior = 0;
double velocidadMotor=0;
//Lectura del tópico
int setpoint = 0;
double error;
double P, I, D, U;
double I_prec=0, U_prec=0, D_prec=0; 

//Se declara proporcional, integrador y derivativo del controlador
double Kp = 60;  
double Ki = 0.10745; 
double Kd = 0.0268625;


// Se declaran las variables globales
//Publicador de la velocidad angular (rad/s)
rcl_publisher_t controller; 
//Mensaje necesario y obligatorio para publicar
std_msgs__msg__Float32 msg; 
//Sub que maneja duty cycle
rcl_subscription_t setpoint_sub; 
//Se declara timer
rcl_timer_t timer_1;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;

/////FUNCIONES PARA VELOCIDAD
//Función para realizar la lectura de las señales del encoder de cuadratura y
//definir el sentido de giro del motor
void IRAM_ATTR Encoder()
{
  BSet = digitalRead(EncB);
  ASet = digitalRead(EncA);
  if (BSet == ASet)
  {
    contador++;
    encoderDirection = true;
  }
  //Si ambas señales leídas son distintas, el motor gira en sentido horario
  //y se decrementa un contador para saber el número de lecturas
  else
  {
    contador--;
    encoderDirection = false;
  }
  tiempo_act = micros();
  delta_tiempo = tiempo_act - tiempo_ant;
  tiempo_ant = tiempo_act;
}

void pose ()
{
  if (encoderDirection)
  {
    posicion = contador * resolucion; //Convertir a grados
    if (contador >= pulsos) //Contar por revoluciones
    {
      revoluciones++;
      contador = 0;
    }
  }
  else
  {
    posicion = contador * resolucion; //Convertir a grados 
    if (contador <= -pulsos) //Contar por revoluciones
    {
      revoluciones--;
      contador = 0;
    }
  }
  //Cálculo de la velocidad mediante un delta de tiempo  
  velocidad = 60000000/(pulsos * delta_tiempo); 
  //Se pregunta por la velocidad, cuando hay una inversion de giro, para hacerla positiva
  if (velocidad < 0)
    velocidad = abs(velocidad);
  encoderDirection = false; // Reiniciar la variable después de usarla
  
}

///Función del control
void controlPID(){
  //Se calcula el error del sistema
  error = valorEncoderRpm - setpoint; 

  //Se obtienen las salidas de los coeficientes del control
  P = Kp*error;

  I = I_prec + T*Ki*error;

  D = (Kd/T)*(valorEncoderRpm - valorEncoderRpm_anterior);

  U = P + I + D; 

  //Se usa la función de la ecuación característica respecto a U
  velocidadMotor = p1*pow(U,3) + p2*pow(U,2) + p3*U + p4;

  ledcWrite(PWM1_Ch, velocidadMotor);

  //Se declaran las variables en anterior para cambiarlas en el presente
  I_prec = I;
  valorEncoderRpm_anterior = valorEncoderRpm;
  D_prec = D; 
}

////FUNCIONES DE ROS
//Marco para verificación de errores
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

// Se define lectura del potenciometro en global
int pot_value = 0;
bool direccion = true;

// Indicador de error critico
void error_loop(){
  while(1){
    digitalWrite(In2, !digitalRead(In2));
    delay(100);
  }
}

// Callback al que se le llamara del publisher
void timer_callback_1(rcl_timer_t * timer_1, int64_t last_call_time)
{  
  RCLC_UNUSED(last_call_time);
  if (timer_1 != NULL) {
    //Calcula la velocidad con el encoder
    pose();

    //Se declara el signo de la velocidad.    
    if (direccion){
      msg.data = -velocidad*2*pi/60;
    }
    else{
      msg.data = velocidad*2*pi/60;
    }
    
    valorEncoderRpm = velocidad;
    RCSOFTCHECK(rcl_publish(&controller, &msg, NULL));
    
  }
}

// Callback al que se le llamara del suscriber

void subscription_callback(const void * msgin)
{  
  const std_msgs__msg__Float32 * msg = (const std_msgs__msg__Float32 *)msgin;

  //Se cambia a RPM ()
  setpoint = abs(msg->data) * 14;
  // Configura el brillo del LED utilizando el valor de PWM
  controlPID();
  
  // Configura los pines In1 e In2 dependiendo del signo del duty cycle
  // Si es que cambia de signo bruscamente, se detiene para no afectar los electrónicos.
  if (msg->data < 0) {
    if (direccion == true){
      digitalWrite(In1, HIGH);
      digitalWrite(In2, LOW);
    }
    else{
      digitalWrite(In1, LOW);
      digitalWrite(In2, LOW);
      delay(10);
      digitalWrite(In1, HIGH);
      digitalWrite(In2, LOW);
      direccion = true;
    }
  } else {
    if(direccion == false){
      digitalWrite(In1, LOW);
      digitalWrite(In2, HIGH);
    }
    else{
      digitalWrite(In1, LOW);
      digitalWrite(In2, LOW);
      delay(10);
      digitalWrite(In1, LOW);
      digitalWrite(In2, HIGH);
      direccion = false;
    }
    
  }
}



void setup() {
  set_microros_transports();
  
  // Se inicializan como salida el PWM y las salidas del motor
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);
  
  // configurar funciones PWM
  ledcSetup(PWM1_Ch, freq, resolution);
  ledcAttachPin(PWM_PIN, PWM1_Ch);


  //Configuracion del encoder.
  pinMode(EncA, INPUT_PULLUP);    // Señal A del encoder como entrada con pull-up
  pinMode(EncB, INPUT_PULLUP);    // Señal B del encoder como entrada con pull-up
  attachInterrupt(digitalPinToInterrupt(EncA), Encoder, CHANGE); // Asignar la función Encoder a la interrupción de cambio en la señal A
  
  allocator = rcl_get_default_allocator();

  //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node (string vacio sería el nombre del namespace)
  RCCHECK(rclc_node_init_default(&node, "micro_ros_arduino_node", "", &support));

  // create publisher para mandar le velocidad lineal
  RCCHECK(rclc_publisher_init_default(
    &controller,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
    "ri_controller"));

  // create subscriber que hará pwm según duty cycle obtenido
  RCCHECK(rclc_subscription_init_default(
    &setpoint_sub,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
    "ri_setpoint"));

  // create timer1 
  // SE TIENE ESA FRECUENNCIA PORQUE ES MÁS DE DOS VECES LAS QUE SE MANDAN DESDE PYTHON (teorena de nyquist)
  const unsigned int timer_timeout = 0.01;
  RCCHECK(rclc_timer_init_default(
    &timer_1,
    &support,
    RCL_MS_TO_NS(timer_timeout),
    timer_callback_1));

  // create executors para todos los publisher y suscribers
  RCCHECK(rclc_executor_init(&executor, &support.context, 3, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer_1));

  RCCHECK(rclc_executor_add_subscription(&executor, &setpoint_sub, &msg, &subscription_callback, ON_NEW_DATA));

  msg.data = 0;
}

//Loop lo más vacio por buenas prácticas
void loop() {
  delay(100);
  RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}
