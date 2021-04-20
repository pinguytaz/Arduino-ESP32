/* *****************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *  
 *  Descripción: Fichero cabecera Lib_Caronte para dispositivo BlueTooth
 *               Compatibles probados ESP32
 *  
 *  Historico:
 *      Creación:  Marzo 2021 Creacion 
 ******************************************************************************/

#ifndef ESP_Caronte_H
#define ESP_Caronte_H

#include "BluetoothSerial.h"
#include "Caronte.h"

 
class BlueESP_Caronte:public Caronte
{
  public:
     BlueESP_Caronte(String nombre);

     void begin(String);  
     virtual int disponibles(void);
     String escucha(void) ; // Se activa esclavo y resetea Lanzara RESET hasta su OK
     void conecta(String) ; // Se activa el maestro Lanzara RESET hasta su OK
     
  private:
     BluetoothSerial *_com;

     virtual bool lee(char &) ;
     virtual bool envia(char*, int) ;
     
};

#endif
