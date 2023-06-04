/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción:  Ejemplo de Servidor BLE
 *                Generamos los UUID de servicios y caracteristica en https://www.uuidgenerator.net/
 *                Dos servicios: Servicio1 y Servicio2
 *                El uno tiene dos caracteristicas, una de notificacion cuando se cambia y la otra vacia
 **************************************************************************************************/
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>


// UUIDs Generados version 4.
#define UUID_SERVICIO1  "4fb52fa9-42ed-4079-84c1-300a165a5849"
// Caracteristica Potenciomentro que nos da el valor del potenciomentro es notificacion (entero)
#define UUID_CHARPOT    "21bf7336-69b5-4798-8bcc-e18f33d57b21"
BLECharacteristic pCaracteristica1(UUID_CHARPOT,
                                   BLECharacteristic::PROPERTY_READ |
                                   BLECharacteristic::PROPERTY_NOTIFY
                                  );


// Caracteristica Led enciendo o apaga el led Lectura/escritura (Encendido / Apagado)
#define UUID_CHARLED    "23af9e65-b65d-4413-bc81-6d5b86d58dc0"

#define UUID_SERVICIO2  "41bb796d-eaa5-4b00-a827-b87bc28824ee"

// Pines
const int boton = 13;
const int potenciometro = 34;


void setup() 
{
   Serial.begin(115200);
   Serial.println("Inicia BLE");

   // Pines
   pinMode(boton,INPUT);
  
   // Bluetooth para servidor.
   BLEDevice::init("Pinguytaz");
   BLEServer *pServidor = BLEDevice::createServer();  // Creamos el Servidor.
   // Creamos los servicios con sus caracteristicas y descriptores si corresponde.
   BLEService *pServicio1 = pServidor->createService(UUID_SERVICIO1);  
  
   pServicio1->addCharacteristic(&pCaracteristica1);
  
   BLECharacteristic *pCaracteristica2 = pServicio1->createCharacteristic(
                                         UUID_CHARLED,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
   pCaracteristica2->setValue("Apagado");

   pServicio1->start();

   BLEService *pServicio2 = pServidor->createService(UUID_SERVICIO2); 
   pServicio2->start();

   // Nos hacemos visible para que pueda conectarse el cliente.
   BLEAdvertising *pPublicidad = BLEDevice::getAdvertising();
   pPublicidad->addServiceUUID(UUID_SERVICIO1);
   pPublicidad->addServiceUUID(UUID_SERVICIO2);
   pPublicidad->setScanResponse(true);                            
   pPublicidad->setMinPreferred(0x06);  
   pPublicidad->setMinPreferred(0x12);  

  BLEDevice::startAdvertising();
  
  Serial.println("Preparado para leerse");
  int lectura = analogRead(potenciometro);
  //int lectura = analogReadMilliVolts(potenciometro); 
  Serial.println(lectura);
  pCaracteristica1.setValue((uint8_t*)&lectura,4);
  pCaracteristica1.notify(true);   
}

void loop() 
{
   int lectura;
   /*// Simulador de Potenciometro
   int valor=random(0,255);
   pCaracteristica1.setValue((uint8_t*)&valor,4);
   pCaracteristica1.notify(true);
   Serial.println(valor);
   */

   if(digitalRead(boton))   // Cuando se pulsa se lee valor del potenciometro y notifica.
   {
      lectura = analogRead(potenciometro);
      //lectura = analogReadMilliVolts(potenciometro); 
  
      Serial.println(lectura);
      pCaracteristica1.setValue((uint8_t*)&lectura,4);
      pCaracteristica1.notify(true);   
   }
   delay(500);
}
