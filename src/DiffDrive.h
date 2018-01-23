#ifndef SRC_DIFFDRIVE_H_
#define SRC_DIFFDRIVE_H_

#include <WPILib.h>
#include "ctre/Phoenix.h"
#include "Prefs.h"

class DiffDrive
{
public:
	DiffDrive(int leftDriveOne, int leftDriveTwo, int leftDriveThree, int rightDriveOne, int rightDriveTwo, int rightDriveThree);
	virtual ~DiffDrive() = default;
	void Init();
	void SetDriveType(int type);
	void Update(Joystick &stick1, Joystick &stick2, Joystick &stick3, Joystick &stick4);
	void GoDistance(float targetDistance);
	void ArcTurn(float turnRadius, float turnAngle, bool direction);
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

	// SpeedControllerGroup a_leftDrive;
	// SpeedControllerGroup a_rightDrive;

	DifferentialDrive a_Drivetrain;

	int driveType;
	int targetPositionRotations;
	int kSlotIdx = 0;
	int kPIDLoopIdx = 0;
	int kTimeoutMs = 10;
};

#endif
