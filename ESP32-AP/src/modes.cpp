#include <Arduino.h>

#include <modes.h>


//Flight mode class
FlightMode::FlightMode(int id, String name, bool stabilize, bool autoThrottle, bool useGPS, bool autoAltitude)
{
  id = id;
  name = name;
  stabilize = stabilize;
  autoThrottle = autoThrottle;
  useGPS = useGPS;
  autoAltitude = autoAltitude;
};



FlightMode MANUAL =     FlightMode(1,"Manual",false, false, false, false);
FlightMode STABILIZE =  FlightMode(2,"Stabilize",true, false, false, false);
FlightMode HOLD =       FlightMode(3,"Stabilize",true, false, true, true);
FlightMode RTH =        FlightMode(4,"RTH",true, true, true, true);
FlightMode CIRCLE =     FlightMode(5,"Circle",true, true, false, true); //TODO possibly use GPS?


//Flight settings
FlightMode currentMode = MANUAL;
