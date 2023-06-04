/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo de comunicacion por el puerto serie de un Arduino y un ESP32
 *               Este codigo pertenece al ESP32, esta a la espera de que se toque Touch3(GPIO15)
 *               que le enviara por serie un aviso al Arduino para que este encienda o apage un LED
 **************************************************************************************************/
#include <HardwareSerial.h>
HardwareSerial Puerto(2);  // Se asigna el UART2
#define RX    16
#define TX    17

#define UMBRAL  15
#define PIN_TOUCH T3 

#define TAMANO 1000

void setup() 
{
  Serial.begin(115200);  // Velocidad de visualización de la consola.
  Puerto.begin(9600, SERIAL_8N1, RX, TX);

}

void loop() 
{
  if(pulsado(PIN_TOUCH)) 
  {
    Serial.println("Enviamos Mensaje a Arduino");
    Puerto.write('P');
    delay(5000);
  }
  delay(1000);
  
}

/***************************************************************************************
 * boolean pulsador(GPIO)  Retorna true o false segun estemos o no tocando el cable
 ***************************************************************************************
*/
boolean pulsado(int Touch)
{
  boolean retorno = false;
  int valor = touchRead(Touch);
  if (valor < UMBRAL ) 
  {
    Serial.println(valor);
    while (valor > UMBRAL) { delay(10); } // Esperamos que se suelte.
    retorno = true;
  }
  return retorno;
}
 
