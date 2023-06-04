/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción:  Ejemplo de cliente BLE
 *                Buscara los dispositivos pinguytaz, con servicio 4fb52fa9-42ed-4079-84c1-300a165a5849 para
 *                ir actualizando los valores de estos segun se notifiquen.
 **************************************************************************************************/
#include "BLEDevice.h"
#include "BLEScan.h"


//  Servicio y caracteristica a la que deseamos conectarnos.
static BLEUUID servicioUUID("4fb52fa9-42ed-4079-84c1-300a165a5849");
static BLEUUID caracteristicaUUID("21bf7336-69b5-4798-8bcc-e18f33d57b21");

#define nombreServidorBLE "Pinguytaz"
#define IPDispositivo1 "3c:61:05:11:e9:b2"
static BLEAdvertisedDevice* miDispositivo1;
static BLERemoteCharacteristic* caracteristicaRemotaServ1;
static boolean conectar1 = false;
static boolean conectado1 = false;


#define IPDispositivo2 "7c:9e:bd:36:d8:ba"
static BLEAdvertisedDevice* miDispositivo2;
static BLERemoteCharacteristic* caracteristicaRemotaServ2;
static boolean conectar2 = false;
static boolean conectado2 = false;   

/**
 * CallBack de busqueda Busca servidores BLE e informa
 **/
class AvisoDispositivo: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice dispositivo) 
  {
     //Serial.println(dispositivo.toString().c_str());
     Serial.printf("Encontrado Nombre: %s IP:%s\n", dispositivo.getName().c_str(), dispositivo.getAddress().toString().c_str());

    // Miramos si tiene el servicio que buscamos.
    if (dispositivo.haveServiceUUID() && dispositivo.isAdvertisingService(servicioUUID)) 
    {
       Serial.println("************* Servicio encontrado *************");
       if (dispositivo.getAddress().toString() == IPDispositivo1 && !conectado1)
       {
          Serial.print("Conecta a 1: ");
          Serial.println(IPDispositivo1);
          BLEDevice::getScan()->stop();
          miDispositivo1 = new BLEAdvertisedDevice(dispositivo);
          conectar1 = true;
       }
       else  if (dispositivo.getAddress().toString() == IPDispositivo2 && !conectado2)
       {
          Serial.print("Conecta a 2: ");
          Serial.println(IPDispositivo2);
          BLEDevice::getScan()->stop();
          miDispositivo2 = new BLEAdvertisedDevice(dispositivo);
          conectar2 = true;
       }
    } 
    //else Serial.println("No tiene el servicio");
  } 
}; 

void setup() 
{
   Serial.begin(115200);
   Serial.println("Inicia aplicacion cliente ESP32...");
   BLEDevice::init("");

  // Escaneamos cada 5 segundos  y llama a la funcion callback cuando detecta un nuevo dispositivo,
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new AvisoDispositivo());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
} 

void loop() 
{
   //Serial.println("Entramos en el bucle");
   
   if (conectar1 == true) // Conexion si es necesaria al dispositivo 1
   {
      if (conectaAServidor(*miDispositivo1)) 
      {
         Serial.print("Conexion correcta del dispositivo 1 ");
         Serial.println(caracteristicaRemotaServ1->toString().c_str());
         Serial.printf("El valor obtenido es %d\n",caracteristicaRemotaServ1->readUInt32());
       } 
       else 
       {
          Serial.println("Fallo en la conexion al dispositivo 1");
       }
       conectar1 = false;
    }

    if (conectar2 == true) // Conexion si es necesaria al dos
    {
      if (conectaAServidor(*miDispositivo2)) 
      {
         Serial.print("Conexion correcta del dispositivo 2 ");
         Serial.println(caracteristicaRemotaServ2->toString().c_str());
         Serial.printf("El valor obtenido es %d\n",caracteristicaRemotaServ2->readUInt32());
       } 
       else 
       {
          Serial.println("Fallo en la conexion al dispositivo 2");
       }
       conectar2 = false;
    }

    if(!conectado1 || !conectado2)
    {
       Serial.println("Rescaneamos");
       BLEDevice::getScan()->start(0);
    }
   delay(3000); 
} 



