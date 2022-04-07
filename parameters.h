#pragma once

strcpy(parameters[0].key, "exit"); strcpy(parameters[0].secondaryKey, "quit");//funktiomakro siistimää?
#define EXIT_REQUESTED parameters[0].value//tää makro Parameter.h tiedostoon
EXIT_REQUESTED = 0;

// ATTACK

#define ATTACK parameters[1]//vittu unohin et makrot toiseen tiedostoon! iha sama
strcpy(ATTACK.name, "Attack");
strcpy(ATTACK.key, "a"); strcpy(ATTACK.secondaryKey, "A");
ATTACK.value = 1; ATTACK.secondaryValue = 0;
void attackMethod(double paramIn)
{
	parameters[1].value = pow(10, -8*paramIn);
	parameters[1].secondaryValue = 1 - parameters[1].value;
}
ATTACK.updateValue = attackMethod;

// DECAY

strcpy(parameters[2].name, "Decay");
strcpy(parameters[2].key, "d"); strcpy(parameters[2].secondaryKey, "D");
parameters[2].value = 0.0001; parameters[2].secondaryValue = 0.9999;
void decayMethod(double paramIn)
{
	parameters[2].value = pow(10, -8*paramIn);
	parameters[2].secondaryValue = 1 - parameters[2].value;
}
parameters[2].updateValue = decayMethod;

// SUSTAIN

strcpy(parameters[3].name, "Sustain");
strcpy(parameters[3].key, "s"); strcpy(parameters[3].secondaryKey, "S");
parameters[3].value = 0.5;

// RELASE

strcpy(parameters[4].name, "Relase");
strcpy(parameters[4].key, "r"); strcpy(parameters[4].secondaryKey, "R");
parameters[4].value = 0.001; parameters[4].secondaryValue = 0.999;
void relaseMethod(double paramIn)
{
	parameters[4].value = pow(10, -8*paramIn);
	parameters[4].secondaryValue = 1 - parameters[4].value;
}
parameters[4].updateValue = relaseMethod;

// EG LEVEL

strcpy(parameters[5].name, "EG Level");
strcpy(parameters[5].key, "l"); strcpy(parameters[5].secondaryKey, "L");
parameters[5].value = 1;

// DC OFFSET

strcpy(parameters[6].name, "DC Offset");
strcpy(parameters[6].key, "dc"); strcpy(parameters[6].secondaryKey, "DC");
parameters[6].value = 0;