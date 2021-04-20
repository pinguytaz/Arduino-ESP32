/* *****************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *  
 *  Descripción: Fichero cabecera Lib_Caronte para dispositivo BlueTooth
 *               Compatibles probados HC-05
 *  
 *  Historico:
 *      Creación:  Marzo 2021 Creacion 
 ******************************************************************************/

#ifndef HC05_Caronte_H
#define HC05_Caronte_H

#include <SoftwareSerial.h>
#include <Arduino.h>
#include "Caronte.h"

typedef enum
{
   V_9600 = 9600,
   V_19200  = 19200,
   V_38400  = 38400,
   V_57600  = 57600,
   V_115200 = 115200,
   V_230400 = 230400,
   V_460800 = 460800
} Velocidad;

typedef enum
{
   bit1 = 0,
   bit2  = 1
} BitStop;

typedef enum
{
   Ninguna  =0,
   Par = 1,
   Impar  = 2
} Paridad;

typedef enum
{
   Esclavo  = 0,
   Maestro = 1,
   B_Esclavo  = 2
} Rol;

typedef enum
{
   Fija  = 0,
   Cualquiera = 1,
   ML_Esclavo  = 2
} Modo;
 
class HC05_Caronte:public Caronte
{
  public:
     HC05_Caronte(String nombre);

     void begin(uint8_t, uint8_t, uint8_t);  // Marcamos pines donde se conecta HC-05 RX,TX, Key 
     void begin(uint8_t, uint8_t, uint8_t, String, String);  //Modo esclavo cambiando nombre y clave.
     virtual int disponibles(void) ;
     //       Comandos AT
     bool set_nombre(String nombre);    // Nombre de conexion NAME
     String get_nombre();
     bool set_pin(String);    // PIN de vinculacion
     String get_pin();
     String get_direccion();            // Direccion ADDR NAP:UAP:LAP
     bool set_uart(Velocidad,BitStop,Paridad);    // UART Configuracion velocidad comunicación
     String get_uart();         
     bool set_rol(Rol);    // Modo de trabajo del dispositivo 0-Esclavo 1-Maestro 2-EsclavoLoop  ROLE
     String get_rol();
     bool set_modo(Modo);    // Modo de conexión  CMODE 0-Dir_Especifica, 1-cualquiera
     String get_modo();
     bool set_dirCon(String);    // Direccion BIND para modo maestro y direccion fija
     String get_dirCon();
      
     bool reset(void);    // RESET
     
     String escucha(void) ; // Se activa esclavo y resetea Lanzara RESET hasta su OK
     void conecta(String) ; // Se activa el maestro Lanzara RESET hasta su OK
     
  private:
     uint8_t _Pin_BT_RX;
     uint8_t _Pin_BT_TX;
     uint8_t _Pin_BT_KEY;
     long _baudios = V_38400;  // Velocidad que por defecto esta configurada.
     
     SoftwareSerial *_com;
  
     virtual bool lee(char &) ;
     virtual bool envia(char*, int) ;
     bool AT_isOK(String);
     String AT(String);
     
};

#endif
