/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Scan de dispositivos BLE
 **************************************************************************************************/
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5; //In seconds
BLEScan *pBLEScan;


/*class CallbacksScan: public BLEAdvertisedDeviceCallbacks 
{
    void onResult(BLEAdvertisedDevice advertisedDevice) 
    {
      Serial.printf("Dispositivo localizado: %s \n", advertisedDevice.toString().c_str());
    }
};*/


void setup() {
  Serial.begin(115200);
  Serial.println("Escaneando dispositivos BLE...");

  BLEDevice::init(""); // Inicializa dispositivo
  pBLEScan = BLEDevice::getScan(); 
  // pBLEScan->setAdvertisedDeviceCallbacks(new CallbacksScan());
  pBLEScan->setActiveScan(true); 
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  
}

void loop() {
  /*  Version 2
  BLEScanResults dispositivosEncontrados = pBLEScan->start(scanTime, false);
  */
  BLEScanResults *dispositivosEncontrados = pBLEScan->start(scanTime, false);
  Serial.print("Dispositivos encontrados: ");
  Serial.println(dispositivosEncontrados->getCount());
  for(int i=0; i<dispositivosEncontrados->getCount(); i++)
  {
     BLEAdvertisedDevice dispositivo = dispositivosEncontrados->getDevice(i);  
     Serial.printf("%d Nombre: %s \n", i+1, dispositivo.getName().c_str());
     Serial.printf("\tDirección: %s \n", dispositivo.getAddress().toString().c_str());
     if(dispositivo.haveTXPower())
        Serial.printf("\tRSSI: %d Potencia %d\n", dispositivo.getRSSI(), dispositivo.getTXPower());
     else
        Serial.printf("\tRSSI: %d Sin indicador de potencia\n", dispositivo.getRSSI());

    // Visualiza servicios
    Serial.printf("\tServicios de datos: %d\n", dispositivo.getServiceDataCount());
    if (dispositivo.getServiceDataCount() > 0)
    {
       for(int s=0 ; s<dispositivo.getServiceDataCount(); s++)
       {
          Serial.printf("\tServicio: %s\n", dispositivo.getServiceData(s).c_str());  
          for(int u=0 ; u<dispositivo.getServiceDataUUIDCount(); u++)
          {
             BLEUUID bleuuid = dispositivo.getServiceDataUUID(u);
             Serial.printf("\t\tUUID datos: %s\n", bleuuid.toString().c_str());  
          }
       }
       
    }
    if(dispositivo.getServiceUUIDCount() > 0)
    {
       for(int u=0 ; u<dispositivo.getServiceUUIDCount(); u++)
       {
           BLEUUID bleuuid = dispositivo.getServiceUUID(u);
           Serial.printf("\tUUID: %s\n", bleuuid.toString().c_str());  
       }
    }
  }
  
  
  Serial.println("Scan realizado!");
  pBLEScan->clearResults();   // Borramos resultados
  delay(20000);
}
