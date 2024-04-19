#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <pigpio.h>
#include "HybridPiSynth.h"

#define MAX_USER_INPUT 100
#define ERROR_CREATING_THREAD "Error: unable to create thread, error code: %d\n"
#define USE_SECOND_THREAD 0
#define EXIT_CMD "exit"
#define QUIT_CMD "quit"
#define IS_COMMAND(STR, CMD) (strcmp((STR), (CMD)) == 0)

void safeExit(int status) {
    gpioTerminate();
    exit(status);
}

int main() {
    // Initialize modulation sources and destinations
    initModSources();
    initModDests();
    g_exitRequested = 0;

    // Initialize GPIO and create threads
    gpioCfgClock(1, 1, 0); // Increase speed
    if (gpioInitialise() < 0) {
        fprintf(stderr, "Could not initialize GPIO!\n");
        safeExit(EXIT_FAILURE);
    }

    pthread_t thread1;
    int threadResult = pthread_create(&thread1, NULL, hardwarePWMout, NULL);
    if (threadResult != 0) {
        fprintf(stderr, ERROR_CREATING_THREAD, threadResult);
        safeExit(EXIT_FAILURE);
    }

#if USE_SECOND_THREAD
    pthread_t thread2;
    threadResult = pthread_create(&thread2, NULL, readCV, NULL);
    if (threadResult != 0) {
        fprintf(stderr, ERROR_CREATING_THREAD, threadResult);
        safeExit(EXIT_FAILURE);
    }
#endif

    // Main loop
    char userInput[MAX_USER_INPUT] = {0};
    int foundKey, i, j;

    printHelp();
    printf("\n\nChoose source: ");

    while (!g_exitRequested) {
        if (scanf("%99s", userInput) != 1) {
            fprintf(stderr, "Error reading input.\n");
            continue;
        }

        if (IS_COMMAND(userInput, EXIT_CMD) || IS_COMMAND(userInput, QUIT_CMD)) {
            g_exitRequested = 1;
            break;
        }

        for (i = 0; i < MAX_PARAMS; i++) {
            if (IS_COMMAND(userInput, modDests[i].modSources[i].key) && strlen(userInput) > 0) {
                foundKey = 1;
                break;
            }
        }

        if (foundKey) {
            while (!g_exitRequested) {
                printf("Choose destination: ");
                if (scanf("%99s", userInput) != 1) {
                    fprintf(stderr, "Error reading input.\n");
                    continue;
                }

                if (IS_COMMAND(userInput, EXIT_CMD) || IS_COMMAND(userInput, QUIT_CMD)) {
                    g_exitRequested = 1;
                    break;
                }

                for (j = 0; j < MAX_PARAMS; j++) {
                    if (IS_COMMAND(userInput, modDests[j].key) && strlen(userInput) > 0) {
                        foundKey = 1;
                        break;
                    }
                }

                if (foundKey) {
                    while (!g_exitRequested) {
                        printf("Set %s to %s modulation (0-100) or choose source: ", modDests[i].modSources[i].name, modDests[j].name);
                        if (scanf("%99s", userInput) != 1) {
                            fprintf(stderr, "Error reading input.\n");
                            continue;
                        }

                        if (IS_COMMAND(userInput, EXIT_CMD) || IS_COMMAND(userInput, QUIT_CMD)) {
                            g_exitRequested = 1;
                            break;
                        }

                        double dUserInput = 0.01 * atoi(userInput);
                        modDests[j].modSources[i].amount = dUserInput;
                        break; // Adjust as necessary for logic
                    }
                }
            }
        }
    }

    pthread_join(thread1, NULL);
#if USE_SECOND_THREAD
    pthread_join(thread2, NULL);
#endif
    gpioTerminate();
    return 0;
}


