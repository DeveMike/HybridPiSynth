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

	printf("\nModulation sources\t\tKeys\t|\tModulation destinations\t\tKeys\n");
	printf("\t\t\t\t\t|\n");
	for(int i=0; i<fmax(modSrcID,modDestID); i++)
	{
		char modSrcName[32];
		strcpy(modSrcName, modDests[0].modSources[i].name);

		if(modSrcName == NULL || modDests[0].name == NULL)
			break;

		printf("%s\t\t\t",modSrcName);
		if (strlen(modSrcName) < 8) printf("\t");
		printf("%s\t", modDests[0].modSources[i].key);

		printf("|\t%s\t\t", modDests[i].name);
		if (strlen(modDests[i].name) < 8) printf("\t");
		printf("\t%s\n", modDests[i].key);
	}

	char userInput[100];
	double dUserInput;
	int foundKey, i, j;

	printf("\n\nChoose source: ");

	// Read user input
	while(1)
	{
		if(!strcmp(userInput,"exit") || !strcmp(userInput,"quit"))
		{
			g_exitRequested = 1;
			goto exiting;
		}

		for(i=0; i<MAX_PARAMS; i++)
		{
			foundKey = !strcmp(userInput, modDests[i].modSources[i].key);
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
					foundKey = !strcmp(userInput, modDests[j].key) || !strcmp(userInput, modDests[j].secondaryKey);
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
					foundKey = !strcmp(userInput, modDests[h].modSources[h].key);
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
	pthread_join(thread2, NULL);
	gpioTerminate();
	return 0;
}

