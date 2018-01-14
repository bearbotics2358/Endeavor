#include <WPILib.h>
#include "DiffDrive.h"

DiffDrive::DiffDrive(int leftDriveOne, int leftDriveTwo, int leftDriveThree, int rightDriveOne, int rightDriveTwo, int rightDriveThree)
: a_leftDriveOne(leftDriveOne),
  a_leftDriveTwo(leftDriveTwo),
  a_leftDriveThree(leftDriveThree),

  a_rightDriveOne(rightDriveOne),
  a_rightDriveTwo(rightDriveTwo),
  a_rightDriveThree(rightDriveThree),

  a_leftDrive(a_leftDriveOne, a_leftDriveTwo, a_leftDriveThree),
  a_rightDrive(a_rightDriveOne, a_rightDriveTwo, a_rightDriveThree),
  a_Drivetrain(a_leftDrive, a_rightDrive)
{

}

void DiffDrive::Update(float StickX, float StickY)
{
	a_Drivetrain.ArcadeDrive(StickX, StickY);
}
