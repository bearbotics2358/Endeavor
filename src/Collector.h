#ifndef SRC_COLLECTOR_H_
#define SRC_COLLECTOR_H_

#include <WPILib.h>
#include "ctre/Phoenix.h"
#include <CompPrefs.h>

class Collector
{
public:
	Collector(int TalonPortLeft, int TalonPortRight);
	virtual ~Collector() = default;
	void Init();
	void Update(float val);
	void Disable();
private:
	WPI_TalonSRX a_leftCollector;
	WPI_TalonSRX a_rightCollector;
};

#endif
