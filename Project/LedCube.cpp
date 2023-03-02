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
    for (int j = 0; j < 8; j++){
      //digitalWrite(layers[j], LOW);
    }
    //digitalWrite(layers[layer], HIGH);
    updateShiftRegisters(activeFrame[layer]);
  }
}

// Update a layer of the cube
void LedCube::updateShiftRegisters(byte shiftLeds[8])
{
  SPI.beginTransaction(Settings_Cube);
  digitalWrite(SS_pin, LOW);

  if (HRpos == CtrlFIRST){SPI.transfer(1);}
  // Loops troug all new shift register values and updates the registers
  for (int i = 0; i < 8; i++)
  {
    // Shifts out 1 byte to a shift register to controll 8 pins
    SPI.transfer(shiftLeds[i]);
  }
  if (HRpos == CtrlLAST){SPI.transfer(1);}
  
  digitalWrite(SS_pin, HIGH);
  SPI.endTransaction();
}