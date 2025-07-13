/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo para realizar una configuración en EEPROM por el puerto o ejecuta programa
 *               normalmente, eso lo marca un pin si esta pulsado entra en modo config sino modo normal.
 *               leyendo la configuración de la EEPROM
 *
 *               Protocolo: Si entra en configutación espera '#' cuando llega envia '|' indicando que
 *                          puede recibir y recibira el número de lineas que se enviaran y cadenas de lineas
 *               <R> <G> <B> que marca el color a poner en el LED 
 *               El programa lee la configuración de la EEPROM Num_Lineas y lineas comandos realizando la secuencia
 *               a golpe de cambio del estado del boton que se usa para configurar. Quitado inicio programa. 
 *
 * Esquema:    Boton que indica si ejecuta y marca ritmo lee configuración, Led RGB conectados a 3 PWM.
 *
 * Librerias:  EEPROM.h
 **************************************************************************************************/
#include <EEPROM.h>
#include "Funciones.h"

#define PINBOTON  2
#define ROJO   11
#define VERDE   10
#define AZUL   9

void setup() 
{
  Serial.begin(9600);
  delay(500); //Dar un poco de tiempo a prepararlo.

  pinMode(PINBOTON, INPUT); 
  // Definimos salidas PWM para el diodo RGB
  pinMode(13, OUTPUT);

  pinMode(ROJO, OUTPUT);
  pinMode(VERDE, OUTPUT);
  pinMode(AZUL, OUTPUT);

  if (!digitalRead(PINBOTON))   // Entramos en modo programación si el boton quitado
  {
    programarEEPROM();
    while (1);    // Se queda sin hacer nada a la espera de que se reinicie
  }

  // No entramos en modo de programación por lo tanto leemos la EEPROM poniendo los datos en variables antes llop
  leerEEPROM();

}

void loop() 
{
  static bool estadoAntiguo = digitalRead(PINBOTON);
  static int estado=0;

  bool val =digitalRead(PINBOTON);
  if(estadoAntiguo != val )  // Cambio de estado
  {
    estadoAntiguo = val;
    Serial.println("El estado: " + String(estado));
    Serial.println("   Rojo: " + String(estados[estado].rojo));
    Serial.println("   Verde: " + String(estados[estado].verde));
    Serial.println("   Azul: " + String(estados[estado].azul));
    analogWrite(ROJO, estados[estado].rojo);
    analogWrite(VERDE, estados[estado].verde);
    analogWrite(AZUL, estados[estado++].azul);
    if(estado == numEstados) estado = 0;
  }

  delay(2000);
}
