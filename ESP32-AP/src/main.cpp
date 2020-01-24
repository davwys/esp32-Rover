#include <Arduino.h>

#include <sensors.h>
#include <display.h>
#include <input.h>
#include <rcinput.h>

int display_page = 1;
unsigned long display_lastframe = 0.0; //time in ms when last frame was drawn

//Whether page can be switched
bool ready_for_next_page = true;

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
  checkPageSwitch();

  //Get RX input
  getReceiverInput(true);


  /*======================
    Display updating
  ======================*/

  if(millis() > display_lastframe + (1000/DISPLAY_HZ)){

    switch(display_page){
      case 1:
        drawStatusData(display_page);
        break;
      case 2:
        drawAccelerometerData(display_page);
        break;
      case 3:
        drawInputData(display_page);
        break;
      case 4:
        drawOutputData(display_page);
        break;

      //Error handling: reset to page 1
      default:
        display_page = 1;
        break;
    }

    display_lastframe = millis();
  }

}
