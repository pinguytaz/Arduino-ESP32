/************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *  
 *  Descripción: Fichero cabecera Blue_Caronte para dispositivo BlueTooth
 *  
 *  Historico:
 *      Creación:  Marzo 2021 Creacion 
 ************************************************************************/

#ifndef _Blue__Caronte_H
#define _Blue__Caronte_H

#include "Caronte.h"
#include <bluetooth/bluetooth.h>

class Blue_Caronte : public Caronte
{
     int id_dispo=-1;
     //int cliente=-1;  // Cliente que se conecta cuando es un esclavo(servidor) 
     int canal=-1;
     int s=-1;   // Socket
     bdaddr_t bdaddr_any =  {{0, 0, 0, 0, 0, 0}};

     char nombre[8] = {0};  // Nombre del dispositivo 
     char mac[19] = { 0}; 
     char mac_cliente[19] = {0}; 

     void info_dispositivo(int dispositivo);
     bool lee(char&);
     bool envia(char*, int);
  public:
     Blue_Caronte(char id[3]);// Usa dispositivo por defecto
     ~Blue_Caronte();//  Cierra conexiones

     bool inicio(void);
     bool inicio(char *);
     int escucha(uint8_t);
     int conecta(char*,uint8_t);

     char *get_nombreDispo();
     char *get_mac();
     char *get_mac_cliente();
};

#endif
