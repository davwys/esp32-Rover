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

extern FlightMode MANUAL;
extern FlightMode STABILIZE;
extern FlightMode HOLD;
extern FlightMode RTH;
extern FlightMode CIRCLE;

extern FlightMode currentMode;
