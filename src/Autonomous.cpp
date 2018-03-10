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
  a_AutoStateU1(kAutoIdleU1),
  a_AutoStateV1(kAutoIdle1),
  a_AutoStateU2(kAutoIdleU2),
  a_AutoStateV2(kAutoIdle2),
  a_AutoStateU3(kAutoIdleU3),
  a_AutoStateV3(kAutoIdle3),
  a_AutoStateU4(kAutoIdleU4),
  a_AutoStateV4(kAutoIdle4),
  a_AutoStateU5(kAutoIdleU5),
  a_AutoStateV5(kAutoIdle5)
{
	a_AngleSaved = 0.0;
	a_time_state = 0;
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
			a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, 0.4);
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

void Autonomous::AutonomousStartU1()
{
	a_AutoStateU1 = kMoveToSwitchU1;
}

void Autonomous::AutonomousPeriodicU1()
{
	AutoStateU1 nextState = a_AutoStateU1;

	switch(a_AutoStateU1){
	case kAutoIdleU1:
		a_DiffDrive.UpdateVal(0,0);
		a_DiffDrive.ZeroEncoders();
		break;

	case kMoveToSwitchU1:
		// move arm while moving bot
		a_CollectorArm.UpdateAngle(60);
		if (a_UltraSoul.GetRearRight() < SWITCH_DISTANCE) {
			a_DiffDrive.DriveStraightGyro(a_Gyro.GetAngle(2), 0, 0.4);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			nextState = kMoveArmU1;
		}
		break;

	case kMoveArmU1:
		a_CollectorArm.UpdateAngle(60);
		if(a_CollectorArm.GetAngle2() >= 60) {
			nextState = kReleaseCubeU1;
			a_time_state = a_DiffDrive.gettime_d();
		}
		break;

	case kReleaseCubeU1:
		a_CollectorArm.UpdateRollers(-1.0);
		// have rollers been running long enough?
		if(a_DiffDrive.gettime_d() - a_time_state > 0.5) {
			a_CollectorArm.UpdateRollers(0.0);
			nextState = kAutoIdleU1;
		}
		break;

	}
	a_AutoStateU1 = nextState;
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

void Autonomous::AutonomousStartU2()
{
	a_AutoStateU2 = kMoveToSideOfSwitchU2;
}

void Autonomous::AutonomousPeriodicU2()
{
	AutoStateU2 nextState = a_AutoStateU2;

	switch(a_AutoStateU2){
	case kAutoIdleU2:
		a_DiffDrive.UpdateVal(0,0);
		a_DiffDrive.ZeroEncoders();
		break;

	case kMoveToSideOfSwitchU2:
		if (a_UltraSoul.GetRearRight() < SIDE_OF_SWITCH_DISTANCE) {
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
		} else {
			a_DiffDrive.UpdateVal(-0.25,0.25); // rotate counter-clockwise
			a_DiffDrive.ZeroEncoders();
			nextState = kTurnLeftU2;
			a_AngleSaved = a_Gyro.GetAngle(2);  // get Z-axis gyro angle
		}
		break;

	case kTurnLeftU2:
		// move arm while moving bot
		a_CollectorArm.UpdateAngle(ARM_ANGLE2);
		// a_DiffDrive.ArcTurn(18, 90, true);
		a_DiffDrive.UpdateVal(-0.25,0.25); // rotate counter-clockwise
		if((a_Gyro.GetAngle(2) - a_AngleSaved) >= 90) {
			// a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kMoveToEdgeOfSwitchU2;
		}
		break;

	case kMoveToEdgeOfSwitchU2:
		a_CollectorArm.UpdateAngle(ARM_ANGLE2);
		if (a_UltraSoul.GetRearRight() < EDGE_OF_SWITCH_DISTANCE) {
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			nextState = kMoveArmU2;
		}
		break;

	case kMoveArmU2:
		a_CollectorArm.UpdateAngle(ARM_ANGLE2);
		if(a_CollectorArm.GetAngle2() >= ARM_ANGLE2) {
			nextState = kReleaseCubeU2;
			a_time_state = a_DiffDrive.gettime_d();
		}
		break;

	case kReleaseCubeU2:
		a_CollectorArm.UpdateRollers(-1.0);
		// have rollers been running long enough?
		if(a_DiffDrive.gettime_d() - a_time_state > 0.5) {
			a_CollectorArm.UpdateRollers(0.0);
			nextState = kAutoIdleU2;
		}
		break;
	}
	a_AutoStateU2 = nextState;
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

void Autonomous::AutonomousStartU3()
{
	a_AutoStateU3 = kMoveToSideOfScaleU3;
}

void Autonomous::AutonomousPeriodicU3()
{
	AutoStateU3 nextState = a_AutoStateU3;

	switch(a_AutoStateU3){
	case kAutoIdleU3:
		a_DiffDrive.UpdateVal(0,0);
		a_DiffDrive.ZeroEncoders();
		break;

	case kMoveToSideOfScaleU3:
		// move arm while moving bot
		a_CollectorArm.UpdateAngle(ARM_ANGLE3);
		if (a_UltraSoul.GetRearRight() < SIDE_OF_SCALE_DISTANCE) {
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			a_AngleSaved = a_Gyro.GetAngle(2);  // get Z-axis gyro angle
			nextState = kTurnLeftU3;
		}
		break;

	case kTurnLeftU3:
		// move arm while moving bot
		a_CollectorArm.UpdateAngle(ARM_ANGLE3);
		// a_DiffDrive.ArcTurn(18, 90, true);
		a_DiffDrive.UpdateVal(-0.25,0.25); // rotate counter-clockwise
		if((a_Gyro.GetAngle(2) - a_AngleSaved) >= 90) {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kMoveToEdgeOfScaleU3;
		}
		break;

	case kMoveToEdgeOfScaleU3:
		// move arm while moving bot
		a_CollectorArm.UpdateAngle(ARM_ANGLE3);
		if (a_UltraSoul.GetRearRight() < EDGE_OF_SCALE_DISTANCE) {
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kMoveArmU3;
		}
		break;

	case kMoveArmU3:
		a_CollectorArm.UpdateAngle(ARM_ANGLE3);
		if(a_CollectorArm.GetAngle2() >= ARM_ANGLE3) {
			nextState = kReleaseCubeU3;
			a_time_state = a_DiffDrive.gettime_d();
		}
		break;

	case kReleaseCubeU3:
		a_CollectorArm.UpdateRollers(-1.0);
		// have rollers been running long enough?
		if(a_DiffDrive.gettime_d() - a_time_state > 0.5) {
			a_CollectorArm.UpdateRollers(0.0);
			nextState = kAutoIdleU3;
		}
		break;
	}
	a_AutoStateU3 = nextState;
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

void Autonomous::AutonomousStartU4()
{
	a_AutoStateU4 = kMoveHalfToSwitchU4;
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
		if (a_UltraSoul.GetRearRight() < HALF_OF_SWITCH_DISTANCE) {
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kTurnRightU4;
			a_AngleSaved = a_Gyro.GetAngle(2);  // get Z-axis gyro angle
		}
		break;

	case kTurnRightU4:
		// a_DiffDrive.ArcTurn(18, 90, false);
		a_DiffDrive.UpdateVal(0.25,-0.25); // rotate clockwise
		if((a_Gyro.GetAngle(2) - a_AngleSaved) <= -90) {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kMoveFlushWithSwitchU4;
		}
		break;

	case kMoveFlushWithSwitchU4:
		if (a_UltraSoul.GetFrontLeft() > FLUSH_WITH_SWITCH) {
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kTurnLeftU4;
			a_AngleSaved = a_Gyro.GetAngle(2);  // get Z-axis gyro angle
		}
		break;

	case kTurnLeftU4:
		// move arm while moving bot
		a_CollectorArm.UpdateAngle(ARM_ANGLE4);
		// a_DiffDrive.ArcTurn(18, 90, true);
		a_DiffDrive.UpdateVal(-0.25,0.25); // rotate counter-clockwise
		if((a_Gyro.GetAngle(2) - a_AngleSaved) >= 90) {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kMoveToFrontOfSwitchU4;
		}
		break;

	case kMoveToFrontOfSwitchU4:
		// move arm while moving bot
		a_CollectorArm.UpdateAngle(ARM_ANGLE4);
		if (a_UltraSoul.GetRearRight() < FRONT_OF_SWITCH_DISTANCE) {
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kMoveArmU4;
		}
		break;

	case kMoveArmU4:
		a_CollectorArm.UpdateAngle(ARM_ANGLE4);
		if(a_CollectorArm.GetAngle2() >= ARM_ANGLE4) {
			nextState = kReleaseCubeU4;
			a_time_state = a_DiffDrive.gettime_d();
		}
		break;

	case kReleaseCubeU4:
		a_CollectorArm.UpdateRollers(-1.0);
		// have rollers been running long enough?
		if(a_DiffDrive.gettime_d() - a_time_state > 0.5) {
			a_CollectorArm.UpdateRollers(0.0);
			nextState = kAutoIdleU4;
		}
		break;
	}
	a_AutoStateU4 = nextState;
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
		break;

	case kMoveTopOfSwitchU5:
		if (a_UltraSoul.GetRearRight() < TOP_OF_SWITCH_DISTANCE) {
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kTurnRightU5;
			a_AngleSaved = a_Gyro.GetAngle(2);  // get Z-axis gyro angle
		}
		break;

	case kTurnRightU5:
		// a_DiffDrive.ArcTurn(10, 90, false);
		a_DiffDrive.UpdateVal(0.25,-0.25); // rotate clockwise
		if((a_Gyro.GetAngle(2) - a_AngleSaved) <= -90) {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kMoveFlushWithScaleU5;
		}
		break;

	case kMoveFlushWithScaleU5:
		if (a_UltraSoul.GetFrontLeft() > FLUSH_WITH_SWITCH) {
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kTurnLeftU5;
			a_AngleSaved = a_Gyro.GetAngle(2);  // get Z-axis gyro angle
		}
		break;

	case kTurnLeftU5:
		// move arm while moving bot
		a_CollectorArm.UpdateAngle(ARM_ANGLE5);
		// a_DiffDrive.ArcTurn(10, 90, true);
		a_DiffDrive.UpdateVal(-0.25,0.25); // rotate counter-clockwise
		if((a_Gyro.GetAngle(2) - a_AngleSaved) >= 90) {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kMoveToFrontOfScaleU5;
		}
		break;

	case kMoveToFrontOfScaleU5:
		// move arm while moving bot
		a_CollectorArm.UpdateAngle(ARM_ANGLE5);
		if (a_UltraSoul.GetRearRight() < FRONT_OF_SCALE_DISTANCE) {
			a_DiffDrive.DriveStraight(LEFT_AGGRO, RIGHT_AGGRO);
		} else {
			a_DiffDrive.UpdateVal(0,0);
			a_DiffDrive.ZeroEncoders();
			nextState = kMoveArmU5;
		}
		break;

	case kMoveArmU5:
		a_CollectorArm.UpdateAngle(ARM_ANGLE5);
		if(a_CollectorArm.GetAngle2() >= ARM_ANGLE5) {
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
