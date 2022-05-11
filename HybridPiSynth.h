#pragma once

// Constant to point to when initializing pointer arrays
const double ZERO;

void initModSources();
void initModDests();

void printHelp();

// Thread functions
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

ModSource modSources[MAX_PARAMS];

typedef struct ModDest
{
	char name[32];
	char key[32];
	ModSource modSources[MAX_PARAMS];
	//double matrix[MAX_PARAMS];
	double modSum;
	double value, secondaryValue;
	void(*updateValue)(double);
} ModDest;

ModDest modDests[MAX_PARAMS];

//-----------------------------------------------

int g_exitRequested;

//-----------------------------------------------

int modSrcCount;

int dcIndex;
int adsrIndex;
int saw1index;
int pulse1index;
int saw2index;
int pulse2index;
int vcaOutIndex;

//paskaaaa mutta menköön
double g_dcValue;
double g_adsrOutput;
double g_saw1output;
double g_pulse1output;
double g_saw2output;
double g_pulse2output;
double g_vcaOutput;

//------------------------------------------------

int modDestCount;

int oscFreqIndex;
#define OSC_FREQ_VALUE			modDests[oscFreqIndex].value

int oscFineIndex;
#define OSC_FINE_VALUE			modDests[oscFineIndex].value

int oscShapeIndex;
#define OSC_SHAPE_VALUE			modDests[oscShapeIndex].value

int oscPWMindex;
#define OSC_PWM_VALUE			modDests[oscPWMindex].value

int attackIndex;
#define ATTAKC_VALUE			modDests[attackIndex].value
#define ATTACK_2NDARY_VALUE		modDests[attackIndex].secondaryValue

int decayIndex;
#define DECAY_VALUE				modDests[decayIndex].value
#define DECAY_2NDARY_VALUE		modDests[decayIndex].secondaryValue

int sustainIndex;
#define SUSTAIN_VALUE			modDests[sustainIndex].value

int releaseIndex;
#define RELEASE_2NDARY_VALUE	modDests[releaseIndex].secondaryValue

int vcaIndex;
#define VCA_IN_VALUE			modDests[vcaIndex].value

int vcaCVindex;
#define VCA_CV_VALUE			modDests[vcaCVindex].value

int out1index;
#define OUT1_VALUE				modDests[out1index].value

int out2index;
#define OUT2_VALUE				modDests[out2index].value