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

//Setup functions
void setupAccelerometer(bool verbose);

//Sensor information functions (TODO remove?)
void displaySensorDetails();
void displayDataRate();
void displayRange();

//Accelerometer data
void getAccelerometerData();
