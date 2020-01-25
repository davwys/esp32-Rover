#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SPI.h>
#include <Wire.h>

#include <hardware/accelerometer.h>


//Accelerometer sensor object
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); //12345 would be the sensor's ID

//Accelerometer values
double pitch = 0.0;
double roll = 0.0;
double yaw = 0.0;

double acc_x = 0.0;
double acc_y = 0.0;
double acc_z = 0.0;

double offset_pitch = 0.0;
double offset_roll = 0.0;
double offset_yaw = 0.0;


/*======================
  Accelerometer information functions
======================*/

void displaySensorDetails()
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void displayDataRate()
{
  Serial.print  ("Data Rate:    ");

  switch(accel.getDataRate())
  {
    case ADXL345_DATARATE_3200_HZ:
      Serial.print  ("3200 ");
      break;
    case ADXL345_DATARATE_1600_HZ:
      Serial.print  ("1600 ");
      break;
    case ADXL345_DATARATE_800_HZ:
      Serial.print  ("800 ");
      break;
    case ADXL345_DATARATE_400_HZ:
      Serial.print  ("400 ");
      break;
    case ADXL345_DATARATE_200_HZ:
      Serial.print  ("200 ");
      break;
    case ADXL345_DATARATE_100_HZ:
      Serial.print  ("100 ");
      break;
    case ADXL345_DATARATE_50_HZ:
      Serial.print  ("50 ");
      break;
    case ADXL345_DATARATE_25_HZ:
      Serial.print  ("25 ");
      break;
    case ADXL345_DATARATE_12_5_HZ:
      Serial.print  ("12.5 ");
      break;
    case ADXL345_DATARATE_6_25HZ:
      Serial.print  ("6.25 ");
      break;
    case ADXL345_DATARATE_3_13_HZ:
      Serial.print  ("3.13 ");
      break;
    case ADXL345_DATARATE_1_56_HZ:
      Serial.print  ("1.56 ");
      break;
    case ADXL345_DATARATE_0_78_HZ:
      Serial.print  ("0.78 ");
      break;
    case ADXL345_DATARATE_0_39_HZ:
      Serial.print  ("0.39 ");
      break;
    case ADXL345_DATARATE_0_20_HZ:
      Serial.print  ("0.20 ");
      break;
    case ADXL345_DATARATE_0_10_HZ:
      Serial.print  ("0.10 ");
      break;
    default:
      Serial.print  ("???? ");
      break;
  }
  Serial.println(" Hz");
}

void displayRange()
{
  Serial.print  ("Range:         +/- ");

  switch(accel.getRange())
  {
    case ADXL345_RANGE_16_G:
      Serial.print  ("16 ");
      break;
    case ADXL345_RANGE_8_G:
      Serial.print  ("8 ");
      break;
    case ADXL345_RANGE_4_G:
      Serial.print  ("4 ");
      break;
    case ADXL345_RANGE_2_G:
      Serial.print  ("2 ");
      break;
    default:
      Serial.print  ("?? ");
      break;
  }
  Serial.println(" g");
}


/*======================
  Accelerometer setup functions
======================*/

void setupAccelerometer(bool verbose){
  //Initialise accelerometer
  if(!accel.begin())
  {
    Serial.println("No accelerometer detected!");
  }
  //Set accelerometer range
  accel.setRange(ADXL345_RANGE_8_G);

  if(verbose){
    //Print accelerometer info
    displaySensorDetails();
    displayDataRate();
    displayRange();
    Serial.println("");
  }
}


/*======================
  Accelerometer data functions
======================*/

void getAccelerometerData(){
  //Get new sensor event
  sensors_event_t event;
  accel.getEvent(&event);

  acc_x = event.acceleration.x;
  acc_y = event.acceleration.y;
  acc_z = event.acceleration.z;

  double pitch_previous = pitch;
  double roll_previous = roll;

  roll = atan(acc_y / sqrt(pow(acc_x, 2) + pow(acc_z, 2))) * 180 / PI;
  pitch = -(atan(-1 * acc_x / sqrt(pow(acc_y, 2) + pow(acc_z, 2))) * 180 / PI);

  //Low-pass filter
  roll = 0.94 * roll + 0.06 * roll_previous;
  pitch = 0.94 * pitch + 0.06 * pitch_previous;

  //Apply offsets
  pitch -= offset_pitch;
  roll -= offset_roll;
  yaw -= offset_yaw;
}

//Sets accelerometer as level
void calibrateAccelerometerLevel(){
  offset_pitch = 0.0;
  offset_roll = 0.0;
  offset_yaw = 0.0;

  getAccelerometerData();

  offset_pitch = pitch;
  offset_roll = roll;
  offset_yaw = yaw;
}
