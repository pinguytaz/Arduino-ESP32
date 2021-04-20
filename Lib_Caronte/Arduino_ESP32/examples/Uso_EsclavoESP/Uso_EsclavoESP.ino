/***********************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *  
 *  Descripción: Ejemplo de uso Caronte con Bluetooth
 *               Bluetooth con la libreria Caronte.
 *               ESP32
 *               
 *  Historico:
 *      Creación:  Marzo 2021  FJRN
 *      
 *  Librerias utilizadas:
 *       SoftwareSerial.h  Para trabajar con puero serie en distintos pines 0,1
 *                         Necesaria para conectar el Bluetooth.
 *                       
 **********************************************/
#include <Arduino.h>
#include <BlueESP_Caronte.h>


BlueESP_Caronte BT("ESP"); 

void setup() 
{
  String msg_conexion="Se conecto: ";
  
  Serial.begin(115200);
  Serial.println("Prueba Esclavo Bluetooth desde ESP con Libreria Caronte"); 

  BT.begin("ESP32Test");  // Tenemos configurado nuestro modulo
  
  Serial.println("Creado el Objeto");

  msg_conexion = msg_conexion + BT.escucha();
  Serial.println("Listos conectado "+msg_conexion);
  BT.T_paquete("Tu esclavo ESP a sus servicios");
}

void loop()    
{
   paquete paq;
   String texto;
   int entero;
   float flotante;

   if(BT.Paquete(paq))
   {
     texto = BT.S_paquete(paq);
     Serial.println("Llega: de "+BT.lee_ID(paq)+" el Texto: "+texto);
     BT.T_paquete("Tu texto es: "+texto);

     while(!BT.Paquete(paq));  // Esperamos paquete entero
     Serial.println("Llego el entero");
     entero = BT.I_paquete(paq);
     Serial.println("Llega entero: de "+BT.lee_ID(paq)+" el numero: "+String(entero));
     BT.T_paquete(entero * 2);
   }
   delay(1000);
}
