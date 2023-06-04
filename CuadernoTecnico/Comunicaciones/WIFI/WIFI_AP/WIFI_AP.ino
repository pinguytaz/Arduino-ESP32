/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo conexión como punto de acceso del ESP32
 **************************************************************************************************/
#include <WiFi.h>

const char *ssid = "AP_ESP32";   // Maximo 63 caracteres
const char *password = "UnaClave";    // Minimo 8 caracteres.

// Funcion que captura evento de conexion de una estación
void WiFiConectaEstacion(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.println("Se conecta una estación al AP.");
}

void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configurando Punto de acceso");
  IPAddress    apIP(10, 10, 10, 1);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));  
  WiFi.softAP(ssid, password);  

  IPAddress miIP = WiFi.softAPIP();   // Obtenemos la IP del AP
  Serial.print("Direccion IP del AP: ");
  Serial.println(miIP);
  
  Serial.println("Punto de acceso iniciado");
  WiFi.onEvent(WiFiConectaEstacion, SYSTEM_EVENT_AP_STACONNECTED);  // Llamada al conectar.
}

void loop()
{
  Serial.println("Estaciones conectadas: " + String(WiFi.softAPgetStationNum()));
  delay(10000);
  
}
