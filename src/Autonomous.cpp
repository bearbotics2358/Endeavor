#include <WPILib.h>
#include <Math.h>
#include "Autonomous.h"

Autonomous::Autonomous(AutonomousHelper &AutoBot, CollectorArm &CollectorArm, DiffDrive &DiffDrive, JrimmyGyro &Gyro, SerialPort &Arduino, UltrasonicSerial &UltraSoul)
: a_AutoBot(AutoBot),
  a_CollectorArm(CollectorArm),
  a_DiffDrive(DiffDrive),
  a_Gyro(Gyro),
  a_Arduino(Arduino),
  a_UltraSoul(UltraSoul),
  a_AutoStateV1(kAutoIdle),
  a_AutoStateV2(kAutoIdle2),
  a_AutoStateV3(kAutoIdle3),
  a_AutoStateV4(kAutoIdle4),
  a_AutoStateV5(kAutoIdle5)

{

}

void Autonomous::Init(){

}

void Autonomous::AutonomousPeriodicV1()
{

	// const float SWITCH_DISTANCE;

    AutoStateV1 nextState = a_AutoStateV1;

    switch(a_AutoStateV1){
    case kMoveToSwitch:
    	/*
        if (robotDistance < SWITCH_DISTANCE) {
			a_DiffDrive.DriveStraight((1 * (LEFT_AGGRO)),(-1 * (RIGHT_AGGRO)));
        } else {
            a_DiffDrive.UpdateVal(0,0);
            nextState = kReleaseCube;
        }
        */
        break;
    case kReleaseCube:
        // a_Robot.ReleaseCube;
        nextState = kAutoIdle;
        break;
    case kAutoIdle:
        a_DiffDrive.UpdateVal(0,0);
        // a_Robot.ResetEncoders();
        break;
    }
    a_AutoStateV1 = nextState;
}

void Autonomous::AutonomousPeriodicV2()
{
	/*
	const float SIDE_OF_SWITCH_DISTANCE;
	const float TURN_ANGLE;
	const float EDGE_OF_SWITCH_DISTANCE;
	 */

    AutoStateV2 nextState = a_AutoStateV2;

    switch(a_AutoStateV2){
    case kMoveToSideOfSwitch:
    	/*
        if (robotDistance < SIDE_OF_SWITCH_DISTANCE) {
				a_DiffDrive.DriveStraight((1 * (LEFT_AGGRO)),(-1 * (RIGHT_AGGRO)));
        } else {
            a_DiffDrive.UpdateVal(0,0);
            nextState = kTurnLeft2;
        }
        */
        break;
    case kTurnLeft2:
		a_DiffDrive.ArcTurn(18, 90, true);
        nextState = kMoveToEdgeOfSwitch;
        break;
    case kMoveToEdgeOfSwitch:
    	/*
        if (robotDistance < EDGE_OF_SWITCH_DISTANCE) {
				a_DiffDrive.DriveStraight((1 * (LEFT_AGGRO)),(-1 * (RIGHT_AGGRO)));
                } else {
            		a_DiffDrive.UpdateVal(0,0);
                    nextState = kReleaseCube2;
                }
        */
        break;
    case kReleaseCube2:
        // a_Robot.ReleaseCube;
        nextState = kAutoIdle2;
        break;
    case kAutoIdle2:
        a_DiffDrive.UpdateVal(0,0);
        // a_Robot.ResetEncoders();
        break;
    }
    a_AutoStateV2 = nextState;
}

void Autonomous::AutonomousPeriodicV3()
{
	/*
	const float SIDE_OF_SCALE_DISTANCE;
	const float TURN_ANGLE3;
	const float EDGE_OF_SCALE_DISTANCE;
	*/

    AutoStateV3 nextState = a_AutoStateV3;

    switch(a_AutoStateV3){
    case kMoveToSideOfScale:
    	/*
        if (robotDistance < SIDE_OF_SCALE_DISTANCE) {
			a_DiffDrive.DriveStraight((1 * (LEFT_AGGRO)),(-1 * (RIGHT_AGGRO)));
        } else {
            a_DiffDrive.UpdateVal(0,0);
            nextState = kTurnLeft3;
        }
        */
        break;
    case kTurnLeft3:
        a_DiffDrive.ArcTurn(18, 90, true);
        nextState = kMoveToEdgeOfScale;
        break;
    case kMoveToEdgeOfScale:
    	/*
        if (robotDistance < EDGE_OF_SCALE_DISTANCE) {
				a_DiffDrive.DriveStraight((1 * (LEFT_AGGRO)),(-1 * (RIGHT_AGGRO)));
                } else {
            		a_DiffDrive.UpdateVal(0,0);
                    nextState = kReleaseCube3;
                }
        */
        break;
    case kReleaseCube3:
        // a_Robot.ReleaseCube;
        nextState = kAutoIdle3;
        break;
    case kAutoIdle3:
        a_DiffDrive.UpdateVal(0,0);
        // a_Robot.ResetEncoders();
        break;
    }
    a_AutoStateV3 = nextState;
}

