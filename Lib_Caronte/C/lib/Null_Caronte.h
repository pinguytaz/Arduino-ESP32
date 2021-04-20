/************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *  
 *  Descripción: Fichero cabecera Ejemplo de canales, sobre el generamos
 *               diversos canales com Bluetooth, Serie, I2C, Ethernet
 *  
 *  Historico:
 *      Creación:  Marzo 2021 Creacion 
 ************************************************************************/

#ifndef _Null__Caronte_H
#define _Null__Caronte_H

#include "Caronte.h"

class Null_Caronte:public Caronte
{
     bool envia(char*, int);
     char lee();
  public:
     Null_Caronte(char id[3]); 

     bool Paquete(paquete&);
};

#endif
