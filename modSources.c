#include <string.h>
#include "HybridPiSynth.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"

void initModSources()
{
    // Get rid of null-pointers in modDests
    for(int i=0; i<MAX_PARAMS; i++)
        for(int j=0; j<MAX_PARAMS; j++)
            modDests[i].modSources[j].out = &ZERO;

    modSrcCount = 0;// Also used for indexing

    #define SET_MOD_SRC_NAME(X) for(int i=0;i<MAX_PARAMS;i++) strcpy(modDests[i].modSources[modSrcCount].name, X)
    #define SET_MOD_SRC_KEY(X)  for(int i=0;i<MAX_PARAMS;i++) strcpy(modDests[i].modSources[modSrcCount].key, X)
    #define MOD_SRC_OUT_ADDR    for(int i=0;i<MAX_PARAMS;i++) modDests[i].modSources[modSrcCount].out

    //----------------------------------------------

    // DC

    SET_MOD_SRC_NAME("DC Offset");
    SET_MOD_SRC_KEY("dc");
    g_dcValue = 1;
    MOD_SRC_OUT_ADDR = &g_dcValue;
    dcIndex = modSrcCount;

    modSrcCount++;

    // OSCILLATOR 1 SAW

    SET_MOD_SRC_NAME("Sawtooth 1");
    SET_MOD_SRC_KEY("saw1");
    MOD_SRC_OUT_ADDR = &g_saw1output;
    saw1index = modSrcCount;

    modSrcCount++;

    // OSCILLATOR 1 PULSE

    SET_MOD_SRC_NAME("Pulse 1");
    SET_MOD_SRC_KEY("pulse1");
    MOD_SRC_OUT_ADDR = &g_pulse1output;
    pulse1index = modSrcCount;

    modSrcCount++;

    // OSCILLATOR 2 SAW

    SET_MOD_SRC_NAME("Sawtooth 2");
    SET_MOD_SRC_KEY("saw2");
    MOD_SRC_OUT_ADDR = &g_saw2output;
    saw2index = modSrcCount;

    modSrcCount++;

    // OSCILLATOR 2 PULSE

    SET_MOD_SRC_NAME("Pulse 2");
    SET_MOD_SRC_KEY("pulse2");
    MOD_SRC_OUT_ADDR = &g_pulse2output;
    pulse2index = modSrcCount;

    modSrcCount++;

    // ADSR

    SET_MOD_SRC_NAME("ADSR");
    SET_MOD_SRC_KEY("adsr");
    MOD_SRC_OUT_ADDR = &g_adsrOutput;
    adsrIndex = modSrcCount;

    modSrcCount++;

    // VCA OUTPUT

    SET_MOD_SRC_NAME("VCA Output");
    SET_MOD_SRC_KEY("vcaout");
    MOD_SRC_OUT_ADDR = &g_vcaOutput;
    vcaOutIndex = modSrcCount;

    modSrcCount++;

    // CV (coming soon)
}

#pragma GCC diagnostic pop