void Autonomous::AutonomousPeriodicV4()
{
	/*
	const float HALF_OF_SWITCH_DISTANCE;
	const float TURN_ANGLE4A;
	const float FLUSH_WITH_SWITCH;
	const float TURN_ANGLE4B;
	const float FRONT_OF_SWITCH_DISTANCE;
	*/

    AutoStateV4 nextState = a_AutoStateV4;

    switch (a_AutoStateV4) {
    case kMoveHalfToSwitch:
    	/*
        if (robotDistance < HALF_OF_SWITCH_DISTANCE) {
			a_DiffDrive.DriveStraight((1 * (LEFT_AGGRO)),(-1 * (RIGHT_AGGRO)));
        } else {
            a_DiffDrive.UpdateVal(0,0);
            nextState = kTurnRight;
        }
        */
        break;
    case kTurnRight4:
        a_DiffDrive.ArcTurn(18, 90, false);
        nextState = kMoveFlushWithSwitch;
        break;
    case kMoveFlushWithSwitch:
    	/*
        if (robotDistance < FLUSH_WITH_SWITCH) {
			a_DiffDrive.DriveStraight((1 * (LEFT_AGGRO)),(-1 * (RIGHT_AGGRO)));
        } else {
            a_DiffDrive.UpdateVal(0,0);
            nextState = kTurnLeft4;
        }
        */
        break;
    case kTurnLeft4:
        a_DiffDrive.ArcTurn(18, 90, true);
        nextState = kMoveToFrontOfSwitch;
        break;
    case kMoveToFrontOfSwitch:
    	/*
        if (robotDistance < FRONT_OF_SWITCH_DISTANCE) {
			a_DiffDrive.DriveStraight((1 * (LEFT_AGGRO)),(-1 * (RIGHT_AGGRO)));
        } else {
            a_DiffDrive.UpdateVal(0,0);
            nextState = kReleaseCube4;
        }
        */
        break;
    case kReleaseCube4:
        // a_Robot.ReleaseCube;
        nextState = kAutoIdle4;
        break;
    case kAutoIdle4:
        a_DiffDrive.UpdateVal(0,0);
        // a_Robot.ResetEncoders();
        break;
    }
    a_AutoStateV4 = nextState;
}

void Autonomous::AutonomousPeriodicV5()
{
	/*
	const float TOP_OF_SWITCH_DISTANCE;
	const float TURN_ANGLE5A;
	const float FLUSH_WITH_SCALE;
	const float TURN_ANGLE5B;
	const float FRONT_OF_SCALE_DISTANCE;
	*/

    AutoStateV5 nextState = a_AutoStateV5;

    switch (a_AutoStateV5) {
    case kMoveTopOfSwitch:
    	/*
        if (robotDistance < TOP_OF_SWITCH_DISTANCE) {
				a_DiffDrive.DriveStraight((1 * (LEFT_AGGRO)),(-1 * (RIGHT_AGGRO)));
        } else {
            a_DiffDrive.UpdateVal(0,0);
            nextState = kTurnRight5;
        }
        */
        break;
    case kTurnRight5:
		a_DiffDrive.ArcTurn(10, 90, false);
        nextState = kMoveFlushWithScale;
        break;
    case kMoveFlushWithScale:
    	/*
        if (robotDistance < FLUSH_WITH_SCALE) {
			a_DiffDrive.DriveStraight((1 * (LEFT_AGGRO)),(-1 * (RIGHT_AGGRO)));
        } else {
            a_DiffDrive.UpdateVal(0,0);
            nextState = kTurnLeft5;
        }
        */
        break;
    case kTurnLeft5:
        a_DiffDrive.ArcTurn(10, 90, true);
        nextState = kMoveToFrontOfScale;
        break;
    case kMoveToFrontOfScale:
    	/*
        if (robotDistance < FRONT_OF_SCALE_DISTANCE) {
			a_DiffDrive.DriveStraight((1 * (LEFT_AGGRO)),(-1 * (RIGHT_AGGRO)));
        } else {
            a_DiffDrive.UpdateVal(0,0);
            nextState = kReleaseCube5;
        }
        */
        break;
    case kReleaseCube5:
        // a_Robot.ReleaseCube;
        nextState = kAutoIdle5;
        break;
    case kAutoIdle5:
        a_DiffDrive.UpdateVal(0,0);
        // a_Robot.ResetEncoders();
        break;
    }
    a_AutoStateV5 = nextState;
}

