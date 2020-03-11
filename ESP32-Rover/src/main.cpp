#include <Arduino.h>
#include <Wire.h>
#include <BluetoothSerial.h>

#include <hardware/accelerometer.h>
#include <hardware/gps.h>
#include <output/servos.h>
#include <output/telemetry.h>
#include <hardware/display.h>
#include <input/input.h>
#include <input/rcinput.h>
#include <modes/modes.h>
#include <config.h>

//Display settings
int display_page = 1;
unsigned long display_lastframe = 0.0; //time in ms when last frame was drawn
bool ready_for_next_page = true; //Whether page can be switched

BluetoothSerial BTSerial;

//Initial setup function
void setup() {

  /*======================
    Communication Setup
  ======================*/

  BTSerial.begin("Rover_MAVLink");
  Serial.begin(57600);
  Wire.begin();

  /*======================
    Sensor Setup
  ======================*/

  setupAccelerometer();
  setupGps();

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
    Servo Setup
  ======================*/

  setupServos();

  /*======================
    LED Setup
  ======================*/

}

//Main Loop function
void loop() {

  //Get sensor data
  getAccelerometerData();
  getGpsData();

  //Check for screen change
  checkPageSwitch();

  //Get RX input
  getReceiverInput(false);

  if(!rx_connected){
    //Check RX status
    checkReceiverConnection();
  }

  //Telemetry
  #ifdef TELEMETRY_ENABLED
    sendTelemetry();
  #endif

  /*======================
    Mode logic
  ======================*/

  if(rx_connected && !rx_failsafe){
    check_mode_change();
  }

  switch(currentMode.id){
    case 1: //Manual
      manual_main();
      break;
      /*
    case 2: //Course hold
      course_main();
      break;*/
  }

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
