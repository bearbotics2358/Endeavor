#ifndef SRC_ULTRASONICSERIAL_H_
#define SRC_ULTRASONICSERIAL_H_

#include <WPILib.h>
#include "Prefs.h"

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
	#define BAUD_RATE_SOUL 38400
	#define DATA_BITS 8
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