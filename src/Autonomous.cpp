#include <WPILib.h>
#include <math.h>
#include "Autonomous.h"

Autonomous::Autonomous(AutonomousHelper &AutoBot, Joystick &ButtonBox, CollectorArm &CollectorArm, DiffDrive &DiffDrive, JrimmyGyro &Gyro, Underglow &Underglow, UltrasonicSerial &UltraSoul)
: a_AutoBot(AutoBot),
  a_ButtonBox(ButtonBox),
  a_CollectorArm(CollectorArm),
  a_DiffDrive(DiffDrive),
  a_Gyro(Gyro),
  a_Underglow(Underglow),
  a_UltraSoul(UltraSoul),
  a_AutoStateVx(kAutoIdlex),
  a_AutoStateU0(kAutoIdleU0),
  a_AutoStateV0(kAutoIdle0),
  a_AutoStateU1(kAutoIdleU1),
  a_AutoStateV1(kAutoIdle1),
  a_AutoStateU2(kAutoIdleU2),
  a_AutoStateV2(kAutoIdle2),
  a_AutoStateU3(kAutoIdleU3),
  a_AutoStateV3(kAutoIdle3),
  a_AutoStateU4(kAutoIdleU4),
  a_AutoStateV4(kAutoIdle4),
  a_AutoStateU5(kAutoIdleU5),
  a_AutoStateV5(kAutoIdle5),
  a_AutoStateU6(kAutoIdleU6),
  a_AutoStateU7(kAutoIdleU7)
{
	a_AngleSaved = 0.0;
	a_time_state = 0;
	autoPathMaster = -1;
	b_left = false;
	b_center = false;
	b_right = false;
	special = false;
	playerStation = -1;
	blue = false;
	ourSwitch = false;
	scale = false;
	oppSwitch = false;
}

void Autonomous::Init(){
	a_Gyro.Zero();
}

void Autonomous::DecidePath(){
	autoPathMaster = -1; // makes sure we start on a clean value
	// ButtonBox Information

	b_left = a_ButtonBox.GetRawButton(2);
	b_center = a_ButtonBox.GetRawButton(3);
	b_right = a_ButtonBox.GetRawButton(4);
	special = a_ButtonBox.GetRawButton(5); // switch with red tape

	// AutoBot Information
	playerStation = a_AutoBot.GetAllianceStation();
	blue = a_AutoBot.GetAllianceSide();
	ourSwitch = a_AutoBot.GetAllianceSwitch();
	scale = a_AutoBot.GetAllianceScale();
	oppSwitch = a_AutoBot.GetOpponentSwitch();

	/*
	 * Auton Path Documentation
	 *
	 * U0 - Drive Straight (Past Line using USonics)
	 * U1 - Drive into front of switch, raise arm, dispense switch
	 * U2 - Drive Straight on side of switch, raise arm, twist 90 in, dispense switch
	 * U3 - Drive straight on side of scale, twist 90 out, arm flicks up, dispense. this is a scale shot
	 * U4 - Drive straight for a bit, twist in, move to other side of switch, twist again, move to switch, dispense.
	 * U5 - Drive past switch, twist in, move across field to center of the side edge of scale, twist, backshot
	 * U6 - Start dead center,  forward, 45 out, forward, 45 in, to front of correct switch.
	 * U7 - Two cubes, nerd. This is the one where we go Scale-->Switch
	 *
	 */

	if (!((b_left && b_center) || (b_center && b_right) || (b_left && b_right))){ // checks for driver error
		// if two switches are down, there's an error, and the program will skip this section.
		if (b_left && ourSwitch){ // Indicates Switch on Left and Left RPos.
			// U2, turn to switch
			autoPathMaster = 2;
		} else if (b_left && scale){
			// U3 or U7 turn to scale
			if (special){
				autoPathMaster = 7;
			} else {
				autoPathMaster = 3;
			}
		} else if (b_right && !ourSwitch){ // Indicates Switch on Right and Right RPos.
			// U2, turn to switch
			autoPathMaster = 2;
		} else if (b_right && !scale){
			// U3 or U7 turn to scale
			if (special){
				autoPathMaster = 7;
			} else {
				autoPathMaster = 3;
			}
		}
		 if (b_center && !ourSwitch){ // Indicates Right of Center RPos and intent to go to front of switch.
			// U1
			autoPathMaster = 1;
		}

		 if (b_center && special){ // Indicates Dead-Center RPos and intent to do the 45-deg turns.
			// U6
			autoPathMaster = 6;
		}
	}

	if (b_left && b_center && b_right){
		// special override to execute U0
		autoPathMaster = 0;
	}
}

void Autonomous::DecidePath(int intent){
	// Call DecidePath with the param to override the decision structure.
	autoPathMaster = intent;
}

int Autonomous::GetCurrentPath(){
	return autoPathMaster;
}

void Autonomous::StartPathMaster(){
	switch(autoPathMaster){
		case -1:
			// Error!
			SmartDashboard::PutBoolean("Auto Started", false);
			a_Underglow.GoRed();
			break;
		case 0:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.MagentaLaser();
			AutonomousStartU0();
			break;
		case 1:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.BlueLaser();
			AutonomousStartU1();
			break;
		case 2:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.YellowLaser();
			AutonomousStartU2();
			break;
		case 3:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.CyanLaser();
			AutonomousStartU3();
			break;
		case 4:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.CyanLaser();
			AutonomousStartU4();
			break;
		case 5:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.CyanLaser();
			AutonomousStartU5();
			break;
		case 6:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.CyanLaser();
			AutonomousStartU6();
			break;
		case 7:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.RedLaser();
			AutonomousStartU7();
			break;
	}
}

void Autonomous::StartPathMaster(int path){
	switch(path){
		case -1:
			// Error!
			SmartDashboard::PutBoolean("Auto Started", false);
			a_Underglow.GoRed();
			break;
		case 0:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.MagentaLaser();
			AutonomousStartU0();
			break;
		case 1:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.BlueLaser();
			AutonomousStartU1();
			break;
		case 2:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.YellowLaser();
			AutonomousStartU2();
			break;
		case 3:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.CyanLaser();
			AutonomousStartU3();
			break;
		case 4:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.CyanLaser();
			AutonomousStartU4();
			break;
		case 5:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.CyanLaser();
			AutonomousStartU5();
			break;
		case 6:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.CyanLaser();
			AutonomousStartU6();
			break;
		case 7:
			SmartDashboard::PutBoolean("Auto Started", true);
			a_Underglow.RedLaser();
			AutonomousStartU7();
			break;
	}
}

