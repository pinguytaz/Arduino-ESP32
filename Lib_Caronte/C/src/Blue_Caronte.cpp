/***********************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *  
 *  Descripción:Libreria Lib_Caronte para Bluetooth
 *        C<ID-3><Tam-1><Paquete0-255>
 *  
 *  Historico:
 *      Creación:  Marzo 2021 Creacion
 *
 *  Info:
 **********************************************************************/

#include <Blue_Caronte.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>

Blue_Caronte::Blue_Caronte(char id[3]) : Caronte(id)
{
    ;
}
Blue_Caronte::~Blue_Caronte()
{
   if(canal != -1) close(canal);
   if(s != -1) close(s);
}
bool Blue_Caronte::inicio()
{
    id_dispo=hci_get_route(NULL);
    if(id_dispo <0) 
    {
       perror("Error en la apertura de dispositivo por defecto");
       return false;
    }

    info_dispositivo(id_dispo);

    return true;
}

bool Blue_Caronte::inicio(char *MAC)
{
   id_dispo = hci_devid(MAC);
   if(id_dispo <0) 
   {
       perror("Error en la apertura de dispositivo especificado");
       return false;
   }

   info_dispositivo(id_dispo);

   return true;
}

int Blue_Caronte::escucha(uint8_t puerto)
{
    struct sockaddr_rc direccion_local = { 0 }, direccion_remota = { 0 };
    socklen_t opt = sizeof(direccion_remota);
    int cliente;
    
    // Obtiene un Socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    //  Enlace socke con el puerto disponible.
    direccion_local.rc_family = AF_BLUETOOTH;
    direccion_local.rc_bdaddr =  bdaddr_any;
    direccion_local.rc_channel = (uint8_t) puerto;  
    bind(s, (struct sockaddr *)&direccion_local, sizeof(direccion_local));

    listen(s,1); //  Modo Escucha una conexión.

    cliente = accept(s, (struct sockaddr *)&direccion_remota, &opt);  // Acepta conexion
    canal = cliente;
    // Obtenemos el identificador MAC del cliente.
    ba2str( &direccion_remota.rc_bdaddr, mac_cliente ); // Toma Mac del cliente.

    return 0;
}

int Blue_Caronte::conecta(char *destino, uint8_t puerto)
{
    struct sockaddr_rc direccion = { 0 };
    int status;

    // Generamos el socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // Preparamos los parametros de conexión al Esclavo
    direccion.rc_family = AF_BLUETOOTH;
    direccion.rc_channel = puerto;
    str2ba( destino, &direccion.rc_bdaddr );

    //  Nos conectamos al servidor
    status = connect(s, (struct sockaddr *)&direccion, sizeof(direccion));

    canal = s;

    //  Envia mensaje
    //if( status == 0 ) {
        //status = write(s, "hello!", 6);
    //}

    if( status < 0 ) perror(" Tenemos un error en la conexion");

    return status;

}

char* Blue_Caronte::get_nombreDispo()
{
   char *tempo= (char*) malloc(sizeof(char)*18);

   strcpy(tempo,nombre);
   return tempo;
}


char* Blue_Caronte::get_mac()
{
   char *tempo= (char*) malloc(sizeof(char)*18);

   strcpy(tempo,mac);
   return tempo;
}

char* Blue_Caronte::get_mac_cliente()
{
   char *tempo= (char*) malloc(sizeof(char)*18);

   strcpy(tempo,mac_cliente);
   return tempo;
}
/************  Funciones privadas ************************************/
bool Blue_Caronte::lee(char &byte)
{ 
   int bytes_leidos=0;
   char buf[1];

   memset(buf, 0, sizeof(buf));
   bytes_leidos = read(canal,buf,1); // Leemos un caracter 
   if(bytes_leidos!=1) return false;

   byte = buf[0];
   return true; //El caracter que se lee esta en byte y se retorna por referencia
}
bool Blue_Caronte::envia(char *datos, int longitud)
{ 
   int i;
   char buf[1];

   for (i=0; i< longitud; i++)
   {
      // Enviamos de byte en byte
      memset(buf, 0, sizeof(buf));
      buf[0] = datos[i];
      write(canal,buf,1);
   }

   return true;
}

void Blue_Caronte::info_dispositivo(int dispositivo)
{
   hci_dev_info info_dev;

   hci_devinfo(dispositivo, &info_dev);

   // Nombre del dispositivo hciX
   strcpy(nombre,info_dev.name);

   //MAC del dispositivo
   ba2str(&(info_dev.bdaddr),mac);

}
