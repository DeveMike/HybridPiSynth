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

int osc1freqIndex;
#define OSC1_FREQ_VALUE			modDests[osc1freqIndex].value

int osc1fineIndex;
#define OSC1_FINE_VALUE			modDests[osc1fineIndex].value

/* int osc1shapeIndex;
#define OSC1_SHAPE_VALUE		modDests[osc1shapeIndex].value */

int osc1PWMindex;
#define OSC1_PWM_VALUE			modDests[osc1PWMindex].value

int osc2freqIndex;
#define OSC2_FREQ_VALUE			modDests[osc2freqIndex].value

int osc2fineIndex;
#define OSC2_FINE_VALUE			modDests[osc2fineIndex].value

/* int osc2shapeIndex;
#define OSC2_SHAPE_VALUE		modDests[osc2shapeIndex].value */

int osc2PWMindex;
#define OSC2_PWM_VALUE			modDests[osc2PWMindex].value

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