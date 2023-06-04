/*  ----------------------------------------------------------------
Fco. Javier Rodriguez Navarro   www.pinguytaz.net

  
Ejemplo de sueño ligero que se activa por tiempo.

----------------------------------------------------------------*/
#define FACTOR 1000000ULL  // Factor de conversión de micro segundos a segundos
#define TIEMPO_DORMIDO  5        // Tiempo en segundos que el ESP32 estará en suspensión ligera 
#define SENSIBILIDAD 40

int contador=0;

void setup()
{
  unsigned long miTiempo = millis();
  miTiempo = miTiempo /1000;
  Serial.begin(115200);
  Serial.printf("Estamos en el SetUp en el segundo %d\n",miTiempo);
}


void loop()
{
  unsigned long miTiempo = millis();
  miTiempo = miTiempo /1000;
  Serial.printf("Estamos en el Loop en el segundo %d y contador %d\n", miTiempo, contador++);
  razonDespertar(); //Imprime la razón por la que se despierta.



  // Definimos las fuentes de activación
  //Despertamos cada 20 segundos
  esp_sleep_enable_timer_wakeup( TIEMPO_DORMIDO * FACTOR); 

  Serial.println("Entramos en sueño ligero");
  Serial.flush(); 
  esp_light_sleep_start();  // Nos dormimos.

}

/*  Funcion que indica la causa por la que se despierta */
void razonDespertar()
{
   esp_sleep_wakeup_cause_t razon;
   razon = esp_sleep_get_wakeup_cause();  // obtenemos causa por la que despierta

   switch(razon)
   {
      case ESP_SLEEP_WAKEUP_EXT0: 
         Serial.println("Causa señal externa RTC_IO");
         break;
      case ESP_SLEEP_WAKEUP_EXT1: 
         Serial.println("Causa señal externa RTC_CNTL"); 
         break;
      case ESP_SLEEP_WAKEUP_TIMER: 
         Serial.println("Causa temporizador."); 
         break;
      case ESP_SLEEP_WAKEUP_TOUCHPAD: 
         Serial.println("Causa de activación el TOUCH"); 
         break;
      case ESP_SLEEP_WAKEUP_ULP: 
         Serial.println("Causa programa ULP"); 
         break;
      default: 
         Serial.printf("No estaba en sueño: %d\n",razon); 
         break;
   }
}
