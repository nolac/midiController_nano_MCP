#include <Arduino.h>
#include "Adafruit_MCP23017.h"
#include "midiPad.hpp"
#include "buttonsDefines.h"

Adafruit_MCP23017 mcp;
MidiPad pad;

uint16_t oldValue(0);
uint16_t currentValue(0);
bool oldPageChanged=0;
bool oldF2=0,oldF1=0,oldF3=0;
void setup()
{
  pad.init();
  mcp.begin();
  pinMode(PAGE, INPUT_PULLUP);
  pinMode(F2,INPUT_PULLUP);
  for (int i = 0; i < 16; i++)
  {
    mcp.pinMode(i, INPUT_PULLUP);
    mcp.digitalWrite(i, HIGH);
  }
  Serial.begin(115200);
}

void loop()
{
  currentValue = ~mcp.readGPIOAB();
  if (currentValue != oldValue)
  {
    pad.handleMidiPad(currentValue,oldValue);
  }
  oldValue=currentValue;

  bool pageChanged = !digitalRead(PAGE);
  if((pageChanged==true)&&(pageChanged!=oldPageChanged)){
    pad.switchPage();
  }oldPageChanged=pageChanged;

//////    dirty functions method ////
//////    HAVE TO BE rewrited    ////
  bool f1= !digitalRead(F1);
  if(f1!=oldF1){
    Serial.write(0xB0);
    Serial.write(0x14);
    Serial.write(f1==1?0x7F:0x00);
  }oldF1=f1;

  bool f2= !digitalRead(F2);
  if(f2!=oldF2){
    Serial.write(0xB0);
    Serial.write(0x15);// CC20
    Serial.write(f2==1?0x7F:0X00);
  }oldF2=f2;

  bool f3= !digitalRead(F3);
  if(f3!=oldF3){
    Serial.write(0xB0);
    Serial.write(0x16);
    Serial.write(f3==1?0x7F:0x00);
  }oldF3=f3;
///////////////////////////////////////

}
