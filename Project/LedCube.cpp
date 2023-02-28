#include "LedCube.h"
LedCube::Cube(char SS_pin, HeightRegister HRpos) {
  this->SS_pin = SS_pin;
  this->HRpos = HRpos;
  init();
}
void LedCube::init() {
  pinMode(SS_pin, OUTPUT);
  SPI.begin();
  SPI.beginTransaction(Settings_Cube);
}

// Updated all leds on the cube
void LedCube::show(byte activeFrame[8][8]){
  for (int layer = 0; layer < 8; layer++){
    for (int j = 0; j < 8; j++){
      digitalWrite(layers[j], LOW);
    }
    digitalWrite(layers[layer], HIGH);
    updateShiftRegister(activeFrame[layer]);
  }
}

// Update a layer of the cube
void LedCube::updateShiftRegisters(byte shiftLeds[8])
{
  digitalWrite(SS_pin, LOW);

  if (HRpos == first){}
  // Loops troug all new shift register values and updates the registers
  for (int i = 0; i < sizeof(shiftLeds); i++)
  {
    // Shifts out 1 byte to a shift register to controll 8 pins
    SPI.transfer(shiftLeds[i]);
  }
  if (HRpos == last){}
  digitalWrite(SS_pin, HIGH);
}