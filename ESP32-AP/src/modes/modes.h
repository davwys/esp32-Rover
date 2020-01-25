#include <Arduino.h>

#ifndef MODES_H
#define MODES_H



class FlightMode {
  public:
    int id;
    String name;
    bool stabilize;
    bool autoThrottle;
    bool useGPS;
    bool autoAltitude;

    FlightMode(int id, String name, bool stabilize, bool autoThrottle, bool useGPS, bool autoAltitude);
};

//Flight modes
extern FlightMode MANUAL;
extern FlightMode STABILIZE;
extern FlightMode HOLD;
extern FlightMode RTH;
extern FlightMode CIRCLE;

//Current mode
extern FlightMode currentMode;

void check_mode_change();

//Main flight mode functions
void manual_main();
void stabilize_main();

#endif
