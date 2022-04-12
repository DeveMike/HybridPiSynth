#pragma once

// Get rid of null-pointers in modDests
double zero = 0;
for(int i=0; i<MAX_PARAMS; i++)
    for(int j=0; j<MAX_PARAMS; j++)
        modDests[i].modArr[j].out = &zero;

// Increment after every mod source declaration for indexing
int modSrcID = 0;

#define MOD_SRC_NAME(X)     for(int i=0;i<MAX_PARAMS;i++) strcpy(modDests[i].modArr[modSrcID].name, X)
#define MOD_SRC_OUT_ADDR    for(int i=0;i<MAX_PARAMS;i++) modDests[i].modArr[modSrcID].out

//----------------------------------------------

// DC

MOD_SRC_NAME("DC Offset");
g_dcValue = 1;
MOD_SRC_OUT_ADDR = &g_dcValue;
int dcIndex = modSrcID;

modSrcID++;

// ADSR

MOD_SRC_NAME("ADSR");
MOD_SRC_OUT_ADDR = &g_adsrOutput;
int adsrIndex = modSrcID;

modSrcID++;

/*
strcpy(modSources[modSrcID].name, "Oscillator");
int oscIndex = modSrcID;
modSrcID++;

strcpy(modSources[modSrcID].name, "CV");
int cvIndex = modSrcID;
modSrcID++;
 */