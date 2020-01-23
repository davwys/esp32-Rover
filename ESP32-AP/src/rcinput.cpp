#include <SBUS.h>

#include <rcinput.h>

bool rx_failsafe = false; //whether the RX is currently in failsafe
bool failsafe = false; //whether the AP is currently in failsafe
bool lostframe = false; //whether the current frame was lost
uint8_t rssi = 0;         //RX RSSI, from 0-100
uint16_t channels[16];    //RX channels 1-16
uint32_t lostframes = 0;

//RX object
SBUS receiver(Serial1); //TODO determine which serial to use


void setupReceiver(){
  receiver.begin();
}

void getReceiverInput(bool verbose){
  if(receiver.read(&channels[0], &rx_failsafe, &lostframe)){
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
