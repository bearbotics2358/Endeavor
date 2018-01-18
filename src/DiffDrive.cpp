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
	driveType = 0;
}

void DiffDrive::SetDriveType(int type)
{
	driveType = type;
}

void DiffDrive::Update(Joystick &stick1, Joystick &stick2, Joystick &stick3, Joystick &stick4)
{
	switch (driveType) {
	  case 0: // ArcadeDrive from the flightstick with a Z
		  a_Drivetrain.ArcadeDrive((-1 * stick4.GetRawAxis(1)), stick4.GetRawAxis(0), false);
	    break;
	  case 1: // CurvatureDrive works better at high speeds.
		  	  // Using flightstick with a z
			a_Drivetrain.CurvatureDrive(stick4.GetRawAxis(0), stick4.GetRawAxis(1), false);
	    break;
	  case 2: // Traditional Two Stick Tank.
		  	  // Uses the two flightsticks without z axes.
		  	a_Drivetrain.TankDrive(stick2.GetRawAxis(1), stick3.GetRawAxis(1), false);
		break;
	  default :
		  a_Drivetrain.TankDrive(0,0, false); // theo disable
	}
}
