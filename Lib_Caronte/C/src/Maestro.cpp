/*
     Ejemplo de un maestro con conexión Bluetooth
     Cliente que se conecta al MAC(de un esclavo) pasado por parametro
*/

#include <Blue_Caronte.h>
#include <cstdio>

int main(int argc, char* argv[])
{
   paquete paq;

   char destino[18];
   Blue_Caronte BT("MAE");

   printf("Uso: MAC_Conecta [Dispo uso]\n"); 

   if(argc <2)
   {
      perror("Es necesario conocer a quien se conecta");
      return -1;
   }
   else if(argc==3) 
   {
      BT.inicio(argv[2]); // Dispositivo indicado
   }
   else
   {
      BT.inicio(); // Dispositivo por defecto
   }

   printf("Dispositivo %s Nombre: %s MAC: %s\n",BT.get_ID(),BT.get_nombreDispo(),BT.get_mac());
   strcpy(destino,argv[1]);
   printf("Se conecta a %s\n",destino);

   if(BT.conecta(destino,1) ==0)  // Poner 22 en Movil
   {
      while(1==1)
      {
         while(!BT.Paquete(paq)) {;} // Espera texto
         printf("LLega una cadena de datos de :%s:::%s\n",BT.lee_ID(paq),BT.S_paquete(paq)); 
         BT.T_paquete("Hola esclavo mio\n");
         while(!BT.Paquete(paq)) {;}
         printf("LLega un byte de datos de :%s:::%2X\n",BT.lee_ID(paq),paq.Datos[0]);
         while(!BT.Paquete(paq)) {;}
         printf("LLega un short de datos de :%s:::%d\n",BT.lee_ID(paq),BT.I_paquete(paq));
         while(!BT.Paquete(paq)) {;}
         printf("LLega un flotante de datos de :%s:::%f\n",BT.lee_ID(paq),BT.F_paquete(paq));
       }
   }

}
