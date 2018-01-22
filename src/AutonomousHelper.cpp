#include <WPILib.h>
#include "AutonomousHelper.h"

AutonomousHelper::AutonomousHelper(){
	gameData = "";
	/*
	 * We can test the AutoHelper using smartdashboard and the "GameData" field.
	 * Just put in 3 letters indicating field layout
	 * "LRL"
	 * and the code should interpret it properly
	 */

}

bool AutonomousHelper::GetAllianceSide(){
	return (true);
}

bool AutonomousHelper::GetAllianceSwitch(){
	return (GetGameData()[0] == 'L');
}
bool AutonomousHelper::GetAllianceScale(){
	return (GetGameData()[1] == 'L');
}
bool AutonomousHelper::GetOpponentSwitch(){
	return (GetGameData()[2] == 'L');
}

std::string AutonomousHelper::GetGameData(){
	return frc::DriverStation::GetInstance().GetGameSpecificMessage();
}
