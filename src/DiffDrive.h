#ifndef SRC_DIFFDRIVE_H_
#define SRC_DIFFDRIVE_H_

#include <WPILib.h>
#include "ctre/Phoenix.h"
#include <pathfinder.h>
#include <PracticePrefs.h>

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
	void InvertLeftDrive();
	void InvertRightDrive();
	void Update(Joystick &stick1, Joystick &stick2, Joystick &stick3, Joystick &stick4);
	void UpdateVal(float left, float right);
	bool UpdateAngle(float curAngle, float tarAngle);
	void ShiftLow();
	void ShiftHigh();
	bool GetShiftState();
	void GoDistance(float targetDistance);
	void DriveStraight(float left, float right);
	void DriveStraightGyro(float tarAngle, float curAngle, float speed);
	double gettime_d();
	int DriveToDist(float ldist, float rdist, float speed, int first_call);
	bool ArcTurn(float turnRadius, float turnAngle, bool direction, int first_call);
	void GenerateTrajectory();
	void ZeroEncoders();
	void UpdateDistance();
	float GetDistanceLeft();
	float GetDistanceRight();
	float GetAvgDistance(); // only used when driving straight.
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

	/*
	Waypoint points[3];

	Waypoint p1 = { -4, -1, d2r(45) };      // Waypoint @ x=-4, y=-1, exit angle=45 degrees
	Waypoint p2 = { -1, 2, 0 };             // Waypoint @ x=-1, y= 2, exit angle= 0 radians
	Waypoint p3 = {  2, 4, 0 };             // Waypoint @ x= 2, y= 4, exit angle= 0 radians
	*/

	int driveType;
	int targetPositionRotations;
	int kSlotIdx = 0;
	int kPIDLoopIdx = 0;
	int kTimeoutMs = 10;

	long totCountLeft = 0;
	long totCountRight = 0;
	long lastCountLeft = 0;
	long lastCountRight = 0;

	double t0;
	double lspeed_target;
	double rspeed_target;
	double avg_speed_target;
};

#endif
