/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción:  Ejemplo completo especialmente para motores paso a paso
 *                Tambien se ve acceso y grabación de Disco: NVS, SPIFFS
 *                WIFI AP con un servidor WEB
 *
 * Libreria: Regexp de Nick Gammon para el tratamiento de expresiones regulares
 ***********************************************************************************************/
#include <Preferences.h>
#include <WiFi.h>
#include <WebServer.h>
#include "Disco.h"
#include <Regexp.h>     // Tratamiento de expresiones regulares
#include "CartesianoX.h"
#include "Coordenadas.h"

#define MOTOR_A     19
#define MOTOR_C     18
#define MOTOR_B     17
#define MOTOR_D     16
#define FINCARRERA  25
#define LED_Encendido     15

Preferences D_WIFI;
IPAddress apIP(10, 18, 74, 24);    // IP de acceso al servidor
WebServer servidor(80);  
Disco discoweb("WEB");
//CartesianoX Motor(96, 920, FINCARRERA);
CartesianoX Motor(96, 920, FINCARRERA);


// Funcion que captura evento de conexion de una estación
void WiFiConectaEstacion(WiFiEvent_t event, WiFiEventInfo_t info);

void setup(void) 
{
  String ssid;
  String clave;
  String hostname;

  Serial.begin(115200);
  Serial.println("Inicio:");
  pinMode(LED_Encendido, OUTPUT);   
   
  // Recogemos información de la configuración
  D_WIFI.begin("guija", false);
  ssid = D_WIFI.getString("SSID","Sin SSID");
  clave = D_WIFI.getString("Clave","Sin Clave");
  Serial.println("*** Aplicación: " + D_WIFI.getString("Aplicacion","Desconocido")+" Version: "+ D_WIFI.getString("Version","Desconocido"));
  Serial.println("********** " + D_WIFI.getString("Autor","Desconocido")+" **********");
  WiFi.setHostname(D_WIFI.getString("Hostname","SinHostnema").c_str());
  D_WIFI.end();
   
  WiFi.disconnect(true);
  delay(1000);
  WiFi.onEvent(WiFiConectaEstacion);
   
  Serial.print("Creamos el AP: " + ssid);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid.c_str(), clave.c_str());
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));  
   
     // Definimos las funciones de las solicitudes WEB
  servidor.on("/", PagRaiz);  // Pagina principal
  servidor.on("/act_texto", HTTP_POST, act_texto);  
   
  servidor.onNotFound(PagNoEncontrada);  

  servidor.begin();
  
  Motor.Inicia(MOTOR_A,MOTOR_B,MOTOR_C,MOTOR_D);
  digitalWrite(LED_Encendido, HIGH);  // Indicamos que conectado
}

void loop() 
{
  servidor.handleClient();
  delay(5);

 /* Motor.avanza();
  Serial.println("La X es: " + String(Motor.get_X()));
  delay(1000);
*/
}


/**** Paginas ****/
void PagRaiz() 
{
  char texto[1024];
  int i=0;

  //discoweb.ficheros();
  i=discoweb.cargaPagina("/raiz.html",texto);
  if(i<0) 
  {
    Serial.println("ERROR en la carga de la pagina " + i);
    return;
  }
    
  MatchState ms;
  ms.Target (texto,i); 
  ms.GlobalReplace ("%>>MIIP<<", "Calculamos la IP");
 
   servidor.send(200, "text/html", texto);
}

void PagNoEncontrada()   // Error 404 Pagina no encontrada
{
   String texto = "Página no encontrada\n\n";
   texto += "URI: ";
   texto += servidor.uri();
   texto += "\nMethod: ";
   texto += (servidor.method() == HTTP_GET) ? "GET" : "POST";
   texto += "\nArguments: ";
   texto += servidor.args();
   texto += "\n";
   servidor.send(404, "text/plain", texto);
}

void act_texto()   
{
  String palabra = servidor.arg(0);
  palabra.toUpperCase();
  int longitud = palabra.length();
  Serial.println("Se genera texto: " + palabra+ " de longitud " + String(longitud));
  
  for (int i=0; i < longitud; i++)
  {
    char c = palabra[i];
    Serial.print(c);
    if (isAlpha(c))
    {
      int cor = (int) c - 65 + 10;
      Motor.irA(cordenada[cor][0]);
    }
    else if (isDigit(c))
    {
       int cor = (int) c - 48;
       Motor.irA(cordenada[cor][0]);
    } 
    delay(5000);
  }
  
  PagRaiz();
}

void WiFiConectaEstacion(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.printf("***[Evento WIFI] :%d --> ",event);
   switch (event) {
    case ARDUINO_EVENT_WIFI_READY:               Serial.println("Interfaz wifi preparado"); break;
    case ARDUINO_EVENT_WIFI_AP_START:           Serial.println("AP iniciado"); break;
    case ARDUINO_EVENT_WIFI_AP_STOP:            Serial.println("AP parado"); break;
    case ARDUINO_EVENT_WIFI_AP_STACONNECTED:    
      Serial.println("Conexión de cliente"); 
      Serial.print("Total de clientes: ");
      Serial.println(WiFi.softAPgetStationNum());
      //if (WiFi.softAPgetStationNum()==2) ESP.restart();
      break;
    case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED: 
      Serial.println("Desconexión de cliente"); 
      Serial.print("Total de clientes: ");
      Serial.println(WiFi.softAPgetStationNum());
      break;
    case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:   
      Serial.print("Asignación de IP: "); 
      Serial.print(IPAddress(info.got_ip.ip_info.ip.addr));
      Serial.println(" a cliente");
      break;
    default:      break;
  }
}