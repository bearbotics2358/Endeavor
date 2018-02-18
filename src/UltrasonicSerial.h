#ifndef SRC_ULTRASONICSERIAL_H_
#define SRC_ULTRASONICSERIAL_H_

#include <WPILib.h>
#include <CompPrefs.h>

class UltrasonicSerial
{
public: UltrasonicSerial();
	virtual ~UltrasonicSerial() = default;
	void Init();
	void Update();
	int GetUltraOne();
	int GetUltraTwo();
	int GetUltraThree();
	int GetUltraFour();

	/*
	 * Alexis' Documentation:
	 * Call update in periodic, it'll update values of each ultrasonic
	 * call each get method individually when needed to get a specific value.
	 */

private:
	#define BUFFER_SIZE 100

	SerialPort a_Ultra;
	int ultraOne;
	int ultraTwo;
	int ultraThree;
	int ultraFour;
	int readIndex;
	char readBuffer[BUFFER_SIZE];
};

#endif
