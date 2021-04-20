/*
     Buscamos los dispositivos esclavos cercanos.
     La forma de invocarlo es sin parametro el Dispositivo por defecto y sino
     pondremos la MAC del dispo que se quiere usar para buscar.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main(int argc, char **argv)
{

   int id_dispo;  // Identificador de dispositivo
   int sock;
   inquiry_info *ii = NULL;  // Informacion de dispositivos.
   int max_rsp,num_rsp; 
   int len,flags;
   char direccion[19] = { 0 };
   char nombre[248] = { 0 };
   int i;


   printf("Buscamos los dispositivos mas cercanos (uso %s [MAC controlador hcix])\n",argv[0]);
   if(argc==2)  // Tenemos direccion del controlador que busca
   {
      // DC:1B:A1:05:2D:F4 (PC) 00:11:B1:07:A3:6C (USB)
      id_dispo = hci_devid(argv[1]);
   }
   else id_dispo = hci_get_route(NULL); // Obtiene el identificador del primer adaptador disponible.

   sock = hci_open_dev( id_dispo); // Abre conexion al adaptador.
   
   if (id_dispo < 0 || sock < 0) 
   {
      perror("Error en la apertura del socket");
      exit(1);
    }
    
    // Recogemos información de los dispositivos cercanos
    max_rsp = 255;  // Maximo de dispositivos localizados.
    len  = 8;  // Tiempo maximo de consulta 1,28*len
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;  // Para que limpie los detectados anteriormente
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
    num_rsp = hci_inquiry(id_dispo,len, max_rsp, NULL, &ii, flags);
    if( num_rsp < 0 ) perror("Error busqueda hci_inquiry");

    // Visualizamos dispositivos y su direccion localizados en rango.
    for (i = 0; i < num_rsp; i++) 
    {
        ba2str(&(ii+i)->bdaddr, direccion); // Transformamos la direccion de bdaddr a direccion XX:XX:... 
        memset(nombre, 0, sizeof(nombre)); // Pone a 0 el nombre, lo borra
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(nombre), nombre, 0) < 0) 
        {
           strcpy(nombre, "[Desconocido]");   // Si no se obtiene nombre ponemos desconocido.
        }
        printf("%s  %s (%2.2x:%2.2x:%2.2x)\n", direccion, nombre, (ii+i)->dev_class[0], (ii+i)->dev_class[1], (ii+i)->dev_class[2]);
    }

    free( ii );  // Liberamos la informacion de dispositivos
    close( sock );  // Cerramos el socket
    return 0;
}


