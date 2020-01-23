#include <Arduino.h>
#include <input.h>

void setupButtons(){
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_ENTER, INPUT_PULLUP);
}
