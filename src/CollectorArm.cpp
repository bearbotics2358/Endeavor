#include <WPILib.h>
#include "CollectorArm.h"

CollectorArm::CollectorArm(int pivotMotorPort)
: a_pivotMotor(pivotMotorPort),
  a_ArmSolenoidOne(PCM_PORT, SOL_PORT_ZRO, SOL_PORT_ONE),
  a_ArmSolenoidTwo(PCM_PORT, SOL_PORT_FOU, SOL_PORT_FIV),
  a_ArmSolenoidThree(PCM_PORT, SOL_PORT_SIX, SOL_PORT_SEV),
  a_Collector(LEFT_COLLECTOR_TALON, RIGHT_COLLECTOR_TALON),
  a_Potentiometer(POTENTIOMETER_PORT)
{

}

void CollectorArm::Init()
{
	Update(0);
	a_Collector.Init();
	a_Potentiometer.InitAccumulator();

	/* Notes:
	 * SolOne is for the fingers
	 * SolsTwo and Three are for the CollectorPosition.
	 */
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

bool CollectorArm::GetCubeStatus(){
	// returns true if the cube is in the collector
	return true;
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
