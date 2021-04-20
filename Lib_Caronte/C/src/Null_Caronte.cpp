/***********************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *  
 *  Descripción:Libreria Lib_Caronte Nula para inicio de creacion de canales
 *        C<ID-3><Tam-1><Paquete0-255>
 *  
 *  Historico:
 *      Creación:  Marzo 2021 Creacion
 *
 *  Info:
 **********************************************************************/

#include <Null_Caronte.h>
#include <cstdio>

/*******************  Constructores  ************************/
Null_Caronte::Null_Caronte(char id[3]): Caronte(id)
{
    printf("Creamos el canal, abriendo conexiones");
}

/************** Funciones publicas  *****************************/
bool Null_Caronte::Paquete(paquete &paq)
{
   printf("Mira si existe paquete y retorna true o false");
   //available si primero # mira segundo 'C'" fallo en obtener retorno falso y se debera volver a 
   // pedir luego ya se coge la secuencia segun longitud.

   // Paquete de prueba que se supone recoge.
   paq.ID[0] = 'P';
   paq.ID[1] = 'R';
   paq.ID[2] = 'U';
   paq.Tam = 4;
   paq.Datos[0] = 'A';
   paq.Datos[1] = '1';
   paq.Datos[2] = lee();
   paq.Datos[3] = 'B';

   envia("1234",2);

   return true;
}

/************  Funciones privadas ************************************/
char Null_Caronte::lee()
{ 
   /* Lee un caracter y lo retorna (Byte) */
   return 'a';
}

bool Null_Caronte::envia(char *datos, int longitud)
{ 
   int i;
   for (i=0; i< longitud; i++)
   {
      // Enviamos un byte.
      printf("%2x,",datos[i]); 
   }
   printf("\n");

   return true;
}
