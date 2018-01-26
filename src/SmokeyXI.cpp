#include <Prefs.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <string>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <SmokeyXI.h>

SmokeyXI::SmokeyXI(void):

a_GamePad(GAMEPAD_PORT), // this should be the gamepad - list on port 0

a_Joystick1(JOYSTICK1_PORT), // this is the flightstick without a z axis, port 1

a_Joystick2(JOYSTICK2_PORT), // this is the flightstick without a z axis, port 2

a_JoystickZ(JOYSTICKZ_PORT), // this is the flightstick WITH a z axis, port 3

a_DiffDrive(LEFT_DRIVE_TALON_ONE, LEFT_DRIVE_TALON_TWO, LEFT_DRIVE_TALON_THREE, RIGHT_DRIVE_TALON_ONE, RIGHT_DRIVE_TALON_TWO, RIGHT_DRIVE_TALON_THREE),

a_Collector(LEFT_COLLECTOR_TALON, RIGHT_COLLECTOR_TALON),

// a_CollectorArm(COLLECTOR_ARM_TALON),

a_Gyro(I2C::kMXP),

a_Arduino(BAUD_RATE_ARDUINO, SerialPort::kUSB1, DATA_BITS,  SerialPort::kParity_None, SerialPort::kStopBits_One), // USB1 is the onboard port closest to the center of the rio

a_Solenoid(PCM_PORT, SOL_PORT_ONE, SOL_PORT_TWO),

a_AutoBot(), // AutoBot Methods return true for left.

a_AutoStateV1(kAutoIdle),

a_AutoStateV2(kAutoIdle2),

a_AutoStateV3(kAutoIdle3),

a_AutoStateV4(kAutoIdle4),

a_AutoStateV5(kAutoIdle5),

a_UltraSoul()

{

}

void SmokeyXI::RobotInit()
{
	SmartDashboard::init();
	// Things go to the SmartDashboard object but I want to try and use Shuffleboard instead.
	// It uses the same method calls to the SmartDashboard, but is much cleaner and easier to interpret data that comes in.
}

void SmokeyXI::RobotPeriodic()
{

}

void SmokeyXI::DisabledInit()
{
	a_Arduino.Write("E", 1);
}

void SmokeyXI::DisabledPeriodic()
{
	SmartDashboard::PutString("Enabled: ", "False");
}

void SmokeyXI::AutonomousInit()
{
	SmartDashboard::PutString("Enabled: ", "True");
	a_Arduino.Write("N", 1); // strips off
}