void Autonomous::PeriodicPathMaster(){
	switch(autoPathMaster){
		case -1:
			// Error!
			break;
		case 0:
			AutonomousPeriodicU0();
			break;
		case 1:
			AutonomousPeriodicU1();
			break;
		case 2:
			AutonomousPeriodicU2();
			break;
		case 3:
			AutonomousPeriodicU3();
			break;
		case 4:
			AutonomousPeriodicU4();
			break;
		case 5:
			AutonomousPeriodicU5();
			break;
		case 6:
			AutonomousPeriodicU6();
			break;
		case 7:
			AutonomousPeriodicU7();
			break;
	}
}

void Autonomous::PeriodicPathMaster(int path){
	switch(path){
		case -1:
			// Error!
			break;
		case 0:
			AutonomousPeriodicU0();
			break;
		case 1:
			AutonomousPeriodicU1();
			break;
		case 2:
			AutonomousPeriodicU2();
			break;
		case 3:
			AutonomousPeriodicU3();
			break;
		case 4:
			AutonomousPeriodicU4();
			break;
		case 5:
			AutonomousPeriodicU5();
			break;
		case 6:
			AutonomousPeriodicU6();
			break;
		case 7:
			AutonomousPeriodicU7();
			break;
	}
}

void Autonomous::AutonomousStartU0()
{
	a_AutoStateU0 = kMoveToSwitchU0;
	a_Gyro.Zero();
}

void Autonomous::AutonomousPeriodicU0()
{
	AutoStateU0 nextState = a_AutoStateU0;

	switch(a_AutoStateU0){
	case kAutoIdleU0:
		a_DiffDrive.UpdateVal(0,0);
		a_DiffDrive.ZeroEncoders();
		a_Gyro.Zero();
		break;

	case kMoveToSwitchU0:
		if (a_UltraSoul.GetRearRight() < (SWITCH_DISTANCE-BOT_LENGTH_BUMPERS)) {
			if (a_UltraSoul.GetRearRight() > (0.50 * (SWITCH_DISTANCE-BOT_LENGTH_BUMPERS))){
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
			} else {
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_HIGH);
			}
		} else {
			SmartDashboard::PutNumber("ENCODER DUMP LEFt", a_DiffDrive.GetDistanceLeft());
			SmartDashboard::PutNumber("ENCODER DUMP Right", a_DiffDrive.GetDistanceRight());
			SmartDashboard::PutNumber("Ultradump right", a_UltraSoul.GetRearRight());
			a_DiffDrive.UpdateVal(0,0);
			nextState = kAutoIdleU0;
		}
		break;
	}
	a_AutoStateU0 = nextState;
}

void Autonomous::AutonomousStartU1()
{
	a_AutoStateU1 = kMoveToSwitchU1;
	a_Gyro.Zero();
	x_T = a_DiffDrive.gettime_d();
	x_Dist = a_DiffDrive.GetAvgDistance();
}

void Autonomous::AutonomousPeriodicU1()
{
	AutoStateU1 nextState = a_AutoStateU1;

	switch(a_AutoStateU1){
	case kAutoIdleU1:
		a_DiffDrive.UpdateVal(0,0);
		a_CollectorArm.UpdateValue(0.0);
		a_DiffDrive.ZeroEncoders();
		break;

	case kMoveToSwitchU1:
		// move arm while moving bot
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		/*
		if ((a_DiffDrive.gettime_d() - x_T) > 2.5){
			a_CollectorArm.RollerPos(1); // send to middle
			a_DiffDrive.UpdateVal(0,0);
			SmartDashboard::PutNumber("ENCODER DUMP 222", a_DiffDrive.GetAvgDistance());
			nextState = kMoveArmU1;
			a_Underglow.CyanLaser();
			break;
		}
		*/

		if (a_DiffDrive.GetAvgDistance() < (SWITCH_DISTANCE - BOT_LENGTH_BUMPERS)){
			if ((a_DiffDrive.GetAvgDistance() - x_Dist) > 6.0){
				x_Dist = a_DiffDrive.GetAvgDistance();
				x_T = a_DiffDrive.gettime_d();
			}

			if (a_DiffDrive.GetAvgDistance() > (0.75 * (SWITCH_DISTANCE - BOT_LENGTH_BUMPERS))){
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
			} else {
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_HIGH);
			}
		} else {
			a_CollectorArm.RollerPos(1); // send to middle
			a_DiffDrive.UpdateVal(0,0);
			SmartDashboard::PutNumber("ENCODER DUMP LEFt", a_DiffDrive.GetDistanceLeft());
			SmartDashboard::PutNumber("ENCODER DUMP Right", a_DiffDrive.GetDistanceRight());
			SmartDashboard::PutNumber("Ultradump right", a_UltraSoul.GetRearRight());
			nextState = kMoveArmU1;
			a_Underglow.CyanLaser();
		}
		break;

	case kMoveArmU1:
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		a_DiffDrive.UpdateVal(0,0);
		if(a_CollectorArm.GetAngle2() >= (SWITCH_ANGLE * 0.9)) {
			nextState = kReleaseCubeU1;
			a_time_state = a_DiffDrive.gettime_d();
		}
		break;

	case kReleaseCubeU1:
		if(a_DiffDrive.gettime_d() - a_time_state > 1.0) {
			a_CollectorArm.UpdateRollers(AUTON_ROLLER_SPEED_SWITCH);
		}
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		a_DiffDrive.UpdateVal(0,0);
		// have rollers been running long enough?
		if(a_DiffDrive.gettime_d() - a_time_state > 1.5) {
			a_CollectorArm.UpdateRollers(0.0);
			a_Underglow.GreenLaser();
			nextState = kAutoIdleU1;
		}
		break;
	}
	a_AutoStateU1 = nextState;
}

void Autonomous::AutonomousStartU2()
{
	a_AutoStateU2 = kMoveToSideOfSwitchU2;
	a_Gyro.Zero();
	a_time_state = a_DiffDrive.gettime_d();
}

