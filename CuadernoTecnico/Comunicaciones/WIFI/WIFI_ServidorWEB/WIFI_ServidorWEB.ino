/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo de servidor WEB 
 *               Nos permitira encender o apagar un LED y ademas informara del 
 *               estado de este ademar dara el valor de un potenciometro que 
 *               simulara ser un sensor de temperatura.
 **************************************************************************************************/
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

// SSID y clave de la WIFI que dara acceso a la red a la que se conectaran los navegadores clientes.
const char* ssid = "tussid";
const char* clave = "tuclave";

WebServer servidor(8080);  // Puerto de nuestra pagina

const int led = 13;
bool estadoLED;
const int potenciometro = 34;

void setup(void) 
{
   pinMode(led, OUTPUT);
   apagar();
   Serial.begin(115200);

   // Nos conectamos ala WIFI de nuestra RED, en modo estación
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, clave);
   Serial.print("Conectando: ");
   while (WiFi.status() != WL_CONNECTED) 
   {
    delay(500);
    Serial.print(".");
   }
   Serial.println("");
   Serial.print("Conectado al SSID");
   Serial.println(ssid);
   Serial.print("Dirección IP: ");
   Serial.println(WiFi.localIP());

   // Definimos las funciones a las que se llamaran, segun la petición
   servidor.on("/", PagRaiz);  // Pagina principal
   servidor.on("/apagaLED", apagar);  // Pagina principal
   servidor.on("/enciendeLED", encender);  // Pagina principal
   servidor.onNotFound(PagNoEncontrada);  // Solicitud no encontrada es el error 404.

   servidor.begin();
   Serial.println("Servidor HTTP inicializado");
}

void loop(void) 
{
   servidor.handleClient();
   delay(2);
}

/****** Funcion que lee el valor del potenciometro *******/
int lectura()   
{
   return analogRead(potenciometro);
}
void encender()
{
   digitalWrite(led, HIGH);
   estadoLED = HIGH;
   //servidor.send(200, "text/plain", "LED Encendido");
   PagRaiz();
}
void apagar()
{
   digitalWrite(led, LOW);
   estadoLED = LOW;
   //servidor.send(200, "text/plain", texto);
   PagRaiz();
}

/**** Paginas ****/
void PagRaiz()   // RAIZ
{
   // Cabecera de todas las paginas WEB
   String texto = "<!DOCTYPE html>\n <html>\n";
   texto += "<head><meta charset=\"utf-8\">\n";
   texto += "<title>Ejemplo WebServer</title>\n";
   texto += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
   texto +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
   texto +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
   texto +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
   texto +=".button-on {background-color: #00FF00;}\n";
   texto +=".button-on:active {background-color: #003300;}\n";
   texto +=".button-off {background-color: #FF0000;}\n";
   texto +=".button-off:active {background-color: #330000;}\n";
   texto +="</style>\n";
   texto += "</head>\n";
   texto += "<body>\n";
   texto += " <p>La medición del potenciometro es: " ;
   texto += (String) lectura();
   texto += "</p>";
   texto += " <p>Estado del LED: ";
   if (estadoLED)
   {
      texto += "ENCENDIDO</p>";
      texto += "<a class=\"button button-off\" href=\"/apagaLED\">Apagar</a>\n";
   }
   else
   {
      texto += "APAGADO</p>";
      texto += "<a class=\"button button-on\" href=\"/enciendeLED\">Encender</a>\n";
   }
   texto += "</body>\n";
   texto += "</html>\n";

   servidor.send(200, "text/html", texto);
   //servidor.send(200, "text/html", "Desarrollar la pagina RAIZ");
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
