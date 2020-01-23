#include <Arduino.h>

#include <sensors.h>
#include <display.h>



#define BUTTON_A 19
#define BUTTON_B 18


/*

MAIN

*/


void setup() {

  /*======================
    Communication Setup
  ======================*/

  Serial.begin(57600);

  /*======================
    Display Setup (optional)
  ======================*/

  setupDisplay();

  /*======================
    Sensor Setup
  ======================*/

  setupAccelerometer(false);

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
