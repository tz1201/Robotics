#include "arduinoFFT.h"
#include <FastLED.h>
 
#define SAMPLES 128             //Must be a power of 2
#define SAMPLING_FREQUENCY 3000 //Hz, must be less than 10000 due to ADC


//define leds
#define LED_PIN     5
#define NUM_LEDS    50
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

//for wheel
#define E1 2
#define E2 3
#define E3 4
#define D1A 22
#define D1B 24
#define D2A 26
#define D2B 28
#define D3A 30
#define D3B 32

CRGBPalette16 currentPalette;
TBlendType    currentBlending;
 
arduinoFFT FFT = arduinoFFT();
 
unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES];
double vImag[SAMPLES];
 
void setup() {
    Serial.begin(115200);
 
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));

    //for LED
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    //currentPalette = SetWhite();
    currentBlending = LINEARBLEND;
    //for motor
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
    pinMode(E3, OUTPUT);
    pinMode(D1A, OUTPUT);
    pinMode(D1B, OUTPUT);
    pinMode(D2A, OUTPUT);
    pinMode(D2B, OUTPUT);
    pinMode(D3A, OUTPUT);
    pinMode(D3B, OUTPUT);
}
 
void loop() {
   
    /*SAMPLING*/
    for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();    //Overflows after around 70 minutes!
     
        vReal[i] = analogRead(A0);
        vImag[i] = 0;
     
        while(micros() < (microseconds + sampling_period_us)){
        }
    }
 
    /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
 
    /*PRINT RESULTS*/
    Serial.println(peak);     //Print out what frequency is the most dominant.

    if ((peak > 255 && peak < 275) || (peak > 510 && peak < 550)){
      SetRed();
      //digitalWrite(LED_PIN,HIGH);
      digitalWrite(E3, HIGH);
      digitalWrite(D3A, HIGH);   
      digitalWrite(D3B, LOW);
      digitalWrite(E2, HIGH);
      digitalWrite(D2A, LOW);   
      digitalWrite(D2B, HIGH);
      digitalWrite(E1, LOW);
      }
    else if ((peak > 275 && peak < 315) || (peak > 550 && peak < 570)){
      SetOrange();
      digitalWrite(E3, HIGH);
      digitalWrite(D3A, HIGH);   
      digitalWrite(D3B, LOW);
      digitalWrite(E1, LOW);
      digitalWrite(E2, LOW);
      }
    else if ((peak > 315 && peak < 337) || (peak > 570 && peak < 630)){
      SetYellow();
      digitalWrite(E3, HIGH);
      digitalWrite(D3A, LOW);   
      digitalWrite(D3B, HIGH);
      digitalWrite(E1, LOW);
      digitalWrite(E2, LOW);
      }
    else if ((peak > 337 && peak < 370) || (peak > 630 && peak < 675)){
      SetGreen();
      digitalWrite(E2, HIGH);
      digitalWrite(D2A, LOW);   
      digitalWrite(D2B, HIGH);
      digitalWrite(E1, LOW);
      digitalWrite(E3, LOW);
      }
    else if ((peak > 370 && peak < 417) || (peak > 675 && peak < 740)){
      SetBlue();
      digitalWrite(E2, HIGH);
      digitalWrite(D2A, HIGH);   
      digitalWrite(D2B, LOW);
      digitalWrite(E1, LOW);
      digitalWrite(E3, LOW);
      }
    else if ((peak > 417 && peak < 460) || (peak > 740 && peak < 840)){
      SetPurple();
      digitalWrite(E1, HIGH);
      digitalWrite(D1A, LOW);   
      digitalWrite(D1B, HIGH);
      digitalWrite(E2, LOW);
      digitalWrite(E3, LOW);
      }
    else if ((peak > 460 && peak < 510) || (peak > 840 && peak < 940)){
      SetWhite();
      digitalWrite(E1, HIGH);
      digitalWrite(D1A, HIGH);   
      digitalWrite(D1B, LOW);
      digitalWrite(E2, LOW);
      digitalWrite(E3, LOW);
      }
     else{
      digitalWrite(E1, LOW);
      digitalWrite(E2, LOW);
      digitalWrite(E3, LOW);
      }

    //
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show(); 
      
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void SetRed(){
  CRGB Red  = CHSV( HUE_RED, 255, 255);
  currentPalette = CRGBPalette16(
                                   Red,  Red,  Red,  Red,
                                   Red,  Red,  Red,  Red,
                                   Red,  Red,  Red,  Red,
                                   Red,  Red,  Red,  Red );
  }
void SetOrange(){
  CRGB Orange  = CHSV( HUE_ORANGE, 255, 255);
  currentPalette = CRGBPalette16(
                                   Orange,  Orange,  Orange,  Orange,
                                   Orange,  Orange,  Orange,  Orange,
                                   Orange,  Orange,  Orange,  Orange,
                                   Orange,  Orange,  Orange,  Orange );
  }
void SetYellow(){
  CRGB Yellow  = CHSV( HUE_YELLOW, 255, 255);
  currentPalette = CRGBPalette16(
                                   Yellow,  Yellow,  Yellow,  Yellow,
                                   Yellow,  Yellow,  Yellow,  Yellow,
                                   Yellow,  Yellow,  Yellow,  Yellow,
                                   Yellow,  Yellow,  Yellow,  Yellow );
  }
void SetGreen(){
  CRGB Green  = CHSV( HUE_GREEN, 255, 255);
  currentPalette = CRGBPalette16(
                                   Green,  Green,  Green,  Green,
                                   Green,  Green,  Green,  Green,
                                   Green,  Green,  Green,  Green,
                                   Green,  Green,  Green,  Green );
  }
void SetBlue(){
  CRGB Blue  = CHSV( HUE_BLUE, 255, 255);
  currentPalette = CRGBPalette16(
                                   Blue,  Blue,  Blue,  Blue,
                                   Blue,  Blue,  Blue,  Blue,
                                   Blue,  Blue,  Blue,  Blue,
                                   Blue,  Blue,  Blue,  Blue );
  }
void SetPurple(){
  CRGB Purple  = CHSV( HUE_PURPLE, 255, 255);
  currentPalette = CRGBPalette16(
                                   Purple,  Purple,  Purple,  Purple,
                                   Purple,  Purple,  Purple,  Purple,
                                   Purple,  Purple,  Purple,  Purple,
                                   Purple,  Purple,  Purple,  Purple );
  }
 void SetWhite(){
  CRGB White  = CRGB::White;
  currentPalette = CRGBPalette16(
                                   White,  White,  White,  White,
                                   White,  White,  White,  White,
                                   White,  White,  White,  White,
                                   White,  White,  White,  White );
  }
