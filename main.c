#include "midi.h"
#include <stdbool.h>
#include <stdlib.h>

int main(void) {

    midiPrintDevices();
    midiStartListen(0u); //TODO;
    while (true) {}
    
    return EXIT_SUCCESS;
}