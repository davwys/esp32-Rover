#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include <SPI.h>

#include <hardware/accelerometer.h>

#include <config.h>

//Accelerometer sensor object
MPU6050 accel;

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

#define INTERRUPT_PIN 2

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}


/*======================
  Accelerometer setup functions
======================*/

void setupAccelerometer(){
  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
      Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
  accel.initialize();
  //Enable interrupt
  pinMode(INTERRUPT_PIN, INPUT);

   // verify connection
   #ifdef DEBUG_ENABLED
    Serial.println(F("Testing device connections..."));
    Serial.println(accel.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
    Serial.println(F("Initializing DMP..."));
   #endif
   devStatus = accel.dmpInitialize();

   //Supply your own gyro offsets here, scaled for min sensitivity
   accel.setXGyroOffset(0);
   accel.setYGyroOffset(0);
   accel.setZGyroOffset(0);
   accel.setZAccelOffset(1688); // 1688 factory default for my test chip

   //Make sure it worked (returns 0 if so)
   if (devStatus == 0) {
       // Calibration Time: generate offsets and calibrate our MPU6050
       accel.CalibrateAccel(6);
       accel.CalibrateGyro(6);
       accel.PrintActiveOffsets();
       //Turn on the DMP, now that it's ready
       #ifdef DEBUG_ENABLED
        Serial.println(F("Enabling DMP..."));
       #endif
       accel.setDMPEnabled(true);

         //Enable Arduino interrupt detection
         #ifdef DEBUG_ENABLED
           Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
           Serial.print(digitalPinToInterrupt(INTERRUPT_PIN));
           Serial.println(F(")..."));
         #endif
         attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
         mpuIntStatus = accel.getIntStatus();


       // set our DMP Ready flag so the main loop() function knows it's okay to use it
       #ifdef DEBUG_ENABLED
          Serial.println(F("DMP ready! Waiting for first interrupt..."));
       #endif
       dmpReady = true;

       // get expected DMP packet size for later comparison
       packetSize = accel.dmpGetFIFOPacketSize();
   } else {
       // ERROR!
       // 1 = initial memory load failed
       // 2 = DMP configuration updates failed
       // (if it's going to break, usually the code will be 1)
       #ifdef DEBUG_ENABLED
         Serial.print(F("DMP Initialization failed (code "));
         Serial.print(devStatus);
         Serial.println(F(")"));
       #endif
   }

}


/*======================
  Accelerometer data functions
======================*/

void getAccelerometerData(){

  double pitch_previous = pitch;
  double roll_previous = roll;

  // if programming failed, don't try to do anything
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
        if (mpuInterrupt && fifoCount < packetSize) {
          // try to get out of the infinite loop
          fifoCount = accel.getFIFOCount();
        }
        // other program behavior stuff here
        // .
        // .
        // .
        // if you are really paranoid you can frequently test in between other
        // stuff to see if mpuInterrupt is true, and if so, "break;" from the
        // while() loop to immediately process the MPU data
        // .
        // .
        // .
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = accel.getIntStatus();

    // get current FIFO count
    fifoCount = accel.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & _BV(MPU6050_INTERRUPT_FIFO_OFLOW_BIT)) || fifoCount >= 1024) {
        // reset so we can continue cleanly
        accel.resetFIFO();
        fifoCount = accel.getFIFOCount();
        //Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & _BV(MPU6050_INTERRUPT_DMP_INT_BIT)) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = accel.getFIFOCount();

        // read a packet from FIFO
        accel.getFIFOBytes(fifoBuffer, packetSize);

        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

        // display Euler angles in degrees
        accel.dmpGetQuaternion(&q, fifoBuffer);
        accel.dmpGetGravity(&gravity, &q);
        accel.dmpGetYawPitchRoll(ypr, &q, &gravity);

        //Save values
        yaw = ypr[0] * 180/M_PI;
        roll = ypr[1] * 180/M_PI;
        pitch = -(ypr[2] * 180/M_PI);

        /*
        mpu.dmpGetAccel(&aa, fifoBuffer);
        Serial.print("\tRaw Accl XYZ\t");
        Serial.print(aa.x);
        Serial.print("\t");
        Serial.print(aa.y);
        Serial.print("\t");
        Serial.print(aa.z);
        mpu.dmpGetGyro(&gy, fifoBuffer);
        Serial.print("\tRaw Gyro XYZ\t");
        Serial.print(gy.x);
        Serial.print("\t");
        Serial.print(gy.y);
        Serial.print("\t");
        Serial.print(gy.z);

        Serial.println();*/
    }

  //Low-pass filter
  roll = 0.9 * roll + 0.1 * roll_previous;
  pitch = 0.9 * pitch + 0.1 * pitch_previous;

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
