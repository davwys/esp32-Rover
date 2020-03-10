#include <ESP32Servo.h>

#include <output/servos.h>

Servo steering;
Servo throttle;

uint16_t steer_out = SERVO_MID;
uint16_t thr_out = SERVO_MIN; //Zero instead of center

//Set up all connected servos
void setupServos(){

  //Set servo rate (hz)
  steering.setPeriodHertz(SERVO_HZ);
  throttle.setPeriodHertz(SERVO_HZ);

  //Attach servos
  steering.attach(STEER_PIN, SERVO_MIN, SERVO_MAX);
  throttle.attach(THR_PIN, SERVO_MIN, SERVO_MAX);

  //Center all servos
  steering.writeMicroseconds(SERVO_MID);

  //Put throttle at 0
  throttle.writeMicroseconds(SERVO_MIN);
}

//Update servo positions
void updateServos(){
  //Write values for all servos
  steering.writeMicroseconds(steer_out);

  throttle.writeMicroseconds(thr_out);
}
