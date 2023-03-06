#include "LedCube.h"
LedCube::LedCube(char SS_pin, HeightRegister HRpos) {
  this->SS_pin = SS_pin;
  this->HRpos = HRpos;
  this->Settings_Cube = SPISettings(8000000, MSBFIRST, SPI_MODE0);
  init();
}
void LedCube::init() {
  pinMode(SS_pin, OUTPUT);
  SPI.begin();
}

// Updated all leds on the cube
void LedCube::show(byte activeFrame[8][8]){
  for (int layer = 0; layer < 8; layer++){
    byte layerByte = 0;
    layerByte |= (1 << (8 - layer));
    updateShiftRegisters(activeFrame[layer], layerByte);
  }
}

// Update a layer of the cube
void LedCube::updateShiftRegisters(byte shiftLeds[8], byte layerByte)
{
  SPI.beginTransaction(Settings_Cube);
  digitalWrite(SS_pin, LOW);

  if (HRpos == CtrlLAST){SPI.transfer(layerByte);}
  // Loops troug all new shift register values and updates the registers
  for (int i = 0; i < 8; i++)
  {
    // Shifts out 1 byte to a shift register to controll 8 pins
    SPI.transfer( shiftLeds[i] );
  }
  if (HRpos == CtrlFIRST){SPI.transfer(layerByte);}
  
  digitalWrite(SS_pin, HIGH);
  SPI.endTransaction();
}

/*
void LedCube::test(){
  
  //count up routine
  for (int j = 0; j < 256; j++) {
    //ground latchPin and hold low for as long as you are transmitting
    SPI.beginTransaction(Settings_Cube);
    digitalWrite(SS_pin, LOW);
    //shiftOut(dataPin, clockPin, LSBFIRST, j);
    SPI.transfer(j);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(SS_pin, HIGH);
    SPI.endTransaction();
    delay(100);
  }
}*/