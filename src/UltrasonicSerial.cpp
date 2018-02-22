#include <WPILib.h>
#include <Math.h>
#include "UltrasonicSerial.h"

UltrasonicSerial::UltrasonicSerial():
	a_Ultra(BAUD_RATE_SOUL, USB_PORT_SOUL, DATA_BITS_SOUL, PARITY_SOUL, STOP_BITS_SOUL)
			// USB1 is the onboard port closest to the center of the rio
			// I dunno which one USB2 is yet. (Rio docs aren't very helpful)
{
	ultraOne = 0;
	ultraTwo = 0;
	ultraThree = 0;
	ultraFour = 0;
	ultraFive = 0;
	ultraSix = 0;
	frontCenterDistance = 0;
	backCenterDistance = 0;
	readIndex = 0;
}

void UltrasonicSerial::Init(){
	ultraOne = 0;
	ultraTwo = 0;
	ultraThree = 0;
	ultraFour = 0;
	ultraFive = 0;
	ultraSix = 0;
	frontCenterDistance = 0;
	backCenterDistance = 0;
	readIndex = 0;
	for(int i = 0; i < BUFFER_SIZE; i++) {
		readBuffer[i] = 0;
	}
}

void UltrasonicSerial::Update(){
	while (a_Ultra.GetBytesReceived() > 0){
		a_Ultra.Read(&readBuffer[readIndex], 1);
		if((readBuffer[readIndex] == '\r') || (readBuffer[readIndex] == '\t')) {
			readBuffer[readIndex] = 0;
			if(readIndex == 6) {
				switch(readBuffer[0]) {
					case 'A':
						ultraOne = strtol(&readBuffer[1], (char **)NULL, 10);
						break;

					case 'B':
						ultraTwo = strtol(&readBuffer[1], (char **)NULL, 10);
						break;

					case 'C':
						ultraThree = strtol(&readBuffer[1], (char **)NULL, 10);
						break;

					case 'D':
						ultraFour = strtol(&readBuffer[1], (char **)NULL, 10);
						break;

					case 'E':
						ultraFive = strtol(&readBuffer[1], (char **)NULL, 10);
						break;

					case 'F':
						ultraSix = strtol(&readBuffer[1], (char **)NULL, 10);
						break;
				}
			}
		readIndex = 0;
		}
		else {
			readIndex++;
			if(readIndex >= BUFFER_SIZE) {
				readIndex = 0;
			}
		}
	}
}

int UltrasonicSerial::GetUltraOne(){
	return ultraOne;
}

int UltrasonicSerial::GetUltraTwo(){
	return ultraTwo;
}

int UltrasonicSerial::GetUltraThree(){
	return ultraThree;
}

int UltrasonicSerial::GetUltraFour(){
	return ultraFour;
}

int UltrasonicSerial::GetUltraFive(){
	return ultraFive;
}

int UltrasonicSerial::GetUltraSix(){
	return ultraSix;
}

int UltrasonicSerial::GetForwardAngle(){
	// should return range of -90 to 90?
	// upper limits on each end should differ based on robot pos tho
	int lenA = GetUltraOne();
	int lenB = GetUltraTwo();

	if (lenA > lenB){
		lenA = lenA - lenB;
		lenB = frontCenterDistance;
		int lenC = pow((lenA * lenA) + (lenB * lenB), (1/2)); // finds hypotenuse of triangle
		return asin(lenA/lenC) * (180/3.1415);
	}
	else if (lenA < lenB) {
		lenA = lenB - lenA;
		lenB = frontCenterDistance;
		int lenC = pow((lenA * lenA) + (lenB * lenB), (1/2)); // finds hypotenuse of triangle
		return asin(lenA/lenC) * (180/3.1415);
	}
	return 0; // theo no angle b/c straight on
}

int UltrasonicSerial::GetBackwardAngle(){
	// should return range of -90 to 90?
	// upper limits on each end should differ based on robot pos tho
	int lenA = GetUltraFive();
	int lenB = GetUltraSix();

	if (lenA > lenB){
		lenA = lenA - lenB;
		lenB = frontCenterDistance;
		int lenC = pow((lenA * lenA) + (lenB * lenB), (1/2)); // finds hypotenuse of triangle
		return asin(lenA/lenC) * (180/3.1415);
	}
	else if (lenA < lenB) {
		lenA = lenB - lenA;
		lenB = frontCenterDistance;
		int lenC = pow((lenA * lenA) + (lenB * lenB), (1/2)); // finds hypotenuse of triangle
		return asin(lenA/lenC) * (180/3.1415);
	}
	return 0; // theo no angle b/c straight on
}


/*
 * From Mr D's documentation of the connected serial device:
 *
 * Quad_ultrasonic

  This program reads up to 4 Maxbotix ultrasonic sensors and sends
  the output back to the connected computer (CRIO).

  The program triggers one sensor at a time and reads its response.
  It waits up to 100 msec for the response.  If none recevied, it
  substitutes a reading of "999".

  A Maxbotix sensor output string example is "R123<CR>".  The program
  substitutes "A", "B", "C", or "D" for the "R", depending on which
  sensor.

  The CR is replaced with a TAB for all but the last enabled sensor
  to assist in debugging.

  The program uses the Software Serial to read the sensors.  This
  must be the New Software Serial library.  It is the included lib
  for version of Arduino >= 1...

  Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created 2/12/14 BD from a dual software serial example

 updated 2/15/14
 - adding commands to this unit from CRIO
 A0, A1, B0, B1, C0, C1, D0, D1
 updated 2/16/14
 - all working now

 */
