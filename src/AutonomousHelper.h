#ifndef SRC_AUTONOMOUSHELPER_H_
#define SRC_AUTONOMOUSHELPER_H_

#include <PracticePrefs.h>
#include <WPILib.h>

class AutonomousHelper
{
public:	AutonomousHelper();
	virtual ~AutonomousHelper() = default;
	bool GetAllianceSide();
	bool GetAllianceSwitch();
	bool GetAllianceScale();
	bool GetOpponentSwitch();

	/*
	 * Alexis' Documentation:
	 * Call each method after auto begins
	 * call each get method individually when needed to get a specific value.
	 */

private:
	std::string GetGameData();
};

#endif
