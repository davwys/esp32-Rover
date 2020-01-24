#include <SBUS.h>
#include <HardwareSerial.h>

#include <rcinput.h>

bool rx_connected = false; //whether the RX was detected
bool rx_failsafe = false; //whether the RX is currently in failsafe
bool failsafe = false; //whether the AP is currently in failsafe
bool lostframe = false; //whether the current frame was lost
uint8_t rssi = 0;         //RX RSSI, from 0-100
float channels[16];    //RX channels 1-16
uint32_t lostframes = 0;

HardwareSerial RCSerial(1);

//RX object
SBUS receiver(RCSerial); //TODO determine which serial to use --> RX on 9, TX on 10?


void setupReceiver(){
  RCSerial.begin(100000, SERIAL_8N2, 23, 14); //RX pin 23, TX pin 14 (unused)
  //Serial.print("RX available: ");
  //Serial.println(RCSerial.available());
  receiver.begin();

  delay(500);

  //Check whether RX is connected
  checkReceiverConnection();
}


//Check for RX connection status
void checkReceiverConnection(){
  uint16_t channels_test[16];
  bool failsafe_test = true;
  bool lostframe_test = true;
  receiver.read(&channels_test[0], &failsafe_test, &lostframe_test);
  Serial.println(failsafe_test);

  if(!failsafe_test){
    rx_connected = true;
  }
  else{
    rx_connected = false;
  }
}

//Gets current RX channel input
void getReceiverInput(bool verbose){
  if(receiver.readCal(&channels[0], &rx_failsafe, &lostframe)){ //TODO check if all channels are read correctly
    //Print all RX inputs (if in verbose mode)
    if(verbose){
       for(int i = 0; i < 16; i++){
         Serial.print("Ch");
         Serial.print(i+1);
         Serial.print(": ");
         Serial.println(channels[i]);
       }
       Serial.println();
     }
  }
  /*else if(verbose){
    Serial.println("RX not connected!");
  }*/

  //If frame was lost, increase counter
  if(lostframe){
    lostframes++;
    if(verbose) Serial.println("Frame lost!");
  }
}
