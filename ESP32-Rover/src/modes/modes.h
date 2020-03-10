#include <Arduino.h>

#ifndef MODES_H
#define MODES_H



class Mode {
  public:
    int id;
    String name;
    bool autoSteer;
    bool autoThrottle;
    bool useGPS;

    Mode(int id, String name, bool autoSteer, bool autoThrottle, bool useGPS);
};

//Modes
extern Mode MANUAL;
extern Mode COURSE;

//Current mode
extern Mode currentMode;

void check_mode_change();

//Main mode functions
void manual_main();

#endif
