#pragma once

typedef struct Parameter
{
	char name[32];
	char key[32], secondaryKey[32];
	double value, secondaryValue;
	void(*updateValue)(double);
} Parameter;

#define MAX_PARAMS 32
Parameter parameters[MAX_PARAMS];