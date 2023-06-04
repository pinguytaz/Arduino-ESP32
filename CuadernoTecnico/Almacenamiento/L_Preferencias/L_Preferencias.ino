/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo de lectura de Preferences.h para leer datos almacenados y actualizarlos 
 *       WIFI: Con los datos necesarios para conectar con nuestra WIFI
 *       Varios: Otros datos como el ultimo arranque, ID de BOTs, etc.   
 ***********************************************************************************************/
#include <Preferences.h>
#include <WiFi.h>

Preferences D_WIFI;    // Para el espacio de nombres de datos WIFI
Preferences D_Varios;   // Para el espacio de nombres de datos diversos.

struct tm infoHora;

void setup() 
{
   String ssid;
   String clave;
   char DiaSemana[10], Dia[3], Mes[10], Ano[5];
   char Hora[3], Minutos[3], Segundos[3];

   Serial.begin(115200);
   D_WIFI.begin("WIFI", false);   // Se abre en modo Lectura
   D_Varios.begin("Varios", false);   // Se abre en modo Lectura/Escritura
   
   ssid = D_WIFI.getString("SSID","Sin SSID");
   clave = D_WIFI.getString("Clave","Sin Clave");

   Serial.print("Nos conectamos a: ");
   Serial.println(ssid);

   // Nos conectamos a la WIFI
   WiFi.mode(WIFI_STA);      // Ponemos modo estacion
   WiFi.begin(ssid.c_str(), clave.c_str());
   Serial.println("Connecting");
   while(WiFi.status() != WL_CONNECTED) 
   {
     delay(500);
     Serial.print(".");
   }
   Serial.println("");
   Serial.print("IP asignada: ");
   Serial.println(WiFi.localIP());

   //Obtenemos Hora y se actualiza.
   configTime(1*60*60, 3600, "pool.ntp.org"); // get UTC time via NTP
   getLocalTime(&infoHora);
   Serial.print("Nos iniciamos el ");
   Serial.println(&infoHora, "%A %d de %B de %Y a las %H:%M:%S");

   Serial.println("Ultimo acceso: " + D_Varios.getString("Dia","--")
                            + " de "+ D_Varios.getString("Mes","--")
                            + " de "+ D_Varios.getString("Ano","--")
                            + " a las "+ D_Varios.getString("Hora","--")
                            + ":"+ D_Varios.getString("Minutos","--")
                            + ":"+ D_Varios.getString("Segundos","--")
                            );

   strftime(DiaSemana,10,"%A",&infoHora);
   strftime(Dia,3,"%d",&infoHora);
   strftime(Mes,10,"%B",&infoHora);
   strftime(Ano,5,"%Y",&infoHora);
   strftime(Hora,3,"%H",&infoHora);
   strftime(Minutos,3,"%M",&infoHora);
   strftime(Segundos,3,"%S",&infoHora);

   //Guardamos la fecha de inicio
   D_Varios.putString("Dia",Dia);
   D_Varios.putString("Mes",Mes);
   D_Varios.putString("Ano",Ano);
   D_Varios.putString("Hora",Hora);
   D_Varios.putString("Minutos",Minutos);
   D_Varios.putString("Segundos",Segundos);
}

void loop() 
{
    char Hora[3], Minutos[3], Segundos[3];
    
    getLocalTime(&infoHora);
    strftime(Hora,3,"%H",&infoHora);
    strftime(Minutos,3,"%M",&infoHora);
    strftime(Segundos,3,"%S",&infoHora);

    Serial.println("Tiempo: " + String(Hora) +":"+String(Minutos)+":"+String(Segundos));

    delay(5000);
}
