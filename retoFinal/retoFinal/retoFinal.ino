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

// Rangos de ADC y voltaje
#define ADC_RESOLUTION 4095
#define VOLTAGE_MAX 3.3

// Se declaran las variables globales
//Publicador de voltaje
rcl_publisher_t raw_pot_publisher; 
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


//Marco para verificación de errores
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

// Se define lectura del potenciometro en global
int pot_value = 0;

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
    
    
  }
}

// Callback al que se le llamara 2

void subscription_callback(const void * msgin)
{  
  const std_msgs__msg__Float32 * msg = (const std_msgs__msg__Float32 *)msgin;
  // Calcula el valor de PWM a partir del duty cycle recibido
  int pwmValue2 = map(abs(msg->data)*100, 0, 100, 0, 255);
  // Configura el brillo del LED utilizando el valor de PWM
  analogWrite(PWM_PIN, pwmValue2);

  // Configura los pines In1 e In2 dependiendo del signo del duty cycle
  if (msg->data < 0) {
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
  } else {
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
  }
}


void setup() {
  set_microros_transports();
  
  // Inicializa el pin del LED como salida
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);
  digitalWrite(In1, HIGH);
  digitalWrite(In2, HIGH);
  digitalWrite(PWM_PIN, HIGH);
  delay(2000);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(PWM_PIN, LOW);
  delay(2000);

  allocator = rcl_get_default_allocator();

  //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node (string vacio sería el nombre del namespace)
  RCCHECK(rclc_node_init_default(&node, "micro_ros_arduino_node", "", &support));

  // create publisher para mandar entrada directa desde el pot
  RCCHECK(rclc_publisher_init_default(
    &raw_pot_publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
    "ri_raw_pot"));

  // create subscriber que hará pwm según duty cycle obtenido
  RCCHECK(rclc_subscription_init_default(
    &setpoint_sub,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
    "ri_setpoint"));

  // create timer1
  const unsigned int timer_timeout = 10;
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