/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo del uso de E Analogica, con un sensor de temperatura
 *  TMP36.
 *  Codigo preparado para Arduino y ESP32.
 **************************************************************************************************/
// Dejamos sin comentar la placa que corresponda
//#define PLAT_ARDUINO
#define PLAT_ESP32

#if defined(PLAT_ARDUINO)
    #define SONDA_TMP A0
    #define RESOL 1024.0
    #define VOLTAJE 5.0
#else
   #define SONDA_TMP 34
   #define RESOL 4096.0
    #define VOLTAJE 3.3
#endif


void setup() 
{
    #if defined(PLAT_ARDUINO)
       Serial.begin(9600);
   #else
       Serial.begin(115200);
   #endif
}

void loop() 
{
   int valor;
   float voltaje;
   float temperatura;
   valor = analogRead(SONDA_TMP);
   voltaje = (valor/RESOL)*VOLTAJE;
   temperatura = (voltaje - .5)*100;
   
   Serial.println("Valor: "+String(valor)+" Voltaje: "+String(voltaje)+" Temperatura: "+String(temperatura));
   delay(1000);
}
