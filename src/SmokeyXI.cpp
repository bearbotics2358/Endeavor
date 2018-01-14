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

a_Joystick(JOYSTICK_PORT), // this should be the gamepad - list on port 1

a_leftDriveOne(LEFT_DRIVE_TALON_ONE),
a_leftDriveTwo(LEFT_DRIVE_TALON_TWO),
a_leftDriveThree(LEFT_DRIVE_TALON_THREE),

a_rightDriveOne(RIGHT_DRIVE_TALON_ONE),
a_rightDriveTwo(RIGHT_DRIVE_TALON_TWO),
a_rightDriveThree(RIGHT_DRIVE_TALON_THREE),

a_leftDrive(a_leftDriveOne, a_leftDriveTwo, a_leftDriveThree),
a_rightDrive(a_rightDriveOne, a_rightDriveTwo, a_rightDriveThree),
a_Drivetrain(a_leftDrive, a_rightDrive),

a_Collector(LEFT_COLLECTOR_TALON, RIGHT_COLLECTOR_TALON)


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
}

void SmokeyXI::TeleopPeriodic()
{
	a_Drivetrain.ArcadeDrive(a_Joystick.GetRawAxis(0), a_Joystick.GetRawAxis(1));
	a_Collector.Update(a_Joystick.GetRawButton(0));
}

void SmokeyXI::TestInit()
{

}

void SmokeyXI::TestPeriodic()
{

}

START_ROBOT_CLASS(SmokeyXI);