void Autonomous::AutonomousPeriodicU2()
{
	AutoStateU2 nextState = a_AutoStateU2;

	switch(a_AutoStateU2){
	case kAutoIdleU2:
		a_DiffDrive.UpdateVal(0,0);
		a_CollectorArm.UpdateValue(0.0);
		a_DiffDrive.ZeroEncoders();
		break;

	case kMoveToSideOfSwitchU2:
		a_DiffDrive.UpdateVal(0,0);
		if (a_UltraSoul.GetRearRight() < (SWITCH_DISTANCE - BOT_LENGTH_BUMPERS)) { // shoestring, fix this in the future u dummy
			if (a_UltraSoul.GetRearRight() > (0.75 * (SWITCH_DISTANCE - BOT_LENGTH_BUMPERS))){
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
				a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05); // raise arm sooner
			} else {
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_HIGH);
			}
		} else {
			SmartDashboard::PutNumber("ENCODER DUMP LEFt", a_DiffDrive.GetDistanceLeft());
			SmartDashboard::PutNumber("ENCODER DUMP Right", a_DiffDrive.GetDistanceRight());
			SmartDashboard::PutNumber("Ultradump right", a_UltraSoul.GetRearRight());
			a_DiffDrive.ZeroEncoders();
			a_DiffDrive.UpdateVal(0,0);
			nextState = kTurnNinetyU2;
			a_Underglow.GreenLaser();
		}
		break;

	case kTurnNinetyU2:
		// move arm while moving bot
		if ((a_DiffDrive.gettime_d() - a_time_state) <= ARM_TIMEOUT_SECONDS){
			a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		}
		a_CollectorArm.RollerPos(1); // move to middle pos
		if (b_left && ourSwitch){
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), -90.0)){
				SmartDashboard::PutNumber("ENCODER DUMP 111", a_DiffDrive.GetAvgDistance());
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				nextState = kMoveArmU2;
				if (a_AutoBot.GetAllianceSide()){
					a_Underglow.BlueLaser();
				}
				else{
					a_Underglow.RedLaser();
				}
			} else {
				// a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), -90.0);
				// might not be even needed because short-circuit in code makes the motors still run
			}
		}
		else if (b_right && !ourSwitch){
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 90.0)) {
				SmartDashboard::PutNumber("ENCODER DUMP 111", a_DiffDrive.GetAvgDistance());
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				nextState = kMoveArmU2;
				if (a_AutoBot.GetAllianceSide()){
					a_Underglow.BlueLaser();
				}
				else{
					a_Underglow.RedLaser();
				}
			}
			else{
				// a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 90.0);
				// might not be even needed because short-circuit in code makes the motors still run
			}
		}
		break;

	case kMoveToEdgeOfSwitchU2:
		if (((a_DiffDrive.gettime_d() - a_time_state)) <= ARM_TIMEOUT_SECONDS){
			a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		}
		a_CollectorArm.RollerPos(2); // send to collect
		if (a_UltraSoul.GetRearRight() < (EDGE_OF_SWITCH_DISTANCE - BOT_LENGTH_BUMPERS)) {
			if (a_UltraSoul.GetRearRight() > (0.8 * (EDGE_OF_SWITCH_DISTANCE - BOT_LENGTH_BUMPERS))){
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), -90.0, DRIVE_STRAIGHT_LOW);
			} else {
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 90.0, DRIVE_STRAIGHT_HIGH);
			}
		} else {
			a_DiffDrive.UpdateVal(0,0);
			nextState = kMoveArmU2;
		}
		break;

	case kMoveArmU2:
		if (((a_DiffDrive.gettime_d() - a_time_state)) <= 15.0){
			a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		}
		if(a_CollectorArm.GetAngle2() >= (SWITCH_ANGLE * 0.9)) {
			nextState = kReleaseCubeU2;
			a_time_state = a_DiffDrive.gettime_d();
		}
		break;

	case kReleaseCubeU2:
		if(a_DiffDrive.gettime_d() - a_time_state > 0.3) { // wait a bit for collector pos to update
			a_CollectorArm.UpdateRollers(AUTON_ROLLER_SPEED_SWITCH);
		}
		// have rollers been running long enough?
		if(a_DiffDrive.gettime_d() - a_time_state > 0.8) {
			a_CollectorArm.UpdateRollers(0.0);
			a_Underglow.GreenLaser();
			nextState = kAutoIdleU2;
		}
		break;
	}
	a_AutoStateU2 = nextState;
}

void Autonomous::AutonomousStartU3()
{
	a_AutoStateU3 = kMoveToSideOfScaleU3;
	a_Gyro.Zero();
}

