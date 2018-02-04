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

a_Compressor(PCM_PORT),

a_Gyro(I2C::kMXP),

// a_Arduino(BAUD_RATE_ARDUINO, SerialPort::kUSB1, DATA_BITS,  SerialPort::kParity_None, SerialPort::kStopBits_One), // USB1 is the onboard port closest to the center of the rio

a_UltraSoul(),

a_AutoBot(), // AutoBot Methods return true for left.

a_AutoStateV1(kAutoIdle),

a_AutoStateV2(kAutoIdle2),

a_AutoStateV3(kAutoIdle3),

a_AutoStateV4(kAutoIdle4),

a_AutoStateV5(kAutoIdle5)

{

}

void SmokeyXI::RobotInit()
{
	SmartDashboard::init();
	a_Gyro.Init();
	// Things go to the SmartDashboard object but I want to try and use Shuffleboard instead.
	// It uses the same method calls to the SmartDashboard, but is much cleaner and easier to interpret data that comes in.
}

void SmokeyXI::RobotPeriodic()
{

}

void SmokeyXI::DisabledInit()
{

}

void SmokeyXI::DisabledPeriodic()
{
	SmartDashboard::PutString("Enabled: ", "False");
}

void SmokeyXI::AutonomousInit()
{
	SmartDashboard::PutString("Enabled: ", "True");
	// a_Arduino.Write("N", 1); // strips off
}

