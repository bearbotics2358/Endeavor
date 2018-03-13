#ifndef SRC_PRACTICEPREFS_H_
#define SRC_PRACTICEPREFS_H_

#define GAMEPAD_PORT 0
#define JOYSTICK1_PORT 1
#define JOYSTICK2_PORT 2
#define BUTTONBOX_PORT 3

#define WHEEL_DISTANCE 24 // distance in inches pls

#define TICKS_PER_INCH_HIGH_GEAR 35.918
#define TICKS_PER_INCH_LOW_GEAR 90.992

#define PDP_PORT 0

// CAN IDs are correct.
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

#define REST_POS 0.0
#define LOWER_ANGLE 0
#define SALUTE 0
#define UPPER_ANGLE 0
#define UPPER_STOP 237.0

#define ARM_P 10
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

#define LEFT_AGGRO 1.0 // used to change how aggressive drive straight correction is on both sides.
#define RIGHT_AGGRO 1.0

#define BAUD_RATE_ARDUINO 9600
#define USB_PORT_ARDUINO SerialPort::kUSB2
#define DATA_BITS_ARDUINO 8
#define PARITY_ARDUINO SerialPort::kParity_None
#define STOP_BITS_ARDUINO SerialPort::kStopBits_One

#define BAUD_RATE_SOUL 38400
#define USB_PORT_SOUL SerialPort::kUSB1
#define DATA_BITS_SOUL 8
#define PARITY_SOUL SerialPort::kParity_None
#define STOP_BITS_SOUL SerialPort::kStopBits_One

// distance between ultrasonic sensors
// NOTE: these values are floats - include a decimal point to guarantee code won't have to cast on divides
#define FRONT_CENTER_DISTANCE 6.0
#define REAR_CENTER_DISTANCE 20.0

#define IR_RECEIVER_PORT 0

#define LIGHT_RING_CONTROLLER_ADDRESS 0x4

#endif /* SRC_PRACTICEPREFS_H_ */