class MiCallBackCliente : public BLEClientCallbacks 
{
   void onConnect(BLEClient* pclient) 
   {
      Serial.println("************** onConnect *****************");
     // Serial.println(pclient->toString().c_str() );
      Serial.printf("Se conecta: %s",pclient->getPeerAddress().toString().c_str());
   }

   void onDisconnect(BLEClient* pclient) 
   {
      Serial.println("************** onDisonnect *****************");
      Serial.printf("Se desconecta conecta: %s\n",pclient->getPeerAddress().toString().c_str() );
      if(pclient->getPeerAddress().toString() == IPDispositivo1)
      {
         conectado1 = false;
      }
      else if(pclient->getPeerAddress().toString() == IPDispositivo2)
      {
         conectado2 = false;
      }
   }
};


/******   Conectamos al servidor que nos indican  *****/
bool conectaAServidor(BLEAdvertisedDevice elDispositivo)
{
   Serial.printf("Nos conectamos al %s\n", elDispositivo.getAddress().toString().c_str());

   BLEClient*  pClient  = BLEDevice::createClient();   // Creamos cliente
   Serial.println(" - Creamos el cliente");

   pClient->setClientCallbacks(new MiCallBackCliente());
   pClient->connect(&elDispositivo);  
   Serial.println(" - Conectado al servidor");
   pClient->setMTU(517); 
  
   // Obtenemos referencias del servicio del servidor remoto.
   BLERemoteService* pRemoteService = pClient->getService(servicioUUID);
   if (pRemoteService == nullptr) 
   {
      Serial.print("Fallo al encontrar el servicio UUID: ");
      Serial.println(servicioUUID.toString().c_str());
      pClient->disconnect();
      return false;
    }
    Serial.println("Servicio localizado perfectamente.");


    // Obtenemos referencia a las caracteristicas
    if (elDispositivo.getAddress().toString() == IPDispositivo1)  // Caracteristica del 1
    {
       caracteristicaRemotaServ1= pRemoteService->getCharacteristic(caracteristicaUUID);
       if (caracteristicaRemotaServ1 == nullptr) 
       {
          Serial.print("Fallo localizando la caracteristica del 1");
          Serial.println(caracteristicaUUID.toString().c_str());
          pClient->disconnect();
          return false;
       }
       Serial.println("Encontrada caracteristicas del 1");
       if(caracteristicaRemotaServ1->canNotify()) caracteristicaRemotaServ1->registerForNotify(notificaDispositivo);
       conectado1 = true;
    }
    else if (elDispositivo.getAddress().toString() == IPDispositivo2)  // Caracteristica del 2
    {
       Serial.println("Caracteristica del 2");
       caracteristicaRemotaServ2= pRemoteService->getCharacteristic(caracteristicaUUID);
       if (caracteristicaRemotaServ2 == nullptr) 
       {
          Serial.print("Fallo localizando la caracteristica del 2");
          Serial.println(caracteristicaUUID.toString().c_str());
          pClient->disconnect();
          return false;
       }
       Serial.println("Encontrada caracteristicas del 2");
       if(caracteristicaRemotaServ2->canNotify()) caracteristicaRemotaServ2->registerForNotify(notificaDispositivo);
       conectado2 = true;
    }
    return true;
}

static void notificaDispositivo(BLERemoteCharacteristic* pBLERemoteCharacteristic,uint8_t* pData,size_t length,bool isNotify) 
{
      Serial.println("Notificacion del dispositivo ");
      BLERemoteService* servicio = pBLERemoteCharacteristic->getRemoteService();
      BLEClient* cliente = servicio->getClient();
      //Serial.println(cliente->toString().c_str());

      int valor = pData[1]*256 + pData[0];
      if (cliente-> getPeerAddress().toString() == IPDispositivo1)
      {
         Serial.println("DISPOSITIVO 1 ");
      }
      else if (cliente-> getPeerAddress().toString() == IPDispositivo2)
      {
         Serial.println("DISPOSITIVO 2");
      }
      Serial.printf("VALOR: %d\n",valor); 
}
