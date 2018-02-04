#ifndef SRC_LIFTER_H_
#define SRC_LIFTER_H_

#include <PracticePrefs.h>
#include <WPILib.h>
#include "ctre/Phoenix.h"

class Lifter
{
public:
	Lifter(int TalonPort);
	virtual ~Lifter() = default;
	void Init();
	void Update(float val);
	void Disable();
private:
	WPI_TalonSRX a_LifterMotor;
};

#endif
