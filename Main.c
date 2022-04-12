#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <pigpio.h>
#include "Parameter.h"
#include "HybridPiSynth.h"

int main()
{
	// Initialize modulation sources and parameters
	#include "modSources.h"
	#include "parameters.h"
	exitRequested = 0;

	/*************************************
	 * INITIALIZE GPIO AND CREATE THREADS
	 * ************************************/

	gpioCfgClock(1,1,0);// Increase speed
	if(gpioInitialise()<0)
	{
		printf("Could not initialize GPIO!");
		exit(-1);
	}

	pthread_t thread1, thread2;
	int threadNotCreated = pthread_create(&thread1, NULL, hardwarePWMout, NULL);
	if(threadNotCreated)
	{
		printf("Error: unable to create thread, %d\n", threadNotCreated);
		exit(-1);
	}
	threadNotCreated = pthread_create(&thread2, NULL, readCV, NULL);
	if(threadNotCreated)
	{
		printf("Error: unable to create thread, %d\n", threadNotCreated);
		exit(-1);
	}

	/***************************************
	 * MAIN LOOP
	 * **************************************/
	
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

		if(!strcmp(userInput, "debug"))
		{
			printf("Anaali-indeksi: %i\n", analOutIndex);
		}

		//if(/*avataankoModMatrix*/)
		
		for(int i=0; i<MAX_PARAMS; i++)
		{
			int foundKey = !strcmp(userInput, parameters[i].key) || !strcmp(userInput, parameters[i].secondaryKey);
			if(foundKey)
			{
				printf("Set %s (0-100) ", parameters[i].name);
				scanf("%s", userInput);
				dUserInput = 0.01*atoi(userInput);

				parameters[i].modArr[dcIndex].amount = dUserInput; // dcIndex = 0
			}
			//else ja jotai koodii joka sallii parametrin arvon vaihtamisen suoraa tost
		}
	}
	
	pthread_join(thread1, NULL);//luuppiin!
	pthread_join(thread2, NULL);
	return 0;
}

