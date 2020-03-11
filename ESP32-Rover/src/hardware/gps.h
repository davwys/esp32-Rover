#include <TinyGPS++.h>
#include <Arduino.h>


//GPS values
extern bool gps_fix;
extern bool gps_connected; //whether the GPS is actually connected
extern uint8_t gps_sats;
extern double gps_hdop;
extern double gps_alt;
extern double gps_course;
extern double gps_speed;

extern double lat;
extern double lon;

//Setup function
void setupGps();

//Get current GPS information
void getGpsData();
