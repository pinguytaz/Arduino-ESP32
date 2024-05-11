/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo de Preferences.h para almacenar datos de uso comun en dos espacios de nombre
 *       WIFI: Con los datos necesarios para conectar con nuestra WIFI
 *       Varios: Otros datos como el ultimo arranque, ID de BOTs, etc.   
 ***********************************************************************************************/
#include <Preferences.h>

Preferences D_WIFI;    // Para el espacio de nombres de datos WIFI
Preferences D_Varios;   // Para el espacio de nombres de datos diversos.

void setup() 
{
   Serial.begin(115200);
   Serial.println(D_WIFI.begin("WIFI", false));   // Se abre en modo Lectura/Escritura
   D_Varios.begin("Varios", false);   // Se abre en modo Lectura/Escritura

   // Borramos todos los datos, por si existiera ese espacio de nombre, ya que en este ejemplo se crean los datos.
   D_WIFI.clear();
   D_Varios.clear();


   // Grabamos los datos del espacio de nombres WIFI
   D_WIFI.putString("SSID","Nombre SSID");
   D_WIFI.putString("Clave","Clave de la WIFI");
   
   
   // Grabamos los datos del espacio de nombres Varios
   D_Varios.putUInt("Contador",0);
   D_Varios.putString("Autor","Fco. Javier Rodriguez Navarro");
   D_Varios.putString("Version","0.1");
 
   D_WIFI.end();
   D_Varios.end();
   Serial.println("La grabacion inicial ha sido realizada");
}

void loop() 
{
   
}
