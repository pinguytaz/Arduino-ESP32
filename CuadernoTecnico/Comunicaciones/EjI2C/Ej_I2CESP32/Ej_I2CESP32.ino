/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo de comunicacion por el puerto I2C de un Arduino y un ESP32
 *               Este codigo pertenece al ESP32, esta a la espera de que Arduino le pida 
 *               una medida mediante el mensaje "P", que este informara
 **************************************************************************************************/
#include <Wire.h>

#define I2C_Freq 400000
#define SDA_0 21
#define SCL_0 22

#define LED  25
#define MEDIDA 34
#define DIRECCION 0x66

enum Msg { CMD_INICIO = 0, 
           CMD_MEDIDA = 1, 
           CMD_OK = 2
         };

Msg comando;

TwoWire I2C_1 = TwoWire(0); // Se selecciona el BUS1
int estado=0;  //0 es en espera, 1 Se solicito dato.
  

void setup() 
{
  Serial.begin(115200);  // Velocidad de visualización de la consola.

  comando = CMD_INICIO;
  pinMode(LED,OUTPUT);
  digitalWrite(LED , LOW);
  Serial.println("Nos iniciamos");

  I2C_1.onReceive(lleganDatos);   // Para tratar los datros que nos llegan
  I2C_1.onRequest(pideDatos);
  I2C_1.begin(DIRECCION,SDA_0,SCL_0, I2C_Freq);    // Es un esclavo

}

void loop() 
{
   
}

void lleganDatos(int len)
{
  comando = (Msg) I2C_1.read();
  if (comando == CMD_OK) digitalWrite(LED, HIGH); 
}

void pideDatos(void)
{
   int valor;
   byte byteAlto, byteBajo;

   Serial.println("Llega comando: "+String(comando));
   switch (comando)
   {
      case CMD_MEDIDA: 
         digitalWrite(LED, LOW);     
         valor = analogRead(MEDIDA);
         Serial.println(valor);
         byteAlto = highByte(valor);
         byteBajo = lowByte(valor);
         //Serial.println(byteAlto,HEX);
         //Serial.println(byteBajo,HEX);     
         I2C_1.write(byteAlto);
         I2C_1.write(byteBajo);  
         break;
      default: 
         break;
  }
}


 
