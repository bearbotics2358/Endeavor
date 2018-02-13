#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <string>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <PracticePrefs.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <SmokeyXI.h>


/*
 *
 * Check out the Smokey XI Repository on GitHub for documentation.
 *
 */

SmokeyXI::SmokeyXI(void):

a_GamePad(GAMEPAD_PORT), // this should be the gamepad - list on port 0

a_Joystick1(JOYSTICK1_PORT), // this is the flightstick without a z axis, port 1

a_Joystick2(JOYSTICK2_PORT), // this is the flightstick without a z axis, port 2

a_JoystickZ(JOYSTICKZ_PORT), // this is the flightstick WITH a z axis, port 3

a_DiffDrive(LEFT_DRIVE_TALON_ONE, LEFT_DRIVE_TALON_TWO, LEFT_DRIVE_TALON_THREE, RIGHT_DRIVE_TALON_ONE, RIGHT_DRIVE_TALON_TWO, RIGHT_DRIVE_TALON_THREE),

a_CollectorArm(COLLECTOR_ARM_TALON),

a_Lifter(LIFTER_TALON),

// a_Compressor(PCM_PORT),

a_Gyro(I2C::kMXP),

a_Arduino(BAUD_RATE_ARDUINO, SerialPort::kUSB1, DATA_BITS,  SerialPort::kParity_None, SerialPort::kStopBits_One), // USB1 is the onboard port closest to the center of the rio

a_UltraSoul(),

// a_PDP(PDP_PORT),

a_AutoBot(), // AutoBot Methods return true for left.

a_Auto(a_AutoBot, a_CollectorArm, a_DiffDrive, a_Gyro, a_Arduino, a_UltraSoul)

{
	SmartDashboard::init();  // dont forget, shuffleboard over sd
	a_Gyro.Init();
	a_Arduino.Write("Z", 1);
}

void SmokeyXI::RobotInit()
{

}

void SmokeyXI::RobotPeriodic()
{

}

void SmokeyXI::DisabledInit()
{

}

void SmokeyXI::DisabledPeriodic()
{

}

void SmokeyXI::AutonomousInit()
{
	a_Arduino.Write("F", 1); // strips off
}

void SmokeyXI::AutonomousPeriodic()
{
	// Following lines are to test AutoPeriodic and the AutoBot autohelper i wrote.
	if (a_AutoBot.GetAllianceSide()){
		a_Arduino.Write("P", 1);
		SmartDashboard::PutBoolean("Blue?", true);
	}
	else{
		a_Arduino.Write("Q", 1);
		SmartDashboard::PutBoolean("Blue?", false);
	}
	SmartDashboard::PutNumber("Station Number", a_AutoBot.GetAllianceStation());
	SmartDashboard::PutBoolean("Our Switch Left? ", a_AutoBot.GetAllianceSwitch());
	SmartDashboard::PutBoolean("Scale Left? ", a_AutoBot.GetAllianceScale());
	SmartDashboard::PutBoolean("Opp Switch Left?", a_AutoBot.GetOpponentSwitch());
}

void SmokeyXI::TeleopInit()
{
	a_DiffDrive.Init();
	a_DiffDrive.SetDriveType(2); // Change the number to change drivetypes. Refer to diffdrive.cpp for help.
	// a_DiffDrive.DisableMotorSafetyTraitor();
	a_Lifter.Init();
	a_CollectorArm.Init();
	// a_Gyro.Cal();
	a_Gyro.Zero();
	// a_Compressor.SetClosedLoopControl(true);
	if (a_AutoBot.GetAllianceSide()){
		a_Arduino.Write("P", 1);
		SmartDashboard::PutBoolean("Blue?", true);
	}
	else{
		a_Arduino.Write("Q", 1);
		SmartDashboard::PutBoolean("Blue?", false);
	}
}


