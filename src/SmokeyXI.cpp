#include <Prefs.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <string>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <SmokeyXI.h>

SmokeyXI::SmokeyXI(void):

a_GamePad(GAMEPAD_PORT), // this should be the gamepad - list on port 0

a_Joystick1(JOYSTICK1_PORT), // this is the flightstick without a z axis, port 1

a_Joystick2(JOYSTICK2_PORT), // this is the flightstick without a z axis, port 2

a_JoystickZ(JOYSTICKZ_PORT), // this is the flightstick WITH a z axis, port 3

a_DiffDrive(LEFT_DRIVE_TALON_ONE, LEFT_DRIVE_TALON_TWO, LEFT_DRIVE_TALON_THREE, RIGHT_DRIVE_TALON_ONE, RIGHT_DRIVE_TALON_TWO, RIGHT_DRIVE_TALON_THREE),

a_Collector(LEFT_COLLECTOR_TALON, RIGHT_COLLECTOR_TALON),

a_CollectorArm(COLLECTOR_ARM_TALON),

a_Gyro(I2C::kMXP),

a_Arduino(BAUD_RATE, SerialPort::kUSB1, DATA_BITS,  SerialPort::kParity_None, SerialPort::kStopBits_One),

a_Solenoid(PCM_PORT, SOL_PORT_ONE, SOL_PORT_TWO)

// USB1 is the onboard port closest to the center of the rio
// It also??? what was i writing??????


{
	SmartDashboard::init();
}

void SmokeyXI::RobotInit()
{
	a_Gyro.Cal();
}

void SmokeyXI::RobotPeriodic()
{

}

void SmokeyXI::DisabledInit()
{
	a_Arduino.Write("E", 1);
}

void SmokeyXI::DisabledPeriodic()
{
	SmartDashboard::PutString("Enabled: ", "False");
}

void SmokeyXI::AutonomousInit()
{
	a_Arduino.Write("F", 1);
}

void SmokeyXI::AutonomousPeriodic()
{

}

void SmokeyXI::TeleopInit()
{
	SmartDashboard::PutString("Enabled: ", "True");
	a_DiffDrive.SetDriveType(0); // Change the number to change drivetypes. Refer to diffdrive.cpp for help.
	a_Arduino.Write("B", 1);

	a_Gyro.Cal();
}


void SmokeyXI::TeleopPeriodic()
{
	a_Gyro.Update();
	float gyroValue = a_Gyro.GetAngle();
	SmartDashboard::PutNumber("Gyro Angle: ", gyroValue);
	SmartDashboard::PutNumber("Gyro X", a_Gyro.GetX());
	SmartDashboard::PutNumber("Gyro Y", a_Gyro.GetY());
	SmartDashboard::PutNumber("Gyro Z", a_Gyro.GetZ());



	if (a_GamePad.GetRawButton(1)){
		a_Solenoid.Set(DoubleSolenoid::kForward);
	}
	if (a_GamePad.GetRawButton(2)){
		a_Solenoid.Set(DoubleSolenoid::kReverse);
	}
	a_DiffDrive.Update(a_GamePad, a_Joystick1, a_Joystick2, a_JoystickZ); // wonder passing four sticks impacts latency
	a_Collector.Update(a_GamePad.GetRawButton(5)); // apparently buttons aren't zero indexed, but axes are???
}

void SmokeyXI::TestInit()
{
	a_Arduino.Write("R", 1);
}

void SmokeyXI::TestPeriodic()
{

}

START_ROBOT_CLASS(SmokeyXI);
