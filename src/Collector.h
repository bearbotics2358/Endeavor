#ifndef SRC_COLLECTOR_H_
#define SRC_COLLECTOR_H_

#include <WPILib.h>
#include "ctre/Phoenix.h"
#include <BeamBreak.h>
#include <PracticePrefs.h>

class Collector
{
public:
	Collector(int TalonPortLeft, int TalonPortRight);
	virtual ~Collector() = default;
	void Init();
	void Update(float val);
	void InvertLeft();
	void InvertRight();
	bool GetCubeStatus();
	void Disable();
private:
	WPI_TalonSRX a_leftCollector;
	WPI_TalonSRX a_rightCollector;
	BeamBreak a_BeamBreak;
};

#endif
