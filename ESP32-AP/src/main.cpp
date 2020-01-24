#include <Arduino.h>

#include <sensors.h>
#include <display.h>
#include <input.h>
#include <rcinput.h>

int display_page = 1;

//Initial setup function
void setup() {

  /*======================
    Communication Setup
  ======================*/

  Serial.begin(57600);

  /*======================
    Sensor Setup
  ======================*/

  setupAccelerometer(false);

  /*======================
    Receiver Setup
  ======================*/

  setupReceiver();

  /*======================
    Display Setup (optional)
  ======================*/

  setupDisplay();

  /*======================
    I/O Setup
  ======================*/

  setupButtons();


  /*======================
    LED Setup
  ======================*/

}

//Main Loop function
void loop() {

  //Get sensor data
  getAccelerometerData();

  //Check for screen change
  if(digitalRead(BTN_UP) == LOW){
    display_page++;
  }
  else if(digitalRead(BTN_DOWN) == LOW){
    display_page--;
  }

  //Limit display num to valid pages
  display_page = max(min(display_page, DISPLAY_PAGES), 1);

  switch(display_page){
    case 1:
      drawAccelerometerData();
      break;
    case 2:
      drawInputData();
      break;
    case 3:
      drawOutputData();
      break;

    //Error handling: reset to page 1
    default:
      display_page = 1;
      break;
  }

  //Get RX input
  getReceiverInput(true);

  delay(50);
}
