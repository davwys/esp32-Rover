#include <ASLUAV/mavlink.h>
#include <Arduino.h>
#include <BluetoothSerial.h>

#include <input/mavlinkinput.h>
#include <input/rcinput.h>

/************************************************************
* @brief Read MAVLink input on Serial
* @param none
* @return void
*************************************************************/


void comm_receive() {
  mavlink_message_t msg;
  mavlink_status_t status;

  //TODO other sources e.g. bluetooth
  while(Serial.available()>0) {
    uint8_t c = Serial.read();

    // Try to get a new message
    if(mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {

/*
      Serial.println("Got mavlink msg!");
      Serial.print("ID: ");
      Serial.println(msg.msgid);
*/
      // Handle message
      switch(msg.msgid) {
        case MAVLINK_MSG_ID_HEARTBEAT:  // #0: Heartbeat
          {
            // E.g. read GCS heartbeat and go into
            // comm lost mode if timer times out
          }
          break;

        case MAVLINK_MSG_ID_MANUAL_CONTROL:  // #69
          {
            /* Message decoding: PRIMITIVE
             *    mavlink_msg_attitude_decode(const mavlink_message_t* msg, mavlink_attitude_t* attitude)
             */
            mavlink_manual_control_t rcchannels;
            mavlink_msg_manual_control_decode(&msg, &rcchannels);

            //Apply scaled channels as input
            //channels[0] = rcchannels.y / 1000.0; --> right stick, not setup atm

            channels[0] = rcchannels.x / 1000.0;

            //Throttle
            channels[1] = rcchannels.z / 1000.0;

          }
          break;


       default:
          break;
      }
    }
  }
}