void Autonomous::AutonomousPeriodicU3()
{
	AutoStateU3 nextState = a_AutoStateU3;

	switch(a_AutoStateU3){
	case kAutoIdleU3:
		a_DiffDrive.UpdateVal(0,0);
		a_DiffDrive.ZeroEncoders();
		a_Gyro.Zero();
		break;

	case kMoveToSideOfScaleU3:
		if (a_DiffDrive.GetAvgDistance() < (SIDE_OF_SCALE_DISTANCE - BOT_LENGTH_BUMPERS)) {
			if (a_DiffDrive.GetAvgDistance() > (0.30 * (SIDE_OF_SCALE_DISTANCE - BOT_LENGTH_BUMPERS))){
				if (a_DiffDrive.GetAvgDistance() > (0.10 * (SIDE_OF_SCALE_DISTANCE - BOT_LENGTH_BUMPERS))){
					a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, 0.2);
					a_CollectorArm.RollerPos(1); // 45 deg
				}
				else{
					a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
				}
				a_CollectorArm.UpdateArmAngleSimple(SCALE_ANGLE, 0.05); // raise the arm sooner
			} else {
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_HIGH);
			}
		} else {
			a_DiffDrive.ZeroEncoders();
			a_DiffDrive.UpdateVal(0,0);
			a_Underglow.GreenLaser();
			nextState = kMoveArmU3;
		}
		break;

	case kMoveArmU3:
		a_CollectorArm.UpdateArmAngleSimple(SCALE_ANGLE, 0.05);
		a_CollectorArm.RollerPos(2); // collect
		if(a_CollectorArm.GetAngle2() >= (0.95 * SCALE_ANGLE)) {
			nextState = kTurnNinetyU3;
		}
		break;

	case kTurnNinetyU3:
		// move arm while moving bot
		a_CollectorArm.UpdateArmAngleSimple(SCALE_ANGLE, 0.05);
		a_DiffDrive.UpdateVal(0,0);
		if (b_left && scale){
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 90.0)) {
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				a_time_state = a_DiffDrive.gettime_d();
				nextState = kReleaseCubeU3;
			}
			else{
				// a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 90.0);
				// might not be even needed because short-circuit in code makes the motors still run
			}
		}
		else if (b_right && !scale){
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), -90.0)) {
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				a_time_state = a_DiffDrive.gettime_d();
				nextState = kReleaseCubeU3;
			}
			else{
				// a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), -90.0);
				// might not be even needed because short-circuit in code makes the motors still run
			}
		}
		break;

	case kMoveToEdgeOfScaleU3:
		// move arm while moving bot
		a_CollectorArm.UpdateArmAngleSimple(SCALE_ANGLE, 0.05);
		if (a_UltraSoul.GetRearRight() < (EDGE_OF_SCALE_DISTANCE - BOT_LENGTH_BUMPERS)) {
			if (a_UltraSoul.GetRearRight() > (0.25 * (EDGE_OF_SCALE_DISTANCE - BOT_LENGTH_BUMPERS))){
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, (-1.0 * DRIVE_STRAIGHT_LOW));
			} else {
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, (-1.0 * DRIVE_STRAIGHT_HIGH));
			}
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kMoveArmU3;
		}
		break;

	case kReleaseCubeU3:
		if(a_DiffDrive.gettime_d() - a_time_state > 0.7) { // wait a bit for collector pos to update
			a_CollectorArm.UpdateRollers(AUTON_ROLLER_SPEED_SCALE);
		}
		// have rollers been running long enough?
		if(a_DiffDrive.gettime_d() - a_time_state > 1.2) {
			a_CollectorArm.UpdateRollers(0.0);
			nextState = kAutoIdleU3;
		}
		break;
	}
	a_AutoStateU3 = nextState;
}

void Autonomous::AutonomousStartU4()
{
	a_AutoStateU4 = kMoveHalfToSwitchU4;
	a_Gyro.Zero();
}

void Autonomous::AutonomousPeriodicU4()
{
	AutoStateU4 nextState = a_AutoStateU4;

	switch (a_AutoStateU4) {
	case kAutoIdleU4:
		a_DiffDrive.UpdateVal(0,0);
		a_DiffDrive.ZeroEncoders();
		break;

	case kMoveHalfToSwitchU4:
		if (a_UltraSoul.GetRearRight() < (HALF_OF_SWITCH_DISTANCE - BOT_LENGTH_BUMPERS)) {
			if (a_UltraSoul.GetRearRight() > (0.5 * (HALF_OF_SWITCH_DISTANCE - BOT_LENGTH_BUMPERS))){
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
			} else {
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_HIGH);
			}
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			a_Gyro.Zero();
			nextState = kTurnNinetyU4;
		}
		break;

	case kTurnNinetyU4:
		if (b_left){ // turn in, theo
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), -90.0)) {
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				nextState = kCenterWithSwitchU4;
			}
			else{
				// a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), -90.0);
				// might not be even needed because short-circuit in code makes the motors still run
			}
		}
		else if (b_right){ // turn in, theo
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 90.0)) {
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				nextState = kCenterWithSwitchU4;
			}
			else{
				// a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 90.0);
				// might not be even needed because short-circuit in code makes the motors still run
			}
		}
		break;

	case kCenterWithSwitchU4:
		if (a_UltraSoul.GetFrontLeft() < (FLUSH_WITH_SWITCH - BOT_LENGTH_BUMPERS)) {
			if (a_UltraSoul.GetRearRight() > (0.5 * (FLUSH_WITH_SWITCH - BOT_LENGTH_BUMPERS))){
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
			} else {
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_HIGH);
			}
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			a_Gyro.Zero();
			nextState = kTurnNinetyOppositeU4;
		}
		break;

	case kTurnNinetyOppositeU4:
		// move arm while moving bot
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		if (b_left){ // turn out, theo
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), -90.0)) {
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				a_Gyro.Zero();
				nextState = kMoveToFrontOfSwitchU4;
			}
			else{
				a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), -90.0);
				// might not be even needed because short-circuit in code makes the motors still run
			}
		}
		else if (b_right){ // turn out, theo
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 90.0)) {
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				a_Gyro.Zero();
				nextState = kMoveToFrontOfSwitchU4;
			}
			else{
				a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 90.0);
				// might not be even needed because short-circuit in code makes the motors still run
			}
		}
		break;

	case kMoveToFrontOfSwitchU4:
		// move arm while moving bot
		// may need the fancy timeout. we'll see if the extra bot length sub makes it go correctly
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		if (a_UltraSoul.GetRearRight() < (FRONT_OF_SWITCH_DISTANCE - BOT_LENGTH_BUMPERS)) {
			if (a_UltraSoul.GetRearRight() > (0.5 * (FRONT_OF_SWITCH_DISTANCE - BOT_LENGTH_BUMPERS))){
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
			} else {
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_HIGH);
			}
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kMoveArmU4;
		}
		break;

	case kMoveArmU4:
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		if(a_CollectorArm.GetAngle2() >= SWITCH_ANGLE) {
			nextState = kReleaseCubeU4;
			a_time_state = a_DiffDrive.gettime_d();
		}
		break;

	case kReleaseCubeU4:
		if(a_DiffDrive.gettime_d() > 1.0) { // wait 1 sec for collector pos to update
			a_CollectorArm.UpdateRollers(AUTON_ROLLER_SPEED_SWITCH);
		}
		// have rollers been running long enough?
		if(a_DiffDrive.gettime_d() - a_time_state > 1.5) {
			a_CollectorArm.UpdateRollers(0.0);
			nextState = kAutoIdleU4;
		}
		break;
	}
	a_AutoStateU4 = nextState;
}

void Autonomous::AutonomousStartU5()
{
	a_AutoStateU5 = kMoveTopOfSwitchU5;
}

