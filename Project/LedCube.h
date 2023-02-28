#ifndef LEDCUBE_H
#define LEDCUBE_H
#include <Arduino.h>
#include <SPI.h>


class LedCube {
  
  private:
    char SS_pin;
    SPISettings Settings_Cube(8000000, MSBFIRST, SPI_MODE0);

    enum HeightRegister {first,last};
    HeightRegister HRpos;

    void updateShiftRegister();
    
  public:
    Cube(char SS_pin, HeightRegister HRpos);

    void init();
    
    void show();
    
};
#endif