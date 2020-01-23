#include <Arduino.h>

#include <sensors.h>
#include <display.h>
#include <input.h>

int display_page = 2;

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

  //Get sensor data
  getAccelerometerData();

  //Check for screen change
  if(digitalRead(BTN_UP) == LOW){
    display_page++;
    Serial.print("pg incr");
  }
  else if(digitalRead(BTN_DOWN) == LOW){
    display_page--;
    Serial.print("pg decr");
  }

  //Limit display num to valid pages
  display_page = max(min(display_page, DISPLAY_PAGES), 1);

  switch(display_page){
    case 1:
      drawAccelerometerData();
      break;
    case 2:
      drawOutputData();
      break;
  }


  delay(50);
}
