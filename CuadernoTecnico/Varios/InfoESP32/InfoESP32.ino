/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Información del ESP32
 *               Modelo, Cores, ID
 *               WIFI MAC
 **************************************************************************************************/
#include <WiFi.h>
#include <BLEDevice.h>
#include <esp32-hal.h>


uint32_t chipId = 0;

void setup() 
{
	Serial.begin(115200);


  Serial.println("\nInformación MODULO");
  Serial.printf("Modelo ESP32: %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
  Serial.printf("Cores del chip %d \n", ESP.getChipCores());
  for(int i=0; i<17; i=i+8) 
  {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  Serial.print("ID Chip: "); Serial.println(chipId);
  Serial.printf("Frecuencia %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("Version SDK %s \n", ESP.getSdkVersion());
  Serial.printf("Memoria interna %d Libre %d\n", ESP.getHeapSize(),ESP.getFreeHeap());
  Serial.printf("Flash %d \n", ESP.getFlashChipSize());
  Serial.printf("Tamaño Sketch %d \n", ESP.getSketchSize());
  Serial.printf("Temperatura interna: %f ºC \n", temperatureRead());

  
  Serial.println("\nInformación WIFI");
  Serial.print("Dirección MAC :  ");
  Serial.println(WiFi.macAddress());

  Serial.println("\nInformación BlueTooth");
  BLEDevice::init("");
  BLEAddress direccion = BLEDevice::getAddress();
  Serial.printf("Direccion: %s\n",direccion.toString().c_str());
  
  
  
  
}

void loop() 
{
	delay(3000);
}
