#ifndef SRC_SMOKEYXI_H_
#define SRC_SMOKEYXI_H_

#include <WPILib.h>
#include <SerialPort.h>
#include <IterativeRobot.h>
#include "SmartDashboard/SmartDashboard.h"
#include "SmartDashboard/SendableChooser.h"
#include "ctre/Phoenix.h"
#include <DiffDrive.h>
#include <Collector.h>
#include <CollectorArm.h>
#include <JrimmyGyro.h>
#include <AutonomousHelper.h>
#include <UltrasonicSerial.h>
#include <Lifter.h>
#include <Autonomous.h>

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
	void AutonomousPeriodic(void);
	void AutonomousPeriodicSimple(void);

private:
	// I'm putting all sticks in the code until we determine which one we like to drive with. -AR
	Joystick a_GamePad;
	Joystick a_Joystick1;
	Joystick a_Joystick2;
	Joystick a_JoystickZ;

	DiffDrive a_DiffDrive; // This is different from Differential Drive in WPILib.

	CollectorArm a_CollectorArm;

	Lifter a_Lifter;

	// Compressor a_Compressor;

	JrimmyGyro a_Gyro;

	SerialPort a_Arduino;

	UltrasonicSerial a_UltraSoul;

	// PowerDistributionPanel a_PDP;

	AutonomousHelper a_AutoBot;

	Autonomous a_Auto;
};

#endif