void Autonomous::AutonomousPeriodicU5()
{
	AutoStateU5 nextState = a_AutoStateU5;

	switch (a_AutoStateU5) {
	case kAutoIdleU5:
		a_DiffDrive.UpdateVal(0,0);
		a_DiffDrive.ZeroEncoders();
		a_Gyro.Zero();
		break;

	case kMoveTopOfSwitchU5:
		if (a_UltraSoul.GetRearRight() < (TOP_OF_SWITCH_DISTANCE - BOT_LENGTH_BUMPERS)) {
			if (a_UltraSoul.GetRearRight() > (0.75 * (TOP_OF_SWITCH_DISTANCE - BOT_LENGTH_BUMPERS))){
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
			} else {
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_HIGH);
			}
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kTurnNinetyU5;
			a_Gyro.Zero();
		}
		break;

	case kTurnNinetyU5:
			nextState = kMoveFlushWithScaleU5;
		break;

	case kMoveFlushWithScaleU5:
		if (a_UltraSoul.GetFrontLeft() > FLUSH_WITH_SWITCH) {
			if (a_UltraSoul.GetFrontLeft() < (0.25 * (FLUSH_WITH_SWITCH - BOT_LENGTH_BUMPERS))){
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
			} else {
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_HIGH);
			}
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kTurnNinetyOppositeU5;
			a_Gyro.Zero();
		}
		break;

	case kTurnNinetyOppositeU5:
			// move arm while moving bot
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
			nextState = kMoveToFrontOfScaleU5;
		break;

	case kMoveToFrontOfScaleU5:
		// move arm while moving bot
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		if (a_UltraSoul.GetRearRight() < FRONT_OF_SCALE_DISTANCE) {
			a_DiffDrive.DriveStraightEncoder(LEFT_AGGRO, RIGHT_AGGRO, 0.4);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kMoveArmU5;
		}
		break;

	case kMoveArmU5:
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		if(a_CollectorArm.GetAngle2() >= SWITCH_ANGLE) {
			nextState = kReleaseCubeU5;
			a_time_state = a_DiffDrive.gettime_d();
		}
		break;

	case kReleaseCubeU5:
		a_CollectorArm.UpdateRollers(-1.0);
		// have rollers been running long enough?
		if(a_DiffDrive.gettime_d() - a_time_state > 0.5) {
			a_CollectorArm.UpdateRollers(0.0);
			nextState = kAutoIdleU5;
		}
		break;
	}
	a_AutoStateU5 = nextState;
}

void Autonomous::AutonomousStartU6()
{
	a_AutoStateU6 = kMoveForwardThirdU6;
	a_Gyro.Zero();
}

void Autonomous::AutonomousPeriodicU6()
{
	AutoStateU6 nextState = a_AutoStateU6;

	switch (a_AutoStateU6) {
	case kAutoIdleU6:
		a_DiffDrive.UpdateVal(0,0);
		a_DiffDrive.ZeroEncoders();
		a_Gyro.Zero();
		break;

	case kMoveForwardThirdU6:
		if (a_DiffDrive.GetAvgDistance() < HALF_OF_SWITCH_DISTANCE) {
			a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
			SmartDashboard::PutNumber("AutoStateDebug", 1);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			SmartDashboard::PutNumber("AutoStateDebug", 2);
			nextState = kTurnFourtyFiveU6;
		}
		break;

	case kTurnFourtyFiveU6:
		// move arm while moving bot
		a_DiffDrive.UpdateVal(0,0);
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		a_CollectorArm.RollerPos(1); // move to middle pos
		SmartDashboard::PutNumber("AutoStateDebug", 8);
		SmartDashboard::PutBoolean("AutoStateLeft", b_left);
		SmartDashboard::PutBoolean("AutoStateRight", b_right);
		if (ourSwitch){ // switch on left side~
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), -45.0)){
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				SmartDashboard::PutNumber("AutoStateDebug", 4);
				nextState = kMoveDiagU6;
			} else {
				a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), -45.0);
				// might not be even needed bbecause short-circuit in code makes the motors still run
			}
			SmartDashboard::PutNumber("AutoStateDebug", 3);
		} else if (!ourSwitch) { // switch on right side~
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 45.0)) {
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				SmartDashboard::PutNumber("AutoStateDebug", 4);
				nextState = kMoveDiagU6;
			} else {
				a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 45.0);
				// might not be even needed because short-circuit in code makes the motors still run
			}
			SmartDashboard::PutNumber("AutoStateDebug", 3);
		}
		break;

	case kMoveDiagU6:
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		SmartDashboard::PutNumber("AutoStateDebug", 5);
		if (a_DiffDrive.GetAvgDistance() < FLUSH_WITH_SWITCH) {
			a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			a_Gyro.Zero();
			nextState = kTurnFourtyFiveOppositeU6;
		}
		break;

	case kTurnFourtyFiveOppositeU6:
		// move arm while moving bot
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		if (ourSwitch){
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 45.0)){
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				nextState = kMoveToFrontOfSwitchU6;
			} else {
				// a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), -90.0);
				// might not be even needed because short-circuit in code makes the motors still run
			}
		} else if (!ourSwitch) {
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), -45.0)) {
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				nextState = kMoveToFrontOfSwitchU6;
			} else {
				// a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 90.0);
				// might not be even needed because short-circuit in code makes the motors still run
			}
		}
		break;

	case kMoveToFrontOfSwitchU6:
		// move arm while moving bot
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		if (a_DiffDrive.GetAvgDistance() < FRONT_OF_SWITCH_DISTANCE) {
			a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kMoveArmU6;
		}
		break;

	case kMoveArmU6:
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		if(a_CollectorArm.GetAngle2() >= (0.95 * SWITCH_ANGLE)) {
			nextState = kReleaseCubeU6;
			a_time_state = a_DiffDrive.gettime_d();
		}
		break;

	case kReleaseCubeU6:
		a_CollectorArm.UpdateRollers(AUTON_ROLLER_SPEED_SWITCH);
		// have rollers been running long enough?
		if(a_DiffDrive.gettime_d() - a_time_state > 0.5) {
			a_CollectorArm.UpdateRollers(0.0);
			nextState = kAutoIdleU6;
		}
		break;
	}
	a_AutoStateU6 = nextState;
}

void Autonomous::AutonomousStartU7()
{
	a_AutoStateU7 = kMoveToScaleU7;
	a_Gyro.Zero();
}

