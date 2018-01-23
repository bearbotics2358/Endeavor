#ifndef SRC_PREFS_H_
#define SRC_PREFS_H_

#define GAMEPAD_PORT 0
#define JOYSTICK1_PORT 1
#define JOYSTICK2_PORT 2
#define JOYSTICKZ_PORT 3

#define WHEEL_DISTANCE 24 // distance in inches pls

// Need to update CAN IDs once we get wiring. They should be correct, theoretically
#define LEFT_DRIVE_TALON_ONE 1
#define LEFT_DRIVE_TALON_TWO 2
#define LEFT_DRIVE_TALON_THREE 3

#define RIGHT_DRIVE_TALON_ONE 8
#define RIGHT_DRIVE_TALON_TWO 9
#define RIGHT_DRIVE_TALON_THREE 10

#define LEFT_COLLECTOR_TALON 6
#define RIGHT_COLLECTOR_TALON 7

#define COLLECTOR_ARM_TALON 5

#define PCM_PORT 12

#define SOL_PORT_ONE 0 // PCM Port ID
#define SOL_PORT_TWO 1

#define BAUD_RATE_ARDUINO 9600
#define DATA_BITS 8

#endif /* SRC_PREFS_H_ */
