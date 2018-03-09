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
	a_Collector.Init();
	a_pivotMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, 0, 0);
	a_pivotMotor.SetNeutralMode(NeutralMode::Brake);
	a_pivotMotor.SetInverted(true);
	a_Collector.InvertRight();
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
	a_pivotMotor.Set(ControlMode::Position, Map(angle, 180, 45, LOWER_ANGLE, UPPER_STOP));
}

void CollectorArm::UpdateRollers(float velo)
{
	a_Collector.Update(velo);
}

void CollectorArm::RollerPos(int state){
	switch(state){
	case 0: // theo af?
		a_ArmSolenoidTwo.Set(DoubleSolenoid::kReverse);
		a_ArmSolenoidThree.Set(DoubleSolenoid::kForward);
		break;

	case 1: // theo af?
		a_ArmSolenoidTwo.Set(DoubleSolenoid::kForward);
		a_ArmSolenoidThree.Set(DoubleSolenoid::kReverse);
		break;

	case 2: // theo af?
		a_ArmSolenoidTwo.Set(DoubleSolenoid::kReverse);
		a_ArmSolenoidThree.Set(DoubleSolenoid::kReverse);
		break;
	case 3: // theo af?
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

float CollectorArm::GetAngle1()
{
	return (a_pivotMotor.GetSelectedSensorPosition(0) & 0xFFF);
}

float CollectorArm::GetAngle2()
{

	return (Map((a_pivotMotor.GetSelectedSensorPosition(0) & 0xFFF), 180, 50, REST_POS, UPPER_STOP));
}

void CollectorArm::SetArmPIDF(float p, float i, float d, float f){
	a_pivotMotor.Config_kF(kPIDLoopIdx, p, kTimeoutMs);
	a_pivotMotor.Config_kP(kPIDLoopIdx, i, kTimeoutMs);
	a_pivotMotor.Config_kI(kPIDLoopIdx, d, kTimeoutMs);
	a_pivotMotor.Config_kD(kPIDLoopIdx, f, kTimeoutMs);

}

void CollectorArm::Disable()
{
	a_pivotMotor.Set(0);
}

float CollectorArm::Map(float x, float in_min, float in_max, float out_min, float out_max){
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
