#include <WPILib.h>
#include "CollectorArm.h"

CollectorArm::CollectorArm(int pivotMotorPort)
: a_pivotMotor(pivotMotorPort),
  a_ArmSolenoidOne(PCM_PORT, SOL_PORT_TWO, SOL_PORT_THR),
  a_ArmSolenoidTwo(PCM_PORT, SOL_PORT_FOU, SOL_PORT_FIV),
  a_Collector(LEFT_COLLECTOR_TALON, RIGHT_COLLECTOR_TALON),
  a_Potentiometer(POTENTIOMETER_PORT)
{

}

void CollectorArm::Init()
{
	Update(0);
	a_Collector.Init();
	a_Potentiometer.InitAccumulator();
}

void CollectorArm::Update(float angle)
{
	a_pivotMotor.Set(angle);
}

void CollectorArm::UpdateRollers(float velo)
{
	a_Collector.Update(velo);
}

void CollectorArm::RollerPos(int state){
	switch(state){
	case 0: // theo rest?
		a_ArmSolenoidOne.Set(DoubleSolenoid::kForward);
		a_ArmSolenoidTwo.Set(DoubleSolenoid::kForward);
		break;

	case 1: // theo middle
		a_ArmSolenoidOne.Set(DoubleSolenoid::kForward);
		a_ArmSolenoidTwo.Set(DoubleSolenoid::kReverse);
		break;

	case 2: // theo up
		a_ArmSolenoidOne.Set(DoubleSolenoid::kReverse);
		a_ArmSolenoidTwo.Set(DoubleSolenoid::kReverse);
		break;
	case 3: // theo nothing?
		a_ArmSolenoidOne.Set(DoubleSolenoid::kReverse);
		a_ArmSolenoidTwo.Set(DoubleSolenoid::kForward);
		break;
	}
}

float CollectorArm::GetAngle1()
{
	return (a_Potentiometer.GetValue());
}

float CollectorArm::GetAngle2()
{
	return (a_Potentiometer.GetAccumulatorValue());
}

void CollectorArm::Disable()
{
	a_pivotMotor.Set(0);
}
