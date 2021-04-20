/* *************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *  
 *  Descripción:Libreria Lib_Caronte
 *        #C<ID-3><Tam-1><Paquete0-255>
 *  
 *  Historico:
 *      Creación:  Marzo 2021 Creacion 
 ******************************************************/

#include <Caronte.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>

//********** Metodos publicos 
Caronte::Caronte(char id[3])
{
   _ID[0] = id[0];
   _ID[1] = id[1];
   _ID[2] = id[2];
}

char* Caronte::get_ID(void)
{
   char *tempo= (char*) malloc(sizeof(char)*4);

   tempo[0] = _ID[0];
   tempo[1] = _ID[1];
   tempo[2] = _ID[2];
   tempo[3] = 0;

   return tempo;
}

bool Caronte::T_paquete(char *cadena)
{
   int longitud = strlen(cadena);   // Longitud cadena a enviar
   char *datos = (char *)malloc(CABECERA+longitud);

   if (longitud > MAXPAQ)
   {
      perror("Error longitud datos cadena");
      return false;
   }

   Cabecera(datos,longitud);

   for(int i=0 ; i<longitud; i++)
   {
       datos[CABECERA+i]=cadena[i];
   }

   return envia(datos,CABECERA+longitud);
}


bool Caronte::T_paquete(char dato)
{
   char datos[CABECERA+1];  // La cabecera y long + caracter
  
   Cabecera(datos,1);
   datos[CABECERA]= dato;
   
   return envia(datos,CABECERA+1);
}

bool Caronte::T_paquete(char *bytes, int longitud)
{
   char *datos = (char *) malloc(CABECERA+longitud);

   if (longitud > MAXPAQ)
   {
      perror("Error longitud datos Bytes");
      return false;
   }

   Cabecera(datos,longitud);
   for(int i=0 ; i<longitud; i++)
   {
       datos[CABECERA+i]=bytes[i];
   }

   return envia(datos,CABECERA+longitud);
}

bool Caronte::T_paquete(short int dato)   // Es short int pues arduino tiene 2 bytes.
{
   char datos[CABECERA+2];
   unsigned char *se1,*se2;

   se1= (unsigned char *) &dato;
   se2= (unsigned char *) &dato+1;
   
   //printf("Envia %d: 0x%X(%u)0x%X(%u)\n",dato,*se1,*se2);
   Cabecera(datos,2);
   datos[CABECERA]= *se1;
   datos[CABECERA+1]= *se2;
   
   return envia(datos,CABECERA+2);
}

bool Caronte::T_paquete(float dato)
{
   char datos[CABECERA+4];
   unsigned char *f1,*f2,*f3,*f4;
   f1= (unsigned char *) &dato;
   f2= (unsigned char *) &dato+1;
   f3= (unsigned char *) &dato+2;
   f4= (unsigned char *) &dato+3;
      
   Cabecera(datos,4);
   datos[CABECERA]=   *f1;
   datos[CABECERA+1]= *f2;  
   datos[CABECERA+2]= *f3;
   datos[CABECERA+3]= *f4;
   
   return envia(datos,CABECERA+4);
}

bool Caronte::Paquete(paquete &paq)
{
   char byte;

   if(!lee(byte)) return false; // Error en C1
   if( byte != '#') return false;

   if(!lee(byte)) return false; // NError en C2
   if( byte != 'C') return false;

   if(!lee(byte)) return false; // Error en ID1
   paq.ID[0] = byte;
   if(!lee(byte)) return false; // Error en ID2
   paq.ID[1] = byte;
   if(!lee(byte)) return false; // Error en ID3
   paq.ID[2] = byte;

   if(!lee(byte)) return false; // Error en Tamaño 
   paq.Tam = (int) byte;

   // Lee datos 
   for(int i=0; i<paq.Tam; i++)
   {
      if(!lee(byte)) return false; // No disponemos de datos.
      paq.Datos[i] = byte;
   }

   return true;
}
char* Caronte::lee_ID(paquete paq)
{
   char *tempo= (char*) malloc(sizeof(char)*4);

   tempo[0] = paq.ID[0];
   tempo[1] = paq.ID[1];
   tempo[2] = paq.ID[2];
   tempo[3] = 0;

   return tempo;
}

char* Caronte::S_paquete(paquete paq)
{
   char *tempo= (char*) malloc(paq.Tam+1);

   for(int i=0; i<paq.Tam; i++)
   {
      tempo[i] = paq.Datos[i];
   }
   tempo[paq.Tam] =0;

   return tempo;
}

int Caronte::I_paquete(paquete paq)
{
   short int tempo=0;

   memcpy(&tempo, paq.Datos,2);

   return tempo;
}

float Caronte::F_paquete(paquete paq)
{
   float tempo=0;
   memcpy(&tempo, paq.Datos,4);

   return tempo;
}

//******************* Funciones privadas  
void Caronte::Cabecera(char *datos, int longitud)
{
   char *entero = (char *)malloc(sizeof(int)); // para obtener entero en bytes

   datos[0]='#';
   datos[1]='C';
   datos[2]=_ID[0];
   datos[3]=_ID[1];
   datos[4]=_ID[2];

   entero = (char *) &longitud; // Paso a bytes
   datos[5]= entero[0];
}


