#include <WPILib.h>
#include "DiffDrive.h"
#include "ctre/Phoenix.h"
#include <Math.h>
#include <pathfinder.h>

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
		  a_Drivetrain.TankDrive((-1.0 * stick2.GetRawAxis(1)), (-1.0 * stick3.GetRawAxis(1)), false);
		break;
	  default:
		  a_Drivetrain.TankDrive(0, 0, false); // theo disable
	}
}

void DiffDrive::UpdateVal(float left, float right){
	a_Drivetrain.TankDrive(left, right, false);
}

bool DiffDrive::UpdateAngle(float curAngle, float tarAngle){ // rets true when its right.
	if(curAngle > (tarAngle - 3)) {
		if(fabs(tarAngle - curAngle) > 10) {
			UpdateVal(-0.3, 0.3);
		} else {
			UpdateVal(-0.2, 0.2);
		}
	} else if(curAngle < tarAngle + 3) {
		if(fabs(tarAngle - curAngle) > 10) {
			UpdateVal(0.3, -0.3);
		} else {
			UpdateVal(0.2, -0.2);
		}
	} else {
		UpdateVal(0.0, 0.0);
		return true;
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
	return (a_DriveSolenoid.Get() == DoubleSolenoid::kForward); // is forward low or high? dunno.
}

void DiffDrive::GoDistance(float targetDistance){
	a_leftDriveTwo.Set(ControlMode::Position, targetDistance * 4096);
	a_rightDriveTwo.Set(ControlMode::Position, targetDistance * 4096);
}

void DiffDrive::DriveStraight(float left, float right){
	double leftDistance = GetDistanceLeft();
	double rightDistance = GetDistanceRight();
	SmartDashboard::PutNumber("left auto", leftDistance);
	SmartDashboard::PutNumber("right auto", rightDistance);
	// difference in inches:
	double diff = (leftDistance - rightDistance);
	if(fabs(diff) < 0.10) {
		a_leftDriveTwo.Set(left);
		a_rightDriveTwo.Set(right);
	} else if(fabs(diff) < 0) {
		// turn right
		a_leftDriveTwo.Set((9.0/7.0) * left);
		a_rightDriveTwo.Set((7.0/9.0) * right);
	} else {
		//turn left
		a_leftDriveTwo.Set((7.0/9.0) * left);
		a_rightDriveTwo.Set((9.0/7.0) * right);
	}
}

void DiffDrive::ArcTurn(float turnRadius, float turnAngle, bool direction){ // radius dictates how gradual turn is, angle dictates how far it goes, direction indicates left vs right
	// do some fancy math here to find the arc length (if its just a circle, then use 2*pi*turnRadius*(turnangle/360)
	if (direction){
		a_leftDriveTwo.Set(ControlMode::Position, 2 * 3.1415 * turnRadius * (turnAngle/360) * 10.0 * 4096);
		a_rightDriveTwo.Set(ControlMode::Position, 2 * 3.1415 * (turnRadius + WHEEL_DISTANCE) * (turnAngle/360) * 10.0 * 4096);
	}
	else{
		a_leftDriveTwo.Set(ControlMode::Position, 2 * 3.1415 * (turnRadius + WHEEL_DISTANCE) * (turnAngle/360) * 10.0 * 4096);
		a_rightDriveTwo.Set(ControlMode::Position, 2 * 3.1415 * turnRadius * (turnAngle/360) * 10.0 * 4096);
	}
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

}

float DiffDrive::GetDistanceLeft(){
	return (a_leftDriveTwo.GetSelectedSensorPosition(0) & 0xFFF);
	// works but rollover is not a thing(?)
}

float DiffDrive::GetDistanceRight(){
	return (a_rightDriveTwo.GetSelectedSensorPosition(0) & 0xFFF);
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
