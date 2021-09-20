/*  ----------------------------------------------------------------
Fco. Javier Rodriguez Navarro   www.pinguytaz.net

  
Ejemplo para creación de sonido con Arduino y ESP32

----------------------------------------------------------------*/
//   Descomentar la plataforma para la que va a ser utilizada la Balanza
//#define PLAT_ARDUINO
#define PLAT_ESP32

// Positivo del Buzer, genera señal
#if defined(PLAT_ARDUINO)
   #define BZ 8
#else
   #define BZ 18
#endif

void setup()  // configuracion placa
{
   // También cambiaríamos la velocidad del puerto de consola segun plataforma
   #if defined(PLAT_ARDUINO)
      Serial.begin(9600);
    #else
      Serial.begin(115200);
      pinMode(BZ, OUTPUT);
      ledcAttachPin(BZ, 0);   // Enlazamos Pin con canal 0
    #endif


  pinMode( BZ , OUTPUT); // Buzzer se define como salida
}

void loop()  //Se repite indefinidamente,
{
  int frecuencia = 262;
  int duracion = 100;
  
  // Codigo Arduino
  #if defined(PLAT_ARDUINO)
     // Codigo Arduino
     tone(BZ, frecuencia);
     delay(duracion);
     noTone(BZ);
  #else
     ledcWriteTone(0, frecuencia); //Toca Tono definido en la frecuencia con su duración
     delay(duracion);
  
     // Cortamos Tono
     //ledcDetachPin(BZ);
     ledcWrite(0,0);
     
   #endif
    
  Serial.println("FIN");
  delay(1500);
}
