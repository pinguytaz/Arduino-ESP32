/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Cliente ESP32 envio datos por WIFI a Servidor,
 *               para captura de datos.
 *
 *  Librerias:
 **************************************************************************************************/
#include <WiFi.h>
#include <WiFiClient.h>

/*
const char* ssid = "{Usuario WIFI}";
const char* clave = "{Clave WIFI}";
*/
const char* ssid = "garum";
const char* clave = "Libro.28091966.2.4";

// Definimos los datos de conexión a nuestro servidor
const uint16_t port = 2809;
//const char *host = "{IP de nuestro servidor}";
const char *host = "192.168.10.20";

#  Identificador del equipo
const byte id_equipo = 'P';

static int valor=0;

void setup() 
{
   Serial.begin(115200); 

   // Nos conectamos a la WIFI
   WiFi.mode(WIFI_STA);      // Ponemos modo estacion
   WiFi.begin(ssid, clave);
   Serial.println("Conectando");
   while(WiFi.status() != WL_CONNECTED) 
   {
     delay(500);
     Serial.print(".");
   }   

  Serial.print("IP del dispositivo: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  WiFiClient client;
  if(WiFi.status()== WL_CONNECTED)    // Verificamos que tenemos conexión al WIFI
  {       
    // Enviamos medida 1
    while(!client.connect(host, port) )
    {
        Serial.println("Fallo en la conexión");
        Serial.println("Se esperan 5 segundos antes de reintentar.");
        delay(5000);
    }
    EnviaMedida1(valor++, client);
    
    # Enviamos medida 1
    if (client.connect(host, port))  // Si no obtiene conexión se pierde el envio de la medida y no bloquea.
    {
      EnviaMedida2(valor*2.5, client);  
    }
  }
  delay(100);
}

void EnviaMedida1(int dato, WiFiClient client)
{
  char cadena[250];
  int longitud;
    
  longitud = sprintf(cadena, "%d", dato);
      
  // Enviamos medida 1
    byte msg[300];
    msg[0] = '#';
    msg[1] = 'W';
    msg[2] = id_equipo;  // ID Equipo
    msg[3] = 'A';        // ID Medida entera
    msg[4] = longitud;      // Longitd

    for (int i=0; i<longitud; i++) // FOR enviando datos de la medida 
    {
       msg[i+5] = cadena[i];     
    }
    
    Serial.print("Envia Media 1 A: " );
    Serial.println(cadena);
    client.write(msg,longitud+5);

    client.stop();   // Cierra conexion
}

void EnviaMedida2(float dato, WiFiClient client)
{
  char cadena[250];
  int longitud;
    
  longitud = sprintf(cadena, "%f", dato);

  // Enviamos medida 1
    byte msg[300];
    msg[0] = '#';
    msg[1] = 'W';
    msg[2] = id_equipo;  // ID Equipo
    msg[3] = 'B';        // ID Medida entera
    msg[4] = longitud;      // Longitd

    for (int i=0; i<longitud; i++) // FOR enviando datos de la medida 
    {
       msg[i+5] = cadena[i];     
    }
    
    Serial.print("Envia Media 1 A: " );
    Serial.println(cadena);
    client.write(msg,longitud+5);

    client.stop();   // Cierra conexion
}

