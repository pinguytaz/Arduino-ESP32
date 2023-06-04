/*  ----------------------------------------------------------------
Fco. Javier Rodriguez Navarro   www.pinguytaz.net

  
Configuración comandos AT del ESP-01
------------------------------------------------------------------*/
#include "SoftwareSerial.h"

const byte rxPin = 12;
const byte txPin = 11;
//SoftwareSerial puertoSerie = SoftwareSerial(rxPin, txPin);
SoftwareSerial puertoSerie(rxPin, txPin);


const int baudios = 9600;

void setup()
{
   Serial.begin(9600);
   puertoSerie.begin(baudios);
   Serial.println("Inicializado");
}

void loop()
{
   bool datos = false;
   while (puertoSerie.available())
   {
      Serial.print((char)puertoSerie.read());
      datos = true;
   }
   if(datos) Serial.println("");
  
  if (Serial.available())
  {
    puertoSerie.write((char)Serial.read());
    //Serial.println((char) Serial.read());
    //Serial.println("DISPO");
  }
}