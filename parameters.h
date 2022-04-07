#pragma once

//strcpy(parameters[0].key, "exit"); strcpy(parameters[0].secondaryKey, "quit");//funktiomakro siistimää?
parameters[0].value = 0;

int paramID = 1;

// ATTACK

strcpy(parameters[paramID].name, "Attack");
strcpy(parameters[paramID].key, "a"); strcpy(parameters[paramID].secondaryKey, "A");
parameters[paramID].value = 1; parameters[paramID].secondaryValue = 0;
parameters[paramID].modArr[0] = 0.0;
int attackIndex = paramID;
void attackMethod(double paramIn)
{
    parameters[attackIndex].value = pow(10, -8*paramIn);
    parameters[attackIndex].secondaryValue = 1 - parameters[attackIndex].value;
}
parameters[paramID].updateValue = attackMethod;

paramID++;

// DECAY

strcpy(parameters[paramID].name, "Decay");
strcpy(parameters[paramID].key, "d"); strcpy(parameters[paramID].secondaryKey, "D");
parameters[paramID].value = 0.0001; parameters[paramID].secondaryValue = 0.9999;
parameters[paramID].modArr[0] = 0.5;
int decayIndex = paramID; 
void decayMethod(double paramIn)
{
    parameters[decayIndex].value = pow(10, -8*paramIn);
    parameters[decayIndex].secondaryValue = 1 - parameters[decayIndex].value;
}
parameters[paramID].updateValue = decayMethod;

paramID++;

// SUSTAIN

strcpy(parameters[paramID].name, "Sustain");
strcpy(parameters[paramID].key, "s"); strcpy(parameters[paramID].secondaryKey, "S");
parameters[paramID].modArr[0] = 0.5;

paramID++;

// RELASE

strcpy(parameters[paramID].name, "Relase");
strcpy(parameters[paramID].key, "r"); strcpy(parameters[paramID].secondaryKey, "R");
parameters[paramID].value = 0.001; parameters[paramID].secondaryValue = 0.999;
parameters[paramID].modArr[0] = 0.5;
int relaseIndex = paramID;
void relaseMethod(double paramIn)
{
    parameters[relaseIndex].value = pow(10, -8*paramIn);
    parameters[relaseIndex].secondaryValue = 1 - parameters[relaseIndex].value;
}
parameters[paramID].updateValue = relaseMethod;

paramID++;

// EG LEVEL

strcpy(parameters[paramID].name, "EG Level");
strcpy(parameters[paramID].key, "l"); strcpy(parameters[paramID].secondaryKey, "L");
parameters[paramID].modArr[0] = 1;

paramID++;

// DC OFFSET

strcpy(parameters[paramID].name, "DC Offset");
strcpy(parameters[paramID].key, "dc"); strcpy(parameters[paramID].secondaryKey, "DC");
