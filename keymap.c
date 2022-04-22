#include "keymap.h"
#include "list.h"
#include <winuser.h>
#include <stdbool.h>


#pragma comment(lib, "user32.lib")

List *list;
bool init = false;
bool configuring = false;

MIDIKEY genSearchKeyFromMIDI(BYTE channel, BYTE type, BYTE note) {
    return (channel << 12) | (type << 8) | note;
}

int listcmp(const void *a, const void *b) {
    return (int)(*(MIDIKEY *)a - ((KeyPair*)b)->midikey);
}

void listprt(const void *_data) {
    KeyPair* data = (KeyPair*)_data;
    printf("midikey = %#x, keyboardkey = %#x\n", data->midikey, data->keyboardkey);
}

DWORD keymapSearch(MIDIKEY midikey) {
    ListElem *e = listFind(list, &midikey, listcmp);
    return e ? ((KeyPair*)(e->data))->keyboardkey : 0;
}

void keymapInsert(MIDIKEY midikey, DWORD keyboardkey) {
    KeyPair* k = (KeyPair*)malloc(sizeof(KeyPair));
    k->midikey = midikey;
    k->keyboardkey = keyboardkey;
    listInsert(list, k);
}

void keymapInit(void) {
    listInit(&list);
}

void keymapPrint(void) {
    listPrintAll(list, listprt);
}

void keymapDelete(MIDIKEY midikey) {
    ;
}

void keymapLoad(const char* filename){
    ;
}

void keymapSave(const char* filename){
    ;
}

void sendKeyboradInput(DWORD key, BYTE event) {
    if (key < 1 || key > 254) {
        perror("invalid vk");
        return;
    }

    // https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-input
    // https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-keybdinput
    INPUT input;
    input.type = INPUT_KEYBOARD;
    // https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
    input.ki.wVk = key;
    input.ki.wScan = input.ki.time = 0;
    switch(event) {
        case KEYUP:
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            break;
        case KEYDOWN:
            input.ki.dwFlags = 0;
            break;
    }

    // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendinput
    UINT uSent = SendInput(1, &input, sizeof(INPUT));
    if (uSent != 1) {
        perror("SendInput");
    }
}

void onMidiKeyEvent(BYTE channel, BYTE type, BYTE note, BYTE event) {
    if (!init) {
        keymapInit();
        init = true;
    }

    if (configuring) {
        ; 

    } else {
        MIDIKEY midikey = genSearchKeyFromMIDI(channel, type, note);
        keymapPrint();
        DWORD key = keymapSearch(midikey);
        if (key != 0) {
            sendKeyboradInput(key, event);
        }
    }

}