void Autonomous::AutonomousPeriodicU7()
{
	AutoStateU7 nextState = a_AutoStateU7;

	switch(a_AutoStateU7){
	case kAutoIdleU7:
		a_DiffDrive.UpdateVal(0,0);
		a_CollectorArm.UpdateValue(0.0);
		a_DiffDrive.ZeroEncoders();
		a_Gyro.Zero();
		break;

	case kMoveToScaleU7:
		if (a_DiffDrive.GetAvgDistance() < (SIDE_OF_SCALE_DISTANCE - BOT_LENGTH_BUMPERS)) {
			if (a_DiffDrive.GetAvgDistance() > (0.30 * (SIDE_OF_SCALE_DISTANCE - BOT_LENGTH_BUMPERS))){
				if (a_DiffDrive.GetAvgDistance() > (0.10 * (SIDE_OF_SCALE_DISTANCE - BOT_LENGTH_BUMPERS))){
					a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, 0.2);
					a_CollectorArm.RollerPos(1); // 45 deg
				}
				else{
					a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
				}
				a_CollectorArm.UpdateArmAngleSimple(SCALE_ANGLE, 0.05); // raise the arm sooner
			} else {
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_HIGH);
			}
		} else {
			a_DiffDrive.ZeroEncoders();
			a_DiffDrive.UpdateVal(0,0);
			a_Underglow.GreenLaser();
			nextState = kMoveArmScaleU7;
		}
		break;
	
	case kMoveArmScaleU7:
		a_CollectorArm.UpdateArmAngleSimple(SCALE_ANGLE, 0.05);
		a_DiffDrive.UpdateVal(0,0);
		a_CollectorArm.RollerPos(2); // collect
		if(a_CollectorArm.GetAngle2() >= (0.95 * SCALE_ANGLE)){
			nextState = kTurnNinetyU7;
		}
		break;

	case kTurnNinetyU7:
		// move arm while moving bot
		a_CollectorArm.UpdateArmAngleSimple(SCALE_ANGLE, 0.05);
		a_DiffDrive.UpdateVal(0,0);
		if (b_left){
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 90.0)){
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				a_time_state = a_DiffDrive.gettime_d();
				nextState = kReleaseCubeScaleU7;	
				if (a_AutoBot.GetAllianceSide()){
					a_Underglow.BlueLaser();
				}
				else{
					a_Underglow.RedLaser();
				}
			} else {
				// a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), -90.0);
				// might not be even needed because short-circuit in code makes the motors still run
			}
		}
		else if (b_right){
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), -90.0)) {
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				a_time_state = a_DiffDrive.gettime_d();
				nextState = kReleaseCubeScaleU7;
				if (a_AutoBot.GetAllianceSide()){
					a_Underglow.BlueLaser();
				}
				else{
					a_Underglow.RedLaser();
				}
			}
			else{
				// a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 90.0);
				// might not be even needed because short-circuit in code makes the motors still run
			}
		}
		break;

	case kMoveToEdgeOfScaleU7:
		// move arm while moving bot
		a_CollectorArm.UpdateArmAngleSimple(SCALE_ANGLE, 0.05);
		if (a_DiffDrive.GetAvgDistance() < (SEVEN_MOVE_BACK_SCALE_DIST - BOT_LENGTH_BUMPERS)) {
			if (a_DiffDrive.GetAvgDistance() > (0.25 * (SEVEN_MOVE_BACK_SCALE_DIST - BOT_LENGTH_BUMPERS))){
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
			} else {
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_HIGH);
			}
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kReleaseCubeScaleU7;
		}
		break;

	case kReleaseCubeScaleU7:
		// time based approach
		if(a_DiffDrive.gettime_d() - a_time_state > 0.1) { // wait a bit for collector pos to update
			a_CollectorArm.UpdateRollers(AUTON_ROLLER_SPEED_SCALE);
		}
		// have rollers been running long enough?
		if(a_DiffDrive.gettime_d() - a_time_state > 0.6) {
			a_CollectorArm.UpdateRollers(0.0);
			nextState = kAutoIdleU7; // short circuit to make it like U3
		}
		/*
		// Beam Break Approach
		if (a_CollectorArm.CubePresent()){
			a_CollectorArm.UpdateRollers(0.0);
			nextState = kTurnToSwitchU7;
			a_CollectorArm.Clamp();
			a_DiffDrive.UpdateVal(0,0);
		}
		a_CollectorArm.UpdateRollers(0.5);
		a_CollectorArm.Release();
		a_DiffDrive.UpdateVal(0,0);
		*/
		break;

	case kTurnToSwitchU7:
		// move arm while moving bot
		a_CollectorArm.UpdateArmAngleSimple(REST_ANGLE, 0.05);
		a_CollectorArm.RollerPos(1); // move to collect pos
		if (b_left){
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 100.0)){
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				nextState = kMoveToSwitchU7;
				if (a_AutoBot.GetAllianceSide()){
					a_Underglow.BlueLaser();
				}
				else{
					a_Underglow.RedLaser();
				}
			} else {
				// a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), -90.0);
				// might not be even needed because short-circuit in code makes the motors still run
			}
		}
		else if (b_right){
			if(a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 100.0)) {
				a_DiffDrive.UpdateVal(0,0);
				a_DiffDrive.ZeroEncoders();
				nextState = kMoveToSwitchU7;
				if (a_AutoBot.GetAllianceSide()){
					a_Underglow.BlueLaser();
				}
				else{
					a_Underglow.RedLaser();
				}
			}
			else{
				// a_DiffDrive.UpdateAngle(a_Gyro.GetAngle(2), 90.0);
				// might not be even needed because short-circuit in code makes the motors still run
			}
		}
		break;
	case kMoveToSwitchU7:
		// move arm while moving bot
		a_CollectorArm.UpdateArmAngleSimple(REST_ANGLE, 0.05);
		if (a_UltraSoul.GetFrontRight() < (SEVEN_TO_SWITCH_DISTANCE - BOT_LENGTH_BUMPERS)) {
			if (a_UltraSoul.GetFrontRight() > (0.75 * (SEVEN_TO_SWITCH_DISTANCE - BOT_LENGTH_BUMPERS))){
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
			} else {
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_HIGH);
			}
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kMoveArmRestU7;
		}
		break;
	case kMoveArmRestU7:
		a_CollectorArm.UpdateArmAngleSimple(REST_ANGLE, 0.05);
		if(a_CollectorArm.GetAngle2() >= REST_ANGLE) {
			nextState = kCollectCubeU7;
			a_time_state = a_DiffDrive.gettime_d();
		}
		break;
	case kCollectCubeU7:
		a_CollectorArm.UpdateArmAngleSimple(REST_ANGLE, 0.05);
		if (a_CollectorArm.CubePresent()){
			a_CollectorArm.UpdateRollers(0.0);
			nextState = kMoveBackU7;
			a_CollectorArm.Clamp();
			a_DiffDrive.UpdateVal(0,0);
		}
		a_CollectorArm.UpdateRollers(0.5);
		a_CollectorArm.Release();
		a_DiffDrive.UpdateVal(0,0);
		break;
	case kMoveBackU7:
		// move arm while moving bot
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		if (a_UltraSoul.GetFrontRight() < (SEVEN_MOVE_BACK_SWITCH_DIST - BOT_LENGTH_BUMPERS)) {
			if (a_UltraSoul.GetFrontRight() > (0.75 * (SEVEN_MOVE_BACK_SWITCH_DIST - BOT_LENGTH_BUMPERS))){
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_LOW);
			} else {
				a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, DRIVE_STRAIGHT_HIGH);
			}
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kMoveArmSwitchU7;
		}
		break;
	case kMoveArmSwitchU7:
		a_CollectorArm.UpdateArmAngleSimple(SWITCH_ANGLE, 0.05);
		if(a_CollectorArm.GetAngle2() >= SWITCH_ANGLE) {
			nextState = kReleaseCubeSwitchU7;
			a_time_state = a_DiffDrive.gettime_d();
		}
		break;
	case kReleaseCubeSwitchU7:
		// time based approach
		if(a_DiffDrive.gettime_d() - a_time_state > 0.1) { // wait a bit for collector pos to update
			a_CollectorArm.UpdateRollers(AUTON_ROLLER_SPEED_SWITCH);
		}
		// have rollers been running long enough?
		if(a_DiffDrive.gettime_d() - a_time_state > 0.6) {
			a_CollectorArm.UpdateRollers(0.0);
			nextState = kAutoIdleU7;
		}
		break;

	a_AutoStateU7 = nextState;

	}
}

