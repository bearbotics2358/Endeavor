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

a_JoystickZ(JOYSTICKZ_PORT), // this is the flightstick WITH a z axis, port 3

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

a_Auto(a_AutoBot, a_CollectorArm, a_DiffDrive, a_Gyro, a_Underglow, a_UltraSoul)

{
	SmartDashboard::init();  // dont forget, shuffleboard over sd
	a_Gyro.Init();
}

void Endeavor::RobotInit()
{
	// for now, using old multiplexer on practice bot
	// so only using 1 front and 1 rear sensor, hooked to channels A and C (ports 0 and 2)
	// Disable the other ports
	a_UltraSoul.DisablePort(1);
	a_UltraSoul.DisablePort(3);
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
	a_DiffDrive.ZeroEncoders();
	a_UltraSoul.Init();
	a_Auto.Init();
	
	// For now, uncomment one of the following lines to run that Autonomous routine
	a_Auto.AutonomousStartU0();
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

	// Following lines are to test AutoPeriodic and the AutoBot autohelper i wrote.
	if (a_AutoBot.GetAllianceSide()){
		a_Underglow.GoBlue();
		SmartDashboard::PutBoolean("Blue?", true);
	}
	else{
		a_Underglow.GoRed();
		SmartDashboard::PutBoolean("Blue?", false);
	}
	SmartDashboard::PutNumber("Station Number", a_AutoBot.GetAllianceStation());
	SmartDashboard::PutBoolean("Our Switch Left? ", a_AutoBot.GetAllianceSwitch());
	SmartDashboard::PutBoolean("Scale Left? ", a_AutoBot.GetAllianceScale());
	SmartDashboard::PutBoolean("Opp Switch Left?", a_AutoBot.GetOpponentSwitch());

	// For now, uncomment one of the following lines to run that Autonomous routine
	a_Auto.AutonomousPeriodicU0();
	// a_Auto.AutonomousPeriodicU1();
	// a_Auto.AutonomousPeriodicU2();
	// a_Auto.AutonomousPeriodicU3();
	// a_Auto.AutonomousPeriodicU4();
	// a_Auto.AutonomousPeriodicU5();
}

void Endeavor::TeleopInit()
{
	a_DiffDrive.Init();
	a_DiffDrive.SetLeftPIDF(LEFT_DRIVE_P,LEFT_DRIVE_I,LEFT_DRIVE_D,LEFT_DRIVE_F);
	a_DiffDrive.SetRightPIDF(RIGHT_DRIVE_P,RIGHT_DRIVE_I,RIGHT_DRIVE_D,RIGHT_DRIVE_F);
	a_DiffDrive.SetDriveType(2);
	// Change the number to change drivetypes. Refer to diffdrive.cpp for help.
	// a_DiffDrive.DisableMotorSafetyTraitor();
	a_CollectorArm.Init(ARM_P, ARM_I, ARM_D, ARM_F);
	a_Lifter.Init();
	a_UltraSoul.Init();
	// a_Gyro.Cal();
	a_Gyro.Zero();
	a_LRC.SetAllColor(0,100,0);
	if (a_AutoBot.GetAllianceSide()){
		a_Underglow.GoBlue();
		SmartDashboard::PutBoolean("Blue?", true);
	}
	else{
		a_Underglow.GoRed();
		SmartDashboard::PutBoolean("Blue?", false);
	}
}

