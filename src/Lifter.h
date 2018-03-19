#ifndef SRC_LIFTER_H_
#define SRC_LIFTER_H_

#include <WPILib.h>
#include "ctre/Phoenix.h"
#include <PracticePrefs.h>

class Lifter
{
public:
	Lifter(int TalonPortLeft, int TalonPortRight);
	virtual ~Lifter() = default;
	void Init();
	void SetLeftPIDF(float p, float i, float d, float f);
	void SetRightPIDF(float p, float i, float d, float f);
	void Update(float val);
	void Disable();
private:
	WPI_TalonSRX a_LifterMotorLeft;
	WPI_TalonSRX a_LifterMotorRight;

	int kSlotIdx = 0;
	int kPIDLoopIdx = 0;
	int kTimeoutMs = 10;
};

#endif
