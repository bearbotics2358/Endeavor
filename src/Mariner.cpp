#include <Mariner.h>
#include <WPILib.h>
#include <Math.h>
#include <stdlib.h>
#include <sys/time.h>

Mariner::Mariner(float mJ, float mV){
	maxJerk = mJ;
	maxVelo = mV;
}

bool Mariner::RunPath(float cD, float tD){
	return false;
}