void Endeavor::TeleopPeriodic()
{

	// get latest values before taking action
	a_UltraSoul.Update();
	a_Gyro.Update();

	a_DiffDrive.UpdateVal(0,0);
	a_DiffDrive.UpdateDistance();
	a_Lifter.Update(0);

	if (a_GamePad.GetRawButton(5)){
		a_CollectorArm.Clamp();
	}
	if (a_GamePad.GetRawButton(6)){
		a_CollectorArm.Release();
	}

	if (a_GamePad.GetRawAxis(3) > 0.00){
		a_CollectorArm.UpdateRollers(a_GamePad.GetRawAxis(3));
	}
	else if ((a_GamePad.GetRawAxis(2) > 0.00)){  // in
		a_CollectorArm.UpdateRollers(a_GamePad.GetRawAxis(2) * -1);
	}
	else {
		a_CollectorArm.UpdateRollers(0.0);
	}
	a_CollectorArm.UpdateValue(0.0);
	if (a_GamePad.GetRawButton(1)){
		a_CollectorArm.UpdateValue(a_GamePad.GetRawAxis(1));
	}

	a_DiffDrive.UpdateVal((a_Joystick1.GetRawAxis(1)), (a_Joystick2.GetRawAxis(1)));
	if (a_GamePad.GetRawButton(2)){ // Change Collector Position
		// B
		a_CollectorArm.RollerPos(3);
	}
	if (a_GamePad.GetRawButton(4)){
		// Y
		a_CollectorArm.RollerPos(1);
	}
	if (a_GamePad.GetRawButton(3)){
		// X
		a_CollectorArm.RollerPos(2);
	}

	if (a_Joystick2.GetRawButton(4)){a_DiffDrive.ShiftLow();}
	if (a_Joystick2.GetRawButton(5)){a_DiffDrive.ShiftHigh();}

	if (a_Joystick2.GetRawButton(6)){
		a_Compressor.SetClosedLoopControl(true);
	}
	if (a_Joystick2.GetRawButton(7)){
		a_Compressor.SetClosedLoopControl(false);
	}

	// a_DiffDrive.Update(a_GamePad, a_Joystick1, a_Joystick2, a_JoystickZ); // wonder if passing four sticks impacts latency -- if it does, i didnt notice
}

void Endeavor::TestInit()
{
	TeleopInit();
}

void Endeavor::TestPeriodic()
{
	a_UltraSoul.Update();
	a_Gyro.Update();

	a_DiffDrive.UpdateVal(0,0);
	a_DiffDrive.UpdateDistance();
	a_Lifter.Update(0);

	if (a_GamePad.GetRawButton(1)){
		a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, a_GamePad.GetRawAxis(2));
	}
	if (a_GamePad.GetRawButton(2)){
		a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 0.0);
	}
	if (a_GamePad.GetRawButton(3)){
		a_Gyro.Zero();
	}
	ShuffleboardPeriodicUpdate();
}

void Endeavor::ShuffleboardPeriodicUpdate(){
	float gyroValue1 = a_Gyro.GetAngle(0);
	float gyroValue2 = a_Gyro.GetAngle(1);
	float gyroValue3 = a_Gyro.GetAngle(2);
	SmartDashboard::PutNumber("Gyro Angle 1: ", gyroValue1);
	SmartDashboard::PutNumber("Gyro Angle 2: ", gyroValue2);
	SmartDashboard::PutNumber("Gyro Angle 3: ", gyroValue3);
	SmartDashboard::PutNumber("Gyro X", a_Gyro.GetX());
	SmartDashboard::PutNumber("Gyro Y", a_Gyro.GetY());
	SmartDashboard::PutNumber("Gyro Z", a_Gyro.GetZ());
	SmartDashboard::PutNumber("Left Encoder Pos: ", a_DiffDrive.GetDistanceLeft());
	SmartDashboard::PutNumber("Right Encoder Pos : ", a_DiffDrive.GetDistanceRight());
	SmartDashboard::PutBoolean("Finger State", a_CollectorArm.GetClampState());
	SmartDashboard::PutBoolean("Shift State", a_DiffDrive.GetShiftState());
	SmartDashboard::PutBoolean("Pressure Switch", a_Compressor.GetPressureSwitchValue());
	SmartDashboard::PutNumber("Compressor Current Draw", a_Compressor.GetCompressorCurrent());
	SmartDashboard::PutNumber("Arm Angle Theo 1: ", a_CollectorArm.GetAngle1());
	SmartDashboard::PutNumber("Arm Angle Theo 2: ", a_CollectorArm.GetAngle2());
	SmartDashboard::PutBoolean("Is there a Cube?", a_CollectorArm.CubePresent());
	// SmartDashboard::PutNumber("PDP Things?", a_PDP.GetTotalPower());
	SmartDashboard::PutNumber("Ultra FrontLeft", a_UltraSoul.GetFrontLeft());
	SmartDashboard::PutNumber("Ultra FrontRight", a_UltraSoul.GetFrontRight());
	SmartDashboard::PutNumber("Ultra LeftSide", a_UltraSoul.GetLeftSide());
	SmartDashboard::PutNumber("Ultra RightSide", a_UltraSoul.GetRightSide());
	SmartDashboard::PutNumber("Ultra RearLeft", a_UltraSoul.GetRearLeft());
	SmartDashboard::PutNumber("Ultra RearRight", a_UltraSoul.GetRearRight());
}

START_ROBOT_CLASS(Endeavor);
