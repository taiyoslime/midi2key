#include <stdio.h>
#include <windows.h>
// https://docs.microsoft.com/en-us/windows/win32/api/mmeapi/
#include <mmeapi.h>

// midi reference:
// https://amei.or.jp/midistandardcommittee/MIDI1.0.pdf
// midi api reference
// https://docs.microsoft.com/en-us/windows/win32/multimedia/midi-reference

#include "keymap.h"

#pragma comment(lib, "winmm.lib")

// MidiInProc
void CALLBACK MidiCallBack(
    HMIDIIN hMidiIn, 
    UINT wMsg, 
    DWORD dwInstance,
    DWORD dwParam1, 
    DWORD dwParam2 
) 
{
    switch (wMsg) {
        case MIM_DATA:
            // https://docs.microsoft.com/en-us/windows/win32/multimedia/mim-data
            {
                // dwParam1 = dwMidiMessage
                // dwParam2 = dwTimestamp 
                
                BYTE status = (dwParam1 & 0x000000ff);
                BYTE msgtype = status >> 4;
                BYTE channel = status & 0x0f;
                BYTE note = (dwParam1 & 0x0000ff00) >> 8;
                BYTE velocity = (dwParam1 & 0x00ff0000) >> 16;

                // 0x8x: note off
                // 0x9x: note on
                // 0xbx: MIDI CC
                BYTE type;
                switch (msgtype) {
                    case 0x8:
                    case 0x9:
                        type = MIDINOTE;
                        break;
                    case 0xb:
                        type = MIDICC;
                        break;
                    default:
                        type = MIDINOTINUSE;
                        break;
                }
                
                if (type != MIDINOTINUSE) {
                    if (velocity == 0x00 || msgtype == 0x08) {
                        // note off
                        onMidiKeyEvent(channel, type, note, KEYUP);
                    } else {
                        // note on
                        onMidiKeyEvent(channel, type, note, KEYDOWN);
                    }
                }

                printf("status=%#x, note=%#x, velocity=%#x\n", status, note, velocity);
            }
            break;
        default:
            break;
    }
}

void midiPrintDevices(void) {
    UINT numDevs = midiInGetNumDevs();

    if (numDevs == 0) {
        exit(EXIT_FAILURE);
    }

    MIDIINCAPS c;
    for (UINT i = 0; i < numDevs; i++) {
        midiInGetDevCaps(i, &c, sizeof(MIDIINCAPS));
        printf("%s\n", c.szPname);
    }
}


void midiStartListen(UINT deviceID) {
    HMIDIIN hmi;

    MMRESULT res;
    // https://docs.microsoft.com/en-us/windows/win32/api/mmeapi/nf-mmeapi-midiinopen
    res = midiInOpen(&hmi, deviceID, (DWORD_PTR)MidiCallBack, (DWORD_PTR)NULL, CALLBACK_FUNCTION);
    if (res != MMSYSERR_NOERROR) {
        perror("midiInOpen");
        exit(EXIT_FAILURE);
    }
    res = midiInStart(hmi);
    if (res != MMSYSERR_NOERROR) {
        perror("midiInStart");
        exit(EXIT_FAILURE);
    }
}