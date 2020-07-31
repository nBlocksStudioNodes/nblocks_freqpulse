#include "freqpulse.h"

nBlock_FreqPulse::nBlock_FreqPulse(PinName pinOut, float frequency, float duration):
	_pwm(pinOut) {
		
	_duration = duration;
	
	// PWM Config
	// PWM Idle state is GND
	_pwm.write(0);
	_pwm.frequency(frequency);
	
	// Reset values
	must_update = 0;
	
}


void nBlock_FreqPulse::triggerInput(uint32_t inputNumber, uint32_t value){
	// input 0 receives an intensity value in range 0-255
	if (inputNumber == 0) {
		// Set flag so we start the pulse at endFrame
		must_update =  1;
	}
}

void nBlock_FreqPulse::endFrame(void){

	if (must_update) {
		must_update = 0;
		
		// Add the callback
		(this->_timer).attach(callback(this, &nBlock_FreqPulse::_timeout), _duration);
		
		// Output wave on
		_pwm.write(0.5f);
	}
	
	
}

void nBlock_FreqPulse::_timeout(void) {
	_pwm.write(0);
}


