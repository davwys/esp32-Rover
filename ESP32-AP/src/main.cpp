#include <Arduino.h>

#include <sensors.h>
#include <display.h>



/*======================
  Pin definitions
======================*/

#define BTN_UP 19
#define BTN_DOWN 18
#define BTN_ENTER 4


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

  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_ENTER, INPUT_PULLUP);
}

//Main Loop function
void loop() {

  getAccelerometerData();

  drawAccelerometerData();

  delay(50);
}
