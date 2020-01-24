#include <SBUS.h>

//Channel definitions
#define CHANNEL_AIL 1
#define CHANNEL_ELE 2
#define CHANNEL_THR 3
#define CHANNEL_RUD 4
#define CHANNEL_MODE 5
#define CHANNEL_GAIN 6


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
