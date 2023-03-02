#ifndef LEDCUBE_H
#define LEDCUBE_H
#include <Arduino.h>
#include <SPI.h>

enum HeightRegister {CtrlFIRST,CtrlLAST};

class LedCube {
  
  private:
    char SS_pin;
    SPISettings Settings_Cube;

    HeightRegister HRpos;

    void updateShiftRegisters(byte shiftLeds[8]);
    
  public:
    LedCube(char SS_pin, HeightRegister HRpos);

    void init();
    
    void show(byte activeFrame[8][8]);
    
};
#endif