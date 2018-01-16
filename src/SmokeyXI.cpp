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

a_Arduino(BAUD_RATE, SerialPort::kOnboard, DATA_BITS,  SerialPort::kParity_None, SerialPort::kStopBits_One)


{
	SmartDashboard::init();

}

void SmokeyXI::RobotInit()
{

}

void SmokeyXI::RobotPeriodic()
{

}

void SmokeyXI::DisabledInit()
{

}

void SmokeyXI::DisabledPeriodic()
{
	SmartDashboard::PutString("Enabled: ", "False");
}

void SmokeyXI::AutonomousInit()
{}

void SmokeyXI::AutonomousPeriodic()
{}

void SmokeyXI::TeleopInit()
{
	SmartDashboard::PutString("Enabled: ", "True");
	a_DiffDrive.SetDriveType(0); // Change the number to change drivetypes. Refer to diffdrive.cpp for help.
	a_Arduino.Write("B",1);
}


void SmokeyXI::TeleopPeriodic()
{
	a_DiffDrive.Update(a_GamePad, a_Joystick1, a_Joystick2, a_JoystickZ); // wonder passing four sticks impacts latency
	a_Collector.Update(a_JoystickZ.GetRawButton(0));
}

void SmokeyXI::TestInit()
{

}

void SmokeyXI::TestPeriodic()
{

}

START_ROBOT_CLASS(SmokeyXI);
