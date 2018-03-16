#include <WPILib.h>
#include "DiffDrive.h"
#include "ctre/Phoenix.h"
#include <Math.h>
#include <pathfinder.h>
#include <stdlib.h> // labs()
#include <sys/time.h>

DiffDrive::DiffDrive(int leftDriveOne, int leftDriveTwo, int leftDriveThree, int rightDriveOne, int rightDriveTwo, int rightDriveThree)
: a_leftDriveOne(leftDriveOne),
  a_leftDriveTwo(leftDriveTwo),
  a_leftDriveThree(leftDriveThree),

  a_rightDriveOne(rightDriveOne),
  a_rightDriveTwo(rightDriveTwo),
  a_rightDriveThree(rightDriveThree),

  a_Drivetrain(a_leftDriveTwo, a_rightDriveTwo),

  a_DriveSolenoid(PCM_PORT, SOL_PORT_SIX, SOL_PORT_SEV)
{
	driveType = 0;
	targetPositionRotations = 10.0 * 4096; /* 10 Rotations in either direction??? */
	kSlotIdx = 0;
	kPIDLoopIdx = 0;
	kTimeoutMs = 10;

	t0 = 0.0;
	lspeed_target = 0.0;
	rspeed_target = 0.0;
	avg_speed_target = 0.0;
}

void DiffDrive::Init()
{
	a_leftDriveTwo.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
	a_leftDriveTwo.SetSensorPhase(true);
	a_leftDriveOne.Follow(a_leftDriveTwo);
	a_leftDriveThree.Follow(a_leftDriveTwo);
	a_rightDriveTwo.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
	a_rightDriveTwo.SetSensorPhase(false);
	a_rightDriveOne.Follow(a_rightDriveTwo);
	a_rightDriveThree.Follow(a_rightDriveTwo);
	InvertLeftDrive();
	InvertRightDrive();
	UpdateVal(0.0,0.0);
	ZeroEncoders();
}

void DiffDrive::Init(float p, float i, float d, float f){
	Init();
	SetLeftPIDF(p,i,d,f);
	SetRightPIDF(p,i,d,f);
}

void DiffDrive::SetLeftPIDF(float p, float i, float d, float f){
	a_leftDriveTwo.Config_kP(kPIDLoopIdx, p, kTimeoutMs);
	a_leftDriveTwo.Config_kI(kPIDLoopIdx, i, kTimeoutMs);
	a_leftDriveTwo.Config_kD(kPIDLoopIdx, d, kTimeoutMs);
	a_leftDriveTwo.Config_kF(kPIDLoopIdx, f, kTimeoutMs);
}

void DiffDrive::SetRightPIDF(float p, float i, float d, float f){
	a_rightDriveTwo.Config_kP(kPIDLoopIdx, p, kTimeoutMs);
	a_rightDriveTwo.Config_kI(kPIDLoopIdx, i, kTimeoutMs);
	a_rightDriveTwo.Config_kD(kPIDLoopIdx, d, kTimeoutMs);
	a_rightDriveTwo.Config_kF(kPIDLoopIdx, f, kTimeoutMs);
}

void DiffDrive::SetDriveType(int type)
{
	driveType = type;
}

void DiffDrive::DisableMotorSafetyTraitor(){
	a_leftDriveOne.SetSafetyEnabled(false);
	a_leftDriveTwo.SetSafetyEnabled(false);
	a_leftDriveThree.SetSafetyEnabled(false);
	a_rightDriveOne.SetSafetyEnabled(false);
	a_rightDriveTwo.SetSafetyEnabled(false);
	a_rightDriveThree.SetSafetyEnabled(false);
}

void DiffDrive::InvertLeftDrive(){
	a_leftDriveOne.SetInverted(true);
	a_leftDriveTwo.SetInverted(true);
	a_leftDriveThree.SetInverted(true);
}

void DiffDrive::InvertRightDrive(){
	a_rightDriveOne.SetInverted(true);
	a_rightDriveTwo.SetInverted(true);
	a_rightDriveThree.SetInverted(true);
}

