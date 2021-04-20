/*************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *  
 *  Descripción: Fichero cabecera Lib_Caronte
 *  
 *  Historico:
 *      Creación:  Marzo 2021 Creacion 
 ************************************************************************/
#ifndef _Caronte_H
#define _Caronte_H

#include <Arduino.h>

//  Definiciones de constantes
#define MAXPAQ  255    // Tamaño maximo paquete
#define CABECERA  6    // Tamaño Cabecera "#C<ID[3]><Long[1]>"

typedef struct 
{
  char ID[3];     // ID del emisor.
  int Tam;       // Tamaño del paquete.
  char Datos[MAXPAQ];  // Datos del paquete.
} paquete; 
  
class Caronte
{

  private:
     char _ID[3];

     void Cabecera(char *datos,int); //Pone al principio la Cabecera.

     virtual bool lee(char &) =0 ;
     virtual bool envia(char*, int) =0 ;

  public:
    Caronte(String id);

    String get_ID(void);

    // Funciones de envio.
    bool T_paquete(String cadena);  // Envia una cadenas
    bool T_paquete(char );  // Envia  un byte
    bool T_paquete(char *,int);  // Envia cadena de bytes
    bool T_paquete(int);  // Envia un entero (2 Bytes)
    bool T_paquete(float);  // Envia un flotante
 
    virtual int disponibles(void) =0 ;
    bool Paquete(paquete&) ; // Mira si tiene paquete y depende de cada canal.

    // Recogida información paquete
    String lee_ID(paquete);
    String S_paquete(paquete);
    int I_paquete(paquete);
    float F_paquete(paquete);
};
#endif
