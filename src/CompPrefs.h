#ifndef SRC_COMPPREFS_H_
#define SRC_COMPPREFS_H_

#define GAMEPAD_PORT 0
#define JOYSTICK1_PORT 1
#define JOYSTICK2_PORT 2
#define JOYSTICKZ_PORT 3

#define WHEEL_DISTANCE 24 // distance in inches pls
#define PULSES_PER_INCH 10 // theo af

#define PDP_PORT 0

// Need to update CAN IDs once we get wiring. They should be correct, theoretically
#define LEFT_DRIVE_TALON_ONE 1
#define LEFT_DRIVE_TALON_TWO 2
#define LEFT_DRIVE_TALON_THREE 3

#define LEFT_LIFTER_TALON 4
#define RIGHT_LIFTER_TALON 5

#define COLLECTOR_ARM_TALON 6

#define LEFT_COLLECTOR_TALON 7
#define RIGHT_COLLECTOR_TALON 8

#define RIGHT_DRIVE_TALON_ONE 9
#define RIGHT_DRIVE_TALON_TWO 10
#define RIGHT_DRIVE_TALON_THREE 11

#define PCM_PORT 12

#define LEFT_DRIVE_P 0.05
#define LEFT_DRIVE_I 0.01
#define LEFT_DRIVE_D 0
#define LEFT_DRIVE_F 0

#define RIGHT_DRIVE_P 0.05
#define RIGHT_DRIVE_I 0.01
#define RIGHT_DRIVE_D 0
#define RIGHT_DRIVE_F 0

#define POTENTIOMETER_PORT 0
#define REST_POS 762
#define LOWER_ANGLE 744
#define SALUTE 591
#define UPPER_ANGLE 424
#define UPPER_STOP 285

#define ARM_P 0.05
#define ARM_I 0.0001
#define ARM_D 0
#define ARM_F 0

#define SOL_PORT_ZRO 0 // PCM Port ID
#define SOL_PORT_ONE 1
#define SOL_PORT_TWO 2
#define SOL_PORT_THR 3
#define SOL_PORT_FOU 4
#define SOL_PORT_FIV 5
#define SOL_PORT_SIX 6
#define SOL_PORT_SEV 7

#define LEFT_AGGRO 0.6 // used to change how aggressive drive straight correction is on both sides.
#define RIGHT_AGGRO 0.6

#define BAUD_RATE_ARDUINO 9600
#define DATA_BITS_ARDUINO 8

#endif /* SRC_COMPPREFS_H_ */
