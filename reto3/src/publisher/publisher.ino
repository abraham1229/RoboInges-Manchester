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
#define POTENTIOMETER_PIN 36
#define LED_PIN 13
#define PWM_PIN 15

// Rangos de ADC y voltaje
#define ADC_RESOLUTION 4095
#define VOLTAGE_MAX 3.3

// Se declaran las variables globales
// Variables globales
rcl_publisher_t raw_pot_publisher;
std_msgs__msg__Int32 msg;
rcl_publisher_t voltage_publisher;
std_msgs__msg__Float32 voltage_msg;
rcl_subscription_t pwm_duty_cycle_sub;
std_msgs__msg__Float32 pwm_duty_cycle_msg;
rcl_timer_t timer_1;
rcl_timer_t timer_2;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;

//Definiciones de pines 
#define LED_PIN 13

//Marco para verificación de errores
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}


// Indicador de error critico
void error_loop(){
  while(1){
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(100);
  }
}

// Callback al que se le llamara
void timer_callback(rcl_timer_t * timer_1, int64_t last_call_time)
{  
  RCLC_UNUSED(last_call_time);
  if (timer_1 != NULL) {
    RCSOFTCHECK(rcl_publish(&raw_pot_publisher, &msg, NULL));
    msg.data++;
  }
}


void setup() {
  set_microros_transports();
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);  
  
  delay(2000);

  allocator = rcl_get_default_allocator();

  //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node (string vacio sería el nombre del namespace)
  RCCHECK(rclc_node_init_default(&node, "micro_ros_arduino_node", "", &support));

  // create publisher
  RCCHECK(rclc_publisher_init_default(
    &raw_pot_publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "micro_ros_arduino_node_publisher"));

  // create timer,
  const unsigned int timer_timeout = 1000;
  RCCHECK(rclc_timer_init_default(
    &timer_1,
    &support,
    RCL_MS_TO_NS(timer_timeout),
    timer_callback));

  // create executor
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer_1));

  msg.data = 0;
}

void loop() {
  delay(100);
  RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}
