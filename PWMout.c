#include <math.h>
#include <pigpio.h>
#include "HybridPiSynth.h"

#define BUTTON 4

void* hardwarePWMout()
{
	gpioSetMode(BUTTON, PI_INPUT);

	int gate;
	double debouncedBtn = 0, pureSaw = 1;
	enum ADSRstages{A, D, R};
	enum ADSRstages currentStage = R;
	unsigned int analOut;

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

		// OSCILLATOR
		pureSaw = OSC_FREQ_VALUE*(-1.5) + OSC_2NDARY_FREQ_VALUE*pureSaw;
		if(pureSaw <= 0)
			pureSaw = 1;
		g_sawOutput = pureSaw; // Implementoidaa koht loppuu.

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
		ANAL_OUT_VALUE = ANAL_OUT_VALUE>1 ? 1 : ANAL_OUT_VALUE<0 ? 0 : ANAL_OUT_VALUE;
		analOut = 1000000*ANAL_OUT_VALUE;
		gpioHardwarePWM(18, 500000, analOut);
	}

	return NULL;
}
