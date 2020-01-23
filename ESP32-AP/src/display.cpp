#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

#include <display.h>
#include <sensors.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

//Setup the SSD1306 display
void setupDisplay(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.println("Display initiated...");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}


//Visualize accelerometer values
void drawAccelerometerData(){
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

    int x = 1;
    int y = 26;
    int w = 38;
    int h = 38;

    //Visualize angle: Draw artificial horizon with 45deg limits

    display.drawRect(x,y,w,h, SSD1306_WHITE);

    //Calculate line angle
    int x0 = x + 2;
    int y0 = (y + h/2) + (roll/45) * h/2 + (pitch/45) * h/2;
    int x1 = x + w - 3;
    int y1 = (y+h/2) - (roll/45) * h/2 + (pitch/45) * h/2;

    y0 = min(max(y0, y+2), y+h-2);
    y1 = min(max(y1, y+2), y+h-2);
    display.drawLine(x0, y0, x1, y1, SSD1306_WHITE);

    display.drawLine(x+w+2, y, 128, y, SSD1306_WHITE);

    display.setCursor(x+w+2,y + 2);
    display.println("Press X to set");
    display.setCursor(x+w+2,display.getCursorY());
    display.println("lvl to current");

    display.drawLine(x+w+2, y+18, 128, y+18, SSD1306_WHITE);

    display.display();
}


/* TEST STUFF

  // text display tests
  display.print("Connecting to SSID\n'adafruit':");
  display.print("connected!");
  display.println("IP: 10.0.1.23");
  display.println("Sending val #0");
  display.setCursor(0,0);
  display.display(); // actually display all of the above
*/
