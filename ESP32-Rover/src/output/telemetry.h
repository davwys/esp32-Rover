#include <Arduino.h>
#include <BluetoothSerial.h>

#ifndef TELEMETRY_H
#define TELEMETRY_H

//Bluetooth
extern BluetoothSerial BTSerial;

//Basic UAV Parameters
extern uint8_t system_id;
extern uint8_t component_id;
extern uint8_t system_type;
extern uint8_t autopilot_type;
extern uint8_t system_mode;
extern uint32_t custom_mode;
extern uint8_t system_state;

// Flight parameters
extern int16_t heading;
extern float alt;
extern float groundspeed;
extern float airspeed;
extern float climbrate; //currently not working
extern float throttle_val;

// GPS parameters
extern uint8_t fixType;

// Battery parameters
extern float battery_remaining;
extern float voltage_battery;
extern float current_battery;

void sendTelemetry();

#endif
