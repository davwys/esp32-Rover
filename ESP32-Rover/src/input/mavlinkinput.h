#include <Arduino.h>
#include <BluetoothSerial.h>

#ifndef MAVLINKINPUT_H
#define MAVLINKINPUT_H

extern BluetoothSerial BTSerial;

void comm_receive();

#endif
