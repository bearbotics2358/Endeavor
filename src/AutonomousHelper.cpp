#include <WPILib.h>
#include "AutonomousHelper.h"

AutonomousHelper::AutonomousHelper(){
	/*
	 * We can test the AutoHelper using smartdashboard and the "GameData" field.
	 * Just put in 3 letters indicating field layout
	 * "LRL"
	 * and the code interprets it properly
	 */

}

bool AutonomousHelper::GetAllianceSide(){
	return (frc::DriverStation::GetInstance().DriverStation::Alliance::kBlue == frc::DriverStation::GetInstance().DriverStation::GetAlliance());
}

int AutonomousHelper::GetAllianceStation(){
	return (frc::DriverStation::GetInstance().DriverStation::GetLocation());
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


