#include <Arduino.h>

#include <modes/modes.h>

#include <input/rcinput.h>
#include <input/mavlinkinput.h>

#include <output/servos.h>

uint16_t diff = SERVO_MAX-SERVO_MIN;


//Flight mode class
Mode::Mode(int i, String n, bool steer, bool thr, bool gps)
{
  id = i;
  name = n;
  autoSteer = steer;
  autoThrottle = thr;
  useGPS = gps;
};

Mode MANUAL =     Mode(1,"Manual",false, false, false);
Mode COURSE =     Mode(1,"Course Hold",true, false, true);

//How many modes there are
int numModes = 2;
//Array of modes (for getting via ID)
Mode MODES[2] = {MANUAL, COURSE};


//Mode settings
Mode currentMode = MANUAL;


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

  //If RX is not in failsafe
  if(mavlink_rc_connected || (rx_connected && !rx_failsafe)){
    //Forward all RC inputs
    steer_out = SERVO_MID + channels[CHANNEL_STEER] * (diff/2);
    thr_out = SERVO_MID + channels[CHANNEL_THR] * (diff/2);

    updateServos();
  }
}