void DiffDrive::Update(Joystick &stick1, Joystick &stick2, Joystick &stick3, Joystick &stick4)
{
	switch (driveType) {
	  case 0: // ArcadeDrive from the flightstick with a Z
		  a_Drivetrain.ArcadeDrive((stick1.GetRawAxis(5)), stick1.GetRawAxis(4), false);
	    break;
	  case 1: // CurvatureDrive works better at high speeds.
		  	  // Using flightstick with a z
		  a_Drivetrain.CurvatureDrive(stick1.GetRawAxis(5), stick1.GetRawAxis(4), false);
	    break;
	  case 2: // Traditional Two Stick Tank.
		  	  // Uses the two flightsticks without z axes.
		  a_Drivetrain.TankDrive((stick2.GetRawAxis(1)), (stick3.GetRawAxis(1)), false);
		break;
	  default:
		  a_Drivetrain.TankDrive(0, 0, false); // theo disable
	}
}

void DiffDrive::UpdateVal(float left, float right){
	a_Drivetrain.TankDrive(left, right, false);
}

bool DiffDrive::UpdateAngle(float curAngle, float tarAngle){ // rets true when its right.
	if (fabs(curAngle - tarAngle) < 3.0){
		UpdateVal(0,0);
		return true;
	}
	if ((tarAngle - curAngle) > 0){
		UpdateVal(-0.5,0.5); // left
	}
	else {
		UpdateVal(0.5, -0.5); // right
	}
	return false;
}

void DiffDrive::ShiftLow(){
	a_DriveSolenoid.Set(DoubleSolenoid::kForward);
}

void DiffDrive::ShiftHigh(){
	a_DriveSolenoid.Set(DoubleSolenoid::kReverse);
}

bool DiffDrive::GetShiftState(){
	// return true for High gear
	return (a_DriveSolenoid.Get() == DoubleSolenoid::kReverse);
}

void DiffDrive::GoDistance(float targetDistance){
	a_leftDriveTwo.Set(ControlMode::Position, targetDistance * 4096);
	a_rightDriveTwo.Set(ControlMode::Position, targetDistance * 4096);
}

void DiffDrive::DriveStraightEncoder(float left, float right, float velo){
	double leftDistance = GetDistanceLeft();
	double rightDistance = GetDistanceRight();
	SmartDashboard::PutNumber("left auto", leftDistance);
	SmartDashboard::PutNumber("right auto", rightDistance);
	// difference in inches:
	double diff = (leftDistance - rightDistance);
	if(fabs(diff) < 0.10) {
		// close enough
		UpdateVal(left * velo * -1, right * velo * -1);
	} else if(diff < 0) {
		// turn right
		UpdateVal(((9.0/7.0) * left * velo * -1), ((7.0/9.0) * right * velo * -1));
	} else {
		// turn left
		UpdateVal(((7.0/9.0) * left * velo * -1), ((9.0/7.0) * right * velo * -1));
	}
}

void DiffDrive::DriveStraightGyro(float tarAngle, float curAngle, float speed){
	if(fabs(curAngle - tarAngle) < 0.10) {
		// close enough
		UpdateVal(speed * -1, speed * -1);
	} else if((curAngle - tarAngle) < 0) {
		// turn right
		UpdateVal(((11.0/7.0) * speed * -1), ((7.0/11.0) * speed * -1));
	} else {
		// turn left
		UpdateVal(((7.0/11.0) * speed * -1), ((11.0/7.0) * speed * -1));
	}
}

double DiffDrive::gettime_d(){
	// return time in seconds as a double
	double t0;
	struct timeval tv0;

	gettimeofday(&tv0, NULL);
	t0 = 1.0 * tv0.tv_sec + (1.0 * tv0.tv_usec) / 1000000.0;
	// printf("seconds: %ld\n", tv0.tv_sec);
	// printf("usecs:   %ld\n", tv0.tv_usec);
	// printf("time:    %lf\n", t0);

	return t0;
}

