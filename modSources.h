#pragma once


int modSrcID = 0;

strcpy(modSources[modSrcID].name, "Command line");
int cmdLineIndex = modSrcID;
modSrcID++;

strcpy(modSources[modSrcID].name, "ADSR");
int adsrIndex = modSrcID;
modSrcID++;

strcpy(modSources[modSrcID].name, "Oscillator");
int oscIndex = modSrcID;
modSrcID++;

strcpy(modSources[modSrcID].name, "CV");
int cvIndex = modSrcID;
modSrcID++;
