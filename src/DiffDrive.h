#ifndef SRC_DIFFDRIVE_H_
#define SRC_DIFFDRIVE_H_

#include <WPILib.h>
#include "ctre/Phoenix.h"
#include <pathfinder.h>
#include <CompPrefs.h>

class DiffDrive
{
public:
	DiffDrive(int leftDriveOne, int leftDriveTwo, int leftDriveThree, int rightDriveOne, int rightDriveTwo, int rightDriveThree);
	virtual ~DiffDrive() = default;
	void Init();
	void Init(float p, float i, float d, float f);
	void SetLeftPIDF(float p, float i, float d, float f); // can be called publicly to set pid separately for each side
	void SetRightPIDF(float p, float i, float d, float f);
	void SetDriveType(int type);
	void DisableMotorSafetyTraitor();
	void Update(Joystick &stick1, Joystick &stick2, Joystick &stick3, Joystick &stick4);
	void UpdateVal(float left, float right);
	void ShiftLow();
	void ShiftHigh();
	bool GetShiftState();
	void GoDistance(float targetDistance);
	void DriveStraight(float left, float right);
	void ArcTurn(float turnRadius, float turnAngle, bool direction);
	void GenerateTrajectory();
	float GetDistanceLeft();
	float GetDistanceRight();
	float GetVelocityLeft();
	float GetVelocityRight();

private:
	WPI_TalonSRX a_leftDriveOne;
	WPI_TalonSRX a_leftDriveTwo;
	WPI_TalonSRX a_leftDriveThree;

	WPI_TalonSRX a_rightDriveOne;
	WPI_TalonSRX a_rightDriveTwo;
	WPI_TalonSRX a_rightDriveThree;

	DifferentialDrive a_Drivetrain;

	DoubleSolenoid a_DriveSolenoid;

	Waypoint points[3];

	Waypoint p1 = { -4, -1, d2r(45) };      // Waypoint @ x=-4, y=-1, exit angle=45 degrees
	Waypoint p2 = { -1, 2, 0 };             // Waypoint @ x=-1, y= 2, exit angle= 0 radians
	Waypoint p3 = {  2, 4, 0 };             // Waypoint @ x= 2, y= 4, exit angle= 0 radians

	int driveType;
	int targetPositionRotations;
	int kSlotIdx = 0;
	int kPIDLoopIdx = 0;
	int kTimeoutMs = 10;
};

#endif