bool DiffDrive::DriveToDist(float ldist, float rdist, float speed, int first_call) {
	// currently only handles driving forward (and forward arcs)

	// distances are in inches 
	// speed is inches/second
	// first_call is set to 1 on initial call to setup variables, and 0 on subsequent calls
	// distances and speed should not change

	// return: 1 when maneuver is complete
	
	float ldist_init = 0;
	float rdist_init = 0;
	float ldist_now;
	float rdist_now;
	double tnow;
	float lerr;
	float rerr;
	float lspeed_ideal = 0.0;
	float rspeed_ideal = 0.0;
	float ldist_ideal;
	float rdist_ideal;
	float ldist_new;
	float rdist_new;
	float lIsum;
	float rIsum;
	float ticks_per_inch;
	float ldist_count;
	float rdist_count;
	
	if(first_call) {
		// calculate ideal speeds for left and right side based on speed and distances
		if(fabs(ldist - rdist) < 0.01) { // using this as "equals" for floats
			lspeed_ideal = speed;
			rspeed_ideal = speed;
		} else if(fabs(ldist) < 0.01) {
			lspeed_ideal = 0;
			rspeed_ideal = speed;
		} else if(fabs(rdist) < 0.01) {
			lspeed_ideal = speed;
			rspeed_ideal = 0;
		} else if(ldist > rdist) {
			lspeed_ideal = speed;
			rspeed_ideal = speed * ((1.0 * rdist) / (1.0 * ldist));
		} if(ldist < rdist) {
			lspeed_ideal = speed * ((1.0 * ldist) / (1.0 * rdist));
			rspeed_ideal = speed;
		}

		ldist_init = GetDistanceLeft();
		rdist_init = GetDistanceRight();
		t0 = gettime_d();
		tnow = t0;
		lerr = rerr = 0.0;
		lIsum = rIsum = 0.0;
	}
	
	// get distance since first call
	ldist_now = GetDistanceLeft();
	rdist_now = GetDistanceRight();
	ldist_now -= ldist_init;
	rdist_now -= rdist_init;
	
	if((ldist_now >= ldist) && (rdist_now >= rdist)) {
		// maneuver complete
		return true;
	}

	// where should it be now?
	tnow = gettime_d();

	ldist_ideal = lspeed_ideal * (tnow - t0);
	if(ldist_ideal > ldist) {
		ldist_ideal = ldist;
	}
	rdist_ideal = rspeed_ideal * (tnow - t0);
	if(rdist_ideal > rdist) {
		rdist_ideal = rdist;
	}
		
	// set the motors to updated distances
	ldist_new = ldist_ideal + ldist_init;
	rdist_new = rdist_ideal + rdist_init;
	// convert to encoder counts
	ticks_per_inch = GetShiftState() ? TICKS_PER_INCH_HIGH_GEAR : TICKS_PER_INCH_LOW_GEAR;
	ldist_count = ldist_new * ticks_per_inch;
	rdist_count = rdist_new * ticks_per_inch;
	a_leftDriveTwo.Set(ControlMode::Position, ldist_count);
	a_rightDriveTwo.Set(ControlMode::Position, rdist_count);
	
	return false;
}

bool DiffDrive::ArcTurn(float turnRadius, float turnAngle, bool direction, int first_call){ // radius dictates how gradual turn is, angle dictates how far it goes, direction indicates left vs right
	// do some fancy math here to find the arc length (if its just a circle, then use 2*pi*turnRadius*(turnangle/360)
	if (direction){
		DriveToDist((2 * 3.1415 * turnRadius * (turnAngle/360) * 10.0 * 4096), (2 * 3.1415 * (turnRadius + WHEEL_DISTANCE) * (turnAngle/360) * 10.0 * 4096), 0.5, 0);
	}
	else{
		DriveToDist((2 * 3.1415 * (turnRadius + WHEEL_DISTANCE) * (turnAngle/360) * 10.0 * 4096), (2 * 3.1415 * (turnRadius) * (turnAngle/360) * 10.0 * 4096), 0.5, 0);
	}
	return false;
}

