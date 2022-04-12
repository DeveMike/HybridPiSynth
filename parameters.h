#pragma once

// Increment after every parameter declaration for indexing
int paramID = 0;

#define PARAM_NAME(X)       strcpy(modDests[paramID].name,X)
#define PARAM_KEY(X)        strcpy(modDests[paramID].key,X)
#define PARAM_2NDARY_KEY(X) strcpy(modDests[paramID].secondaryKey,X)
#define PARAM_INIT_VALUE    modDests[paramID].modArr[dcIndex].amount
#define PARAM_UPDATE_METHOD modDests[paramID].updateValue

//----------------------------------------------------

// ATTACK

PARAM_NAME("Attack");
PARAM_KEY("a");
PARAM_2NDARY_KEY("A");
attackIndex = paramID;
void attackMethod(double paramIn)
{
    modDests[attackIndex].value = pow(10, -8*paramIn);
    modDests[attackIndex].secondaryValue = 1 - modDests[attackIndex].value;
}
PARAM_UPDATE_METHOD = attackMethod;

paramID++;

// DECAY

PARAM_NAME("Decay");
PARAM_KEY("d"); 
PARAM_2NDARY_KEY("D");
PARAM_INIT_VALUE = 0.5;
decayIndex = paramID; 
void decayMethod(double paramIn)
{
    modDests[decayIndex].value = pow(10, -8*paramIn);
    modDests[decayIndex].secondaryValue = 1 - modDests[decayIndex].value;
}
PARAM_UPDATE_METHOD = decayMethod;

paramID++;

// SUSTAIN

PARAM_NAME("Sustain");
PARAM_KEY("s");
PARAM_2NDARY_KEY("S");
PARAM_INIT_VALUE = 0.5;
sustainIndex = paramID;

paramID++;

// RELASE

PARAM_NAME("Relase");
PARAM_KEY("r");
PARAM_2NDARY_KEY("R");
PARAM_INIT_VALUE = 0.5;
relaseIndex = paramID;
void relaseMethod(double paramIn)
{
    modDests[relaseIndex].value = pow(10, -8*paramIn);
    modDests[relaseIndex].secondaryValue = 1 - modDests[relaseIndex].value;
}
PARAM_UPDATE_METHOD = relaseMethod;

paramID++;

// ANALOG OUTPUT

PARAM_NAME("Analog out");
PARAM_KEY("out");
PARAM_2NDARY_KEY("OUT");
modDests[paramID].modArr[adsrIndex].amount = 1; // adsr -> analOut initial modulation amount
analOutIndex = paramID;

paramID++;