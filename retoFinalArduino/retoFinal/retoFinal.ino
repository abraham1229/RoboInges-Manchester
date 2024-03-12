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

// Definiciones de pines
#define In1 27 //Pin que lee la entrada del pot.
#define In2 33 // Pin que sera modificado con por duty cycle
#define PWM_PIN 12 // Pin que será modificado con el pot
#define EncA  25 // GPIO para señal A del encoder
#define EncB  26 // GPIO para señal B del encoder

#define freq 5000//Frecuencia de PWM
#define resolution 8 //Resolución de PWM 2^8 = 256
#define PWM1_Ch 0 // Canal de PWM

int32_t tiempo_act = 0, tiempo_ant = 0, delta_tiempo = 2e9;
int pwmValue = 0;        // valor de salida al PWM
int pot;
char opcion;
float posicion=0, posactual = 0, posanterior = 0, velocidad = 0;
float resolucion = 0.065;  //Definir resolución del encoder
int pulsos = 5500;      //Número de pulsos a la salida del motorreductor
int32_t contador = 0, contaux = 0, revoluciones;
volatile bool BSet = 0;
volatile bool ASet = 0;
volatile bool encoderDirection = false;

// Se declaran las variables globales
//Publicador de voltaje
rcl_publisher_t controller; 
//Mensaje necesario y obligatorio para publicar
std_msgs__msg__Float32 msg; 
//Sub que maneja duty cycle
rcl_subscription_t setpoint_sub; 
//Se declaran timers
rcl_timer_t timer_1;
rcl_timer_t timer_2;
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

// Callback al que se le llamara
void timer_callback_1(rcl_timer_t * timer_1, int64_t last_call_time)
{  
  RCLC_UNUSED(last_call_time);
  if (timer_1 != NULL) {
    // Leer el valor del potenciómetro
    pose();    
    msg.data = velocidad;
    RCSOFTCHECK(rcl_publish(&controller, &msg, NULL));
    
  }
}

// Callback al que se le llamara 2

void subscription_callback(const void * msgin)
{  
  const std_msgs__msg__Float32 * msg = (const std_msgs__msg__Float32 *)msgin;
  // Calcula el valor de PWM a partir del duty cycle recibido
  pwmValue = map(abs(msg->data)*100, 0, 100, 0, 255);
  // Configura el brillo del LED utilizando el valor de PWM
  ledcWrite(PWM1_Ch, pwmValue);

  // Configura los pines In1 e In2 dependiendo del signo del duty cycle
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
  
  // Inicializa el pin del LED como salida
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);
  
  // configurar funciones PWM
  ledcSetup(PWM1_Ch, freq, resolution);
  ledcAttachPin(PWM_PIN, PWM1_Ch);

  pinMode(EncA, INPUT_PULLUP);    // Señal A del encoder como entrada con pull-up
  pinMode(EncB, INPUT_PULLUP);    // Señal B del encoder como entrada con pull-up
  attachInterrupt(digitalPinToInterrupt(EncA), Encoder, CHANGE); // Asignar la función Encoder a la interrupción de cambio en la señal A
  
  allocator = rcl_get_default_allocator();

  //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node (string vacio sería el nombre del namespace)
  RCCHECK(rclc_node_init_default(&node, "micro_ros_arduino_node", "", &support));

  // create publisher para mandar entrada directa desde el pot
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
  const unsigned int timer_timeout = 0.1;
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
