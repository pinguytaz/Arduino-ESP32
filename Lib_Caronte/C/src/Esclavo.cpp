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
   BT.escucha(1);  // Se conecta al puerto 22, para Movil.
   printf("Se ha conectado el maestro: %s\n",BT.get_mac_cliente());

   BT.T_paquete("Hola Sr. Maestro, soy tu esclavo");

   while(1==1)
   {
      printf("Vemos si tenemos paquete\n");
      if(BT.Paquete(paq)) printf("Han llegado de Maestro los datos de %s: %s\n",BT.lee_ID(paq),BT.S_paquete(paq));

      printf("Se envia byte 66(%X)\n",100);
      BT.T_paquete((char)100);

      printf("Se short int %d)\n",-53);
      BT.T_paquete((short int)-53);

      printf("envia flotante %f)\n",-28.0966);
      BT.T_paquete((float)-28.0666);

      BT.T_paquete("Terminada las pruebas\n");

      sleep(10); 
   }
}
