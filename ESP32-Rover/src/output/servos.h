#include <Arduino.h>

#ifndef SERVOS_H
#define SERVOS_H

//Steering/throttle pins
#define STEER_PIN 25
#define THR_PIN 13

//Auxilary function pins
//TODO testing on all pins
#define AUX1_PIN 26
#define AUX2_PIN 27
//#define AUX3_PIN 5

//Servo rate / travel
#define SERVO_HZ 50
#define SERVO_MIN 1000
#define SERVO_MAX 2000
#define SERVO_MID (SERVO_MIN + SERVO_MAX) / 2

//Current servo PWM values
extern uint16_t steer_out;
extern uint16_t thr_out;
extern uint16_t aux1_out;
extern uint16_t aux2_out;


void setupServos();

//Update all servo positions
void updateServos();

#endif