void Autonomous::AutonomousPeriodicV0()
{
    AutoStateV0 nextState = a_AutoStateV0;

    switch(a_AutoStateV0){
    case kMoveToSwitch0:
        if (a_DiffDrive.GetAvgDistance() < SWITCH_DISTANCE) {
			a_DiffDrive.DriveStraightEncoder(LEFT_AGGRO, RIGHT_AGGRO, 0.4);
        } else {
            a_DiffDrive.UpdateVal(0,0);
            nextState = kAutoIdle0;
        }
        break;
    case kAutoIdle0:
        a_DiffDrive.UpdateVal(0,0);
        a_DiffDrive.ZeroEncoders();
        break;
    }
    a_AutoStateV0 = nextState;
}

void Autonomous::AutonomousPeriodicV1()
{
    AutoStateV1 nextState = a_AutoStateV1;

    switch(a_AutoStateV1){
    case kMoveToSwitch1:
        if (a_DiffDrive.GetAvgDistance() < SWITCH_DISTANCE) {
        	a_DiffDrive.DriveStraightEncoder(LEFT_AGGRO, RIGHT_AGGRO, 0.4);
        } else {
            a_DiffDrive.UpdateVal(0,0);
            nextState = kMoveArm1;
        }
        break;
    case kMoveArm1:
    	a_CollectorArm.UpdateAngle(60);
    	nextState = kReleaseCube1;
    	break;
    case kReleaseCube1:
    	a_CollectorArm.UpdateRollers(-1.0);
        nextState = kAutoIdle1;
        break;
    case kAutoIdle1:
        a_DiffDrive.UpdateVal(0,0);
        a_DiffDrive.ZeroEncoders();
        break;
    }
    a_AutoStateV1 = nextState;
}

void Autonomous::AutonomousPeriodicV2()
{
    AutoStateV2 nextState = a_AutoStateV2;

    switch(a_AutoStateV2){
    case kMoveToSideOfSwitch:
        if (a_DiffDrive.GetAvgDistance() < SIDE_OF_SWITCH_DISTANCE) {
        	a_DiffDrive.DriveStraightEncoder(LEFT_AGGRO, RIGHT_AGGRO, 0.4);
        } else {
            a_DiffDrive.UpdateVal(0,0);
            a_DiffDrive.ZeroEncoders();
            nextState = kTurnLeft2;
        }
        break;
    case kTurnLeft2:
		a_DiffDrive.ZeroEncoders();
        nextState = kMoveToEdgeOfSwitch;
        break;
    case kMoveToEdgeOfSwitch:
        if (a_DiffDrive.GetAvgDistance() < EDGE_OF_SWITCH_DISTANCE) {
        	a_DiffDrive.DriveStraightEncoder(LEFT_AGGRO, RIGHT_AGGRO, 0.4);
        } else {
			a_DiffDrive.UpdateVal(0,0);
			nextState = kMoveArm2;
		}
        break;
    case kMoveArm2:
    	a_CollectorArm.UpdateAngle(SWITCH_ANGLE);
    	nextState = kReleaseCube2;
    	break;
    case kReleaseCube2:
    	a_CollectorArm.UpdateRollers(-1.0);
        nextState = kAutoIdle2;
        break;
    case kAutoIdle2:
        a_DiffDrive.UpdateVal(0,0);
        a_DiffDrive.ZeroEncoders();
        break;
    }
    a_AutoStateV2 = nextState;
}

