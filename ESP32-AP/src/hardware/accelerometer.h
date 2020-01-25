#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

//Sensor object
extern Adafruit_ADXL345_Unified accel ; //12345 would be the sensor's ID

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
void setupAccelerometer(bool verbose);

//Accelerometer data
void getAccelerometerData();

//Calibration
void calibrateAccelerometerLevel();

#endif
