/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo de comunicacion por el puerto serie de un Arduino y un ESP32
 *               Este codigo pertenece al Arduino, que actua como maestro, y solicitara una 
 *               medida para reflejarla en el DISPLAY, mediante el mensaje "P" y dara el OK
 *               mediante un mesnaje "O".
 ******************************************************************************************/
#include <Wire.h>
#include <Adafruit_GFX.h>    // Nucleo de la libreria
#include <Adafruit_ST7735.h> // Hardware ST7735
#include <SPI.h>             // Comunicacion SPI, por el que se comunica el Display.

#define TFT_CS   10  // Selector (HSPI_MOSI 15)
#define TFT_MOSI 11  // Datos de salida (HSPI_MOSI 13)
#define TFT_SCLK 13  // Reloj   (HSPI_MOSI 14)
 
#define TFT_RST        9
#define TFT_DC         8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
#define BOTON  12
#define DIRECCION 0x66

enum Msg { CMD_INICIO = 0, 
           CMD_MEDIDA = 1, 
           CMD_OK = 2
         };

#define X 65
#define Y 80
#define R 50

void setup() 
{
  Serial.begin(9600);  

  Wire.begin();     // Es un maestro.
  
  pinMode(BOTON,INPUT);
  // Inicializamos la pantalla
  tft.initR(INITR_BLACKTAB);   
  tft.fillScreen(ST77XX_BLUE);
  tft.print("Arduino ");
  tft.fillCircle(X,Y,R,ST77XX_YELLOW);

  Serial.println("Nos iniciamos");     
}

void loop() 
{
   byte byteAlto;
   byte byteBajo;
   int medida ;
   int reading = 0;

   while (digitalRead(BOTON))
   {
      Serial.println("Boton Pulsado se envia mensaje");
      delay(2000);   // Evitamos el rebote
      Wire.beginTransmission(DIRECCION);
         Wire.write(CMD_MEDIDA) ;
      Wire.endTransmission();

      // Esperamos respuesta que deben de ser 2 bytes con la medida
      Serial.println(String(Wire.requestFrom(DIRECCION, 2))); 
      while(Wire.available()!=2) { delay(100); }
      byteAlto = Wire.read();
      byteBajo = Wire.read();
      
      medida = (byteAlto << 8) + byteBajo;
      Serial.println("Medida " + String(medida));
      medida = map(medida,0,4095,0,360);
      Serial.println("Mapeada " + String(medida));

      // Dibujamos
      tft.fillScreen(ST77XX_RED);
      tft.fillCircle(X,Y,R,ST77XX_YELLOW);
      for (int angulo=0; angulo <= medida; angulo++)
      {
         double X2 = R * cos(angulo * PI/180) +X  ;
         double Y2 = Y - ( R * sin(angulo * PI/180) );
         tft.drawLine(X,Y,X2,Y2,ST77XX_RED);
      }
      Serial.println("OK fin del dibujo");
      Wire.beginTransmission(DIRECCION);
         Wire.write(CMD_OK) ;
      Wire.endTransmission();      
   }
   delay(100);
}
