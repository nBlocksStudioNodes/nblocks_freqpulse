#ifndef __NB_FREQPULSE
#define __NB_FREQPULSE

#include "nworkbench.h"

class nBlock_FreqPulse: public nBlockSimpleNode<1> {
public:

    nBlock_FreqPulse(PinName pinOut, float frequency, float duration);
    void triggerInput(nBlocks_Message message);
	void endFrame();
	
   
private:
	// Store duration
	float _duration;
	
	//We use a combination of PWM and Ticker
    PwmOut _pwm;
	Timeout _timer;
	
	// Flag to trigger the pulse at endFrame
	uint32_t must_trigger;
	

	// Timeout callback
    void _timeout(void);
	
};

#endif