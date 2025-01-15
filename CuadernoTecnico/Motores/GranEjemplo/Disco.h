/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción:  Clase gestion disco WEB
 *
 ***********************************************************************************************/
#ifndef Disco_H
#define Disco_H

#include "FS.h"
#include "SPIFFS.h"

class Disco
{
  private:
     fs::SPIFFSFS pdatos;
     
  public:
     Disco(char *);
     float cargaPagina(String , char*);
     void ficheros();
};

#endif