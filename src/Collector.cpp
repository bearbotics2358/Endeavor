#include <WPILib.h>
#include "Collector.h"

Collector::Collector(int TalonPortLeft, int TalonPortRight)
: a_leftCollector(TalonPortLeft),
  a_rightCollector(TalonPortRight)
{

}

void Collector::Init()
{
	Update(0);
}

void Collector::Update(float val)
{
	a_leftCollector.Set(val);
	a_rightCollector.Set(val);
}

void Collector::Disable()
{
	a_leftCollector.Set(0);
	a_rightCollector.Set(0);
}
