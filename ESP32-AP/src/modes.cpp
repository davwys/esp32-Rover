#include <Arduino.h>

#include <modes.h>


//Flight mode class
FlightMode::FlightMode(int i, String n, bool stab, bool thr, bool gps, bool alt)
{
  id = i;
  name = n;
  stabilize = stab;
  autoThrottle = thr;
  useGPS = gps;
  autoAltitude = alt;
};

FlightMode MANUAL =     FlightMode(1,"Manual",false, false, false, false);
FlightMode STABILIZE =  FlightMode(2,"Stabilize",true, false, false, false);
FlightMode HOLD =       FlightMode(3,"Hold",true, false, true, true);
FlightMode RTH =        FlightMode(4,"RTH",true, true, true, true);
FlightMode CIRCLE =     FlightMode(5,"Circle",true, true, false, true); //TODO possibly use GPS?

//Flight mode settings
FlightMode currentMode = MANUAL;