void DiffDrive::GenerateTrajectory(){
	/*
	points[0] = p1;
	points[1] = p2;
	points[2] = p3;
	TrajectoryCandidate candidate;
	*/
	// Prepare the Trajectory for Generation.
	//
	// Arguments:
	// Fit Function:        FIT_HERMITE_CUBIC or FIT_HERMITE_QUINTIC
	// Sample Count:        PATHFINDER_SAMPLES_HIGH (100 000)
	//                      PATHFINDER_SAMPLES_LOW  (10 000)
	//                      PATHFINDER_SAMPLES_FAST (1 000)
	// Time Step:           0.001 Seconds
	// Max Velocity:        15 m/s
	// Max Acceleration:    10 m/s/s
	// Max Jerk:            60 m/s/s/s
	// pathfinder_prepare(points, 3, FIT_HERMITE_CUBIC, PATHFINDER_SAMPLES_HIGH, 0.001, 15.0, 10.0, 60.0, &candidate);

	// int length = candidate.length;

	// Array of Segments (the trajectory points) to store the trajectory in
	// Segment *trajectory = malloc(length * sizeof(Segment));

	// Generate the trajectory
	// int result = pathfinder_generate(&candidate, trajectory);
	// if (result < 0) { // An error occured }
}

void DiffDrive::ZeroEncoders(){
	totCountLeft = 0;
	totCountRight = 0;
	lastCountLeft = 0;
	lastCountRight = 0;

	a_leftDriveTwo.SetSelectedSensorPosition(0, kPIDLoopIdx, kTimeoutMs);
	a_rightDriveTwo.SetSelectedSensorPosition(0, kPIDLoopIdx, kTimeoutMs);
}

void DiffDrive::UpdateDistance(){
	GetDistanceLeft();
	GetDistanceRight();
}

float DiffDrive::GetDistanceLeft(){
	// returns distance in inches
	long count;
	float ret;
	float ticks_per_inch;
	
	count = a_leftDriveTwo.GetSelectedSensorPosition(0);
	/*
	// add change since last reading
	totCountLeft += (count - lastCountLeft);
	// did it rollover?
	if(labs(count - lastCountLeft) > 2048) {
		// rollover
		if((count - lastCountLeft) < -2048) {
			// increasing count rollover
			totCountLeft += 4096;
		} else 	if((count - lastCountLeft) > 2048) {
			// decreasing count rollover
			totCountLeft -= 4096;
		}
	}

	// update for next time
	lastCountLeft = count;
	*/

	// convert to inches
	// ticks_per_inch = GetShiftState() ? TICKS_PER_INCH_HIGH_GEAR : TICKS_PER_INCH_LOW_GEAR;
	ticks_per_inch = TICKS_PER_INCH_HIGH_GEAR;
	ret = count / (float)ticks_per_inch;
	
	return ret;
}

float DiffDrive::GetDistanceRight(){
	// returns distance in inches
	long count;
	float ret;
	float ticks_per_inch;
	
	count = a_rightDriveTwo.GetSelectedSensorPosition(0);
	/*
	// add change since last reading
	totCountRight += (count - lastCountRight);
	// did it rollover?
	if(labs(count - lastCountRight) > 2048) {
		// rollover
		if((count - lastCountRight) < -2048) {
			// increasing count rollover
			totCountRight += 4096;
		} else 	if((count - lastCountRight) > 2048) {
			// decreasing count rollover
			totCountRight -= 4096;
		}
	}

	// update for next time
	lastCountRight = count;
	*/

	// convert to inches
	// ticks_per_inch = GetShiftState() ? TICKS_PER_INCH_HIGH_GEAR : TICKS_PER_INCH_LOW_GEAR;
	ticks_per_inch = TICKS_PER_INCH_HIGH_GEAR;
	ret = count / (float)ticks_per_inch;
	
	return ret;
}

float DiffDrive::GetAvgDistance(){
	return ((GetDistanceLeft() + GetDistanceRight()) / 2.0);
}

float DiffDrive::GetVelocityLeft(){
	return a_leftDriveTwo.GetSensorCollection().GetPulseWidthVelocity();
	// theo part two
}

float DiffDrive::GetVelocityRight(){
	return a_rightDriveTwo.GetSensorCollection().GetPulseWidthVelocity();
}