void SmokeyXI::TeleopPeriodic()
{
	a_DiffDrive.UpdateVal(0,0);
	a_CollectorArm.UpdateRollers(0.0);
	if (a_Joystick1.GetRawButton(1)){
		a_CollectorArm.UpdateRollers(-1.0);
	}
	if (a_Joystick1.GetRawButton(6)){
		a_CollectorArm.UpdateRollers(1.0);
	}
	if (a_Joystick2.GetRawButton(1)){
		a_CollectorArm.UpdateValue(-1.0 * a_Joystick2.GetRawAxis(1));
		a_DiffDrive.UpdateVal(0,0);
	}
	else{
		a_DiffDrive.UpdateVal((-1.0 * a_Joystick1.GetRawAxis(1)), (-1.0 * a_Joystick2.GetRawAxis(1)));
	}

	if (a_Joystick1.GetRawButton(2)){ // Change Collector Position
		a_CollectorArm.RollerPos(0);
	}
	if (a_Joystick1.GetRawButton(3)){
		a_CollectorArm.RollerPos(1);
	}
	if (a_Joystick1.GetRawButton(4)){
		a_CollectorArm.RollerPos(2);
	}
	if (a_Joystick1.GetRawButton(5)){
		a_CollectorArm.RollerPos(3);
	}
	if (a_Joystick2.GetRawButton(2)){a_CollectorArm.Clamp();}
	if (a_Joystick2.GetRawButton(3)){a_CollectorArm.Release();}	

	if (a_Joystick2.GetRawButton(4)){a_DiffDrive.ShiftLow();}
	if (a_Joystick2.GetRawButton(5)){a_DiffDrive.ShiftHigh();}

	if (a_Joystick2.GetRawButton(6)){
		a_CollectorArm.UpdateAngle(45);

	}
	if (a_Joystick2.GetRawButton(7)){
		a_CollectorArm.UpdateAngle(90);
	}
	if (a_Joystick2.GetRawButton(10)){
		a_CollectorArm.UpdateAngle(135);
	}
	SmartDashboard::PutNumber("Arm Angle Theo 1: ", a_CollectorArm.GetAngle1());
	SmartDashboard::PutNumber("Arm Angle Theo 2: ", a_CollectorArm.GetAngle2());

	// apparently buttons aren't zero indexed, but axes are???
	/*
	if (a_Joystick1.GetRawButton(3)){
	a_DiffDrive.DriveStraight((1 * (LEFT_AGGRO)),(-1 * (RIGHT_AGGRO)));
	}
	if (a_Joystick2.GetRawButton(3)){
	a_DiffDrive.DriveStraight((-1 * (LEFT_AGGRO)),(1 * (RIGHT_AGGRO)));
	}
	*/
	// a_DiffDrive.Update(a_GamePad, a_Joystick1, a_Joystick2, a_JoystickZ); // wonder if passing four sticks impacts latency -- if it does, i didnt notice

	a_Gyro.Update();
	float gyroValue1 = a_Gyro.GetAngle(0);
	float gyroValue2 = a_Gyro.GetAngle(1);
	float gyroValue3 = a_Gyro.GetAngle(2);
	SmartDashboard::PutNumber("Gyro Angle X: ", gyroValue1);
	SmartDashboard::PutNumber("Gyro Angle 2: ", gyroValue2);
	SmartDashboard::PutNumber("Gyro Angle 3: ", gyroValue3);
	SmartDashboard::PutNumber("Gyro X", a_Gyro.GetX());
	SmartDashboard::PutNumber("Gyro Y", a_Gyro.GetY());
	SmartDashboard::PutNumber("Gyro Z", a_Gyro.GetZ());
	/*
	SmartDashboard::PutNumber("Arm Angle Theo 1: ", a_CollectorArm.GetAngle1());

	SmartDashboard::PutNumber("Left Encoder Pos: ", a_DiffDrive.GetDistanceLeft());
	SmartDashboard::PutNumber("Right Encoder Pos : ", a_DiffDrive.GetDistanceRight());
	SmartDashboard::PutNumber("Left Encoder Velo: ", a_DiffDrive.GetVelocityLeft());
	SmartDashboard::PutNumber("Right Encoder Velo : ", a_DiffDrive.GetVelocityRight());
	*/
	SmartDashboard::PutBoolean("Finger State", a_CollectorArm.GetClampState());

	SmartDashboard::PutBoolean("Shift State", a_DiffDrive.GetShiftState());

}

void SmokeyXI::TestInit()
{
	// test is currently only used to run the compressor
	a_DiffDrive.Init();
	a_Lifter.Init();
}

void SmokeyXI::TestPeriodic()
{
	a_DiffDrive.UpdateVal(0,0);
	if (a_Joystick2.GetRawButton(1)){
		a_Lifter.Update(-1); // this actually doesn't do anything to the lifter lol, it runs the compressor for now
	}
}

START_ROBOT_CLASS(SmokeyXI);
