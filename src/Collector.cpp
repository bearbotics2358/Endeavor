#include <WPILib.h>
#include "Collector.h"
#include "ctre/Phoenix.h"

Collector::Collector(int TalonPortLeft, int TalonPortRight)
: a_leftCollector(TalonPortLeft),
  a_rightCollector(TalonPortRight),
  a_BeamBreak()
{

}

void Collector::Init()
{
	a_BeamBreak.Init();
	Update(0);
}

void Collector::Update(float val)
{
	a_leftCollector.Set(ControlMode::PercentOutput, val);
	a_rightCollector.Set(ControlMode::PercentOutput, val);
}

void Collector::InvertLeft(){
	a_leftCollector.SetInverted(true);
}

void Collector::InvertRight(){
	a_rightCollector.SetInverted(true);
}

bool Collector::GetCubeStatus(){
	return a_BeamBreak.GetStatus();
}

void Collector::Disable()
{
	a_leftCollector.Set(ControlMode::PercentOutput, 0);
	a_rightCollector.Set(ControlMode::PercentOutput, 0);
}
