#include <Arduino.h>

#include <modes/modes.h>
#include <input/rcinput.h>
#include <output/servos.h>
#include <modes/stabilization.h>


//Flight mode class
FlightMode::FlightMode(int i, String n, bool stab, bool thr, bool gps, bool alt)
{
  id = i;
  name = n;
  stabilize = stab;
  autoThrottle = thr;
  useGPS = gps;
  autoAltitude = alt;
};

FlightMode MANUAL =     FlightMode(1,"Manual",false, false, false, false);
FlightMode STABILIZE =  FlightMode(2,"Stabilize",true, false, false, false);
FlightMode HOLD =       FlightMode(3,"Hold",true, false, true, true);
FlightMode RTH =        FlightMode(4,"RTH",true, true, true, true);
FlightMode CIRCLE =     FlightMode(5,"Circle",true, true, false, true); //TODO possibly use GPS?

//How many flight modes there are
int numModes = 5;
//Array of Flight modes (for getting via ID)
FlightMode MODES[5] = {MANUAL, STABILIZE, STABILIZE, STABILIZE, CIRCLE};


//Flight mode settings
FlightMode currentMode = STABILIZE; //TODO change


//Checks for mode change input & applies it
void check_mode_change(){
  float mode_input = (channels[CHANNEL_MODE] + 1)/2; //Scale channel input from 0 to 1
  int incr = 100/numModes;

  int newMode = div(int(mode_input*100), incr).quot; //Map value to mode

  if(currentMode.id != newMode){
    currentMode = MODES[newMode];
  }
}



//Manual mode: forwards RC input
void manual_main(){

  uint16_t diff = SERVO_MAX-SERVO_MIN;

  //Forward all RC inputs
  ail_out = SERVO_MID + channels[CHANNEL_AIL] * (diff/2);
  ele_out = SERVO_MID + channels[CHANNEL_ELE] * (diff/2);
  thr_out = SERVO_MID + channels[CHANNEL_THR] * (diff/2);
  rud_out = SERVO_MID + channels[CHANNEL_RUD] * (diff/2);

  updateServos();
}

//Stabilize mode: stabilizes with RC input
void stabilize_main(){

  uint16_t diff = SERVO_MAX-SERVO_MIN;

  stabilize(false);
  //Forward all RC inputs
  /*
  ail_out = SERVO_MID + channels[CHANNEL_AIL] * (diff/2);
  ele_out = SERVO_MID + channels[CHANNEL_ELE] * (diff/2);
  thr_out = SERVO_MID + channels[CHANNEL_THR] * (diff/2);
  rud_out = SERVO_MID + channels[CHANNEL_RUD] * (diff/2);
  */
  updateServos();
}
