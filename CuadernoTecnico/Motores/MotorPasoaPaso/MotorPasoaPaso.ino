/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo de programacion de un Motor paso a paso
 *
 *  Librerias:   
 *  
 ***********************************************************************************************/
#include <Stepper.h>
#define PULSADOR  2

const int pasosPorVuelta = 200;
Stepper myStepper = Stepper(pasosPorVuelta, 8, 9, 10, 11);


int estado = 1; 
bool antiguo = LOW;
 

void setup() 
{
  Serial.begin(9600);    // abre el Puerto serie y lanza los primeros envios
  
  // Definimos Pines
  pinMode(PULSADOR, INPUT); // declara pulsador como entrada

  Serial.println("---- INICIO -------");  
  myStepper.setSpeed(100);    //Velocidad del motor RPM
  

}

void loop() 
{
  int val = 0;
  val =digitalRead(PULSADOR);
myStepper.step(160);
  delay(2000);
  //myStepper.step(-90);
  //if ( (((estado % 2) == 0) && val == HIGH) || (((estado % 2) != 0) && val == LOW))  // Se cambia en estado par se pulsa y en impares se suelta
  if(antiguo != val)  // Cambio de estado
  {
    antiguo = val;
    Serial.println("Realiza el estado " + String(estado++));
    
    delay(1500);   // Evita rebote
  }
}
