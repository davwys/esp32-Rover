#include <SBUS.h>

#ifndef RCINPUT_H
#define RCINPUT_H

//Channel definitions (offset by one due to array positions)
#define CHANNEL_AIL 0
#define CHANNEL_ELE 1
#define CHANNEL_THR 2
#define CHANNEL_RUD 3
#define CHANNEL_MODE 4
#define CHANNEL_GAIN 5

//Receiver values
extern bool rx_connected;
extern bool failsafe;
extern bool rx_failsafe;
extern SBUS receiver;
extern uint8_t rssi;
extern float channels[16];
extern uint32_t lostframes;


//Setup function
void setupReceiver();

//Checks whether RX has been connected
void checkReceiverConnection();

//Get all RX channels as input
void getReceiverInput(bool verbose);

#endif
