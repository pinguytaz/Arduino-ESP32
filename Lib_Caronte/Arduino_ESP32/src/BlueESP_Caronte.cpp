/* ******************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *  
 *  Descripción:Libreria Lib_Caronte para modulo BlueTooth ESP
 *  
 *  Historico:
 *      Creación:  Marzo 2021 Creacion
 *
 *  Info:
 *       https://www.pinguytaz.net/index.php/2016/11/10/uso-modulo-bluetooth-hc-05-en-arduino
 ********************************************************/
//#include "Arduino.h"

#include "BlueESP_Caronte.h"
#include <BluetoothSerial.h>

/*******************  Constructores  ************************/
BlueESP_Caronte::BlueESP_Caronte(String nombre): Caronte(nombre) {;}

void BlueESP_Caronte::begin(String nombre)
{   
   String resultado="";

  _com = new BluetoothSerial();
  
  _com->begin(nombre);
}

/************** Funciones publicas  *****************************/
int BlueESP_Caronte::disponibles(void)
{
   return _com->available();
}

String BlueESP_Caronte::escucha(void) 
{
  String msg_conexion="";
  paquete paq;
  
  // Ahora esperamos que nos mande un mensaje el Maestro, que sera el retornado.
  while (!Paquete(paq))
  {
    delay(500);
  }
  msg_conexion = msg_conexion + S_paquete(paq);
  
  return msg_conexion;
} 

void BlueESP_Caronte::conecta(String direccion) 
{
;
} 


/******************  Funciones privadas ********************************************/
bool BlueESP_Caronte::lee(char &bytes)
{ 
   int bytes_leidos=0;
   char buf;

   bytes_leidos = _com->available();
   if (bytes_leidos ==0) return false;  //No tenemos datos.
   
   buf = _com->read(); // Leemos un caracter 
   bytes = buf;
   
   return true; //El caracter que se lee esta en byte y se retorna por referencia
}

bool BlueESP_Caronte::envia(char *datos, int longitud)
{ 
   int i;
   char buf;
   for (i=0; i< longitud; i++)
   {
      // Enviamos de byte en byte
      buf = datos[i];
      _com->write(buf);
   }

   return true;
}
