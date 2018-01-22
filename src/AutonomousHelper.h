#ifndef SRC_AUTONOMOUSHELPER_H_
#define SRC_AUTONOMOUSHELPER_H_

#include <WPILib.h>
#include "Prefs.h"

class AutonomousHelper
{
public:	AutonomousHelper();
	virtual ~AutonomousHelper() = default;
	bool GetAllianceSide();
	bool GetAllianceSwitch();
	bool GetAllianceScale();
	bool GetOpponentSwitch();

private:
	std::string GetGameData();
	std::string gameData;
};

#endif
