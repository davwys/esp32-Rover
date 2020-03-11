# ESP32-Rover

This is a work-in-progress "autopilot" for RC rovers, using an ESP32 as well as various sensors.
It is UNTESTED in its current state, so proceed with caution. If you're interested in working on this project, let me know.

Current features:
=================

- SSD1306 OLED support for config/status
- (Uninverted) SBUS RC input, incl. failsafe
- Bidirectional MAVLink telemetry
- RC via MAVLink (joystick support in groundstation apps)
- MPU6050 gyro/accelerometer support
- BN220 GPS support
- Direct servo connection

TODOs:
======

- Support for additional sensors (barometer, ultrasonic, etc.)
- Proper hardware design
- much more...
