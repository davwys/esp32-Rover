#include <Arduino.h>

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


FlightMode MANUAL =     FlightMode(1,"Manual",false, false, false, false);
FlightMode STABILIZE =  FlightMode(2,"Stabilize",true, false, false, false);
FlightMode HOLD =       FlightMode(3,"Stabilize",true, false, true, true);
FlightMode RTH =        FlightMode(4,"RTH",true, true, true, true);
FlightMode CIRCLE =     FlightMode(5,"Circle",true, true, false, true); //TODO possibly use GPS?
