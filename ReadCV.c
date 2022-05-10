#include <stdio.h>
#include <pigpio.h>
#include "HybridPiSynth.h"

void* readCV()
{
	int sqrGpio = 20;
	gpioSetMode(21, PI_INPUT);
	gpioSetMode(sqrGpio, PI_OUTPUT);

	// Generate stable high frequency square wave
	gpioPulse_t pulse[2];
	pulse[0].gpioOn = (1<<sqrGpio);
	pulse[0].gpioOff = 0;
	pulse[0].usDelay = 4;
	pulse[1].gpioOn = 0;
	pulse[1].gpioOff = (1<<sqrGpio);
	pulse[1].usDelay = 4;
	gpioWaveAddGeneric(2, pulse);
	int wave_id = gpioWaveCreate();
	if(wave_id >= 0) gpioWaveTxSend(wave_id, PI_WAVE_MODE_REPEAT);
	else printf("Wave create failed.");

	printf("exitRequestedin osote tokas threadis: %i\n", (int)&g_exitRequested);

	while(1)
	{
		if(g_exitRequested) //break;
		{
			break;
		}
		//potPos = 0.000001*gpioRead(21) + 0.999999*potPos; //potPosin tilalle CV
	}
	return NULL;
}