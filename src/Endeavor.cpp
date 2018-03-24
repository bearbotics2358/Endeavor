#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <string>
#include <WPILib.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <PracticePrefs.h>
#include <Endeavor.h>

/*
 *
 * Check out the Endeavor Repository on GitHub for documentation.
 *
 */

Endeavor::Endeavor(void):

a_GamePad(GAMEPAD_PORT), // this should be the gamepad - list on port 0

a_Joystick1(JOYSTICK1_PORT), // this is the flightstick without a z axis, port 1

a_Joystick2(JOYSTICK2_PORT), // this is the flightstick without a z axis, port 2

a_ButtonBox(BUTTONBOX_PORT), // this is the buttonbox, who would have guessed, port 3

a_DiffDrive(LEFT_DRIVE_TALON_ONE, LEFT_DRIVE_TALON_TWO, LEFT_DRIVE_TALON_THREE, RIGHT_DRIVE_TALON_ONE, RIGHT_DRIVE_TALON_TWO, RIGHT_DRIVE_TALON_THREE),

a_CollectorArm(COLLECTOR_ARM_TALON),

a_Lifter(LEFT_LIFTER_TALON, RIGHT_LIFTER_TALON),

a_Compressor(PCM_PORT),

a_Gyro(I2C::kMXP),

a_Underglow(),

a_UltraSoul(),

a_LRC(),

// a_PDP(PDP_PORT),

a_AutoBot(), // AutoBot Methods return true for left.

a_Auto(a_AutoBot, a_ButtonBox, a_CollectorArm, a_DiffDrive, a_Gyro, a_Underglow, a_UltraSoul)

{
	SmartDashboard::init();  // dont forget, shuffleboard over sd
	a_Gyro.Init();
	autonTesting = false;
}

void Endeavor::RobotInit()
{
	autonTesting = false;
}

void Endeavor::RobotPeriodic()
{
	a_Gyro.Update();
	ShuffleboardPeriodicUpdate();
}

void Endeavor::DisabledInit()
{

}

void Endeavor::DisabledPeriodic()
{

}

void Endeavor::AutonomousInit()
{
	MasterInit();
	a_Auto.Init();
	a_Auto.DecidePath(); // call this with a number to override automatic selection
	a_Auto.StartPathMaster(); // override by commenting this and the above call to decide path
	// a_Auto.AutonomousStartU0();
	// a_Auto.AutonomousStartU1();
	// a_Auto.AutonomousStartU2();
	// a_Auto.AutonomousStartU3();
	// a_Auto.AutonomousStartU4();
	// a_Auto.AutonomousStartU5();
}

void Endeavor::AutonomousPeriodic()
{
	// get latest values before taking action
	a_UltraSoul.Update();
	a_Gyro.Update();
	a_Auto.PeriodicPathMaster();
	// a_Auto.AutonomousPeriodicU0();
	// a_Auto.AutonomousPeriodicU1();
	// a_Auto.AutonomousPeriodicU2();
	// a_Auto.AutonomousPeriodicU3();
	// a_Auto.AutonomousPeriodicU4();
	// a_Auto.AutonomousPeriodicU5();
}

void Endeavor::TeleopInit()
{
	MasterInit();
	a_Underglow.MagentaLaser();
}

void Endeavor::TeleopPeriodic()
{
	// get latest values before taking action
	a_UltraSoul.Update();
	a_Gyro.Update();
	a_DiffDrive.UpdateVal(0,0);
	a_DiffDrive.UpdateDistance();
	a_Lifter.Update(0.0);

	if (a_GamePad.GetRawButton(6)){ // flip on comp bot
		a_CollectorArm.Release();
	}
	if (a_GamePad.GetRawButton(5)){
		a_CollectorArm.Clamp();
	}

	if (a_GamePad.GetRawAxis(3) > 0.00) {
		a_CollectorArm.UpdateRollers(pow(a_GamePad.GetRawAxis(3), 0.5));
	} else if ((a_GamePad.GetRawAxis(2) > 0.00)) {  // in
		a_CollectorArm.UpdateRollers(-1 * pow(a_GamePad.GetRawAxis(2), 0.5));
	} else {
		a_CollectorArm.UpdateRollers(0.0);
	}
	a_CollectorArm.UpdateValue(0.0);
	if (a_GamePad.GetRawButton(1)){
		a_CollectorArm.UpdateValue(a_GamePad.GetRawAxis(1) * -1);
	}

	a_DiffDrive.UpdateVal((a_Joystick1.GetRawAxis(1)), (a_Joystick2.GetRawAxis(1)));
	if (a_GamePad.GetRawButton(2)){ // Change Collector Position
		// B
		a_CollectorArm.RollerPos(3); // stow
	}
	if (a_GamePad.GetRawButton(4)){
		// Y
		a_CollectorArm.RollerPos(1); // 45
	}
	if (a_GamePad.GetRawButton(3)){
		// X
		a_CollectorArm.RollerPos(2); // flat
	}

	if (a_Joystick2.GetRawButton(4)){a_DiffDrive.ShiftLow();}
	if (a_Joystick2.GetRawButton(5)){a_DiffDrive.ShiftHigh();}

	if (a_Joystick2.GetRawButton(6)){
		a_Compressor.SetClosedLoopControl(true);
	}
	if (a_Joystick2.GetRawButton(7)){
		a_Compressor.SetClosedLoopControl(false);
	}
	if (a_Joystick2.GetRawButton(8)){
		a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_HIGH);
	}
	if (a_Joystick2.GetRawButton(8)){
		a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), a_Gyro.GetAngle(2) + 10);
	}
}

