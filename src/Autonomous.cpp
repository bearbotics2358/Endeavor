#include <WPILib.h>
#include <Math.h>
#include "Autonomous.h"

Autonomous::Autonomous(AutonomousHelper &AutoBot, CollectorArm &CollectorArm, DiffDrive &DiffDrive, JrimmyGyro &Gyro, Underglow &Underglow, UltrasonicSerial &UltraSoul)
: a_AutoBot(AutoBot),
  a_CollectorArm(CollectorArm),
  a_DiffDrive(DiffDrive),
  a_Gyro(Gyro),
  a_Underglow(Underglow),
  a_UltraSoul(UltraSoul),
  a_AutoStateVx(kAutoIdlex),
  a_AutoStateU0(kAutoIdleU0),
  a_AutoStateV0(kAutoIdle0),
  a_AutoStateV1(kAutoIdle1),
  a_AutoStateV2(kAutoIdle2),
  a_AutoStateV3(kAutoIdle3),
  a_AutoStateV4(kAutoIdle4),
  a_AutoStateV5(kAutoIdle5)
{

}

void Autonomous::Init(){

}

void Autonomous::AutonomousPeriodicVx()
{
	AutoStateVx nextState = a_AutoStateVx;
	int ret;
	
	switch(a_AutoStateVx){
	case kAutoIdlex:
		a_DiffDrive.UpdateVal(0,0);
		a_DiffDrive.ZeroEncoders();
		break;

	case kMoveToSwitchInitx:
		a_DiffDrive.DriveToDist(SWITCH_DISTANCE, SWITCH_DISTANCE, 12, 1);
		nextState = kMoveToSwitchx;
		break;

	case kMoveToSwitchx:
		ret = a_DiffDrive.DriveToDist(SWITCH_DISTANCE, SWITCH_DISTANCE, 12, 0);
		if(ret) {
			a_DiffDrive.UpdateVal(0,0);
			nextState = kAutoIdlex;
		}
		break;
	}
	a_AutoStateVx = nextState;
}

void Autonomous::AutonomousStartU0()
{
	a_AutoStateU0 = kMoveToSwitchU0;
}

void Autonomous::AutonomousPeriodicU0()
{
	AutoStateU0 nextState = a_AutoStateU0;

	switch(a_AutoStateU0){
	case kAutoIdleU0:
		a_DiffDrive.UpdateVal(0,0);
		a_DiffDrive.ZeroEncoders();
		break;

	case kMoveToSwitchU0:
		if (a_UltraSoul.GetRearRight() < SWITCH_DISTANCE) {
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			nextState = kAutoIdleU0;
		}
		break;

	}
	a_AutoStateU0 = nextState;
}

void Autonomous::AutonomousPeriodicV0()
{
    AutoStateV0 nextState = a_AutoStateV0;

    switch(a_AutoStateV0){
    case kMoveToSwitch0:
        if (a_DiffDrive.GetAvgDistance() < SWITCH_DISTANCE) {
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
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
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
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
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
        } else {
            a_DiffDrive.UpdateVal(0,0);
            a_DiffDrive.ZeroEncoders();
            nextState = kTurnLeft2;
        }
        break;
    case kTurnLeft2:
		// a_DiffDrive.ArcTurn(18, 90, true);
		a_DiffDrive.ZeroEncoders();
        nextState = kMoveToEdgeOfSwitch;
        break;
    case kMoveToEdgeOfSwitch:
        if (a_DiffDrive.GetAvgDistance() < EDGE_OF_SWITCH_DISTANCE) {
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			nextState = kMoveArm2;
		}
        break;
    case kMoveArm2:
    	a_CollectorArm.UpdateAngle(ARM_ANGLE2);
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
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
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
				a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
                } else {
            		a_DiffDrive.UpdateVal(0,0);
                    a_DiffDrive.ZeroEncoders();
                    nextState = kMoveArm3;
                }
        break;
    case kMoveArm3:
    	a_CollectorArm.UpdateAngle(ARM_ANGLE3);
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
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
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
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
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
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
        } else {
            a_DiffDrive.UpdateVal(0,0);
            a_DiffDrive.ZeroEncoders();
            nextState = kMoveArm4;
        }
        break;
    case kMoveArm4:
    	a_CollectorArm.UpdateAngle(ARM_ANGLE4);
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
				a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
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
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
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
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
        } else {
            a_DiffDrive.UpdateVal(0,0);
            a_DiffDrive.ZeroEncoders();
            nextState = kMoveArm5;
        }
        break;
    case kMoveArm5:
    	a_CollectorArm.UpdateAngle(ARM_ANGLE5);
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
