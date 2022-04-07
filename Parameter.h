#pragma once

#define MAX_PARAMS 16

typedef struct Parameter //ModDest
{
	char name[32];
	char key[32], secondaryKey[32];
	double modArr[MAX_PARAMS];
	double modSum;
	double value, secondaryValue;//nimee ehkä final valueks tai jotai
	void(*updateValue)(double);
} Parameter;

Parameter parameters[MAX_PARAMS];

#define EXIT_REQUESTED parameters[0].value

typedef struct ModSource
{
	char name[32];
	double coeff;//tarviiko?
} ModSource;

ModSource modSources[MAX_PARAMS];