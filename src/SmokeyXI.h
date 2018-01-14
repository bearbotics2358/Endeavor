#ifndef SRC_SMOKEYXI_H_
#define SRC_SMOKEYXI_H_

#include <WPILib.h>
#include <SerialPort.h>
#include <IterativeRobot.h>
#include "SmartDashboard/SmartDashboard.h"
#include "SmartDashboard/SendableChooser.h"
#include "ctre/Phoenix.h"
#include <Collector.h>
#include <DiffDrive.h>

class SmokeyXI : public IterativeRobot {
public:
	SmokeyXI(void);
	void RobotInit(void);
	void RobotPeriodic(void);
	void DisabledInit(void);
	void DisabledPeriodic(void);
	void TeleopInit(void);
	void TeleopPeriodic(void);
	void TestInit(void);
	void TestPeriodic(void);
	void AutonomousInit(void);
	void AutonomousPeriodicFull(void);
	void AutonomousPeriodic(void);
	void AutonomousPeriodicSimple(void);

private:
	Joystick a_Joystick;

	DiffDrive a_DiffDrive; // This is different from Differential Drive in WPILib.

	Collector a_Collector;

	/*
	CANTalon.h is now deprecated, we have to use the new Phoenix framework.
	Apparently it's not a drop in replacement. Great.

	https://github.com/CrossTheRoadElec/Phoenix-Documentation#what-is-new--kickoff
	https://github.com/CrossTheRoadElec/Phoenix-Documentation/blob/master/Migration%20Guide.md
	https://www.chiefdelphi.com/forums/showthread.php?p=1717815

	Really hope this new library actually works.
	If we end up using WPILib's drives, apparently we can cast the new talon object to a speedcontroller object.
	We should test that function out.

	*/
};

#endif
