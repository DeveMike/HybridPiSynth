#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>//tätä ei vissii tarvii?
#include <pigpio.h>
//mitkä kirastot oikeesti tarvii?fdfdsa
#include "Parameter.h"
#include "HybridPiSynth.h"

void* hardwarePWMout()
{
	const int BUTTON = 4;
	gpioSetMode(BUTTON, PI_INPUT);
	
	int gate;
	double filteredBtn = 0;
	enum ADSRstages{A, D, R};
	enum ADSRstages currentStage = R;
	//double adsrOutput = 0.0;//<-----------------
	double output = 0.0;
	unsigned int uiOutput;

	while(1)
	{
		if(exitRequested) break;

		// Calculate parameter values
		for(int i=0; i<MAX_PARAMS; i++)
		{
			parameters[i].modSum = 0;
			for(int j=0; j<MAX_PARAMS; j++)
			{
				parameters[i].modSum += parameters[i].modArr[j].amount * (*parameters[i].modArr[j].out);
			}
			if(parameters[i].updateValue==NULL) parameters[i].value = parameters[i].modSum;
			else
			{
				parameters[i].updateValue(parameters[i].modSum);
			}
		}
		
		//---------------------------------------

		filteredBtn = 0.05*!gpioRead(BUTTON) + 0.95*filteredBtn;// Debounce nimee uudellee!
		gate = filteredBtn > 0.5; //Funktioon nämä? 
		if(gate)
		{
			if(currentStage==R) currentStage = A;
			if(currentStage==A)
			{
				adsrOutput = parameters[1].value*2 + parameters[1].secondaryValue*adsrOutput;	
			}
			if(adsrOutput>=1)
			{
				currentStage = D;
				adsrOutput = log(adsrOutput) + 1;// Curb fast attack overshoot
			}
			if(currentStage==D)
			{
				adsrOutput = parameters[2].value*parameters[3].value + parameters[2].secondaryValue*adsrOutput;
			}
		}
		else
		{
			currentStage = R;
			adsrOutput = parameters[4].secondaryValue*adsrOutput;
		}
		
		output = parameters[analOutIndex].value;
		
		output = output>1 ? 1 : output<0 ? 0 : output;
		uiOutput = 1000000*output;
		gpioHardwarePWM(18, 500000, uiOutput);
	}
	
	gpioTerminate();
	return NULL;
}
