#include <Arduino.h>
#include <BluetoothSerial.h>
#include <ASLUAV/mavlink.h>
#include <output/mavlink/commands.h>
#include <input/rcinput.h>
#include <hardware/accelerometer.h>
#include <hardware/gps.h>


// Serial Baud rate
//Default: 57600 baud
#define BAUD_RATE 57600

// Telemetry message rate in Hz
//Default: 10hz
//Maximum: 40hz (depending on what additional processing is being done)
#define TELEMETRY_HZ 10


uint16_t wait = 1000/(TELEMETRY_HZ+4); //reduce wait time to account for other delays

uint64_t lastSent = 0;

// Parameter setup

//Basic UAV Parameters
uint8_t system_id = 1;                              // MAVLink system ID. Leave at 0 unless you need a specific ID.
uint8_t component_id = MAV_COMP_ID_ALL;
uint8_t system_type = MAV_TYPE_GROUND_ROVER;
uint8_t autopilot_type = MAV_AUTOPILOT_GENERIC;     //Generic with all capabilities
uint8_t system_mode = MAV_MODE_MANUAL_ARMED;        //Mode
uint32_t custom_mode = 0;                           // Usually set to 0
uint8_t system_state = MAV_STATE_ACTIVE;

// Flight parameters TODO are these needed?
float alt = 0.0;        // Relative flight altitude in m
float airspeed = 0.0;    // Airspeed in m/s
float climbrate = 0.0;    // Climb rate in m/s, currently not working
float throttle_val= 0.0;     // Throttle percentage

// GPS parameters
// GPS fix type. 0-1: no fix, 2: 2D fix, 3: 3D fix

// Battery parameters
float battery_remaining = 0.0;  // Remaining battery percentage
float voltage_battery = 0.0;    // Battery voltage in V
float current_battery = 0.0;    // Battery current in A



//Sends the current parameters as MAVLink telemetry
void sendTelemetry(){
  //If we should send the next message
  if(millis() > lastSent + wait){

    lastSent = millis();

    //Send MAVLink heartbeat
    command_heartbeat(system_id, component_id, system_type, autopilot_type, system_mode, custom_mode, system_state);

    // Send parameters (needed for detection by some GCS software)
    command_parameters(system_id, component_id);

    //Send battery status
    command_status(system_id, component_id, battery_remaining, voltage_battery, current_battery);

    // Send GPS and altitude data
    command_gps(system_id, component_id, millis(), gps_fix? 3:0, lat, lon, alt, gps_alt, gps_course, gps_speed, gps_hdop, gps_sats);

    // Send HUD data (speed, heading, climbrate etc.)
    command_hud(system_id, component_id, airspeed, gps_speed, gps_course, throttle_val, alt, climbrate);

    // Send attitude data to artificial horizon
    command_attitude(system_id, component_id, millis(), roll, pitch, yaw);
  }
}
