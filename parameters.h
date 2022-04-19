#pragma once

// Increment after every parameter declaration for indexing
int modDestID = 0;

#define SET_MOD_DEST_NAME(X)       strcpy(modDests[modDestID].name,X)
#define SET_MOD_DEST_KEY(X)        strcpy(modDests[modDestID].key,X)
#define SET_MOD_DEST_2NDARY_KEY(X) strcpy(modDests[modDestID].secondaryKey,X)
#define MOD_DEST_INIT_VALUE        modDests[modDestID].modSources[dcIndex].amount
#define MOD_DEST_UPDATE_METHOD     modDests[modDestID].updateValue

//----------------------------------------------------

// ATTACK

SET_MOD_DEST_NAME("Attack");
SET_MOD_DEST_KEY("a");
SET_MOD_DEST_2NDARY_KEY("A");
attackIndex = modDestID;
void attackMethod(double paramIn)
{
    modDests[attackIndex].value = pow(10, -8*paramIn);
    modDests[attackIndex].secondaryValue = 1 - modDests[attackIndex].value;
}
MOD_DEST_UPDATE_METHOD = attackMethod;

modDestID++;

// DECAY

SET_MOD_DEST_NAME("Decay");
SET_MOD_DEST_KEY("d");
SET_MOD_DEST_2NDARY_KEY("D");
MOD_DEST_INIT_VALUE = 0.5;
decayIndex = modDestID;
void decayMethod(double paramIn)
{
    modDests[decayIndex].value = pow(10, -8*paramIn);
    modDests[decayIndex].secondaryValue = 1 - modDests[decayIndex].value;
}
MOD_DEST_UPDATE_METHOD = decayMethod;

modDestID++;

// SUSTAIN

SET_MOD_DEST_NAME("Sustain");
SET_MOD_DEST_KEY("s");
SET_MOD_DEST_2NDARY_KEY("S");
MOD_DEST_INIT_VALUE = 0.5;
sustainIndex = modDestID;

modDestID++;

// RELEASE

SET_MOD_DEST_NAME("Release");
SET_MOD_DEST_KEY("r");
SET_MOD_DEST_2NDARY_KEY("R");
MOD_DEST_INIT_VALUE = 0.5;
releaseIndex = modDestID;
void releaseMethod(double paramIn)
{
    modDests[releaseIndex].value = pow(10, -8*paramIn);
    modDests[releaseIndex].secondaryValue = 1 - modDests[releaseIndex].value;
}
MOD_DEST_UPDATE_METHOD = releaseMethod;

modDestID++;

// ANALOG OUTPUT

SET_MOD_DEST_NAME("Analog out");
SET_MOD_DEST_KEY("out");
SET_MOD_DEST_2NDARY_KEY("OUT");
modDests[modDestID].modSources[adsrIndex].amount = 1; // adsr -> analOut initial modulation amount
analOutIndex = modDestID;

modDestID++;