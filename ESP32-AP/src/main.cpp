#include <Arduino.h>

#include <sensors.h>
#include <display.h>
#include <input.h>



//Initial setup function
void setup() {

  /*======================
    Communication Setup
  ======================*/

  Serial.begin(57600);

  /*======================
    Display Setup (optional)
  ======================*/

  setupDisplay();

  /*======================
    Sensor Setup
  ======================*/

  setupAccelerometer(false);

  /*======================
    IO Setup
  ======================*/

  setupButtons();
}

//Main Loop function
void loop() {

  getAccelerometerData();

  drawAccelerometerData();

  delay(50);
}
