/* **********************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *  
 *  Descripción: Ejemplo de manejo libreria HMC5883L
 *  
 *  Historico:
 *      Creación:  Febrero 2021  FJRN
 *                 
 *  *********************************************/

#include "HMC5883L_3Axi.h"
#include <math.h>
#include <Wire.h>


HMC5883L_3Axi medidor;

void setup() 
{
   Serial.begin(9600);  // Para sacar debug e información por el puerto serie

   Wire.begin(); // Se inicializa el interface I2C
   Serial.println("-------------------\n");
   
   if(!medidor.inicializa()) Serial.println("Error Dispo 3Axi");
   else Serial.println("Correcto");

   // medidor.setModo(HMC5883L_SIMPLE);  // Modo lectura simple
   
}

void loop() 
{
  float angulo;
  String punto;
  
  coordenadas misdatos;
  
  misdatos = medidor.leedatos();

  // Campo magnetico
  Serial.print("--"+String(millis())+"--\n");
  Serial.print("RX: "+ String(misdatos.datoX)+"\n");
  Serial.print("RXN: "+ String(misdatos.datoXN)+"\n");
  Serial.print("RY: "+ String(misdatos.datoY)+"\n");
  Serial.print("RYN: "+ String(misdatos.datoYN)+"\n");
  Serial.print("RZ: "+ String(misdatos.datoZ)+"\n");
  Serial.print("RZN: "+ String(misdatos.datoZN)+"\n");
  
  // Grados
  angulo = atan2(misdatos.datoYN,misdatos.datoXN);
  if(angulo<0) angulo += 2*PI;
  if(angulo> 2*PI) angulo -= 2*PI;
  Serial.print("Ang_R: "+ String(angulo)+"\n");
  Serial.print("Ang_G: "+ String(angulo*(180/PI))+"\n");
 
  Serial.println("+++++++++");
  
  
 
  delay(10000);
}
