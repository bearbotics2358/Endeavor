#ifndef SRC_PREFS_H_
#define SRC_PREFS_H_

#define GAMEPAD_PORT 0
#define JOYSTICK1_PORT 1
#define JOYSTICK2_PORT 2
#define JOYSTICKZ_PORT 3

// Need to update CAN IDs once we get wiring. They should be correct, theoretically
#define LEFT_DRIVE_TALON_ONE 0
#define LEFT_DRIVE_TALON_TWO 1
#define LEFT_DRIVE_TALON_THREE 2

#define RIGHT_DRIVE_TALON_ONE 3
#define RIGHT_DRIVE_TALON_TWO 4
#define RIGHT_DRIVE_TALON_THREE 5

#define LEFT_COLLECTOR_TALON 6
#define RIGHT_COLLECTOR_TALON 7

#define COLLECTOR_ARM_TALON 8

#define BAUD_RATE 9600
#define DATA_BITS 8

#endif /* SRC_PREFS_H_ */
