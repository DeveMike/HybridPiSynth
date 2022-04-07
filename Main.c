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
	#include "parameters.h"
	#include "modSources.h"

	pthread_t thread1;
	int threadNotCreated = pthread_create(&thread1, NULL, hardwarePWMout, NULL);
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
			EXIT_REQUESTED = 1;
			break;
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

				parameters[i].modArr[cmdLineIndex] = dUserInput; // cmdLineIndex = 0
			}
			//else ja jotai koodii joka sallii parametrin arvon vaihtamisen suoraa tost
		}
	}
	
	pthread_join(thread1, NULL);
	return 0;
}

