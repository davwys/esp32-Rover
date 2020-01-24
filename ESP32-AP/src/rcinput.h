#include <SBUS.h>

//Receiver values
extern bool failsafe;
extern bool rx_failsafe;
extern SBUS receiver;
extern uint8_t rssi;
extern float channels[16];
extern uint32_t lostframes;


//Setup function
void setupReceiver();

void getReceiverInput(bool verbose);
