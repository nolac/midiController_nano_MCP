#include "midiPad.hpp"
#include "Arduino.h"

#define NOTE_ON 0x90
#define NOTE_OFF 0x80


MidiPad::MidiPad(){
  currentPage=0;
}

void MidiPad::init(){
  /// init notes out
    byte note=60;
    for(int page=0;page<2;page++){
      for(int i=0;i<16;i++,note++){
        _note[page][i]=note;
      }
    }
}

bool MidiPad::convertByteToBoolBits(uint16_t value,int bitNumber){
    // get the pin state at n bit from MCP readGPIOAB uint16_t value
    return value&(1<<bitNumber);
}

void MidiPad::handleMidiPad(uint16_t curent_state, uint16_t old_state){
    /// read the state of each bit from MCP buttons state
    /// and send the value "note on" or "note of" whatever the status
    for(int i=0;i<16;i++){
        if(convertByteToBoolBits(curent_state,i)!=convertByteToBoolBits(old_state,i)){
            Serial.write(convertByteToBoolBits(curent_state,i)==1?NOTE_ON:NOTE_OFF);
            Serial.write(_note[currentPage][i]);
            Serial.write(0x7F);
        }
    }
}

void MidiPad::switchPage(){
  currentPage=!currentPage;
  //Serial.println(currentPage);
}
