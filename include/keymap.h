#ifndef M2K_KEYMAP_H
#define M2K_KEYMAP_H

#include <windows.h>

#define MIDIKEYDOWN 0
#define MIDIKEYKUP 1

void onMidiKeyEvent(BYTE channel, BYTE note, BYTE event);

#endif