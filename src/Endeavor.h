#ifndef SRC_ENDEAVOR_H_
#define SRC_ENDEAVOR_H_

#include <WPILib.h>
#include <SerialPort.h>
#include <IterativeRobot.h>
#include "SmartDashboard/SmartDashboard.h"
#include "SmartDashboard/SendableChooser.h"
#include "ctre/Phoenix.h"
#include <PracticePrefs.h>
#include <DiffDrive.h>
#include <Collector.h>
#include <CollectorArm.h>
#include <Lifter.h>
#include <JrimmyGyro.h>
#include <Underglow.h>
#include <UltrasonicSerial.h>
#include <LightRingController.h>
#include <AutonomousHelper.h>
#include <Autonomous.h>

class Endeavor : public IterativeRobot {
public:
	Endeavor(void);
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
	void MasterInit();
	void ShuffleboardPeriodicUpdate();

private:
	// I'm putting all sticks in the code until we determine which one we like to drive with. -AR
	Joystick a_GamePad;
	Joystick a_Joystick1;
	Joystick a_Joystick2;
	Joystick a_ButtonBox;

	DiffDrive a_DiffDrive; // This is different from Differential Drive in WPILib.

	CollectorArm a_CollectorArm;

	Lifter a_Lifter;

	Compressor a_Compressor;

	JrimmyGyro a_Gyro;

	Underglow a_Underglow;

	UltrasonicSerial a_UltraSoul;

	LightRingController a_LRC;

	// PowerDistributionPanel a_PDP;

	AutonomousHelper a_AutoBot;

	Autonomous a_Auto;

	bool autonTesting;
};

#endif
