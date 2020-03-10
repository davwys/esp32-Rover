#include <TinyGPS++.h>
#include <Arduino.h>

extern bool gps_fix;
extern uint8_t gps_sats;
extern double gps_hdop;
extern double gps_alt;
extern double lat;
extern double lon;

void setupGps();

void getGpsData();
