#pragma once

#define MAX_PARAMS 16

typedef struct ModSource
{
	char name[32];
	char key[32];
	double* out;
	double amount;
} ModSource;

typedef struct Parameter //ModDest
{
	char name[32];
	char key[32], secondaryKey[32];
	ModSource modArr[MAX_PARAMS];
	double modSum;
	double value, secondaryValue;//nimee ehkä final valueks tai jotai
	void(*updateValue)(double);
} Parameter;

Parameter parameters[MAX_PARAMS];

//-----------------------------------------------

int exitRequested;

double dcValue;
double adsrOutput;

//------------------------------------------------

int analOutIndex;