void SmokeyXI::AutonomousPeriodic()
{
	// Following lines are to test AutoPeriodic and the AutoBot autohelper i wrote.
	if (a_AutoBot.GetAllianceSwitch()){
		// a_Arduino.Write("B", 1); // Left side, Blue leds for indicators
		SmartDashboard::PutBoolean("Our Switch Left? ", true);
	}
	else{
		// a_Arduino.Write("M", 1); // Right side, Red leds for indicators
		SmartDashboard::PutBoolean("Our Switch Left? ", false);
	}
	if (a_AutoBot.GetAllianceScale()){
		SmartDashboard::PutBoolean("Scale Left? ", true);
	}
	else{
		SmartDashboard::PutBoolean("Scale Left? ", false);
	}
	if (a_AutoBot.GetOpponentSwitch()){
		SmartDashboard::PutBoolean("Opp Switch Left?", true);
	}
	else{
		SmartDashboard::PutBoolean("Opp Switch Left?", true);
	}

	/*
	void SmokeyXI::AutonomousPeriodicV1()
	{

		const float SWITCH_DISTANCE;

	    AutoStateV1 nextState = a_AutoStateV1;

	    switch(a_AutoStateV1){
	    case kMoveToSwitch:
	        if (robotDistance < SWITCH_DISTANCE) {
	            a_DiffDrive.DriveStraight(0.6, -0.6);
	        } else {
	            a_Robot.AutonUpdate(0,0);
	            nextState = kReleaseCube;
	        }
	        break;
	    case kReleaseCube:
	        a_Robot.ReleaseCube;
	        nextState = kAutoIdle;
	        break;
	    case kAutoIdle:
	        a_Robot.AutonUpdate(0,0);
	        a_Robot.ResetEncoders();
	        break;
	    }
	    a_AutoStateV1 = nextState;
	}

	void SmokeyXI::AutonomousPeriodicV2()
	{
		const float SIDE_OF_SWITCH_DISTANCE;
		const float TURN_ANGLE;
		const float EDGE_OF_SWITCH_DISTANCE;

	    AutoStateV2 nextState = a_AutoStateV2;

	    switch(a_AutoStateV2){
	    case kMoveToSideOfSwitch:
	        if (robotDistance < SIDE_OF_SWITCH_DISTANCE) {
	            a_DiffDrive.DriveStraight(0.6, -0.6);
	        } else {
	            a_Robot.AutonUpdate(0,0);
	            nextState = kTurnLeft2;
	        }
	        break;
	    case kTurnLeft2:
			a_DiffDrive.ArcTurn(18, 90, true);
	        nextState = kMoveToEdgeOfSwitch;
	        break;
	    case kMoveToEdgeOfSwitch:
	        if (robotDistance < EDGE_OF_SWITCH_DISTANCE) {
	                    a_DiffDrive.DriveStraight(0.6, -0.6);
	                } else {
	                    a_Robot.AutonUpdate(0,0);
	                    nextState = kReleaseCube2;
	                }
	        break;
	    case kReleaseCube2:
	        a_Robot.ReleaseCube;
	        nextState = kAutoIdle2;
	        break;
	    case kAutoIdle2:
	        a_Robot.AutonUpdate(0,0);
	        a_Robot.ResetEncoders();
	        break;
	    }
	    a_AutoStateV2 = nextState;
	}

	void SmokeyXI::AutonomousPeriodicV3()
	{
		const float SIDE_OF_SCALE_DISTANCE;
		const float TURN_ANGLE3;
		const float EDGE_OF_SCALE_DISTANCE;

	    AutoStateV3 nextState = a_AutoStateV3;

	    switch(a_AutoStateV3){
	    case kMoveToSideOfScale:
	        if (robotDistance < SIDE_OF_SCALE_DISTANCE) {
	            a_DiffDrive.DriveStraight(0.6, -0.6);
	        } else {
	            a_Robot.AutonUpdate(0,0);
	            nextState = kTurnLeft3;
	        }
	        break;
	    case kTurnLeft3:
	        a_DiffDrive.ArcTurn(18, 90, true);
	        nextState = kMoveToEdgeOfScale;
	        break;
	    case kMoveToEdgeOfScale:
	        if (robotDistance < EDGE_OF_SCALE_DISTANCE) {
	                    a_DiffDrive.DriveStraight(0.6, -0.6);
	                } else {
	                    a_Robot.AutonUpdate(0,0);
	                    nextState = kReleaseCube3;
	                }
	        break;
	    case kReleaseCube3:
	        a_Robot.ReleaseCube;
	        nextState = kAutoIdle3;
	        break;
	    case kAutoIdle3:
	        a_Robot.AutonUpdate(0,0);
	        a_Robot.ResetEncoders();
	        break;
	    }
	    a_AutoStateV3 = nextState;
	}

	void SmokeyXI::AutonomousPeriodicV4()
	{
		const float HALF_OF_SWITCH_DISTANCE;
		const float TURN_ANGLE4A;
		const float FLUSH_WITH_SWITCH;
		const float TURN_ANGLE4B;
		const float FRONT_OF_SWITCH_DISTANCE;

	    AutoStateV4 nextState = a_AutoStateV4;

	    switch (a_AutoStateV4) {
	    case kMoveHalfToSwitch:
	        if (robotDistance < HALF_OF_SWITCH_DISTANCE) {
	            a_DiffDrive.DriveStraight(0.6, -0.6);
	        } else {
	            a_Robot.AutonUpdate(0, 0);
	            nextState = kTurnRight;
	        }
	        break;
	    case kTurnRight:
	        a_DiffDrive.ArcTurn(18, 90, false);
	        nextState = kMoveFlushWithSwitch;
	        break;
	    case kMoveFlushWithSwitch:
	        if (robotDistance < FLUSH_WITH_SWITCH) {
	            a_DiffDrive.DriveStraight(0.6, -0.6);
	        } else {
	            a_Robot.AutonUpdate(0, 0);
	            nextState = kTurnLeft4;
	        }
	        break;
	    case kTurnLeft4:
	        a_DiffDrive.ArcTurn(18, 90, true);
	        nextState = kMoveToFrontOfSwitch;
	        break;
	    case kMoveToFrontOfSwitch:
	        if (robotDistance < FRONT_OF_SWITCH_DISTANCE) {
	            a_DiffDrive.DriveStraight(0.6, -0.6);
	        } else {
	            a_Robot.AutonUpdate(0, 0);
	            nextState = kReleaseCube4;
	        }
	        break;
	    case kReleaseCube4:
	        a_Robot.ReleaseCube;
	        nextState = kAutoIdle4;
	        break;
	    case kAutoIdle4:
	        a_Robot.AutonUpdate(0, 0);
	        a_Robot.ResetEncoders();
	        break;
	    }
	    a_AutoStateV4 = nextState;
	}

	void SmokeyXI::AutonomousPeriodicV5()
	{
		const float TOP_OF_SWITCH_DISTANCE;
		const float TURN_ANGLE5A;
		const float FLUSH_WITH_SCALE;
		const float TURN_ANGLE5B;
		const float FRONT_OF_SCALE_DISTANCE;

	    AutoStateV5 nextState = a_AutoStateV5;

	    switch (a_AutoStateV5) {
	    case kMoveTopOfSwitch:
	        if (robotDistance < TOP_OF_SWITCH_DISTANCE) {
	            a_DiffDrive.DriveStraight(0.6, -0.6);
	        } else {
	            a_Robot.AutonUpdate(0, 0);
	            nextState = kTurnRight5;
	        }
	        break;
	    case kTurnRight5:
			a_DiffDrive.ArcTurn(10, 90, false);
	        nextState = kMoveFlushWithScale;
	        break;
	    case kMoveFlushWithScale:
	        if (robotDistance < FLUSH_WITH_SCALE) {
	            a_DiffDrive.DriveStraight(0.6, -0.6);
	        } else {
	            a_Robot.AutonUpdate(0, 0);
	            nextState = kTurnLeft5;
	        }
	        break;
	    case kTurnLeft5:
	        a_DiffDrive.ArcTurn(10, 90, true);
	        nextState = kMoveToFrontOfScale;
	        break;
	    case kMoveToFrontOfScale:
	        if (robotDistance < FRONT_OF_SCALE_DISTANCE) {
	            a_DiffDrive.DriveStraight(0.6, -0.6);
	        } else {
	            a_Robot.AutonUpdate(0, 0);
	            nextState = kReleaseCube5;
	        }
	        break;
	    case kReleaseCube5:
	        a_Robot.ReleaseCube;
	        nextState = kAutoIdle5;
	        break;
	    case kAutoIdle5:
	        a_Robot.AutonUpdate(0, 0);
	        a_Robot.ResetEncoders();
	        break;
	    }
	    a_AutoStateV5 = nextState;
	}
	*/

}

