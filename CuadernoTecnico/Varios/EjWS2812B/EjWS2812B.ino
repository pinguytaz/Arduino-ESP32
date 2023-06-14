/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción:  Ejemplo uso de leds RGB WS2812B con Arduino y libreria


 **************************************************************************************************/
#include <Arduino.h>
#include <FastLED.h>

#define TIPO_LED    WS2812B  // WS2812B
#define ORDEN_COLOR GRB   // GRB o RGB
#define NUM_LEDS   4  //  Numero de Leds 

#define PIN_LED     12  // Pin en el que se conecta la tira.
#define LEDs_SEC 16  // Secuencias 

CRGB leds[NUM_LEDS];   // Matriz que permite manipular los LEDs
CRGB secuencias[LEDs_SEC][NUM_LEDS]={
//CRGB secuencias[LEDs_SEC][4]={
  CRGB::White,CRGB::Red,CRGB::Green,CRGB::Blue,
  CRGB::Red,CRGB::White,CRGB::Green,CRGB::Blue,
  CRGB::Red,CRGB::Green,CRGB::White,CRGB::Blue,
  CRGB::Red,CRGB::Green,CRGB::Blue,CRGB::White,
  CRGB::DarkViolet,CRGB::Red,CRGB::Green,CRGB::Blue,
  CRGB::Red,CRGB::DarkViolet,CRGB::Green,CRGB::Blue,
  CRGB::Red,CRGB::Green,CRGB::DarkViolet,CRGB::Blue,
  CRGB::Red,CRGB::Green,CRGB::Blue,CRGB::DarkViolet,
  CRGB::Yellow,CRGB::Red,CRGB::Green,CRGB::Blue,
  CRGB::Red,CRGB::Yellow,CRGB::Green,CRGB::Blue,
  CRGB::Red,CRGB::Green,CRGB::Yellow,CRGB::Blue,
  CRGB::Red,CRGB::Green,CRGB::Blue,CRGB::Yellow,
  CRGB::Black,CRGB::Red,CRGB::Green,CRGB::Blue,
  CRGB::Red,CRGB::Black,CRGB::Green,CRGB::Blue,
  CRGB::Red,CRGB::Green,CRGB::Black,CRGB::Blue,
  CRGB::Red,CRGB::Green,CRGB::Blue,CRGB::Black
};

void setup() 
{
  Serial.begin(9600);  // Coonfiguración para la consola. Se usuara para depuración y configuracion.
  // Configuramos Tiras de LEDs y sin pin de control.
  FastLED.addLeds < TIPO_LED, PIN_LED, ORDEN_COLOR  > (leds, NUM_LEDS); 
  //FastLED.setMaxPowerInVoltsAndMilliamps(5,50);  // Maximo consumo que tendremos
   FastLED.setBrightness(4);
  delay(1000);
  FastLED.clearData();  // Reiniciamos toda la tira.

  for (int l=0; l<NUM_LEDS; l++) leds[l]= CRGB::Black;  // Se apagan
   FastLED.show();
   delay(4200);
  
}

void loop() 
{ 
  Serial.println("Inicio Secuencia");
  for (int i = 0; i<LEDs_SEC; i++)
  {
    Serial.println("Secuencia "+ String(i));
    for (int l=0; l<NUM_LEDS; l++) 
    //for (int l=0; l<4; l++) 
    {
        leds[l]= secuencias[i][l];
        /*leds[l+4]= secuencias[i][l];
        leds[l+8]= secuencias[i][l];
        leds[l+12]= secuencias[i][l];
        leds[l+16]= secuencias[i][l];
        */
    }
    FastLED.show();
    delay(1000); 
  }
  delay (3000);
}
