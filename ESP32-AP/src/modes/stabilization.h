#include <Arduino.h>

#ifndef STABILIZATION_H
#define STABILIZATION_H

//Maximum angles during normal flight
#define PITCH_MAX 35
#define ROLL_MAX 45
#define YAW_MAX 25

//Maximum angles during auto flight
#define PITCH_MAX_AUTO 25
#define ROLL_MAX_AUTO 30
#define YAW_MAX_AUTO 25

void setupStabilization();
void stabilize(bool stabilize_yaw);

#endif
