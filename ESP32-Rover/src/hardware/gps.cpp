#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Arduino.h>


static const int RXPin = 33, TXPin = 32;
static const uint32_t GPSBaud = 9600;

//TinyGPS++ object
TinyGPSPlus gps;

//Serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

bool gps_fix = false;
uint8_t gps_sats = 0;
double lat;
double lon;

//Set up the BN-180 GPS
void setupGps(){
  ss.begin(GPSBaud);
  Serial.println("Initializing GPS...");
}



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
      //displayInfo();
      lat = gps.location.lat();
      lon = gps.location.lng();
      gps_sats = gps.satellites.value();
      gps_fix = gps.location.isValid();
    }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
  }
}
