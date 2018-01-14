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
	void Update(float StickX, float StickY);
private:
	WPI_TalonSRX a_leftDriveOne;
	WPI_TalonSRX a_leftDriveTwo;
	WPI_TalonSRX a_leftDriveThree;

	WPI_TalonSRX a_rightDriveOne;
	WPI_TalonSRX a_rightDriveTwo;
	WPI_TalonSRX a_rightDriveThree;

	SpeedControllerGroup a_leftDrive;
	SpeedControllerGroup a_rightDrive;

	DifferentialDrive a_Drivetrain;
};

#endif
