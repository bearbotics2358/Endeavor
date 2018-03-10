#ifndef SRC_AUTONOMOUS_H_
#define SRC_AUTONOMOUS_H_

#include <WPILib.h>
#include <SerialPort.h>
#include <PracticePrefs.h>
#include <PracticePrefsAutonomous.h>
#include <DiffDrive.h>
#include <Collector.h>
#include <CollectorArm.h>
#include <JrimmyGyro.h>
#include <AutonomousHelper.h>
#include <Underglow.h>
#include <UltrasonicSerial.h>

enum AutoStateVx {
	kAutoIdlex = 0,
	kMoveToSwitchInitx,
	kMoveToSwitchx,
};

enum AutoStateU0 {
	kAutoIdleU0 = 0,
	kMoveToSwitchU0,
};

enum AutoStateV0 {
	kMoveToSwitch0 = 0,
	kAutoIdle0
};

enum AutoStateU1 {
	kAutoIdleU1 = 0,
	kMoveToSwitchU1,
	kMoveArmU1,
	kReleaseCubeU1
};

enum AutoStateV1 {
	kMoveToSwitch1 = 0,
	kMoveArm1,
	kReleaseCube1,
	kAutoIdle1
};

enum AutoStateU2 {
	kAutoIdleU2 =0,
	kMoveToSideOfSwitchU2,
	kTurnLeftU2,
	kMoveToEdgeOfSwitchU2,
	kMoveArmU2,
	kReleaseCubeU2,
};

enum AutoStateV2 {
	kMoveToSideOfSwitch = 0,
	kTurnLeft2,
	kMoveToEdgeOfSwitch,
	kMoveArm2,
	kReleaseCube2,
	kAutoIdle2
};

enum AutoStateU3 {
	kAutoIdleU3 = 0,
	kMoveToSideOfScaleU3,
	kTurnLeftU3,
	kMoveToEdgeOfScaleU3,
	kMoveArmU3,
	kReleaseCubeU3,
};

enum AutoStateV3 {
	kMoveToSideOfScale = 0,
	kTurnLeft3,
	kMoveToEdgeOfScale,
	kMoveArm3,
	kReleaseCube3,
	kAutoIdle3
};

enum AutoStateU4
{
	kAutoIdleU4 = 0,
	kMoveHalfToSwitchU4,
	kTurnRightU4,
	kMoveFlushWithSwitchU4,
	kTurnLeftU4,
	kMoveToFrontOfSwitchU4,
	kMoveArmU4,
	kReleaseCubeU4,
};

enum AutoStateV4
{
	kMoveHalfToSwitch = 0,
	kTurnRight4,
	kMoveFlushWithSwitch,
	kTurnLeft4,
	kMoveToFrontOfSwitch,
	kMoveArm4,
	kReleaseCube4,
	kAutoIdle4
};

enum AutoStateU5
{
	kAutoIdleU5 = 0,
	kMoveTopOfSwitchU5,
	kTurnRightU5,
	kMoveFlushWithScaleU5,
	kTurnLeftU5,
	kMoveToFrontOfScaleU5,
	kMoveArmU5,
	kReleaseCubeU5,
};

enum AutoStateV5
{
	kMoveTopOfSwitch = 0,
	kTurnRight5,
	kMoveFlushWithScale,
	kTurnLeft5,
	kMoveToFrontOfScale,
	kMoveArm5,
	kReleaseCube5,
	kAutoIdle5
};

class Autonomous
{
 public:
	Autonomous(AutonomousHelper &AutoBot, CollectorArm &CollectorArm, DiffDrive &DiffDrive, JrimmyGyro &Gyro, Underglow &Underglow, UltrasonicSerial &UltraSoul);
	virtual ~Autonomous() = default;
	void Init();
	void AutonomousPeriodicVx();
	void AutonomousStartU0();
	void AutonomousPeriodicU0();
	void AutonomousPeriodicV0();
	void AutonomousStartU1();
	void AutonomousPeriodicU1();
	void AutonomousPeriodicV1();
	void AutonomousStartU2();
	void AutonomousPeriodicU2();
	void AutonomousPeriodicV2();
	void AutonomousStartU3();
	void AutonomousPeriodicU3();
	void AutonomousPeriodicV3();
	void AutonomousStartU4();
	void AutonomousPeriodicU4();
	void AutonomousPeriodicV4();
	void AutonomousStartU5();
	void AutonomousPeriodicU5();
	void AutonomousPeriodicV5();

 private:
	AutonomousHelper &a_AutoBot;

	CollectorArm &a_CollectorArm;

	DiffDrive &a_DiffDrive;

	JrimmyGyro &a_Gyro;

	Underglow &a_Underglow;

	UltrasonicSerial &a_UltraSoul;

	AutoStateVx a_AutoStateVx;
	AutoStateU0 a_AutoStateU0;
	AutoStateV0 a_AutoStateV0;
	AutoStateU1 a_AutoStateU1;
	AutoStateV1 a_AutoStateV1;
	AutoStateU2 a_AutoStateU2;
	AutoStateV2 a_AutoStateV2;
	AutoStateU3 a_AutoStateU3;
	AutoStateV3 a_AutoStateV3;
	AutoStateU4 a_AutoStateU4;
	AutoStateV4 a_AutoStateV4;
	AutoStateU5 a_AutoStateU5;
	AutoStateV5 a_AutoStateV5;

	float a_AngleSaved;
	double a_time_state = 0;

	/* Example internal auto function
	 * bool DriveStraight(int distance);*/

};

#endif
