#include <ESP32Servo.h>

#include <servos.h>

Servo aileron;
Servo elevator;
Servo throttle;
Servo rudder;

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
  aileron.write(90);
  elevator.write(90);
  rudder.write(90);

  //Put throttle at 0
  throttle.write(0);
}
