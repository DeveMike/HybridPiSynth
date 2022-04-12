#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <pigpio.h>
#include "HybridPiSynth.h"

int main()
{
	// Initialize modulation sources and modDests
	#include "modSources.h"
	#include "parameters.h"
	g_exitRequested = 0;

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
			g_exitRequested = 1;
			break;
		}

		if(!strcmp(userInput, "debug")) // DEBUG ------------------
		{
			printf("%s\n", modDests[0].modArr[dcIndex].name);
			printf("%s\n", modDests[1].modArr[dcIndex].name);
			printf("%s\n", modDests[2].modArr[dcIndex].name);
		} // DEBUG ------------------------------------------------

		//if(/*avataankoModMatrix*/)
		
		for(int i=0; i<MAX_PARAMS; i++)
		{
			int foundKey = !strcmp(userInput, modDests[i].key) || !strcmp(userInput, modDests[i].secondaryKey);
			if(foundKey)
			{
				printf("Set %s (0-100) ", modDests[i].name);
				scanf("%s", userInput);
				dUserInput = 0.01*atoi(userInput);

				modDests[i].modArr[dcIndex].amount = dUserInput;
			}
			//else ja jotai koodii joka sallii parametrin arvon vaihtamisen suoraa tost
		}
	}
	
	pthread_join(thread1, NULL);//luuppiin!
	pthread_join(thread2, NULL);
	return 0;
}

