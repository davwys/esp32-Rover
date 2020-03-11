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

//Enable (or disable) bluetooth telemetry
#define BLUETOOTH_ENABLED

uint16_t wait = 1000/(TELEMETRY_HZ+4); //reduce wait time to account for other delays

uint64_t lastSent = 0;

// Parameter setup

//Basic UAV Parameters
uint8_t system_id = 1;        // MAVLink system ID. Leave at 0 unless you need a specific ID.
uint8_t component_id = 0;     // Should be left at 0. Set to 190 to simulate mission planner sending a command
uint8_t system_type = 10;      // UAV type. 0 = generic, 1 = fixed wing, 2 = quadcopter, 3 = helicopter, 10=rover
uint8_t autopilot_type = 0;   // Autopilot type. Usually set to 0 for generic autopilot with all capabilities
uint8_t system_mode = 64;     // Flight mode. 4 = auto mode, 8 = guided mode, 16 = stabilize mode, 64 = manual mode
uint32_t custom_mode = 0;     // Usually set to 0
uint8_t system_state = 4;     // 0 = unknown, 3 = standby, 4 = active

// Flight parameters
float alt = 0.0;        // Relative flight altitude in m
float airspeed = 0.0;    // Airspeed in m/s
float climbrate = 0.0;    // Climb rate in m/s, currently not working
float throttle_val= 0.0;     // Throttle percentage

// GPS parameters
uint8_t fixType = 0;      // GPS fix type. 0-1: no fix, 2: 2D fix, 3: 3D fix

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
