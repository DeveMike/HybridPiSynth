#include <math.h>
#include <pigpio.h>
#include "HybridPiSynth.h"

#define BUTTON 4

void* hardwarePWMout()
{
	gpioSetMode(BUTTON, PI_INPUT);

	double pureSaw1 = 1;
	double freq1coeff_a = 0, freq1coeff_b = 0;
	double pureSaw2 = 1;
	double freq2coeff_a = 0, freq2coeff_b = 0;

	int gate;
	double debouncedBtn = 0;
	enum ADSRstages{A, D, R};
	enum ADSRstages currentStage = R;

	unsigned int hw_pwm1, hw_pwm2;

	while(1)
	{
		if(g_exitRequested) break;

		// Calculate values from mod matrix
		for(int i=0; i<MAX_PARAMS; i++)
		{
			modDests[i].modSum = 0;
			for(int j=0; j<MAX_PARAMS; j++)
				modDests[i].modSum += modDests[i].modSources[j].amount * (*modDests[i].modSources[j].out);//toi out pois
			if(modDests[i].updateValue==NULL)
				modDests[i].value = modDests[i].modSum;
			else
				modDests[i].updateValue(modDests[i].modSum);
		}

		//---------------------------------------
		//		DSP
		//---------------------------------------

		// OSCILLATORS

		freq1coeff_a = pow(2, -10*(OSC1_FREQ_VALUE + 0.1*OSC1_FINE_VALUE)); // ei oo oikee
		freq1coeff_b = 1 - freq1coeff_a;
		pureSaw1 = freq1coeff_a*(-1.5) + freq1coeff_b*pureSaw1;
		if(pureSaw1 <= 0)
			pureSaw1 = 1;
		g_saw1output = pureSaw1; // Implementoidaa koht loppuu.
		g_pulse1output = pureSaw1 >= OSC1_PWM_VALUE ? 1 : 0;

		freq2coeff_a = pow(2, -10*(OSC2_FREQ_VALUE + 0.1*OSC2_FINE_VALUE)); // ei oo oikee
		freq2coeff_b = 1 - freq2coeff_a;
		pureSaw2 = freq2coeff_a*(-1.5) + freq2coeff_b*pureSaw2;
		if(pureSaw2 <= 0)
			pureSaw2 = 1;
		g_saw2output = pureSaw2; // Implementoidaa koht loppuu.
		g_pulse2output = pureSaw2 >= OSC2_PWM_VALUE ? 1 : 0;

		// ADSR

		debouncedBtn = 0.01*!gpioRead(BUTTON) + 0.99*debouncedBtn;
		gate = debouncedBtn > 0.5;
		if(gate)
		{
			if(currentStage==R) currentStage = A;
			if(currentStage==A)
			{
				g_adsrOutput = ATTAKC_VALUE*2 + ATTACK_2NDARY_VALUE*g_adsrOutput;
			}
			if(g_adsrOutput>=1)
			{
				currentStage = D;
				g_adsrOutput = log(g_adsrOutput) + 1;// Curb fast attack overshoot
			}
			if(currentStage==D)
			{
				g_adsrOutput = DECAY_VALUE*SUSTAIN_VALUE + DECAY_2NDARY_VALUE*g_adsrOutput;
			}
		}
		else
		{
			currentStage = R;
			g_adsrOutput = RELEASE_2NDARY_VALUE*g_adsrOutput;
		}

		// VCA

		VCA_CV_VALUE = VCA_CV_VALUE >= 0 ? VCA_CV_VALUE : 0; // Half wave rectify
		g_vcaOutput = VCA_IN_VALUE * VCA_CV_VALUE;

		// HARDWARE OUTPUTS

		OUT1_VALUE = OUT1_VALUE>1 ? 1 : OUT1_VALUE<0 ? 0 : OUT1_VALUE; // Clipping
		hw_pwm1 = 1000000*OUT1_VALUE;
		gpioHardwarePWM(18, 500000, hw_pwm1);

		OUT2_VALUE = OUT2_VALUE>1 ? 1 : OUT2_VALUE<0 ? 0 : OUT2_VALUE; // Clipping
		hw_pwm2 = 1000000*OUT2_VALUE;
		gpioHardwarePWM(19, 500000, hw_pwm2);
	}

	return NULL;
}
