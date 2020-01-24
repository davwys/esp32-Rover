#include <Arduino.h>
#include <input.h>
#include <display.h>

void setupButtons(){
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_ENTER, INPUT_PULLUP);
}

void checkPageSwitch(){
  if(ready_for_next_page && digitalRead(BTN_UP) == LOW){
    display_page++;
    ready_for_next_page = false;
  }
  else if(ready_for_next_page && digitalRead(BTN_DOWN) == LOW){
    display_page--;
    ready_for_next_page = false;
  }
  else if(!ready_for_next_page && digitalRead(BTN_DOWN) == HIGH && digitalRead(BTN_UP) == HIGH){
    ready_for_next_page = true;
  }

  //Limit display num to valid pages
  display_page = max(min(display_page, DISPLAY_PAGES), 1);
}
