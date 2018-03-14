#ifndef SRC_COLLECTORARM_H_
#define SRC_COLLECTORARM_H_

#include <WPILib.h>
#include "ctre/Phoenix.h"
#include <Collector.h>
#include <CompPrefs.h>

class CollectorArm
{
public:
	CollectorArm(int pivotArmPort);
	virtual ~CollectorArm() = default;
	void Init();
	void Init(float p, float i, float d, float f);
	void UpdateValue(float val);
	void UpdateAngle(float angle);
	void UpdateRollers(float velo);
	void RollerPos(int state);
	void Clamp();
	void Release();
	bool GetClampState();
	bool CubePresent();
	void SetAngle(float val);
	float GetAngle1();
	float GetAngle2();
	void SetArmPIDF(float p, float i, float d, float f);
	void Disable();
private:
	float Map(float x, float in_min, float in_max, float out_min, float out_max);
	WPI_TalonSRX a_pivotMotor;
	DoubleSolenoid a_ArmSolenoidOne;
	DoubleSolenoid a_ArmSolenoidTwo;
	DoubleSolenoid a_ArmSolenoidThree;
	Collector a_Collector;
	int kSlotIdx = 0;
	int kPIDLoopIdx = 0;
	int kTimeoutMs = 10;
};

#endif
