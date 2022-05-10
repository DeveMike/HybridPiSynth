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
	initModSources();
	initModDests();
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

	pthread_t thread1/*, thread2*/; // Toka threadi bugaa jos se ei tee mitää.
	int threadNotCreated = pthread_create(&thread1, NULL, hardwarePWMout, NULL);
	if(threadNotCreated)
	{
		printf("Error: unable to create thread, %d\n", threadNotCreated);
		exit(-1);
	}
	/* threadNotCreated = pthread_create(&thread2, NULL, readCV, NULL);
	if(threadNotCreated)
	{
		printf("Error: unable to create thread, %d\n", threadNotCreated);
		exit(-1);
	} */

	/***************************************
	 * MAIN LOOP
	 * **************************************/

	char userInput[100];
	double dUserInput;
	int foundKey, i, j;

	printHelp();
	printf("\n\nChoose source: ");

	// Read user input
	while(1)
	{
		if(!strncmp(userInput,"exit", 4) || !strncmp(userInput,"quit",4))
		{
			g_exitRequested = 1;
			goto exiting;
		}

		for(i=0; i<MAX_PARAMS; i++)
		{
			foundKey = !strcmp(userInput, modDests[i].modSources[i].key) && strlen(userInput)>0;
			if (foundKey) break;
		}
		if(foundKey)
		{
			while(1)
			{
				printf("Choose destination: ");
				scanf("%s", userInput);

				if(!strcmp(userInput,"exit") || !strcmp(userInput,"quit"))
				{
					g_exitRequested = 1;
					goto exiting;
				}

				for(j=0; j<MAX_PARAMS; j++)
				{
					foundKey = !strcmp(userInput, modDests[j].key) && strlen(userInput)>0;
					if (foundKey) break;
				}
				if (foundKey) break;
			}

			while(1)
			{
				printf("Set %s to %s modulation (0-100) or choose source. ",modDests[i].modSources[i].name, modDests[j].name);
				scanf("%s", userInput);

				if(!strcmp(userInput,"exit") || !strcmp(userInput,"quit"))
				{
					g_exitRequested = 1;
					goto exiting;
				}

				for(int h=0; h<MAX_PARAMS; h++)
				{
					foundKey = !strcmp(userInput, modDests[h].modSources[h].key) && strlen(userInput)>0;
					if (foundKey)
					{
						i = h;
						break;
					}
				}
				if (foundKey) break;

				dUserInput = 0.01*atoi(userInput);
				modDests[j].modSources[i].amount = dUserInput;
			}
		}
		else
		{
			scanf("%s", userInput);
		}
	}

exiting:
	pthread_join(thread1, NULL);
	//pthread_join(thread2, NULL);
	gpioTerminate();
	return 0;
}

