#include <WPILib.h>
#include "Underglow.h"

Underglow::Underglow():
	a_Arduino(BAUD_RATE_ARDUINO, USB_PORT_ARDUINO, DATA_BITS_ARDUINO, PARITY_ARDUINO, STOP_BITS_ARDUINO)
{

}

void Underglow::Init(){
	GoDark();
}

void Underglow::GoBlue(){
	a_Arduino.Write("B", 1);
}

void Underglow::GoRed(){
	a_Arduino.Write("C", 1);
}

void Underglow::GoWhite(){
	a_Arduino.Write("W", 1);
}

void Underglow::GoDark(){
	a_Arduino.Write("F", 1); // strips off
}

void Underglow::FadeBlue(){
	a_Arduino.Write("D", 1);
}

void Underglow::FadeRed(){
	a_Arduino.Write("E", 1);
}

void Underglow::FadeDark(){
	a_Arduino.Write("G", 1);
}

void Underglow::BlueBounce(){
	a_Arduino.Write("P", 1);
}

void Underglow::RedBounce(){
	a_Arduino.Write("Q", 1);
}

void Underglow::Rainbow(){
	a_Arduino.Write("Z", 1);
}

void Underglow::BlueLaser(){
	a_Arduino.Write("X", 1);
}