void Endeavor::TestInit(){
	MasterInit();
	a_Auto.Init();
	a_Auto.DecidePath();
	SmartDashboard::PutNumber("AUTOPATHMASTER1", a_Auto.GetCurrentPath());
}

void Endeavor::TestPeriodic(){
	a_Auto.DecidePath();
	SmartDashboard::PutNumber("AUTOPATHMASTER2", a_Auto.GetCurrentPath());
	// ShuffleboardPeriodicUpdate();
}

void Endeavor::MasterInit(){
	a_DiffDrive.Init();
	a_DiffDrive.SetLeftPIDF(LEFT_DRIVE_P,LEFT_DRIVE_I,LEFT_DRIVE_D,LEFT_DRIVE_F);
	a_DiffDrive.SetRightPIDF(RIGHT_DRIVE_P,RIGHT_DRIVE_I,RIGHT_DRIVE_D,RIGHT_DRIVE_F);
	a_DiffDrive.SetDriveType(2);
	a_DiffDrive.ZeroEncoders();
	// Change the number to change drivetypes. Refer to diffdrive.cpp for help.
	// a_DiffDrive.DisableMotorSafetyTraitor();
	// a_DiffDrive.InvertLeftDrive();
	// a_DiffDrive.InvertRightDrive();
	a_CollectorArm.Init(ARM_P, ARM_I, ARM_D, ARM_F);
	a_Lifter.Init();
	a_UltraSoul.Init();
	// for now, using old multiplexer on practice bot
	// so only using 1 front and 1 rear sensor, hooked to channels A and C (ports 0 and 2)
	// Disable the other ports
	a_UltraSoul.DisablePort(0);
	a_UltraSoul.DisablePort(3);

	a_Underglow.Init();
	// a_Gyro.Cal();
	a_Gyro.Zero();
	a_Compressor.SetClosedLoopControl(false);
	a_LRC.SetAllColor(100,100,0);
}

void Endeavor::ShuffleboardPeriodicUpdate(){
	// float gyroValue1 = a_Gyro.GetAngle(0);
	// float gyroValue2 = a_Gyro.GetAngle(1);
	float gyroValue3 = a_Gyro.GetAngle(2);
	// SmartDashboard::PutNumber("Gyro Angle 1: ", gyroValue1);
	// SmartDashboard::PutNumber("Gyro Angle 2: ", gyroValue2);
	SmartDashboard::PutNumber("Gyro Angle 3: ", gyroValue3);
	// SmartDashboard::PutNumber("Gyro X", a_Gyro.GetX());
	// SmartDashboard::PutNumber("Gyro Y", a_Gyro.GetY());
	// SmartDashboard::PutNumber("Gyro Z", a_Gyro.GetZ());
	SmartDashboard::PutNumber("Left Encoder Pos: ", a_DiffDrive.GetDistanceLeft());
	SmartDashboard::PutNumber("Right Encoder Pos : ", a_DiffDrive.GetDistanceRight());
	SmartDashboard::PutBoolean("Finger State", a_CollectorArm.GetClampState());
	SmartDashboard::PutBoolean("Shift State", a_DiffDrive.GetShiftState());
	SmartDashboard::PutBoolean("Pressure Switch", a_Compressor.GetPressureSwitchValue());
	SmartDashboard::PutNumber("Compressor Current Draw", a_Compressor.GetCompressorCurrent());
	SmartDashboard::PutNumber("Arm Angle Raw: ", a_CollectorArm.GetAngle1());
	SmartDashboard::PutNumber("Arm Angle Scaled: ", a_CollectorArm.GetAngle2());
	SmartDashboard::PutBoolean("Is there a Cube?", a_CollectorArm.CubePresent());
	// SmartDashboard::PutNumber("PDP Things?", a_PDP.GetTotalPower());
	SmartDashboard::PutNumber("Ultra FrontLeft", a_UltraSoul.GetFrontLeft());
	SmartDashboard::PutNumber("Ultra FrontRight", a_UltraSoul.GetUltraB());
	SmartDashboard::PutNumber("Ultra LeftSide", a_UltraSoul.GetLeftSide());
	SmartDashboard::PutNumber("Ultra RightSide", a_UltraSoul.GetRightSide());
	SmartDashboard::PutNumber("Ultra RearLeft", a_UltraSoul.GetRearLeft());
	SmartDashboard::PutNumber("Ultra RearRight", a_UltraSoul.GetRearRight());
}

START_ROBOT_CLASS(Endeavor);
