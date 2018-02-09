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

enum AutoStateV1 {
	kMoveToSwitch = 0,
	kReleaseCube,
	kAutoIdle
};

enum AutoStateV2 {
	kMoveToSideOfSwitch = 0,
	kTurnLeft2,
	kMoveToEdgeOfSwitch,
	kReleaseCube2,
	kAutoIdle2
};

enum AutoStateV3 {
	kMoveToSideOfScale = 0,
	kTurnLeft3,
	kMoveToEdgeOfScale,
	kReleaseCube3,
	kAutoIdle3
};

enum AutoStateV4
{
	kMoveHalfToSwitch = 0,
	kTurnRight4,
	kMoveFlushWithSwitch,
	kTurnLeft4,
	kMoveToFrontOfSwitch,
	kReleaseCube4,
	kAutoIdle4
};

enum AutoStateV5
{
	kMoveTopOfSwitch = 0,
	kTurnRight5,
	kMoveFlushWithScale,
	kTurnLeft5,
	kMoveToFrontOfScale,
	kReleaseCube5,
	kAutoIdle5
};

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
    void AutonomousPeriodicV1(void);
    void AutonomousPeriodicV2(void);
    void AutonomousPeriodicV3(void);
    void AutonomousPeriodicV4(void);
    void AutonomousPeriodicV5(void);

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

	// JrimmyGyro a_Gyro;

	// SerialPort a_Arduino;

	// UltrasonicSerial a_UltraSoul;

	AutonomousHelper a_AutoBot;

	// PowerDistributionPanel a_PDP;

    AutoStateV1 a_AutoStateV1;
    AutoStateV2 a_AutoStateV2;
    AutoStateV3 a_AutoStateV3;
    AutoStateV4 a_AutoStateV4;
    AutoStateV5 a_AutoStateV5;

};

#endif
