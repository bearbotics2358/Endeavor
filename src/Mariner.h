#ifndef SRC_MARINER_H_
#define SRC_MARINER_H_

#include <WPILib.h>
#include <DiffDrive.h>

class Mariner{

public:
	Mariner(DiffDrive &DiffDrive, float mJ, float mV);
	void SetMaxJerk(float mJ);
	void SetMaxVelo(float mV);
	bool RunPath(float cD, float tD);
	float GetCurrentPathStatus();
	float DataCollectionMaxJerk();
	float DataCollectionMaxVelo();

private:
	float maxJerk = 0;
	float maxVelo = 0;
	float targetDistance = 0;
	float currentDistance = 0;

};

#endif
