/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Realiza un escaneo de las redes disponibles
 *  ***********************************************************************************************/
#include <WiFi.h>

void setup()
{
  Serial.begin(115200);
  // Nos ponemos en modo estacion y nos desconectamos.
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop()
{
  Serial.println("*************** Redes encontradas ********************");
  int n =WiFi.scanNetworks();  // Numero de redes localizadas.

  // Realizamos un recorrido por las redes encontradas
  for(int i = 0 ; i < n; i++)
  {
    Serial.print(WiFi.SSID(i));
    Serial.print(" (");
    Serial.print(WiFi.RSSI(i));
    Serial.print(" ) ");
    Serial.println(Seguridad(WiFi.encryptionType(i)));
    delay(10);
  }
  
  Serial.println("********************************************");
  delay(5000);
}

String Seguridad(int var)
{
  
   String retorno = "";
   switch (var) 
   {
       case WIFI_AUTH_OPEN:
          retorno ="Abierta";
          break;
       case WIFI_AUTH_WEP:
          retorno ="WEP";
          break;
       case WIFI_AUTH_WPA_PSK:
          retorno ="WPA";
          break;
       case WIFI_AUTH_WPA2_PSK:
          retorno ="WPA2";
          break;
       case WIFI_AUTH_WPA_WPA2_PSK:
          retorno ="WPA_WPA2";
          break;
       case WIFI_AUTH_WPA2_ENTERPRISE:
          retorno ="WPA2 Enterprise";
          break;
    }
}
