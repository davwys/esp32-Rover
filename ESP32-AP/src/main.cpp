#include <Arduino.h>

#include <sensors.h>
#include <display.h>
#include <input.h>
#include <rcinput.h>

int display_page = 1;

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
  if(ready_for_next_page && digitalRead(BTN_UP) == LOW){
    display_page++;
    ready_for_next_page = false;
  }
  else if(ready_for_next_page && digitalRead(BTN_DOWN) == LOW){
    display_page--;
    ready_for_next_page = false;
  }
  else if(!ready_for_next_page && digitalRead(BTN_DOWN) == HIGH && digitalRead(BTN_UP) == HIGH){
    ready_for_next_page = true;
  }

  //Limit display num to valid pages
  display_page = max(min(display_page, DISPLAY_PAGES), 1);

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

  //Get RX input
  getReceiverInput(true);

  delay(50);
}
