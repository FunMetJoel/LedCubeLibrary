#include <SPI.h>

unsigned long previousMillis = 0;
const long interval = 250;
int frame = 0;

SPISettings Settings_Cube(8000000, MSBFIRST, SPI_MODE0);
SPISettings Settings_SD(8000000, MSBFIRST, SPI_MODE0);

const char SS_Cube = 10;
const char SS_SD = 10;


char layers[8] = {2,3,4,5,6,7,8,9};

// Format [Frame][Plate][Row]
byte leds[9][8][8] = {
  {
  {255,255,255,255,255,255,255,255},
  {127,127,127,127,127,127,127,127},
  {63,63,63,63,63,63,63,63},
  {31,31,31,31,31,31,31,31},
  {15,15,15,15,15,15,15,15},
  {7,7,7,7,7,7,7,7},
  {3,3,3,3,3,3,3,3},
  {1,1,1,1,1,1,1,1}},
  {
    {1,1,1,1,1,1,1,1},
  {255,255,255,255,255,255,255,255},
  {127,127,127,127,127,127,127,127},
  {63,63,63,63,63,63,63,63},
  {31,31,31,31,31,31,31,31},
  {15,15,15,15,15,15,15,15},
  {7,7,7,7,7,7,7,7},
  {3,3,3,3,3,3,3,3}},
  {
    {3,3,3,3,3,3,3,3},
  {1,1,1,1,1,1,1,1},
  {255,255,255,255,255,255,255,255},
  {127,127,127,127,127,127,127,127},
  {63,63,63,63,63,63,63,63},
  {31,31,31,31,31,31,31,31},
  {15,15,15,15,15,15,15,15},
  {7,7,7,7,7,7,7,7}},
  {
    {7,7,7,7,7,7,7,7},
  {3,3,3,3,3,3,3,3},
  {1,1,1,1,1,1,1,1},
  {255,255,255,255,255,255,255,255},
  {127,127,127,127,127,127,127,127},
  {63,63,63,63,63,63,63,63},
  {31,31,31,31,31,31,31,31},
  {15,15,15,15,15,15,15,15}},
  {
    {15,15,15,15,15,15,15,15},
  {7,7,7,7,7,7,7,7},
  {3,3,3,3,3,3,3,3},
  {1,1,1,1,1,1,1,1},
  {255,255,255,255,255,255,255,255},
  {127,127,127,127,127,127,127,127},
  {63,63,63,63,63,63,63,63},
  {31,31,31,31,31,31,31,31}},
  {
    {31,31,31,31,31,31,31,31},
  {15,15,15,15,15,15,15,15},
  {7,7,7,7,7,7,7,7},
  {3,3,3,3,3,3,3,3},
  {1,1,1,1,1,1,1,1},
  {255,255,255,255,255,255,255,255},
  {127,127,127,127,127,127,127,127},
  {63,63,63,63,63,63,63,63}},
  {
    {63,63,63,63,63,63,63,63},
  {31,31,31,31,31,31,31,31},
  {15,15,15,15,15,15,15,15},
  {7,7,7,7,7,7,7,7},
  {3,3,3,3,3,3,3,3},
  {1,1,1,1,1,1,1,1},
  {255,255,255,255,255,255,255,255},
  {127,127,127,127,127,127,127,127}},
  {
    {127,127,127,127,127,127,127,127},
  {63,63,63,63,63,63,63,63},
  {31,31,31,31,31,31,31,31},
  {15,15,15,15,15,15,15,15},
  {7,7,7,7,7,7,7,7},
  {3,3,3,3,3,3,3,3},
  {1,1,1,1,1,1,1,1},
  {255,255,255,255,255,255,255,255}},
  {
    {255,255,255,255,255,255,255,255},
  {127,127,127,127,127,127,127,127},
  {63,63,63,63,63,63,63,63},
  {31,31,31,31,31,31,31,31},
  {15,15,15,15,15,15,15,15},
  {7,7,7,7,7,7,7,7},
  {3,3,3,3,3,3,3,3},
  {1,1,1,1,1,1,1,1}}
};

//byte leds[6][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};

/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup() 
{
  SPI.begin();
  SPI.beginTransaction(Settings_Cube);
  
  
  for (int i = 0; i < 8; i++){
    pinMode(layers[i], OUTPUT);
  }
}

/*
 * loop() - this function runs over and over again
 */
void loop() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    frame++;
    if(frame==8){
      frame=0;
    }
  }
  showCube(frame);
}

void showCube(int mFrame){
  for (int layer = 0; layer < 8; layer++){
    for (int j = 0; j < 8; j++){
      digitalWrite(layers[j], LOW);
    }
    digitalWrite(layers[layer], HIGH);
    updateShiftRegister(leds[mFrame][layer]);
  }
}

/*
 * updateShiftRegister() - This function sets the latchPin to low, then calls the Arduino function 'shiftOut' to shift out contents of variable 'leds' in the shift register before putting the 'latchPin' high again.
 */
void updateShiftRegister(byte shiftLeds[8])
{
  digitalWrite(SS, LOW);
  for (int i = 0; i < sizeof(shiftLeds); i++)
  {
    SPI.transfer(shiftLeds[i]);
  }
  digitalWrite(SS, HIGH);
}