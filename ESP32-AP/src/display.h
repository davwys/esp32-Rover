#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;
extern int DISPLAY_PAGES;

void setupDisplay();
void drawAccelerometerData();
void drawOutputData();
