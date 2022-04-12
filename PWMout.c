#include <math.h>
#include <pigpio.h>
#include "HybridPiSynth.h"

void* hardwarePWMout()
{
	const int BUTTON = 4;
	gpioSetMode(BUTTON, PI_INPUT);
	
	int gate;
	double debouncedBtn = 0;
	enum ADSRstages{A, D, R};
	enum ADSRstages currentStage = R;
	unsigned int analOut;

	while(1)
	{
		if(g_exitRequested) break;

		// Calculate parameter values
		for(int i=0; i<MAX_PARAMS; i++)
		{
			modDests[i].modSum = 0;
			for(int j=0; j<MAX_PARAMS; j++)
			{
				modDests[i].modSum += modDests[i].modArr[j].amount * (*modDests[i].modArr[j].out);
			}
			if(modDests[i].updateValue==NULL) modDests[i].value = modDests[i].modSum;
			else
			{
				modDests[i].updateValue(modDests[i].modSum);
			}
		}
		
		//---------------------------------------

		debouncedBtn = 0.05*!gpioRead(BUTTON) + 0.95*debouncedBtn;
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
			g_adsrOutput = RELASE_2NDARY_VALUE*g_adsrOutput;
		}
		
		ANAL_OUT_VALUE = ANAL_OUT_VALUE>1 ? 1 : ANAL_OUT_VALUE<0 ? 0 : ANAL_OUT_VALUE;
		analOut = 1000000*ANAL_OUT_VALUE;
		gpioHardwarePWM(18, 500000, analOut);
	}
	
	gpioTerminate();
	return NULL;
}
