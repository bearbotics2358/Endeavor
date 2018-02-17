#ifndef SRC_UNDERGLOW_H_
#define SRC_UNDERGLOW_H_

#include <WPILib.h>
#include <CompPrefs.h>

class Underglow
{
public: Underglow();
	virtual ~Underglow() = default;
	void Init();
	void GoBlue();
	void GoRed();
	void GoWhite();
	void GoDark();
	void FadeBlue();
	void FadeRed();
	void FadeDark();
	void BlueBounce();
	void RedBounce();
	void Rainbow();
	void BlueLaser();

private:
	SerialPort a_Arduino;
};

#endif
