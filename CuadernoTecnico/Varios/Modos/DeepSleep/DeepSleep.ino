/*  ----------------------------------------------------------------
Fco. Javier Rodriguez Navarro   www.pinguytaz.net

  
Ejemplo de modo profundo con activación por tiempo, TOUCH

----------------------------------------------------------------*/
#define FACTOR 1000000ULL  // Factor de conversión de micro segundos a segundos
#define TIEMPO_DORMIDO  15        // Tiempo en segundos que el ESP32 estará en suspensión ligera 
#define SENSIBILIDAD 20

int contador=0;
RTC_DATA_ATTR int contadorRTC = 0;


// CallBack de los TOUCH
void callback(){ }

void setup()
{
  unsigned long miTiempo = millis();
  miTiempo = miTiempo /1000;
  Serial.begin(115200);
  delay(1000);
  Serial.printf("Estamos en el SetUp en el segundo %d y los contadores %d -- %d\n",miTiempo,contador,contadorRTC);
  contador++;
  contadorRTC++;

  razonDespertar(); //Imprime la razón por la que se despierta.
 
  // Definimos las fuentes de activación
  // Despertamos cada 20 segundos
  esp_sleep_enable_timer_wakeup( TIEMPO_DORMIDO * FACTOR); 

  // Despertamos al pulsar alguno de los TOUCH3(GPIO15) y TOUCH7(GPIO27) 
 // touchAttachInterrupt(T3, callback, SENSIBILIDAD);
  //touchAttachInterrupt(T7, callback, SENSIBILIDAD);
  //esp_sleep_enable_touchpad_wakeup() ;  

  // Activación por ext0 en el GPIO13 que es el RTC_GPIO 14
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_13,1); //1 = High, 0 = Low

  if(contadorRTC < 3)  // Solo dormimos tres veces consecutivas.
  {
     Serial.println("Entramos en sueño profundo");
     Serial.flush(); 
     esp_deep_sleep_start();  // Nos dormimos.
  } 
}


void loop()   // En modo profundo no se ejecutara
{
  unsigned long miTiempo = millis();
  miTiempo = miTiempo /1000;
  Serial.printf("Estamos en el Loop en el segundo %d y contadores %d -- %d\n", miTiempo, contador++, contadorRTC++);
  //razonDespertar(); //Imprime la razón por la que se despierta.

  if (contador>5)  // Volvemos a dormir cuando pasamos por 5 loops
  {
     contadorRTC = 0;
     Serial.println("Entramos en sueño profundo");
     Serial.flush(); 
     esp_deep_sleep_start();  // Nos dormimos.
  }

  delay(2000);
}

/*  Funcion que indica la causa por la que se despierta */
void razonDespertar()
{
   esp_sleep_wakeup_cause_t razon;
   razon = esp_sleep_get_wakeup_cause();  // obtenemos causa por la que despierta

   switch(razon)
   {
      case ESP_SLEEP_WAKEUP_EXT0: 
         Serial.println("Causa señal ext0 usando RTC_IO");
         break;
      case ESP_SLEEP_WAKEUP_EXT1: 
         Serial.println("Causa señal ext1 usando RTC_CNTL"); 
         break;
      case ESP_SLEEP_WAKEUP_TIMER: 
         Serial.println("Causa temporizador."); 
         break;
      case ESP_SLEEP_WAKEUP_TOUCHPAD: 
         Serial.printf("Causa de activación el TOUCH-%d\n",esp_sleep_get_touchpad_wakeup_status()); 
         Serial.printf("T3: %d\n",touchRead(T3));
         Serial.printf("T7: %d\n",touchRead(T7));
         break;
      case ESP_SLEEP_WAKEUP_ULP: 
         Serial.println("Causa programa ULP"); 
         break;
      default: 
         Serial.printf("No estaba en sueño: %d\n",razon); 
         break;
   }
}
