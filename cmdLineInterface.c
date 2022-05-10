#include <stdio.h>
#include <math.h>
#include <string.h>
#include "HybridPiSynth.h"

void printHelp()
{
	printf("\nModulation sources\t\tKeys\t|\tModulation destinations\t\tKeys\n");
	printf("\t\t\t\t\t|\n");
	for(int i=0; i<fmax(modSrcCount,modDestCount); i++)
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
}