void SmokeyXI::TeleopInit()
{
	SmartDashboard::PutString("Enabled: ", "True");
	a_DiffDrive.Init();
	a_DiffDrive.SetDriveType(2); // Change the number to change drivetypes. Refer to diffdrive.cpp for help.
	a_DiffDrive.DisableMotorSafetyTraitor();
	a_Lifter.Init();
	a_CollectorArm.Init();
	a_Gyro.Cal();
	a_Compressor.SetClosedLoopControl(true);
	// a_Arduino.Write("B", 1);
}


void SmokeyXI::TeleopPeriodic()
{
	// apparently buttons aren't zero indexed, but axes are???

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

	if (a_Joystick1.GetRawButton(1) && a_Joystick2.GetRawButton(1)){
		a_CollectorArm.Update(a_Joystick1.GetRawAxis(1));
		a_CollectorArm.UpdateRollers(-1.0 * a_Joystick2.GetRawAxis(1));
	}
	else {
		a_DiffDrive.UpdateVal((-1.0 * a_Joystick1.GetRawAxis(1)), (-1.0 * a_Joystick2.GetRawAxis(1)));
	}

	// Roll the rollers ^

	/*
	if (a_Joystick1.GetRawButton(3)){
		a_DiffDrive.DriveStraight(0.6,-0.6);
	}
	if (a_Joystick2.GetRawButton(3)){
		a_DiffDrive.DriveStraight(-0.6,0.6);
	}
	*/

	/// a_DiffDrive.Update(a_GamePad, a_Joystick1, a_Joystick2, a_JoystickZ); // wonder if passing four sticks impacts latency -- if it does, i didnt notice
	
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

	SmartDashboard::PutNumber("Arm Angle Theo 1: ", a_CollectorArm.GetAngle1());
	SmartDashboard::PutNumber("Arm Angle Theo 2: ", a_CollectorArm.GetAngle2());

	SmartDashboard::PutNumber("Left Encoder Pos: ", a_DiffDrive.GetDistanceLeft());
	SmartDashboard::PutNumber("Right Encoder Pos : ", a_DiffDrive.GetDistanceRight());
	SmartDashboard::PutNumber("Left Encoder Velo: ", a_DiffDrive.GetVelocityLeft());
	SmartDashboard::PutNumber("Right Encoder Velo : ", a_DiffDrive.GetVelocityRight());
}

void SmokeyXI::TestInit()
{
	// test is currently only used to run the compressor
	SmartDashboard::PutString("Enabled: ", "True");

}

void SmokeyXI::TestPeriodic()
{
	if (a_Joystick2.GetRawButton(1)){
		a_Lifter.Update(-1); // this actually doesn't do anything to the lifter lol, it runs the compressor for now
	}
}

START_ROBOT_CLASS(SmokeyXI);
