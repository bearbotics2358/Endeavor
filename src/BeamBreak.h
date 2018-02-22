#ifndef SRC_BEAMBREAK_H_
#define SRC_BEAMBREAK_H_

#include <WPILib.h>
#include <CompPrefs.h>

class BeamBreak
{
	public:
		BeamBreak();
		virtual ~BeamBreak() = default;
		void Init();
		void InvertStatus();
		bool GetStatus();
	private:
		DigitalInput a_Receiver;
		bool inverted;

};

#endif
