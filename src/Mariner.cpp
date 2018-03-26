#include <Mariner.h>
#include <DiffDrive.h>
#include <WPILib.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

Mariner::Mariner(DiffDrive &DiffDrive, float mJ, float mV){
	maxJerk = mJ;
	maxVelo = mV;
}

void Mariner::SetMaxJerk(float mJ){
	maxJerk = mJ;
}

void Mariner::SetMaxVelo(float mV){
	maxVelo = mV;
}

bool Mariner::RunPath(float cD, float tD){
	return false;
}

float Mariner::GetCurrentPathStatus(){ // returns a percentage
	return ((currentDistance/targetDistance) * 100.0);
}

float DataCollectionMaxJerk(){

}

float DataCollectionMaxVelo(){

}
