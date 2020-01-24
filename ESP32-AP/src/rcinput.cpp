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
SBUS receiver(Serial1); //TODO determine which serial to use --> RX on 9, TX on 10?


void setupReceiver(){
  RCSerial.begin(100000, SERIAL_8N2, 23, 14); //RX pin 23, TX pin 14 (unused)
  receiver.begin();

  delay(500);

  //Check whether RX is connected
  checkReceiverConnection();
}

//Checks for RX connection
void checkReceiverConnection(){
  uint16_t channels_test[16];
  bool failsafe_test;
  bool lostframe_test;
  receiver.read(&channels_test[0], &failsafe_test, &lostframe_test);
  if(!failsafe_test && !lostframe_test && channels_test[0] != 0){
    rx_connected = true;
  }
}

//Gets current RX channel input
void getReceiverInput(bool verbose){
  if(receiver.readCal(&channels[0], &rx_failsafe, &lostframe)){ //TODO check if all channels are read correctly
    //Print all RX inputs (if in verbose mode)
    if(verbose){
       for(int i = 0; i < 16; i++){
         Serial.print("Ch");
         Serial.print(i);
         Serial.print(": ");
         Serial.println(channels[i]);
       }
       Serial.println();
     }
  }

  //If frame was lost, increase counter
  if(lostframe){
    lostframes++;
    if(verbose) Serial.println("Frame lost!");
  }
}
