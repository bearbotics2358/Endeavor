#include <WPILib.h>
#include "CollectorArm.h"
#include "ctre/Phoenix.h"

CollectorArm::CollectorArm(int pivotMotorPort)
: a_pivotMotor(pivotMotorPort),
  a_ArmSolenoidOne(PCM_PORT, SOL_PORT_TWO, SOL_PORT_THR),
  a_ArmSolenoidTwo(PCM_PORT, SOL_PORT_FOU, SOL_PORT_FIV),
  a_ArmSolenoidThree(PCM_PORT, SOL_PORT_ZRO, SOL_PORT_ONE),
  a_Collector(LEFT_COLLECTOR_TALON, RIGHT_COLLECTOR_TALON)
{

}

void CollectorArm::Init()
{
	UpdateValue(0);
	UpdateRollers(0);
	a_Collector.Init();
	a_pivotMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, 0, 0);
	a_pivotMotor.SetNeutralMode(NeutralMode::Brake);
	a_pivotMotor.SetInverted(true);
	a_Collector.InvertRight();
	SetAngle(0.0);
	// a_pivotMotor.SetSensorPhase(false); // possibly needs this?

	/* Notes:
	 * SolOne is for the fingers
	 * SolsTwo and Three are for the CollectorPosition.
	 */
}

void CollectorArm::Init(float p, float i, float d, float f)
{
	Init();
	SetArmPIDF(p,i,d,f);
}

void CollectorArm::UpdateValue(float val)
{
	a_pivotMotor.Set(ControlMode::PercentOutput, val);
}

void CollectorArm::UpdateAngle(float angle)
{
	a_pivotMotor.Set(ControlMode::Position, angle);
}

void CollectorArm::UpdateRollers(float velo)
{
	a_Collector.Update(Map(velo, REST_POS, UPPER_STOP, 50.0, 180.0));
}

void CollectorArm::RollerPos(int state){
	switch(state){
	case 0: // middle pos - PRAC
		a_ArmSolenoidTwo.Set(DoubleSolenoid::kReverse);
		a_ArmSolenoidThree.Set(DoubleSolenoid::kForward);
		break;
	case 1: // middle pos - PRAC
		a_ArmSolenoidTwo.Set(DoubleSolenoid::kForward);
		a_ArmSolenoidThree.Set(DoubleSolenoid::kReverse);
		break;
	case 2: // collect - PRAC
		a_ArmSolenoidTwo.Set(DoubleSolenoid::kReverse);
		a_ArmSolenoidThree.Set(DoubleSolenoid::kReverse);
		break;
	case 3: // stow - PRAC
		a_ArmSolenoidTwo.Set(DoubleSolenoid::kForward);
		a_ArmSolenoidThree.Set(DoubleSolenoid::kForward);
		break;
	}
}

void CollectorArm::Clamp(){
	a_ArmSolenoidOne.Set(DoubleSolenoid::kForward);
}

void CollectorArm::Release(){
	a_ArmSolenoidOne.Set(DoubleSolenoid::kReverse);
}

bool CollectorArm::GetClampState(){
	return (a_ArmSolenoidOne.Get() == DoubleSolenoid::kForward); // is forward low or high? dunno.
}

bool CollectorArm::CubePresent(){
	// returns true if the cube is in the collector
	return a_Collector.GetCubeStatus();
}

void CollectorArm::SetAngle(float val){
	a_pivotMotor.SetSelectedSensorPosition(0, kPIDLoopIdx, kTimeoutMs);
}

float CollectorArm::GetAngle1() // returns raw values
{
	float ret = (a_pivotMotor.GetSelectedSensorPosition(0));
	// SmartDashboard::PutNumber("ArmTheta", ret);
	// SmartDashboard::PutNumber("ArmTheta", (ret * 1.0));
	return ret;
}

float CollectorArm::GetAngle2() // returns the corrected value using map function.
{
	float ret = Map((1.0 * (a_pivotMotor.GetSelectedSensorPosition(0))), REST_POS, UPPER_STOP, 50.0, 180.0);
	return ret;
}

void CollectorArm::SetArmPIDF(float p, float i, float d, float f){
	a_pivotMotor.Config_kF(kPIDLoopIdx, p, kTimeoutMs);
	a_pivotMotor.Config_kP(kPIDLoopIdx, i, kTimeoutMs);
	a_pivotMotor.Config_kI(kPIDLoopIdx, d, kTimeoutMs);
	a_pivotMotor.Config_kD(kPIDLoopIdx, f, kTimeoutMs);
}

void CollectorArm::Disable(){
	a_pivotMotor.Set(0);
}

float CollectorArm::Map(float x, float in_min, float in_max, float out_min, float out_max){
	float ret = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	return ret;
}
