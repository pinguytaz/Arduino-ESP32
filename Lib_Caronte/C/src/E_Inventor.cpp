/*
     Ejemplo de un esclavo con conexión Bluetooth
     Servidor que espera que se conecte un Maestro(Cliente)
*/

#include <Blue_Caronte.h>
#include <cstdio>
#include <unistd.h>

int main(int argc, char* argv[])
{
   paquete paq;
   Blue_Caronte BT("ESC");

   if(argc==2) 
   {
      BT.inicio(argv[1]); // Dispositivo indicado
   }
   else
   {
      BT.inicio(); // Dispositivo por defecto
   }
   printf("Dispositivo esclavo %s Nombre: %s MAC: %s\n",BT.get_ID(),BT.get_nombreDispo(),BT.get_mac());
   printf("Se pone a la escucha de un Maestro");


   // Se prepara a escuchar se le pasa puerto
   BT.escucha(22);  // Se conecta al puerto 1
   printf("Se ha conectado el maestro: %s\n",BT.get_mac_cliente());

   //BT.T_paquete("Hola Sr. Maestro, soy tu esclavo");

   while(1==1)
   {
      printf("Vemos si tenemos paquete\n");
      if(BT.Paquete(paq)) printf("Han llegado de Maestro los datos de %s: %s\n",BT.lee_ID(paq),BT.S_paquete(paq));

      sleep(30); 
   }
}
