#include <WPILib.h>
#include "Lifter.h"

Lifter::Lifter(int TalonPortLeft, int TalonPortRight)
: a_LifterMotorLeft(TalonPortLeft),
  a_LifterMotorRight(TalonPortRight)
{

}

void Lifter::Init()
{
	Update(0);
}

void Lifter::SetLeftPIDF(float p, float i, float d, float f){
	a_LifterMotorLeft.Config_kP(kPIDLoopIdx, p, kTimeoutMs);
	a_LifterMotorLeft.Config_kI(kPIDLoopIdx, i, kTimeoutMs);
	a_LifterMotorLeft.Config_kD(kPIDLoopIdx, d, kTimeoutMs);
	a_LifterMotorLeft.Config_kF(kPIDLoopIdx, f, kTimeoutMs);
}

void Lifter::SetRightPIDF(float p, float i, float d, float f){
	a_LifterMotorRight.Config_kP(kPIDLoopIdx, p, kTimeoutMs);
	a_LifterMotorRight.Config_kI(kPIDLoopIdx, i, kTimeoutMs);
	a_LifterMotorRight.Config_kD(kPIDLoopIdx, d, kTimeoutMs);
	a_LifterMotorRight.Config_kF(kPIDLoopIdx, f, kTimeoutMs);
}

void Lifter::Update(float val)
{
	a_LifterMotorLeft.Set(val);
	a_LifterMotorRight.Set(val);
}

void Lifter::Disable()
{
	a_LifterMotorLeft.Set(0);
	a_LifterMotorRight.Set(0);
}
