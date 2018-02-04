#ifndef SRC_COLLECTORARM_H_
#define SRC_COLLECTORARM_H_

#include <WPILib.h>
#include "ctre/Phoenix.h"
#include "Prefs.h"
#include "Collector.h"

class CollectorArm
{
public:
	CollectorArm(int pivotArmPort);
	virtual ~CollectorArm() = default;
	void Init();
	void Update(float angle);
	void UpdateRollers(float velo);
	void RollerPos(int state);
	void Clamp();
	void Release();
	bool GetCubeStatus();
	float GetAngle1();
	float GetAngle2();
	void Disable();
private:
	WPI_TalonSRX a_pivotMotor;
	DoubleSolenoid a_ArmSolenoidOne;
	DoubleSolenoid a_ArmSolenoidTwo;
	DoubleSolenoid a_ArmSolenoidThree;
	Collector a_Collector;
	AnalogInput a_Potentiometer;
};

#endif
