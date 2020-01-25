#include <Arduino.h>
#include <PID_v1.h>

#include <modes/stabilization.h>
#include <input/rcinput.h>
#include <hardware/accelerometer.h>
#include <output/servos.h>


//PID values
double P_PITCH=2, I_PITCH=0.1, D_PITCH=0.5;
double P_ROLL=2, I_ROLL=0.1, D_ROLL=0.5;
double P_YAW=2, I_YAW=0.1, D_YAW=0.5;

//Current target angles
double pitch_target = 0.0;
double roll_target = 0.0;
double yaw_target = 0.0;

double ail_out_temp;
double ele_out_temp;
double rud_out_temp;

//Specify the links and initial tuning parameters
PID PID_Pitch(&pitch, &ele_out_temp, &pitch_target, P_PITCH, I_PITCH, D_PITCH, DIRECT);
PID PID_Roll(&roll, &ail_out_temp, &roll_target, P_ROLL, I_ROLL, D_ROLL, DIRECT);
PID PID_Yaw(&roll, &ail_out_temp, &roll_target, P_ROLL, I_ROLL, D_ROLL, DIRECT);

//Sets up the PID controllers for three axis stabilization
void setupStabilization(){
  //turn the PID on
  PID_Pitch.SetMode(AUTOMATIC);
  PID_Roll.SetMode(AUTOMATIC);
  PID_Yaw.SetMode(AUTOMATIC);
}

//Generates stabilized outputs, given current angle and angle target
void stabilize(bool stabilize_yaw){
  PID_Pitch.Compute();
  PID_Roll.Compute();
  if(stabilize_yaw){
    PID_Yaw.Compute();
  }

  //Generate output mixed with TX input


  uint16_t diff = SERVO_MAX-SERVO_MIN;

  ail_out_temp = ail_out_temp / 90.0;
  Serial.print("Roll out: ");
  Serial.println(ail_out_temp);

  uint16_t ail_out_t = SERVO_MID + ail_out_temp * (diff/2);
  ail_out_t = min(max(int(ail_out_t), SERVO_MIN), SERVO_MAX);
  Serial.print("Roll Servo out: ");
  Serial.println(ail_out_t);

}