void Autonomous::AutonomousPeriodicV3()
{
    AutoStateV3 nextState = a_AutoStateV3;

    switch(a_AutoStateV3){
    case kMoveToSideOfScale:
        if (a_DiffDrive.GetAvgDistance() < SIDE_OF_SCALE_DISTANCE) {
        	a_DiffDrive.DriveStraightEncoder(LEFT_AGGRO, RIGHT_AGGRO, 0.4);
        } else {
            a_DiffDrive.UpdateVal(0,0);
            a_DiffDrive.ZeroEncoders();
            nextState = kTurnLeft3;
        }
        break;
    case kTurnLeft3:
        // a_DiffDrive.ArcTurn(18, 90, true);
        a_DiffDrive.ZeroEncoders();
        nextState = kMoveToEdgeOfScale;
        break;
    case kMoveToEdgeOfScale:
        if (a_DiffDrive.GetAvgDistance() < EDGE_OF_SCALE_DISTANCE) {
        	a_DiffDrive.DriveStraightEncoder(LEFT_AGGRO, RIGHT_AGGRO, 0.4);
                } else {
            		a_DiffDrive.UpdateVal(0,0);
                    a_DiffDrive.ZeroEncoders();
                    nextState = kMoveArm3;
                }
        break;
    case kMoveArm3:
    	a_CollectorArm.UpdateAngle(SCALE_ANGLE);
    	nextState = kReleaseCube3;
    	break;
    case kReleaseCube3:
    	a_CollectorArm.UpdateRollers(-1.0);
        nextState = kAutoIdle3;
        break;
    case kAutoIdle3:
        a_DiffDrive.UpdateVal(0,0);
        a_DiffDrive.ZeroEncoders();
        break;
    }
    a_AutoStateV3 = nextState;
}

void Autonomous::AutonomousPeriodicV4()
{
    AutoStateV4 nextState = a_AutoStateV4;

    switch (a_AutoStateV4) {
    case kMoveHalfToSwitch:
        if (a_DiffDrive.GetAvgDistance() < HALF_OF_SWITCH_DISTANCE) {
        	a_DiffDrive.DriveStraightEncoder(LEFT_AGGRO, RIGHT_AGGRO, 0.4);
        } else {
            a_DiffDrive.UpdateVal(0,0);
            a_DiffDrive.ZeroEncoders();
            nextState = kTurnRight4;
        }
        break;
    case kTurnRight4:
        // a_DiffDrive.ArcTurn(18, 90, false);
        a_DiffDrive.ZeroEncoders();
        nextState = kMoveFlushWithSwitch;
        break;
    case kMoveFlushWithSwitch:
        if (a_DiffDrive.GetAvgDistance() < FLUSH_WITH_SWITCH) {
        	a_DiffDrive.DriveStraightEncoder(LEFT_AGGRO, RIGHT_AGGRO, 0.4);
        } else {
            a_DiffDrive.UpdateVal(0,0);
            a_DiffDrive.ZeroEncoders();
            nextState = kTurnLeft4;
        }
        break;
    case kTurnLeft4:
        // a_DiffDrive.ArcTurn(18, 90, true);
        a_DiffDrive.ZeroEncoders();
        nextState = kMoveToFrontOfSwitch;
        break;
    case kMoveToFrontOfSwitch:
        if (a_DiffDrive.GetAvgDistance() < FRONT_OF_SWITCH_DISTANCE) {
        	a_DiffDrive.DriveStraightEncoder(LEFT_AGGRO, RIGHT_AGGRO, 0.4);
        } else {
            a_DiffDrive.UpdateVal(0,0);
            a_DiffDrive.ZeroEncoders();
            nextState = kMoveArm4;
        }
        break;
    case kMoveArm4:
    	a_CollectorArm.UpdateAngle(SWITCH_ANGLE);
    	nextState = kReleaseCube4;
    	break;
    case kReleaseCube4:
    	a_CollectorArm.UpdateRollers(-1.0);
        nextState = kAutoIdle4;
        break;
    case kAutoIdle4:
        a_DiffDrive.UpdateVal(0,0);
        a_DiffDrive.ZeroEncoders();
        break;
    }
    a_AutoStateV4 = nextState;
}

void Autonomous::AutonomousPeriodicV5()
{
    AutoStateV5 nextState = a_AutoStateV5;

    switch (a_AutoStateV5) {
    case kMoveTopOfSwitch:
        if (a_DiffDrive.GetAvgDistance() < TOP_OF_SWITCH_DISTANCE) {
        	a_DiffDrive.DriveStraightEncoder(LEFT_AGGRO, RIGHT_AGGRO, 0.4);
        } else {
            a_DiffDrive.UpdateVal(0,0);
            a_DiffDrive.ZeroEncoders();
            nextState = kTurnRight5;
        }
        break;
    case kTurnRight5:
		// a_DiffDrive.ArcTurn(10, 90, false);
		a_DiffDrive.ZeroEncoders();
        nextState = kMoveFlushWithScale;
        break;
    case kMoveFlushWithScale:
        if (a_DiffDrive.GetAvgDistance() < FLUSH_WITH_SCALE) {
        	a_DiffDrive.DriveStraightEncoder(LEFT_AGGRO, RIGHT_AGGRO, 0.4);
        } else {
            a_DiffDrive.UpdateVal(0,0);
            a_DiffDrive.ZeroEncoders();
            nextState = kTurnLeft5;
        }
        break;
    case kTurnLeft5:
        // a_DiffDrive.ArcTurn(10, 90, true);
        a_DiffDrive.ZeroEncoders();
        nextState = kMoveToFrontOfScale;
        break;
    case kMoveToFrontOfScale:
        if (a_DiffDrive.GetAvgDistance() < FRONT_OF_SCALE_DISTANCE) {
        	a_DiffDrive.DriveStraightEncoder(LEFT_AGGRO, RIGHT_AGGRO, 0.4);
        } else {
            a_DiffDrive.UpdateVal(0,0);
            a_DiffDrive.ZeroEncoders();
            nextState = kMoveArm5;
        }
        break;
    case kMoveArm5:
    	a_CollectorArm.UpdateAngle(SWITCH_ANGLE);
    	nextState = kReleaseCube5;
    	break;
    case kReleaseCube5:
    	a_CollectorArm.UpdateRollers(-1.0);
        nextState = kAutoIdle5;
        break;
    case kAutoIdle5:
        a_DiffDrive.UpdateVal(0,0);
        a_DiffDrive.ZeroEncoders();
        break;
    }
    a_AutoStateV5 = nextState;
}


/* Example internal auto function
 * bool Autonomous::DriveStraight(int distance) {
	if (a_DiffDrive.GetAvgDistance() < distance) {
		a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
		return false;
	} else {
		a_DiffDrive.UpdateVal(0, 0);
		return true;
	}
}*/
