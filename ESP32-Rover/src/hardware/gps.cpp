#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Arduino.h>


static const int RXPin = 33, TXPin = 32;
static const uint32_t GPSBaud = 9600;

//TinyGPS++ object
TinyGPSPlus gps;

//Serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

//GPS values
bool gps_fix = false;
bool gps_connected = false; //whether the GPS is actually connected
uint8_t gps_sats = 0;
double gps_hdop = 0.0;
double gps_alt = 0.0;
double gps_course = 0.0;
double gps_speed = 0.0;

double lat;
double lon;


//Set up the BN-220 GPS
void setupGps(){
  ss.begin(GPSBaud);
  Serial.println("Initializing GPS...");
}


//Print GPS info to serial
void displayInfo()
{
  Serial.print("Sats:");
  Serial.print(gps.satellites.value());
  Serial.print('  ');
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}


//Get current GPS data
void getGpsData(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read())){
      gps_connected = true;
      gps_fix = gps.location.isValid();

      if(gps.location.isValid()){

        //Location
        lat = gps.location.lat();
        lon = gps.location.lng();

        //Satellites
        gps_sats = gps.satellites.value();

        //HDOP
        gps_hdop = gps.hdop.hdop();

        //GPS Altitude
        if(gps.altitude.isValid())
          gps_alt = gps.altitude.meters();

        //GPS course
        if(gps.course.isValid())
          gps_course = gps.course.deg();
        //GPS speed (m/s)
        if(gps.speed.isValid())
          gps_speed = gps.speed.mps();
      }
    }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    gps_connected = false;
    Serial.println(F("No GPS detected: check wiring."));
  }
}
