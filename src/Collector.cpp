#include <WPILib.h>
#include "Collector.h"

Collector::Collector(int TalonPortLeft, int TalonPortRight)
: a_leftCollector(TalonPortLeft),
  a_rightCollector(TalonPortRight)
{

}

void Collector::Update(float val)
{
	a_leftCollector.Set(val);
	a_rightCollector.Set(val);
}
