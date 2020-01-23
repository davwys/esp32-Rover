#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <sensors.h>



Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);


#define BUTTON_A 19
#define BUTTON_B 18


/*

MAIN

*/


void setup() {
  //Initiate serial comms
  Serial.begin(57600);


  // DISPLAY SETUP

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.println("OLED begun");
  display.display();
  delay(2000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  /*======================
      Sensor Setup
  ======================*/

  //Initialise accelerometer
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }
  //Set accelerometer range
  accel.setRange(ADXL345_RANGE_8_G);

  //Print sensor info
  displaySensorDetails();
  displayDataRate();
  displayRange();
  Serial.println("");


  /*======================
      IO Setup
  ======================*/

  Serial.println("IO test");

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);

  // text display tests
  /*
  display.print("Connecting to SSID\n'adafruit':");
  display.print("connected!");
  display.println("IP: 10.0.1.23");
  display.println("Sending val #0");
  display.setCursor(0,0);
  display.display(); // actually display all of the above
  */
}

void loop() {

  /*
  if(!digitalRead(BUTTON_A)) display.print("A");
  if(!digitalRead(BUTTON_B)) display.print("B");
  delay(10);
  */

  getAccelerometerData();

  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Roll:");
  display.print(roll);
  display.println(" deg");
  display.print("Pitch:");
  display.print(pitch);
  display.println(" deg");
  display.print("Yaw:");
  display.print(yaw);
  display.println(" deg");
  display.println();
  yield();
  display.display();

  delay(50);
}
