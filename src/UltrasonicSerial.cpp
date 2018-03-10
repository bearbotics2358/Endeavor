#include <WPILib.h>
#include <Math.h>
#include "UltrasonicSerial.h"

// return all distances in inches
UltrasonicSerial::UltrasonicSerial():
	a_Ultra(BAUD_RATE_SOUL, USB_PORT_SOUL, DATA_BITS_SOUL, PARITY_SOUL, STOP_BITS_SOUL)
			// USB1 is the onboard port closest to the center of the rio
			// I dunno which one USB2 is yet. (Rio docs aren't very helpful)
{
	ultraA = 0;
	ultraB = 0;
	ultraC = 0;
	ultraD = 0;
	ultraE = 0;
	ultraF = 0;
	readIndex = 0;
}

void UltrasonicSerial::Init(){
	ultraA = 0;
	ultraB = 0;
	ultraC = 0;
	ultraD = 0;
	ultraE = 0;
	ultraF = 0;
	readIndex = 0;
	for(int i = 0; i < BUFFER_SIZE; i++) {
		readBuffer[i] = 0;
	}
}

void UltrasonicSerial::Update(){
	int dist;
	
	while (a_Ultra.GetBytesReceived() > 0){
		a_Ultra.Read(&readBuffer[readIndex], 1);
		if((readBuffer[readIndex] == '\r') || (readBuffer[readIndex] == '\t')) {
			readBuffer[readIndex] = 0;
			if(readIndex == 6) {
				switch(readBuffer[0]) {
					case 'A':
						dist = strtol(&readBuffer[1], (char **)NULL, 10);
						// convert mm to inches
						ultraA = (float)dist/25.4;
						break;

					case 'B':
						dist = strtol(&readBuffer[1], (char **)NULL, 10);
						// convert mm to inches
						ultraB = (float)dist/25.4;
						break;

					case 'C':
						dist = strtol(&readBuffer[1], (char **)NULL, 10);
						// convert mm to inches
						ultraC = (float)dist/25.4;
						break;

					case 'D':
						dist = strtol(&readBuffer[1], (char **)NULL, 10);
						// convert mm to inches
						ultraD = (float)dist/25.4;
						break;

					case 'E':
						dist = strtol(&readBuffer[1], (char **)NULL, 10);
						// convert mm to inches
						ultraE = (float)dist/25.4;
						break;

					case 'F':
						dist = strtol(&readBuffer[1], (char **)NULL, 10);
						// convert mm to inches
						ultraF = (float)dist/25.4;
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

float UltrasonicSerial::GetUltraA(){
	return ultraA;
}

float UltrasonicSerial::GetUltraB(){
	return ultraB;
}

float UltrasonicSerial::GetUltraC(){
	return ultraC;
}

float UltrasonicSerial::GetUltraD(){
	return ultraD;
}

float UltrasonicSerial::GetUltraE(){
	return ultraE;
}

float UltrasonicSerial::GetUltraF(){
	return ultraF;
}



float UltrasonicSerial::GetFrontLeft(){
	return GetUltraD();
}

float UltrasonicSerial::GetFrontRight(){
	return GetUltraA();
}

float UltrasonicSerial::GetLeftSide(){
	return GetUltraE();
}

float UltrasonicSerial::GetRightSide(){
	return GetUltraB();
}

float UltrasonicSerial::GetRearLeft(){
	return GetUltraF();
}

float UltrasonicSerial::GetRearRight(){
	return GetUltraC();
}


void UltrasonicSerial::EnablePort(int port)
{
	char cmd[3];
	cmd[0] = 'A' + port;
	cmd[1] = '1';
	cmd[2] = '\r';
	a_Ultra.Write(cmd, 3);
	a_Ultra.Flush();
}

void UltrasonicSerial::DisablePort(int port)
{
	char cmd[3];
	cmd[0] = 'A' + port;
	cmd[1] = '0';
	cmd[2] = '\r';
	a_Ultra.Write(cmd, 3);
	a_Ultra.Flush();
}

float UltrasonicSerial::GetForwardAngle(){
	// returns range of -90 to 90
	// positive angles mean bot is counter-clockwise relative to straight on
	// negative angles mean bot is clockwise relative to straight on
	float ret;
	float delta = GetFrontLeft() - GetFrontRight();

	ret = atan2(delta, FRONT_CENTER_DISTANCE) * (180.0/M_PI);
	return ret;
}

float UltrasonicSerial::GetBackwardAngle(){
	// returns range of -90 to 90
	// positive angles mean bot is counter-clockwise relative to straight on
	// negative angles mean bot is clockwise relative to straight on
	float ret;
	float delta = GetRearRight() - GetRearLeft();

	ret = atan2(delta, REAR_CENTER_DISTANCE) * (180.0/M_PI);
	return ret;
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
