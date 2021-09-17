/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo del uso de E Analogica, con un sensor de temperatura
 *  TMP36, con display LCD-I2C
 *  
 *  Codigo preparado para Arduino y ESP32.
 *  Libreria: LiquidCrystal_I2C   https://github.com/johnrickman/LiquidCrystal_I2C
 *  
 **************************************************************************************************/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Dejamos sin comentar la placa que corresponda
//#define PLAT_ARDUINO
#define PLAT_ESP32

#if defined(PLAT_ARDUINO)
    #define SONDA_TMP A0
    #define RESOL 1024.0
    #define VOLTAJE 5.0
#else
   #define SONDA_TMP 34
   #define RESOL 4094.0
   #define VOLTAJE 3.3
#endif

LiquidCrystal_I2C lcd(0x27,20,4); // Poner la dirección localizada con el scaner I2C


void setup() 
{
    #if defined(PLAT_ARDUINO)
       Serial.begin(9600);
   #else
       Serial.begin(115200);
      // analogReadResolution(9);  // Definimos resolución de 9 o 12
   #endif
   Wire.begin();

   
   // DISPLAY

   // Definimos un caracter de carita sonriente.
    uint8_t muneco[8] = {
                    B01110,
                    B01110,
                    B00100,
                    B11111,
                    B00100,
                    B01010,
                    B10001,
                    B00000,
                   };

   lcd.init();   // Iniciar el LCD para trabajar
   lcd.backlight(); //Activar la retroiluminación.
   lcd.createChar(3, muneco); // Definimos muñeco en el 3
      
   lcd.clear();
   lcd.write(3);   
   lcd.print("www.pinguytaz.net");
   lcd.write(3);   
}

void loop() 
{
   int valor;
   float voltaje;
   float temperatura;
   valor = analogRead(SONDA_TMP);
   
   voltaje = (valor / RESOL)*VOLTAJE;
   //temperatura = (voltaje - 0.5)*100;
   temperatura =((voltaje*25.0)/0.75);   // 25 Grados son 750mV
  
   Serial.println("Valor: "+String(valor)+" Voltaje: "+String(voltaje)+" Temperatura: "+String(temperatura));
   
   lcd.setCursor(0, 1); 
   lcd.print("Valor: ");
   lcd.print(String(valor));
   lcd.setCursor(0, 2); 
   lcd.print("Voltaje: "); 
   lcd.print(String(voltaje));
   lcd.setCursor(0, 3); 
   lcd.print("Temperatura:        ");
   lcd.setCursor(13, 3); 
   lcd.print(String(temperatura));
   lcd.write(0xDF);  // Caracter de grados.
   
   delay(1000);
}
