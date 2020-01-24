#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

#include <display.h>
#include <sensors.h>
#include <input.h>
#include <rcinput.h>

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

Adafruit_SSD1306 display = Adafruit_SSD1306(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire);

//Number of possible display pages
int DISPLAY_PAGES = 3;

/*======================
  Display setup functions
======================*/

void setupDisplay(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.println("Display initiated...");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}


/*======================
  Helper functions
======================*/

//Draw page number
void drawPageNumber(int num){
      display.setCursor(DISPLAY_WIDTH - 30,0);
      display.print("(");
      display.print(num);
      display.print("/");
      display.print(DISPLAY_PAGES);
      display.print(")");
}


/*======================
  Main display page functions
======================*/

//Page 1: accelerometer values
void drawAccelerometerData(){
    display.clearDisplay();

    //Page number
    drawPageNumber(1);

    display.setTextSize(1);
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

    //Leveling info

    display.drawLine(x+w+2, y, 128, y, SSD1306_WHITE);
    display.setCursor(x+w+2,y + 2);
    display.println("Press Enter");
    display.setCursor(x+w+2,display.getCursorY());
    display.println("to set level");
    display.drawLine(x+w+2, y+18, 128, y+18, SSD1306_WHITE);

    //Offsets
    display.setCursor(x+w+2,display.getCursorY() + 3);
    display.print("P:");
    display.print(offset_pitch, 1);
    display.print(" R:");
    display.println(offset_roll, 1);
    display.setCursor(x+w+2,display.getCursorY());
    display.print("Y:");
    display.println(offset_yaw, 1);

    display.display();

    //Check for input to level accelerometer
    if(digitalRead(BTN_ENTER) == LOW){
      calibrateAccelerometerLevel();
    }
}

//Page 2: input values
void drawInputData(){
  display.clearDisplay();

  drawPageNumber(2);

  display.setCursor(0,0);
  display.println("Inputs");
  display.drawLine(0, 10, 80, 10, SSD1306_WHITE);

  //Draw all channel values
  for(int i = 0; i < 16; i++){

    //6 channels per column
    uint8_t col = div(i,6).quot;
    if(div(i,6).rem == 0)
      display.setCursor(42 * col, 14);
    else
      display.setCursor(42 * col, display.getCursorY());

    display.print("C");
    display.print(i+1);
    display.print(":");
    display.println(channels[i], 1);
  }

  display.display();
}

//Page 3: output values
void drawOutputData(){
  display.clearDisplay();

  drawPageNumber(3);
  display.display();
}
