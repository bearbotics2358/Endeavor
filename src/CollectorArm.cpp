#include <WPILib.h>
#include "CollectorArm.h"

CollectorArm::CollectorArm(int pivotMotorPort)
: a_pivotMotor(pivotMotorPort)
{

}

void CollectorArm::Init()
{
	Update(0);
}

void CollectorArm::Update(float angle)
{
	// a_pivotMotor.SetAngle(angle);
}

float CollectorArm::GetAngle()
{
	return (0);
}

void CollectorArm::Disable()
{
	a_pivotMotor.Set(0);
}
