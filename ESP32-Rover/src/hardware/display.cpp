#include <SPI.h>
#include <Wire.h>

#include <hardware/display.h>
#include <hardware/accelerometer.h>
#include <hardware/gps.h>

#include <input/input.h>
#include <input/rcinput.h>
#include <input/mavlinkinput.h>

#include <output/servos.h>
#include <modes/modes.h>

#include <config.h>

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

Adafruit_SSD1306 display = Adafruit_SSD1306(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire);

//Number of possible display pages
int DISPLAY_PAGES = 5;

/*======================
  Display setup functions
======================*/

void setupDisplay(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  #ifdef DEBUG_ENABLED
    Serial.println("Display initiated...");
  #endif
  display.display();
  delay(600);
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

//Page: general status
void drawStatusData(int page){
  display.clearDisplay();

  //Page number
  drawPageNumber(page);

  //Title
  display.setCursor(0,0);
  display.println("Status");
  display.drawLine(0, 10, 80, 10, SSD1306_WHITE);

  display.setCursor(0,14);
  display.print("Mode: ");
  display.println(currentMode.name);
  display.print("Gyro: ");
  display.println(accel.getDeviceID() != NULL ? "OK":"ERROR");
  display.print("GPS : ");
  display.print(gps_connected ? gps_fix? "3D Fix": "No fix" : "ERROR");
  display.println(gps_connected? ", " + String(gps_sats) + " sats" : "");
  display.print("RX  : ");
  display.println(mavlink_rc_connected ? "MAVLink": rx_connected ? (rx_failsafe? "In Failsafe":"Connected"):"ERROR");
  display.print("Volt: ");
  display.print(analogRead(35)/4096.0*7.445, 1); //Input voltage calculation
  display.println("V");

  display.display();
};

//Page: general status
void drawConfigData(int page){
  display.clearDisplay();

  //Page number
  drawPageNumber(page);

  //Title
  display.setCursor(0,0);
  display.println("Configuration");
  display.drawLine(0, 10, 80, 10, SSD1306_WHITE);

  display.setCursor(0,14);
  display.print("Telemetry: ");
  #ifdef TELEMETRY_ENABLED
    #ifdef BLUETOOTH_TELEMETRY
      display.println("USB & BT");
    #else
      display.println("USB");
    #endif
  #else
    display.println("Disabled");
  #endif

  display.print("Debug: ");
  #ifdef DEBUG_ENABLED
    display.println("Enabled");
  #else
    display.println("Disabled");
  #endif



  display.display();
};

//Page: accelerometer values
void drawAccelerometerData(int page){
    display.clearDisplay();

    //Page number
    drawPageNumber(page);

    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Roll : ");
    display.print(roll,1);
    display.println("deg");
    display.print("Pitch: ");
    display.print(pitch,1);
    display.println("deg");
    display.print("Yaw  : ");
    display.print(yaw,1);
    display.println("deg");
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

//Page: input values
void drawInputData(int page){

  display.clearDisplay();

  drawPageNumber(page);

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

//Page: output values
void drawOutputData(int page){
  display.clearDisplay();

  drawPageNumber(page);

  display.setCursor(0,0);
  display.println("Outputs");
  display.drawLine(0, 10, 80, 10, SSD1306_WHITE);

  display.setCursor(0,14);
  //Draw all output values
  display.print("Steer: ");
  display.print(steer_out);
  display.println("us");
  display.print("Thr  : ");
  display.print(thr_out);
  display.println("us");
  display.print("Aux1 : ");
  display.print(aux1_out);
  display.println("us");
  display.print("Aux2 : ");
  display.print(aux2_out);
  display.println("us");

  display.drawLine(0, display.getCursorY() + 1, 80, display.getCursorY() + 1, SSD1306_WHITE);

  display.setCursor(0,display.getCursorY() + 3);
  display.print("Rate: ");
  display.print(SERVO_HZ);
  display.println("hz");

  display.print("Min/max: ");
  display.print(SERVO_MIN);
  display.print("/");
  display.print(SERVO_MAX);
  display.println("us");

  display.display();
}
