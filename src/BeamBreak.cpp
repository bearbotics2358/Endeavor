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
	return (!(a_Receiver.Get() == inverted));
}

bool BeamBreak::GetStatusThresh(){
	return (!(StatusThresh() == inverted));
}

bool BeamBreak::StatusThresh(){
	return (a_Receiver.Get() > BEAM_BREAK_UPPER_THRESH);
}
