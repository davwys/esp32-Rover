#include <Arduino.h>

//TODO testing on all pins

//Control surface/throttle pins
#define AIL_PIN 25
#define ELE_PIN 26
#define RUD_PIN 27
#define THR_PIN 13

//Auxilary function pins
#define AUX1_PIN 32
#define AUX2_PIN 33
#define AUX3_PIN 5

//Servo rate / travel
#define SERVO_HZ 50
#define SERVO_MIN 1000
#define SERVO_MAX 2000

//Current servo PWM values
extern uint16_t ail_out;
extern uint16_t ele_out;
extern uint16_t thr_out;
extern uint16_t rud_out;


void setupServos();
