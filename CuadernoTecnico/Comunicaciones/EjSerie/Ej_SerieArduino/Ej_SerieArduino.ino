/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo de comunicacion por el puerto serie de un Arduino y un ESP32
 *               Este codigo pertenece al arduino
 *               Lo primero es poner el LED RGB en blanco a la espera de mensajes del ESP32 'P'
 *               Cada vez que nos llega un mensaje se cambia el color a Rojo, Verde, Azul, Rojo...
 **************************************************************************************************/

#include <SoftwareSerial.h>

const byte rxPin = 2;
const byte txPin = 3;
SoftwareSerial puertoSerie(rxPin, txPin); // RX, TX

#define ROJO  11
#define VERDE  10
#define AZUL  9

int estado =0;  //0 apagado, 1 Rojo, 2 Verde, 3 Azul y de este pasara a ROJO.

void setup()
{
   Serial.begin(9600);
   puertoSerie.begin(9600);   // Definimos la velocidad
   puertoSerie.listen();   // Ponemos el puerto a la escucha.
   while (!puertoSerie.isListening()){ delay(1000); }

   // Definimos salidas PWM para el diodo RGB
   pinMode(ROJO, OUTPUT);
   pinMode(VERDE, OUTPUT);
   pinMode(AZUL, OUTPUT);
   // Se pone en apagado
   analogWrite(ROJO, 0);
   analogWrite(VERDE, 0);
   analogWrite(AZUL, 0);
}

void loop() 
{
  delay(100);
  Serial.println("Vivo");
  if(puertoSerie.available() && puertoSerie.read() == 'P')
  {
     Serial.println(String(estado++));
     if (estado > 3) estado = 1;
     switch (estado) 
     {
        case 1:  // Ponemos Rojo
           analogWrite(ROJO, 250);
           analogWrite(VERDE, 0);
           analogWrite(AZUL, 0);
           break;
        case 2:  // Ponemos Verde
           analogWrite(ROJO, 0);
           analogWrite(VERDE, 250);
           analogWrite(AZUL, 0);
           break;
        case 3:  // Ponemos Azul
           analogWrite(ROJO, 0);
           analogWrite(VERDE, 0);
           analogWrite(AZUL, 250);
           break;
     }
  }
}
