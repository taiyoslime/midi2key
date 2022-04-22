#ifndef M2K_KEYMAP_H
#define M2K_KEYMAP_H

#include <windows.h>

#define KEYDOWN 0
#define KEYUP 1

#define MIDINOTE 0
#define MIDICC 1
#define MIDINOTINUSE 127

typedef WORD MIDIKEY;

void onMidiKeyEvent(BYTE channel, BYTE type, BYTE note, BYTE event);

typedef struct keypair {
    MIDIKEY midikey;
    DWORD keyboardkey;
} KeyPair;

#endif