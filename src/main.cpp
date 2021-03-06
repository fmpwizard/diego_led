#include <Adafruit_NeoPixel.h>
#include "Arduino.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6 // Diego's lamnp has 6 here
//#define PIN 11 // Stella's lamnp has 11 here

//======================================

// Read pin from moteino
//uint32_t numOfLeds = 150;
uint32_t numOfLeds = 2; // diego's lamp 2 led
//uint32_t numOfLeds =16; // Stella's lamp, 16 led
//======================================

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel hoop = Adafruit_NeoPixel(numOfLeds, PIN, NEO_RGB + NEO_KHZ800); //Diffused individual leds use this
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(numOfLeds, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  Serial.begin(9600);

  hoop.begin();
  hoop.show(); // Initialize all pixels to 'off'
}

//=============================
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return hoop.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return hoop.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return hoop.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint16_t wait) {
  uint16_t i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< numOfLeds; i++) {
      hoop.setPixelColor(i, Wheel(((i * 256 / numOfLeds) + j) & 255));
    }
    hoop.show();
    delay(wait);
  }
}



// cycle just two colors
void cycleTwoColors(uint16_t wait) {
  hoop.clear();

  for(uint16_t i=0; i<numOfLeds; i++) {
    hoop.setPixelColor(i, hoop.Color(250, 0, 0));
    hoop.show();
    delay(wait);
    hoop.setPixelColor(i, hoop.Color(0, 0, 250));
    hoop.show();
    delay(wait);
  }
}


void rainbowStop() {
  uint16_t x;
  for(x=0; x < numOfLeds; x++) {
    hoop.setPixelColor( x, hoop.Color(200,100,100));
  }
  hoop.show();
}

void loop() {
    //rainbowCycle(100);
    //rainbowStop();
    cycleTwoColors(900);
}
