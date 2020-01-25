#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifndef DISPLAY_H
#define DISPLAY_H

//Sets the external OLED update framerate
#define DISPLAY_HZ 20

extern Adafruit_SSD1306 display;
extern int DISPLAY_PAGES;

void setupDisplay();
void drawStatusData(int page);
void drawAccelerometerData(int page);
void drawInputData(int page);
void drawOutputData(int page);

#endif
