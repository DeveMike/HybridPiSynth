#pragma once

// Increment after every parameter declaration for indexing
int paramID = 1;

#define PARAM_NAME(X)       strcpy(parameters[paramID].name,X)
#define PARAM_KEY(X)        strcpy(parameters[paramID].key,X)
#define PARAM_2NDARY_KEY(X) strcpy(parameters[paramID].secondaryKey,X)
#define PARAM_INIT_VALUE    parameters[paramID].modArr[0].amount        //aka initial dc -> param modulation amount
#define PARAM_UPDATE_METHOD parameters[paramID].updateValue

// ATTACK

PARAM_NAME("Attack");
PARAM_KEY("a");
PARAM_2NDARY_KEY("A");
int attackIndex = paramID;
void attackMethod(double paramIn)
{
    parameters[attackIndex].value = pow(10, -8*paramIn);
    parameters[attackIndex].secondaryValue = 1 - parameters[attackIndex].value;
}
PARAM_UPDATE_METHOD = attackMethod;

paramID++;

// DECAY

PARAM_NAME("Decay");
PARAM_KEY("d"); 
PARAM_2NDARY_KEY("D");
PARAM_INIT_VALUE = 0.5;
int decayIndex = paramID; 
void decayMethod(double paramIn)
{
    parameters[decayIndex].value = pow(10, -8*paramIn);
    parameters[decayIndex].secondaryValue = 1 - parameters[decayIndex].value;
}
PARAM_UPDATE_METHOD = decayMethod;

paramID++;

// SUSTAIN

PARAM_NAME("Sustain");
PARAM_KEY("s");
PARAM_2NDARY_KEY("S");
PARAM_INIT_VALUE = 0.5;

paramID++;

// RELASE

PARAM_NAME("Relase");
PARAM_KEY("r");
PARAM_2NDARY_KEY("R");
PARAM_INIT_VALUE = 0.5;
int relaseIndex = paramID;
void relaseMethod(double paramIn)
{
    parameters[relaseIndex].value = pow(10, -8*paramIn);
    parameters[relaseIndex].secondaryValue = 1 - parameters[relaseIndex].value;
}
PARAM_UPDATE_METHOD = relaseMethod;

paramID++;

// ANALOG OUTPUT

PARAM_NAME("Analog out");
PARAM_KEY("out");
PARAM_2NDARY_KEY("OUT");
parameters[paramID].modArr[adsrIndex].amount = 1; // adsr -> analOut initial modulation amount
analOutIndex = paramID;

paramID++;