/***********************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *  
 *  Descripción: Ejemplo de uso Caronte con Bluetooth
 *               Bluetooth con la libreria Caronte.
 *               HC05_Caronte  Modulo HC05
 *               
 *  Historico:
 *      Creación:  Marzo 2021  FJRN
 *      
 *  Librerias utilizadas:
 *       SoftwareSerial.h  Para trabajar con puero serie en distintos pines 0,1
 *                         Necesaria para conectar el Bluetooth.
 *                       
 **********************************************/

#include <HC05_Caronte.h>

// Conexiones a Bluetooth (Se debe pasar a libreria Caronte)
#define  PIN_BT_TX 10   
#define  PIN_BT_RX 11
#define  PIN_BT_KEY 9
HC05_Caronte BT("EH5"); 


void setup() 
{
  String msg_conexion="Se conecto: ";
  Serial.begin(9600);
  Serial.println("Prueba Maestro Bluetooth con Libreria Caronte desde Arduino"); 
  BT.begin(PIN_BT_TX, PIN_BT_RX, PIN_BT_KEY);  // Tenemos configurado nuestro modulo
  //BT.begin(PIN_BT_TX, PIN_BT_RX, PIN_BT_KEY,"PRHC05 RESET","1001"); //Nombre y PIN (Esclavo) 
  
  Serial.println("Creado el Objeto");

  Serial.println("Nombre del dispositivo: "+ String(BT.get_nombre()));
  Serial.println("PIN de emparejamiento: "+ String(BT.get_pin()));
  Serial.println("Dirección a la que conectarse: "+ String(BT.get_direccion()));


  msg_conexion = msg_conexion + BT.escucha();
  Serial.println("Listos conectado "+msg_conexion);
  BT.T_paquete("Tu esclavo a sus servicios");
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
