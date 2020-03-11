#include <Arduino.h>
#include <BluetoothSerial.h>

#ifndef MAVLINKINPUT_H
#define MAVLINKINPUT_H

extern BluetoothSerial BTSerial;
extern bool mavlink_rc_connected;

void comm_receive();

#endif
