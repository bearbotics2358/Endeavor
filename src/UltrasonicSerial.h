#ifndef SRC_ULTRASONICSERIAL_H_
#define SRC_ULTRASONICSERIAL_H_

#include <WPILib.h>
#include <PracticePrefs.h>

class UltrasonicSerial
{
public: UltrasonicSerial();
	virtual ~UltrasonicSerial() = default;
	void Init();
	void Update();
	float GetUltraA();
	float GetUltraB();
	float GetUltraC();
	float GetUltraD();
	float GetUltraE();
	float GetUltraF();
	float GetFrontLeft();
	float GetFrontRight();
	float GetLeftSide();
	float GetRightSide();
	float GetRearLeft();
	float GetRearRight();
	void EnablePort(int port);
	void DisablePort(int port);
	float GetForwardAngle();
	float GetBackwardAngle();


	/*
	 * Alexis' Documentation:
	 * Call update in periodic, it'll update values of each ultrasonic
	 * call each get method individually when needed to get a specific value.
	 */

private:
	#define BUFFER_SIZE 100

	SerialPort a_Ultra;
	float ultraA;
	float ultraB;
	float ultraC;
	float ultraD;
	float ultraE;
	float ultraF;
	int readIndex;
	char readBuffer[BUFFER_SIZE];
};

#endif
