#pragma once

// Get rid of null-pointers in parameters
double zero = 0;
for(int i=0; i<MAX_PARAMS; i++)
{
    for(int j=0; j<MAX_PARAMS; j++)
    {
        parameters[i].modArr[j].out = &zero;
    }
}

int modSrcID = 0;

// DC

dcValue = 1;
for(int i=0; i<MAX_PARAMS; i++)
{
    strcpy(parameters[i].modArr[modSrcID].name, "DC Offset");
    parameters[i].modArr[modSrcID].out = &dcValue; // Initialize dc-value//<-------regfefaa
}
int dcIndex = modSrcID;

modSrcID++;

// ADSR

for(int i=0; i<MAX_PARAMS; i++)
{
    strcpy(parameters[i].modArr[modSrcID].name, "ADSR");
    parameters[i].modArr[modSrcID].out = &adsrOutput;
}
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