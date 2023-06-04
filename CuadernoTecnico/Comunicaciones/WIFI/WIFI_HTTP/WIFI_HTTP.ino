
/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo de solicitudes GET y POST 
 *               La prueba de POST, es con https y cifrando los datos JSON que se envian como parametros.
 **************************************************************************************************/
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "{Usuario WIFI}";
const char* clave = "{Clave WIFI}";

//Direcciones de prueba
String PruebaGET = "https://ifconfig.me/ip";
String PruebaPOST = "https://api.telegram.org/bot{TOKEN BOT}";  // API Telegram Poner TOKEN de servicio
int UsuarioDestino = {ID Usuario de destino};   // Cambiar por un usuario conocido

void setup() 
{
  Serial.begin(115200); 

  // Nos conectamos a la WIFI
  WiFi.mode(WIFI_STA);      // Ponemos modo estacion
  WiFi.begin(ssid, clave);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP del dispositivo: ");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  
   // Confirmamos que continuamos conectados.
   if(WiFi.status()== WL_CONNECTED)
   {
      HTTPClient http;
      int httpResponseCode;
      String Parametros;
      String resultado;

      //Primera prueba GET
      Serial.println("Solicitud GET para obtener IP publica");
      Serial.print(PruebaGET);
      http.begin(PruebaGET.c_str());
      httpResponseCode = http.GET();   // Solicitamos GET
      if (httpResponseCode>0) 
      {
         Serial.println("HTTP codigo respuesta en GET: ");
         Serial.println(httpResponseCode);
         resultado = http.getString();
         Serial.println("Nuestra IP es: " + resultado);
      }
      else 
      {
        Serial.print("Error codigo: ");
        Serial.println(httpResponseCode);
      }

      Serial.println("--------");

      // Segunda prueba Envio a Telegram con POST con certificado y formato JSON
      Serial.println("Solicitud POST para enviar un mensaje a Telegram");
      PruebaPOST = PruebaPOST + "/SendMessage" ;   // Metodo enviar mensaje
      
      Serial.println(PruebaPOST);
      http.begin(PruebaPOST.c_str());
      http.addHeader("Content-Type", "application/json");  //Cabecera contenido JSON 

      // Formamos el mensaje JSON con los parametros
      StaticJsonDocument<200> doc;
      doc["chat_id"] = UsuarioDestino;
      doc["text"] = "Mensaje de prueba desde ESP32";
      serializeJson(doc,Parametros);
      
      Serial.println(Parametros);
      httpResponseCode = http.POST(Parametros.c_str());   // Solicitamos POST
      if (httpResponseCode>0) 
      {
         Serial.print("HTTP codigo respuesta en POST: ");
         Serial.println(httpResponseCode);
         resultado = http.getString();
         Serial.println("Retorno mensaje: " + resultado);
      }
      else 
      {
        Serial.print("Error codigo: ");
        Serial.println(httpResponseCode);
      }     
      
      // Liberamos recursos.
      http.end();
    }
    else 
    {
      Serial.println("WiFi Desconectado");
    }
    delay(555000);
}
