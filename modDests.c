#include <string.h>
#include <math.h>
#include "HybridPiSynth.h"

void initModDests()
{
    modDestCount = 0; // Also used for indexing

    #define SET_MOD_DEST_NAME(X)       strcpy(modDests[modDestCount].name,X)
    #define SET_MOD_DEST_KEY(X)        strcpy(modDests[modDestCount].key,X)
    #define MOD_DEST_INIT_VALUE        modDests[modDestCount].modSources[dcIndex].amount
    #define MOD_DEST_UPDATE_METHOD     modDests[modDestCount].updateValue

    //----------------------------------------------------

    // OSCILLATOR FREQUENCY

    SET_MOD_DEST_NAME("Osc freq");
    SET_MOD_DEST_KEY("f");
    oscFreqIndex = modDestCount;
    void oscFreqMethod(double paramIn)
    {
        modDests[oscFreqIndex].value = pow(10, -8*paramIn);
        modDests[oscFreqIndex].secondaryValue = 1 - modDests[oscFreqIndex].value;
    }
    MOD_DEST_UPDATE_METHOD = oscFreqMethod;

    modDestCount++;

    // OSCILLATOR SHAPE

    SET_MOD_DEST_NAME("Osc shape");
    SET_MOD_DEST_KEY("shape");
    oscShapeIndex = modDestCount;

    modDestCount++;

    // OSCILLATOR PULSE WIDTH

    SET_MOD_DEST_NAME("Osc pulse width");
    SET_MOD_DEST_KEY("pwm");
    oscPWMindex = modDestCount;

    modDestCount++;

    // ATTACK

    SET_MOD_DEST_NAME("Attack");
    SET_MOD_DEST_KEY("a");
    attackIndex = modDestCount;
    void attackMethod(double paramIn)
    {
        modDests[attackIndex].value = pow(10, -8*paramIn);
        modDests[attackIndex].secondaryValue = 1 - modDests[attackIndex].value;
    }
    MOD_DEST_UPDATE_METHOD = attackMethod;

    modDestCount++;

    // DECAY

    SET_MOD_DEST_NAME("Decay");
    SET_MOD_DEST_KEY("d");
    MOD_DEST_INIT_VALUE = 0.5;
    decayIndex = modDestCount;
    void decayMethod(double paramIn)
    {
        modDests[decayIndex].value = pow(10, -8*paramIn);
        modDests[decayIndex].secondaryValue = 1 - modDests[decayIndex].value;
    }
    MOD_DEST_UPDATE_METHOD = decayMethod;

    modDestCount++;

    // SUSTAIN

    SET_MOD_DEST_NAME("Sustain");
    SET_MOD_DEST_KEY("s");
    MOD_DEST_INIT_VALUE = 0.5;
    sustainIndex = modDestCount;

    modDestCount++;

    // RELEASE

    SET_MOD_DEST_NAME("Release");
    SET_MOD_DEST_KEY("r");
    MOD_DEST_INIT_VALUE = 0.5;
    releaseIndex = modDestCount;
    void releaseMethod(double paramIn)
    {
        modDests[releaseIndex].value = pow(10, -8*paramIn);
        modDests[releaseIndex].secondaryValue = 1 - modDests[releaseIndex].value;
    }
    MOD_DEST_UPDATE_METHOD = releaseMethod;

    modDestCount++;

    // ANALOG OUTPUT

    SET_MOD_DEST_NAME("Analog out");
    SET_MOD_DEST_KEY("out");
    modDests[modDestCount].modSources[adsrIndex].amount = 1; // adsr -> analOut initial modulation amount
    analOutIndex = modDestCount;

    modDestCount++;
}