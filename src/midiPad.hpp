#ifndef midiPad_hpp
#define midiPad_hpp
#include "Arduino.h"

class MidiPad {

public:
// concstructors //
MidiPad();       //
///////////////////
void init();
bool convertByteToBoolBits(uint16_t value,int bitNumber);
void handleMidiPad(uint16_t curent_state, uint16_t old_state);
void switchPage();
private:
byte _note[2][16]={};
bool currentPage;

};
#endif
