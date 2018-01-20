#include <WPILib.h>
#include "DiffDrive.h"

DiffDrive::DiffDrive(int leftDriveOne, int leftDriveTwo, int leftDriveThree, int rightDriveOne, int rightDriveTwo, int rightDriveThree)
: a_leftDriveOne(leftDriveOne),
  a_leftDriveTwo(leftDriveTwo),
  a_leftDriveThree(leftDriveThree),

  a_rightDriveOne(rightDriveOne),
  a_rightDriveTwo(rightDriveTwo),
  a_rightDriveThree(rightDriveThree),

  // a_leftDrive(a_leftDriveOne, a_leftDriveTwo, a_leftDriveThree),
  // a_rightDrive(a_rightDriveOne, a_rightDriveTwo, a_rightDriveThree),
  a_Drivetrain(a_leftDriveTwo, a_rightDriveTwo)
{
	driveType = 0;
	targetPositionRotations = 10.0 * 4096; /* 50 Rotations in either direction */
	kSlotIdx = 0;
	kPIDLoopIdx = 0;
	kTimeoutMs = 10;
}

void DiffDrive::Init()
{
	a_leftDriveTwo.Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
	a_leftDriveTwo.Config_kP(kPIDLoopIdx, 0.0, kTimeoutMs);
	a_leftDriveTwo.Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	a_leftDriveTwo.Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

	a_rightDriveTwo.Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
	a_rightDriveTwo.Config_kP(kPIDLoopIdx, 0.0, kTimeoutMs);
	a_rightDriveTwo.Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	a_rightDriveTwo.Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

	// int absolutePositionLeft = a_leftDriveTwo.GetSelectedSensorPosition(0) & 0xFFF;
	a_leftDriveTwo.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
	a_leftDriveOne.Follow(a_leftDriveTwo);
	a_leftDriveThree.Follow(a_leftDriveTwo);

	// int absolutePositionRight = a_rightDriveTwo.GetSelectedSensorPosition(0) & 0xFFF;
	a_rightDriveTwo.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
	a_rightDriveOne.Follow(a_rightDriveTwo);
	a_rightDriveThree.Follow(a_rightDriveTwo);
}

void DiffDrive::SetDriveType(int type)
{
	driveType = type;
}

void DiffDrive::Update(Joystick &stick1, Joystick &stick2, Joystick &stick3, Joystick &stick4)
{
	switch (driveType) {
	  case 0: // ArcadeDrive from the flightstick with a Z
		  a_Drivetrain.ArcadeDrive((stick1.GetRawAxis(5)), stick1.GetRawAxis(4), false);
	    break;
	  case 1: // CurvatureDrive works better at high speeds.
		  	  // Using flightstick with a z
		  a_Drivetrain.CurvatureDrive(stick1.GetRawAxis(5), stick1.GetRawAxis(4), false);
	    break;
	  case 2: // Traditional Two Stick Tank.
		  	  // Uses the two flightsticks without z axes.
		  a_Drivetrain.TankDrive(stick2.GetRawAxis(1), stick3.GetRawAxis(1), false);
		break;
	  default :
		 a_Drivetrain.TankDrive(0, 0, false); // theo disable
	}
}

void DiffDrive::GoDistance(float targetDistance){
	a_leftDriveTwo.Set(ControlMode::Position, targetDistance * 10.0 * 4096);
	a_rightDriveTwo.Set(ControlMode::Position, targetDistance * 10.0 * 4096); // 50 rotations? fingers crossed!
}

float DiffDrive::GetDistance(){
	// a_leftDriveTwo.GetDistance()?

	return 0;
}
