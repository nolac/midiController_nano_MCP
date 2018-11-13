#include <Arduino.h>
#include "Adafruit_MCP23017.h"
#include "midiPad.hpp"
#include "buttonsDefines.h"
#include "algos.h"

Adafruit_MCP23017 mcp;
MidiPad pad;

uint16_t oldValue(0);
uint16_t currentValue(0);
bool oldPageChanged=0;
bool page=0;
//bool oldF2=0,oldF1=0,oldF3=0;

void setup()
{
  pad.init();
  mcp.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,page);
  pinMode(PAGE, INPUT_PULLUP);
  //pinMode(F2,INPUT_PULLUP);
  for (int i = 0; i < 16; i++)
  {
    mcp.pinMode(i, INPUT_PULLUP);
    mcp.digitalWrite(i, HIGH);
  }
  for(int i=3;i<=5;i++){
    pinMode(i, INPUT_PULLUP);
    digitalWrite(i,HIGH);
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

  // switch between page 1 & 2
  // page 1 from 60 to 75
  // page 2 from 76 to 82
  bool pageChanged = !digitalRead(PAGE);
  delay(5);
  if((pageChanged==true)&&(pageChanged!=oldPageChanged)){
    pad.switchPage();
    page=!page;
    digitalWrite(LED_BUILTIN, page);

  }oldPageChanged=pageChanged;

  sendControle();
}
