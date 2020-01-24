#include <ESP32Servo.h>

#include <output/servos.h>

Servo aileron;
Servo elevator;
Servo throttle;
Servo rudder;

uint16_t ail_out = SERVO_MID;
uint16_t ele_out = SERVO_MID;
uint16_t thr_out = SERVO_MIN; //Zero instead of center
uint16_t rud_out = SERVO_MID;

//Set up all connected servos
void setupServos(){

  //Set servo rate (hz)
  aileron.setPeriodHertz(SERVO_HZ);
  elevator.setPeriodHertz(SERVO_HZ);
  throttle.setPeriodHertz(SERVO_HZ);
  rudder.setPeriodHertz(SERVO_HZ);

  //Attach servos
  aileron.attach(AIL_PIN, SERVO_MIN, SERVO_MAX);
  elevator.attach(ELE_PIN, SERVO_MIN, SERVO_MAX);
  throttle.attach(THR_PIN, SERVO_MIN, SERVO_MAX);
  rudder.attach(RUD_PIN, SERVO_MIN, SERVO_MAX);

  //Center all servos
  aileron.writeMicroseconds(SERVO_MID);
  elevator.writeMicroseconds(SERVO_MID);
  rudder.writeMicroseconds(SERVO_MID);

  //Put throttle at 0
  throttle.writeMicroseconds(SERVO_MIN);
}

//Update servo positions
void updateServos(){
  //Write values for all servos
  aileron.writeMicroseconds(ail_out);
  elevator.writeMicroseconds(ele_out);
  rudder.writeMicroseconds(rud_out);

  throttle.writeMicroseconds(thr_out);
}
