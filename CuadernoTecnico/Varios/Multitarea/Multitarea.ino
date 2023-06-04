/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción:  Ejemplo de multitarea
 *                Una tarea por defecto en el loop (Nucleo1)
 *                Tarea1 Creada por nosotros es nocleo0 
 **************************************************************************************************/
TaskHandle_t Tarea1;
TaskHandle_t Tarea2;

void setup() 
{
   Serial.begin(115200);
   Serial.print("El SETUP se esta ejecutando en el CORE- ");
   Serial.println(xPortGetCoreID());  
   creaTareas();  
}

void loop() 
{
   Serial.print("El Loop se esta ejecutando en el CORE ");  
   Serial.println(xPortGetCoreID());    
   vTaskDelay(pdMS_TO_TICKS(1000)); //Bloquea la tarea 1 segundo
   
}

void fnTarea1(void *pvParameters) 
{
   // Esta parte seria como el setup() definiriamos los Pines por ejemplo
   Serial.print("Se inicia la Tarea1 en el CORE-->");
   Serial.print(xPortGetCoreID());  
   int contador=0; 

   String p =  (char *) pvParameters;
   Serial.println("Llego"+p);
          
   // Ahora el loop
   for (;;) 
   {   
      long tiempo = millis()/1000;
      Serial.print("LOOP Tarea1 se esta ejecutando en el CORE ");  
      Serial.println(xPortGetCoreID());  
      Serial.printf("CONTADOR: %d\n",  contador++);
      vTaskDelay(pdMS_TO_TICKS(5000));
   
      if(contador == 5)  // Cuando se ejecuta 5 veces mata la tarea2
      {
         Serial.println("Matamos la tarea ");
         vTaskDelete(Tarea2); 
      }
   }
   // Nunca debe llegar a este punto y si llega la tarea debe ser eliminada.
   vTaskDelete(NULL);
}

void fnTarea2(void *pvParameters) 
{
   // Esta parte seria como el setup() definiriamos los Pines por ejemplo
   Serial.print("Se inicia la Tarea2 en el CORE-->");
   Serial.println(xPortGetCoreID());  
        
   // Ahora el loop
   for (;;) 
   {   
      Serial.print("LOOP Tarea2 se esta ejecutando en el CORE ");  
      Serial.println(xPortGetCoreID());  
      vTaskDelay(pdMS_TO_TICKS(500));
   
   }
   // Nunca debe llegar a este punto y si llega la tarea debe ser eliminada.
   vTaskDelete(NULL);
}

/************  Funcion que crea las Tareas por limpiar algo de codigo en setup() ****/
void creaTareas()
{
   xTaskCreatePinnedToCore(fnTarea1, // Funcion con el codigo de la Tarea
                           "MiTarea1", // Nombre de la Tarea
                           2048, // Tamaño de la pila
                           (void *) "Prueba Paramentro", // Parametros a pasar.
                           1, // Prioridad de 0-9, 1 es como la del Loop
                           &Tarea1, // Controlador de tarea, por ejemplo matarla desde otra tarea.
                           1    // Core en el que asignamos la Tarea.
                          );
   xTaskCreatePinnedToCore(fnTarea2, 
                           "MiTarea2", 
                           2048, 
                           NULL,
                           1, 
                           &Tarea2,
                           0
                          );
}    
