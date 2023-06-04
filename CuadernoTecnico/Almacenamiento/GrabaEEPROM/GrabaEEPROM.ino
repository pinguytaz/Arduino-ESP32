/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Graba Datos en las EPROM o FLASH Segun sea Arduino o ESP32
 ***********************************************************************************************/
#include <EEPROM.h>
//   Dejar la plataforma para el que se compila
//#define PLAT_ARDUINO
#define PLAT_ESP32

#if defined(PLAT_ARDUINO)
   
#else                       
   #define EEPROM_SIZE 5
#endif

void setup() 
{
  int dato;
#if defined(PLAT_ARDUINO)
  Serial.begin(9600);
   
#else                       
   Serial.begin(115200);
   EEPROM.begin(EEPROM_SIZE);
#endif
   EEPROM.get(0,dato);
   Serial.print("El viejo valor es: ");
   Serial.println(dato);

   
   EEPROM.put(0,1966);   //EEPROM.write(direccion, valor) seria un byte
   Serial.println("Grabado el 1966");

#if defined(PLAT_ESP32)
   EEPROM.commit();
#endif
}


void loop() {}
