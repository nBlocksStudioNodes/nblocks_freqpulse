#include "freqpulse.h"

nBlock_FreqPulse::nBlock_FreqPulse(PinName pinOut, float frequency, float duration):
	_pwm(pinOut) {
		
	if (frequency <= 0.0) {
		// Disable if frequency is not valid
		_duration = 0;
	}
	
	else {
		_duration = duration;
		
		// PWM Config
		// PWM Idle state is GND
		_pwm.write(0);
		_pwm.period(1.0/frequency);
	}
	
	// Reset values
	must_trigger = 0;
	
}


void nBlock_FreqPulse::triggerInput(nBlocks_Message message){
	// input 0 receives an intensity value in range 0-255
	if (message.inputNumber == 0) {
		// Set flag so we start the pulse at endFrame
		must_trigger =  1;
	}
}

void nBlock_FreqPulse::endFrame(void){

	if (must_trigger) {
		must_trigger = 0;
		
		// If duration is 0, the node is disabled
		if (_duration > 0.0) {
			// Add the callback
			(this->_timer).attach(callback(this, &nBlock_FreqPulse::_timeout), _duration);
			
			// Output wave on
			_pwm.write(0.5f);
		}
	}
	
	
}

void nBlock_FreqPulse::_timeout(void) {
	_pwm.write(0);
}


