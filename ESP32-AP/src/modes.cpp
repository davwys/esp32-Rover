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
