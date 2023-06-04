/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo de uso del SPIFFS, escribiendo el texto deunos ficheros y dibujando
 *               imagenes.
 *  Librerias:   SPIFSS
 *  
 *  Cargas: Debemos cargar los ficheros Racoon1.bmp y Racoon2.bmp para el dibujo y Texto.txt
 ***********************************************************************************************/
#include "SPIFFS.h";
#include <Adafruit_GFX.h>    // Nucleo de la libreria
#include <Adafruit_ST7735.h> // Hardware ST7735
#include <SPIFFS_ImageReader.h>
#include <SPI.h>             // Comunicacion SPI, por el que se comunica el Display.

#define TFT_CS   5  // Selector (HSPI_MOSI 15)
#define TFT_MOSI 23  // Datos de salida (HSPI_MOSI 13)
#define TFT_SCLK 18  // Reloj   (HSPI_MOSI 14)

#define TFT_RST        2
#define TFT_DC         4

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
SPIFFS_ImageReader lector;

uint16_t colorFondo = 0;   // 0-0xFFFF
bool racon=true;

void setup()
{
    Serial.begin(115200);
    if(!SPIFFS.begin(true))
    {
       Serial.println("Error Montando SPIFFS");
       return;
    }

    Serial.print(F("Inicio Test SPIFFS y Dibujo en display"));

    // Inicializamos la pantalla
    tft.initR(INITR_BLACKTAB);   
}

void loop() 
{
   File fp;
   
   // Se inicializa la pantalla.
   tft.fillScreen(colorFondo);  // Cambiamos color y limpiamos fondo
   colorFondo += 255;
   if(colorFondo >= 0xFFFF) colorFondo=0;
   tft.setRotation(0); // Definimos que se escriba de aabajo arriba
   tft.setTextSize(1);   // Tamaño del texto de 1-5
   tft.setCursor(0,0); // Posicion del Cursor en la esquina de arriba a la izquierda.
   tft.setTextColor(ST77XX_GREEN,ST77XX_RED);  // Color del texto y fondo

   // Imprimimos el Texto.
   fp = SPIFFS.open("/Texto.txt");
   if(!fp)
   {
      Serial.println("Fallo al abrir el fichero");
      return;
   }
  
   Serial.println("Imprimimos el contenido del fichero.");
   while(fp.available())
   {
      char caracter;
      caracter = fp.read();
      Serial.write(caracter);
      tft.print(String(caracter));
  }
  fp.close();

  tft.setCursor(0,130); // Posicion del Cursor en la esquina de arriba a la izquierda.
  tft.setTextColor(ST77XX_RED,ST77XX_BLUE);  // Color del texto y fondo
  tft.setTextSize(2);
 
  // Imprimimos El dibujo.
  if (racon) 
  {
    lector.drawBMP("/Racoon1.bmp", tft, 0, 20);
    Serial.println("Se dibuja Racoon1");
    tft.print("Racoon1");
  }
  else
  {
    lector.drawBMP("/Racoon2.bmp", tft, 0, 20);
    Serial.println("Se dibuja Racoon2");
    tft.print("Racoon2");
  }
  racon = !racon;
  
  delay(15000);    
}
