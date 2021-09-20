/*  ----------------------------------------------------------------
Fco. Javier Rodriguez Navarro   www.pinguytaz.net

  
Generando musica
 
------------------------------------------------------------------*/

// Descomenta la melodia que desees
//#include "FrereJacques.h"
#include "GGalaxia.h"



//   Descomentar la plataforma para la que va a ser utilizada la Balanza
#define PLAT_ARDUINO
//#define PLAT_ESP32


// Positivo del Buzer, genera señal
#if defined(PLAT_ARDUINO)
   #define BZ 8
#else
   #define BZ 18
#endif


void setup()  // configuracion placa
{
   // También cambiaríamos la velocidad del puerto de consola segun plataforma
   pinMode(BZ, OUTPUT);

   #if defined(PLAT_ARDUINO)
      Serial.begin(9600);
    #else
      ledcSetup(0, 0, 10);
      ledcAttachPin(BZ, 0);

      Serial.begin(115200);
    #endif
}

void loop()  //Se repite indefinidamente,
{
  Serial.print("Inicio Melodia --- ");
  for (int i=0 ; i < NOTAS; i++)
  {
     beep(duracion[i],melodia[i]);
  }
 
  Serial.println("FIN");
  delay(1500);
}


/************************************************************
 * Funciones para generar sonido
 * 
 * void beep(float, unsigned int tono)  
 *    Genera una nota indexada como 0 el DO de la 4ª Octava
 *    de una duración.
 *    La Nota 100 Indica silencio
  ************************************************************/
void beep(float duracion, unsigned int nota)
{
   int frecuencia;  

   if(nota < 100)
   {
      // Calculamos la frecuencia a tocar, indice 0 Do4
      frecuencia = (int) 261.625 * pow(1.0594630943593,nota);
   }
   else frecuencia =0;
   
 // Codigo Arduino
  #if defined(PLAT_ARDUINO)
     // Codigo Arduino
     tone(BZ, frecuencia);
     delay(duracion*500);
     noTone(BZ);
  #else
    ledcWriteTone(0, frecuencia); //Toca Tono definido en la frecuencia con su duración
    delay(duracion*500);
    ledcWrite(0,0);   
  #endif
}
