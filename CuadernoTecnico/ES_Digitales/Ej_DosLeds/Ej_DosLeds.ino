/*  ----------------------------------------------------------------
Fco. Javier Rodriguez Navarro   www.pinguytaz.net

  
Este ejemplo enciende un LED y apaga otro , con una unica salida digital (P_LED), 
segunse pulsa un boton (P_Boton
El ejemplo muestra como podemos codificar para dos plataformas distintas en un solo
codigo gracias a las funciones del preprocesador.
------------------------------------------------------------------*/
//   Dejar la plataforma para la que va a ser utilizada la Balanza
//#define PLAT_ARDUINO
#define PLAT_ESP32

#if defined(PLAT_ARDUINO)
   #define P_LED 4
   #define P_Boton 7
#else                       
   #define P_LED 25
   #define P_Boton 34
#endif

bool cambio=true;

void setup() 
{
  // También cambiaríamos la velocidad del puerto de consola segun plataforma
  #if defined(PLAT_ARDUINO)
     Serial.begin(9600);
  #else
        Serial.begin(115200);
  #endif
  pinMode(P_LED, OUTPUT);
  pinMode(P_Boton, INPUT);
}

void loop() 
{
  if(digitalRead(P_Boton) == LOW) 
  {
    cambio = !cambio;
    Serial.println(cambio);   // Visualiza en consola la variable cambio, así verificamos que se lee el cambio de botón.
    if(cambio) digitalWrite(P_LED,HIGH);
    else digitalWrite(P_LED,LOW);
    delay(500);  // Evitamos rebote
  }
}