void SmokeyXI::AutonomousPeriodic()
{
	// Following lines are to test AutoPeriodic and the AutoBot autohelper i wrote.
	if (a_AutoBot.GetAllianceSwitch()){
		a_Arduino.Write("B", 1); // Left side, Blue leds for indicators
		SmartDashboard::PutBoolean("Our Switch Left? ", true);
	}
	else{
		a_Arduino.Write("M", 1); // Right side, Red leds for indicators
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
	    AutoStateV1 nextState = a_AutoStateV1;

	    switch(a_AutoStateV1){
	    case kMoveToSwitch:
	        if (robotDistance < SWITCH_DISTANCE) {
	            a_Robot.AutonUpdateDriveStraight();
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
	    AutoStateV2 nextState = a_AutoStateV2;

	    switch(a_AutoStateV2){
	    case kMoveToSideOfSwitch:
	        if (robotDistance < SIDE_OF_SWITCH_DISTANCE) {
	            a_Robot.AutonUpdateDriveStraight();
	        } else {
	            a_Robot.AutonUpdate(0,0);
	            nextState = kTurnLeft2;
	        }
	        break;
	    case kTurnLeft2:
	        a_Robot.SetAngle(a_Gyro.GetAngle(), TURN_ANGLE);
	        nextState = kMoveToEdgeOfSwitch;
	        break;
	    case kMoveToEdgeOfSwitch:
	        if (robotDistance < EDGE_OF_SWITCH_DISTANCE) {
	                    a_Robot.AutonUpdateDriveStraight();
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
	    AutoStateV3 nextState = a_AutoStateV3;

	    switch(a_AutoStateV3){
	    case kMoveToSideOfScale:
	        if (robotDistance < SIDE_OF_SCALE_DISTANCE) {
	            a_Robot.AutonUpdateDriveStraight();
	        } else {
	            a_Robot.AutonUpdate(0,0);
	            nextState = kTurnLeft3;
	        }
	        break;
	    case kTurnLeft3:
	        a_Robot.SetAngle(a_Gyro.GetAngle(), TURN_ANGLE);
	        nextState = kMoveToEdgeOfScale;
	        break;
	    case kMoveToEdgeOfScale:
	        if (robotDistance < EDGE_OF_SCALE_DISTANCE) {
	                    a_Robot.AutonUpdateDriveStraight();
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

	void SmokeyXI::AutonomousPeriodicV4() {
	    AutoStateV4 nextState = a_AutoStateV4;

	    switch (a_AutoStateV4) {
	    case kMoveHalfToSwitch:
	        if (robotDistance < HALF_OF_SWITCH_DISTANCE) {
	            a_Robot.AutonUpdateDriveStraight();
	        } else {
	            a_Robot.AutonUpdate(0, 0);
	            nextState = kTurnRight;
	        }
	        break;
	    case kTurnRight:
	        a_Robot.SetAngle(a_Gyro.GetAngle(), TURN_ANGLE);
	        nextState = kMoveFlushWithSwitch;
	        break;
	    case kMoveFlushWithSwitch:
	        if (robotDistance < FLUSH_WITH_SWITCH) {
	            a_Robot.AutonUpdateDriveStraight();
	        } else {
	            a_Robot.AutonUpdate(0, 0);
	            nextState = kTurnLeft4;
	        }
	        break;
	    case kTurnLeft4:
	        a_Robot.SetAngle(a_Gyro.GetAngle(), TURN_ANGLE);
	        nextState = kMoveToFrontOfSwitch;
	        break;
	    case kMoveToFrontOfSwitch:
	        if (robotDistance < FRONT_OF_SWITCH_DISTANCE) {
	            a_Robot.AutonUpdateDriveStraight();
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

	void SmokeyXI::AutonomousPeriodicV5() {
	    AutoStateV5 nextState = a_AutoStateV5;

	    switch (a_AutoStateV5) {
	    case kMoveTopOfSwitch:
	        if (robotDistance < TOP_OF_SWITCH_DISTANCE) {
	            a_Robot.AutonUpdateDriveStraight();
	        } else {
	            a_Robot.AutonUpdate(0, 0);
	            nextState = kTurnRight5;
	        }
	        break;
	    case kTurnRight5:
	        a_Robot.SetAngle(a_Gyro.GetAngle(), TURN_ANGLE);
	        nextState = kMoveFlushWithScale;
	        break;
	    case kMoveFlushWithScale:
	        if (robotDistance < FLUSH_WITH_SCALE) {
	            a_Robot.AutonUpdateDriveStraight();
	        } else {
	            a_Robot.AutonUpdate(0, 0);
	            nextState = kTurnLeft5;
	        }
	        break;
	    case kTurnLeft5:
	        a_Robot.SetAngle(a_Gyro.GetAngle(), TURN_ANGLE);
	        nextState = kMoveToFrontOfScale;
	        break;
	    case kMoveToFrontOfScale:
	        if (robotDistance < FRONT_OF_SCALE_DISTANCE) {
	            a_Robot.AutonUpdateDriveStraight();
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
	a_DiffDrive.SetDriveType(1); // Change the number to change drivetypes. Refer to diffdrive.cpp for help.
	a_Gyro.Init();
	// a_Arduino.Write("B", 1);
}


void SmokeyXI::TeleopPeriodic()
{
	a_DiffDrive.Update(a_GamePad, a_Joystick1, a_Joystick2, a_JoystickZ); // wonder if passing four sticks impacts latency -- if it does, i didnt notice
	a_Gyro.Update();
	float gyroValue = a_Gyro.GetAngle();
	SmartDashboard::PutNumber("Gyro Angle: ", gyroValue);
	SmartDashboard::PutNumber("Gyro X", a_Gyro.GetX());
	SmartDashboard::PutNumber("Gyro Y", a_Gyro.GetY());
	SmartDashboard::PutNumber("Gyro Z", a_Gyro.GetZ());

	if (a_GamePad.GetRawButton(1)){
		a_Solenoid.Set(DoubleSolenoid::kForward);
	}
	if (a_GamePad.GetRawButton(2)){
		a_Solenoid.Set(DoubleSolenoid::kReverse);
	}
	if (a_GamePad.GetRawButton(3)){
		a_DiffDrive.GoDistance(0.2); // 10 rotations? theo af
	}
	if (a_GamePad.GetRawButton(4)){
		a_Collector.Update(a_GamePad.GetRawAxis(2)); // apparently buttons aren't zero indexed, but axes are???
	}
	else{
		a_Collector.Update(-1 * a_GamePad.GetRawAxis(3));
	}
	SmartDashboard::PutNumber("Left Encoder: ", a_DiffDrive.GetDistanceLeft());
	SmartDashboard::PutNumber("Right Encoder: ", a_DiffDrive.GetDistanceRight());
}

void SmokeyXI::TestInit()
{
	a_Arduino.Write("R", 1);
}

void SmokeyXI::TestPeriodic()
{

}

START_ROBOT_CLASS(SmokeyXI);
