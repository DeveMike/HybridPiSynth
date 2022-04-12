#pragma once

void* hardwarePWMout();
void* readCV();

#define MAX_PARAMS 16

//-------------------------------------------------

typedef struct ModSource
{
	char name[32];
	char key[32];
	double* out;
	double amount;
} ModSource;

typedef struct ModDest
{
	char name[32];
	char key[32], secondaryKey[32];
	ModSource modArr[MAX_PARAMS];
	double modSum;
	double value, secondaryValue;
	void(*updateValue)(double);
} ModDest;

ModDest modDests[MAX_PARAMS];

//-----------------------------------------------

int g_exitRequested;

double g_dcValue;
double g_adsrOutput;

//------------------------------------------------

int attackIndex;
#define ATTAKC_VALUE		modDests[attackIndex].value
#define ATTACK_2NDARY_VALUE	modDests[attackIndex].secondaryValue

int decayIndex;
#define DECAY_VALUE			modDests[decayIndex].value
#define DECAY_2NDARY_VALUE	modDests[decayIndex].secondaryValue

int sustainIndex;
#define SUSTAIN_VALUE		modDests[sustainIndex].value

int relaseIndex;
#define RELASE_2NDARY_VALUE	modDests[relaseIndex].secondaryValue

int analOutIndex;
#define ANAL_OUT_VALUE		modDests[analOutIndex].value