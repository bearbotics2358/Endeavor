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
#include <NetworkTables/NetworkTable.h>
#include <SmokeyXI.h>

SmokeyXI::SmokeyXI(void):

a_Joystick(JOYSTICK_PORT) // this should be the gamepad - list on port 1

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

}

void SmokeyXI::TestInit()
{

}

void SmokeyXI::TestPeriodic()
{

}

START_ROBOT_CLASS(SmokeyXI);
