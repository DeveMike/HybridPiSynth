#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <pigpio.h>
//#include "mylib/mylib.h"

/* TODO:
 * 
 * Siivoo parametrit ja funktiot sun muut
 * 
 * Funktiot omiin tiedostoihin oikeeoppisesti? DSP-threadi nyt ainaki
 * 
 * Käyttäjälle mahollisuus valita lineaarisen la exponentiaalisen lähön välil
 * 
 * */

int exitRequested=0;

#define MAX_PARAMS 48
char paramNames[MAX_PARAMS][32] = {"Attack", "Decay", "Sustain", "Relase", "Level", "DC Offset"};
char paramKeys[MAX_PARAMS][16] = {"a", "d", "s", "r", "l", "dc"};
double paramValues[MAX_PARAMS] = {1.0, 0.0001, 0.5, 0.001, 1.0, 0.0}; // definet näille
double param2ndaryValues[MAX_PARAMS] = {0.0, 0.9999, 0, 0.999, 0, 0.0};

void attackFunction(double paramIn)
{
	paramValues[0] = pow(10, -8*paramIn);
	param2ndaryValues[0] = 1 - paramValues[0];
}
void decayFunction(double paramIn)
{
	paramValues[1] = pow(10, -6*paramIn);
	param2ndaryValues[1] = 1 - paramValues[1];
}
void sustainFunction(double paramIn)
{
	paramValues[2] = paramIn;
}
void relaseFunction(double paramIn)
{
	paramValues[3] = pow(10, -6*paramIn);
	param2ndaryValues[3] = 1 - paramValues[3];
}
void levelFunction(double paramIn)
{
	paramValues[4] = paramIn;
}
void dcOffsetFunction(double paramIn)
{
	paramValues[5] = paramIn;
}
void(*paramFunctions[MAX_PARAMS])() = 
{
	attackFunction,
	decayFunction,
	sustainFunction,
	relaseFunction,
	levelFunction,
	dcOffsetFunction
};

void *gpiodsp(void *threadid)
{
	gpioCfgClock(1,1,0);// Increase speed
	if(gpioInitialise()<0)
	{
		printf("Could not initialize GPIO!");
		pthread_exit(NULL);
	}
	
	const int BUTTON = 4;
	gpioSetMode(BUTTON, PI_INPUT);
	
	int gate;
	double filteredBtn = 0;
	enum ADSRstages{A, D, R};
	enum ADSRstages currentStage = R;
	double adsrOutput = 0.0;
	double output = 0.0;
	unsigned int uiOutput;
	
	while(1)
	{
		if(exitRequested) break;
		
		filteredBtn = 0.1*!gpioRead(BUTTON) + 0.9*filteredBtn;// Debounce
		gate = filteredBtn > 0.5; //Funktioon nämä? 
		if(gate)
		{
			if(currentStage==R) currentStage = A;
			if(currentStage==A)
			{
				adsrOutput = paramValues[0]*2 + param2ndaryValues[0]*adsrOutput;	
			}
			if(adsrOutput>=1)
			{
				currentStage = D;
				adsrOutput = log(adsrOutput) + 1;// Curb fast attack overshoot
			}
			if(currentStage==D)
			{
				adsrOutput = paramValues[1]*paramValues[2] + param2ndaryValues[1]*adsrOutput;
			}
		}
		else
		{
			currentStage = R;
			adsrOutput = param2ndaryValues[3]*adsrOutput;
		}
		
		output = paramValues[4]*adsrOutput + paramValues[5];
		
		output = output>1 ? 1 : output<0 ? 0 : output;
		uiOutput = 1000000*output;
		gpioHardwarePWM(18, 500000, uiOutput);
	}
	
	gpioTerminate();
	return NULL;
}

//--------------------------------------------------------------------------

int main()
{
	pthread_t thread1;
	int threadNotCreated = pthread_create(&thread1, NULL, gpiodsp, NULL);
	if(threadNotCreated)
	{
		printf("Error: unable to create thread, %d\n", threadNotCreated);
		exit(-1);
	}
	
	//---------------------------------------
	
	char userInput[100];
	double dUserInput;
	
	// Read user input
	while(1)
	{
		printf("Input parameter to change. ");//tää salee pois ja luupin ulkopuolelle vaa printataa lista kaiksest shidist ja sillee
		scanf("%s", userInput);
		
		if(!strcmp(userInput,"exit") || !strcmp(userInput,"quit"))
		{
			exitRequested = 1;
			break;
		}
		
		for(int i=0; i<MAX_PARAMS; i++)
		{
			int foundKey = !strcmp(userInput, paramKeys[i]);
			if(foundKey)
			{
				printf("Set %s (0-100) ", paramNames[i]);
				scanf("%s", userInput);//pystyykö suoraa vaa lätkii iUserInputtii?
				dUserInput = 0.01*atoi(userInput);
				paramFunctions[i](dUserInput);
			}
			//else ja jotai koodii joka sallii parametrin arvon vaihtamisen suoraa tost
		}
	}
	
	pthread_join(thread1, NULL);
	return 0;
}

