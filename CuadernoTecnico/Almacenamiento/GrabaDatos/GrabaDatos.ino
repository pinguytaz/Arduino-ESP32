/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Graba Datos en las EPROM para el uso de WIFI y Bot de Telegram
 ***********************************************************************************************/
#include "EEPROM.h"

#define TAMANO 1000
typedef struct
{
   String ssid;   // Maximo tamaño 63
   String clave;   // Maximo tamaño 40
} Datos;

void setup() 
{
   Datos misdatos;
   Serial.begin(115200);
 
   misdatos.ssid= "SSID de la WIFI";
   misdatos.clave= "Clave de acceso a wifi";
   Serial.println("\nComenzamos la grabacion");
   escribe(misdatos);
   Serial.println("Datos Grabados");

/*   misdatos = lee();
   Serial.println("SSID: "+ misdatos.ssid);
   Serial.println("Clave: "+ misdatos.clave);
   
  */ 
}

void loop() {}

void escribe(Datos datos)
{
   if (!EEPROM.begin(TAMANO)) 
   {
      Serial.println("Fallo al iniciar EEPROM");
      Serial.println("Reiniciamos...");
      delay(1000);
      ESP.restart();
   }
   int direccion =0;
   EEPROM.writeString(direccion, datos.ssid);
   direccion += datos.ssid.length() + 1;

   EEPROM.writeString(direccion, datos.clave);
   direccion += datos.clave.length() + 1;

   EEPROM.commit(); 
}

Datos lee()
{
   int direccion =0;
   Datos losdatos;

    if (!EEPROM.begin(TAMANO)) 
   {
      Serial.println("Fallo al iniciar EEPROM");
      Serial.println("Reiniciamos...");
      delay(1000);
      ESP.restart();
   }
   
   losdatos.ssid = EEPROM.readString(direccion);
   direccion += losdatos.ssid.length() + 1;

   losdatos.clave = EEPROM.readString(direccion);
   direccion += losdatos.clave.length() + 1;
   
   return losdatos;
   
}
