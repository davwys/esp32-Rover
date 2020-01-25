/*======================
  Pin definitions
======================*/

#ifndef INPUT_H
#define INPUT_H

#define BTN_UP 18
#define BTN_DOWN 19
#define BTN_ENTER 4

extern bool ready_for_next_page;
extern int display_page;

void setupButtons();

void checkPageSwitch();

#endif
