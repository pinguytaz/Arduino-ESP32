// Obtener Informacion del sistema

#include <Arduino.h>

uint32_t chipId = 0;

void setup() 
{
   Serial.begin(115200);
   
  // CHIP ID
   Serial.println("----- Informacion CHIP -----");
   for(int i=0; i<17; i=i+8) 
   {
	    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	 }
   Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
   Serial.printf("Este chip tiene %d cores\n", ESP.getChipCores());
   Serial.print("Chip ID: "); Serial.println(chipId);

// PSRAM   
  if(psramFound())   // Verifica si PSRAM esta presente
  {
     Serial.println("----- Dispone de PSRAM -----");
     Serial.printf("Total heap: %d\n", ESP.getHeapSize());
     Serial.printf("Free heap: %d\n", ESP.getFreeHeap());
     Serial.printf("Total PSRAM: %d\n", ESP.getPsramSize());
     Serial.printf("Free PSRAM: %d\n", ESP.getFreePsram());
  }
}

void loop() {}