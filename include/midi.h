#ifndef M2K_MIDI_H
#define M2K_MIDI_H
#include <windows.h>

void midiPrintDevices(void);
void midiStartListen(UINT deviceID);
#endif