#include <WPILib.h>
#include "Lifter.h"

Lifter::Lifter(int TalonPort)
: a_LifterMotor(TalonPort)
{

}

void Lifter::Init()
{
	Update(0);
}

void Lifter::Update(float val)
{
	a_LifterMotor.Set(val);
}

void Lifter::Disable()
{
	a_LifterMotor.Set(0);
}
