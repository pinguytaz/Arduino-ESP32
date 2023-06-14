/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo de uso de la pantalla TFT ST7735 mediante SPI.
 *  
 *  Libreria: Adafruit-ST7735
 ***************************************************************************************************/
#include <Adafruit_GFX.h>    // Nucleo de la libreria
#include <Adafruit_ST7735.h> // Hardware ST7735
#include <SPI.h>             // Comunicacion SPI, por el que se comunica el Display.


#if defined(ESP32) // ESP32
   #define TFT_CS   5  // Selector (HSPI_MOSI 15)
   #define TFT_MOSI 23  // Datos de salida (HSPI_MOSI 13)
   #define TFT_SCLK 18  // Reloj   (HSPI_MOSI 14)
  
   #define TFT_RST        2
   #define TFT_DC         4
#else     // Arduino
   #define TFT_CS         10  // Selector
   #define TFT_MOSI 11  // Datos de salida
   #define TFT_SCLK 13  // Reloj
   
   #define TFT_RST        9
   #define TFT_DC         8
   
#endif

// 1.8" TFT con ST7735:
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


void setup()
{
  #if defined(ESP32) 
     Serial.begin(115200);
  #else
     Serial.begin(9600);
  #endif

  Serial.print(F("Inicio Test ST7735S"));

  // Inicializamos la pantalla
  tft.initR(INITR_BLACKTAB);   

  
}

void loop() 
{
   // Uso de TEXTO
   tft.fillScreen(ST77XX_BLUE);  // Ponemos Fondo Azul y limpiamos pantalla  
   
   tft.setRotation(3); // Definimos que se escriba de aabajo arriba
   tft.setTextSize(1);   // Tamaño del texto de 1-5
   tft.setCursor(0,100); // Posicion del Cursor,x,y
   tft.setTextColor(ST77XX_GREEN,ST77XX_RED);  // Color del texto y fondo
   tft.print("Texto de abajo arriba");
  
   tft.setRotation(0); // Define como escribira  (0 Normal, 1 90 Grados, 2 180 y 3 270 Grados)
   tft.setCursor(0,0); // Posicion del Cursor,x,y
   tft.setTextColor(ST77XX_YELLOW);  // Color del texto
   tft.println("Prueba de ST7735");
   tft.setTextColor(ST77XX_RED);  // Color del texto
   tft.setTextSize(2);   // Tamaño del texto de 1-5
   tft.println("Otra linea");
   tft.setTextSize(1,2);   // Tamaño del texto de 1-5 el ancho y el alto
   tft.println("Ancho: "+ String(tft.width()));   // Da el ancho
   tft.println("Alto: "+ String(tft.height()));   // Da el alto de la pantalla
   
   delay(10000);

   // Dibujo de lineas
   tft.fillScreen(ST77XX_RED);
   tft.setRotation(0); 
   tft.setCursor(0,0); // Posicion del Cursor,x,y
   tft.setTextSize(3); 
   tft.setTextColor(ST77XX_YELLOW);  // Color del texto
   tft.println("Lineas");
   
   tft.drawFastVLine(10,30,66,ST77XX_CYAN);   // Horizontal x,y, longitud y color
   tft.drawFastHLine(10,30,66,ST77XX_BLUE);    // Linea vertical x,y,longitud,color
   tft.drawLine(0,0,50,100,ST77XX_MAGENTA);              // Linea de x,y a x2,y2 y color
   delay(10000); 

   // Dibujo figuras geometricas
   tft.fillScreen(ST77XX_BLACK);   // Negro
   tft.setRotation(0); 
   tft.setCursor(0,0); // Posicion del Cursor,x,y
   tft.setTextSize(2); 
   tft.setTextColor(ST77XX_WHITE);  // Color del texto
   tft.println("Figuras");

   tft.drawRect(0,20,50,10,ST77XX_BLUE);   // Rectangulo x,y,ancho, alto, color
   tft.fillRect(50,20,50,10,ST77XX_BLUE);   // Rectangulo relleno
   tft.drawRoundRect(0,35,50,10,2,ST77XX_RED);   // Esquinas redondeadas  x,y,ancho, alto, radio esquinas, color
   tft.fillRoundRect(50,35,50,10,15,ST77XX_RED);   // Igual pero relleno
   tft.drawCircle(15,70,7,ST77XX_GREEN);   // Circulo x,y,radio,color
   tft.fillCircle(50,70,10,ST77XX_GREEN);  // Circulo relleno.
   tft.drawTriangle(0,150,50,150,10,90,ST77XX_BLUE);  // Triangulo indicando las esquinas y color
   tft.fillTriangle(50,150,80,150,10,90,ST77XX_ORANGE);   // Triangilño relleno
   
   delay(10000); 
}
