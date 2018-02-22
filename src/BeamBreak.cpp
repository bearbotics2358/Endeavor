#include <WPILib.h>
#include <BeamBreak.h>

BeamBreak::BeamBreak()
: a_Receiver(IR_RECEIVER_PORT)
{
	inverted = false;
}

void BeamBreak::Init(){
	// InvertStatus();
}

void BeamBreak::InvertStatus(){
	inverted = true;
}

bool BeamBreak::GetStatus(){
	return (!((a_Receiver.Get() == 1) == inverted));
}
