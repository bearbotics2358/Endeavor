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

a_Arduino(BAUD_RATE_ARDUINO, SerialPort::kUSB1, DATA_BITS,  SerialPort::kParity_None, SerialPort::kStopBits_One), // USB1 is the onboard port closest to the center of the rio

a_Solenoid(PCM_PORT, SOL_PORT_ONE, SOL_PORT_TWO),

a_AutoBot(), // AutoBot Methods return true for left.

a_UltraSoul()

{

}

void SmokeyXI::RobotInit()
{
	SmartDashboard::init();
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
	SmartDashboard::PutString("Enabled: ", "True");
	a_Arduino.Write("N", 1); // strips off
}

void SmokeyXI::AutonomousPeriodic()
{
	// Following lines are to test AutoPeriodic and the AutoBot autohelper i wrote.
	if (a_AutoBot.GetAllianceSwitch()){
		a_Arduino.Write("B", 1); // Left side, Blue leds for indicators
		SmartDashboard::PutBoolean("Our Switch Left? ", true);
	}
	else{
		a_Arduino.Write("M", 1); // Right side, Red leds for indicators
		SmartDashboard::PutBoolean("Our Switch Left? ", false);
	}
	if (a_AutoBot.GetAllianceScale()){
		SmartDashboard::PutBoolean("Scale Left? ", true);
	}
	else{
		SmartDashboard::PutBoolean("Scale Left? ", false);
	}
	if (a_AutoBot.GetOpponentSwitch()){
		SmartDashboard::PutBoolean("Opp Switch Left?", true);
	}
	else{
		SmartDashboard::PutBoolean("Opp Switch Left?", true);
	}

}

void SmokeyXI::TeleopInit()
{
	SmartDashboard::PutString("Enabled: ", "True");
	a_DiffDrive.Init();
	a_DiffDrive.SetDriveType(2); // Change the number to change drivetypes. Refer to diffdrive.cpp for help.
	a_Gyro.Init();
	a_Arduino.Write("B", 1);
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
	if (a_GamePad.GetRawButton(3)){
		a_DiffDrive.GoDistance(0.2); // 10 rotations? theo af
	}
	a_DiffDrive.Update(a_GamePad, a_Joystick1, a_Joystick2, a_JoystickZ); // wonder if passing four sticks impacts latency -- if it does, i didnt notice
	// a_Collector.Update(a_GamePad.GetRawButton(5)); // apparently buttons aren't zero indexed, but axes are???
}

void SmokeyXI::TestInit()
{
	a_Arduino.Write("R", 1);
}

void SmokeyXI::TestPeriodic()
{

}

START_ROBOT_CLASS(SmokeyXI);
