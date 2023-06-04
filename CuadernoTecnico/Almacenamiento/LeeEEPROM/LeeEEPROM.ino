/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Lee datos en las EPROM o FLASH Segun sea Arduino o ESP32
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
   //EEPROM.get(0,dato);  // EEPROM.read(direccion) Retorna byte
   //dato=EEPROM.read(0);
   EEPROM.get(0,dato);
   Serial.print("El Numero Leido es: ");
   Serial.println(dato);  
}

void loop() {}
