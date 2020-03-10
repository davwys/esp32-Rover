#include "I2Cdev.h"
#include "MPU6050.h"
#include <Adafruit_Sensor.h>

#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

//Sensor object
extern MPU6050 accel ;

//Sensor values
extern double pitch;
extern double roll;
extern double yaw;
extern double acc_x;
extern double acc_y;
extern double acc_z;
extern double offset_pitch;
extern double offset_roll;
extern double offset_yaw;


//Setup functions
void setupAccelerometer();

//Accelerometer data
void getAccelerometerData();

//Calibration
void calibrateAccelerometerLevel();

#endif
