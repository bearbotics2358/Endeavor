#ifndef SRC_MARINER_H_
#define SRC_MARINER_H_

class Mariner{

public:
	Mariner(float mJ, float mV);
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
