#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>


//Sensor object
extern Adafruit_ADXL345_Unified accel ; //12345 would be the sensor's ID

//Sensor values
extern float pitch;
extern float roll;
extern float yaw;
extern float acc_x;
extern float acc_y;
extern float acc_z;
extern float offset_pitch;
extern float offset_roll;
extern float offset_yaw;


//Setup functions
void setupAccelerometer(bool verbose);

//Accelerometer data
void getAccelerometerData();
