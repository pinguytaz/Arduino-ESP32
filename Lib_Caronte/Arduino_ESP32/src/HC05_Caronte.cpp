/* ******************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *  
 *  Descripción:Libreria Lib_Caronte para modulo BlueTooth HC-05
 *        C<ID-3><Tam-1><Paquete0-255>
 *  
 *  Historico:
 *      Creación:  Marzo 2021 Creacion
 *
 *  Info:
 *       https://www.pinguytaz.net/index.php/2016/11/10/uso-modulo-bluetooth-hc-05-en-arduino
 ********************************************************/
#include "Arduino.h"

#include "HC05_Caronte.h"
#include <SoftwareSerial.h>

/*******************  Constructores  ************************/
HC05_Caronte::HC05_Caronte(String nombre): Caronte(nombre) {;}

void HC05_Caronte::begin(uint8_t Pin_BT_TX, uint8_t Pin_BT_RX, uint8_t Pin_BT_KEY)
{   
   String resultado="";
     
  _Pin_BT_RX = Pin_BT_RX;
  _Pin_BT_TX = Pin_BT_RX;
  _Pin_BT_KEY = Pin_BT_KEY;
  _com = new SoftwareSerial(Pin_BT_TX, Pin_BT_RX);

  pinMode(_Pin_BT_KEY,OUTPUT);
  digitalWrite(_Pin_BT_KEY, LOW);  // En principio sin ser comando.
  delay(1500);  // Esperamos que se estabilice el modulo

  _com->begin(_baudios);   //Configuracion velocidad comunicarse con el dispositivo.
  delay(500);  // Esperamos esta
  _com->flush();  // Limpiamos

}

void HC05_Caronte::begin(uint8_t Pin_BT_TX, uint8_t Pin_BT_RX, uint8_t Pin_BT_KEY, String nombre, String pin)   // Si se quiere cambiar nombre y clave
{ 
    String resultado;
    
    begin(Pin_BT_TX, Pin_BT_RX, Pin_BT_KEY);   // Por defecto a esclavo.
    delay(1000);

    // Ahora cambiamos nombre y clave de vinculación.
    do
    {
       resultado = AT("AT+ORGL"); 
       Serial.println("Resultado de ORGL"+resultado);
    } while(!AT_isOK(resultado));

    while(!set_nombre(nombre)) delay(5000);
    while(!set_pin(pin)) delay(5000);
    
}

/************** Funciones publicas  *****************************/
int HC05_Caronte::disponibles()
{
   return _com->available();
}

bool HC05_Caronte::set_nombre(String nombre)
{
  String resultado=AT("AT+NAME="+nombre);
  return AT_isOK(resultado);
}
     
String HC05_Caronte::get_nombre()  // Nombre configurado
{
  String resultado=AT("AT+NAME?");
  return resultado.substring(resultado.indexOf(":")+1,resultado.indexOf("\r\n"));
}


bool HC05_Caronte::set_pin(String pin)
{
  String resultado;
   
  pin = "\""+pin+"\"";
  resultado=AT("AT+PSWD="+pin);
  return AT_isOK(resultado);
}
     
String HC05_Caronte::get_pin()  // PIN de emparejamiento
{
  String resultado=AT("AT+PSWD?");
  return resultado.substring(resultado.indexOf(":")+1,resultado.indexOf("\r\n"));
}


String HC05_Caronte::get_direccion() // Direccción del dispositivo NAP:UAP:LAP
{
  String resultado=AT("AT+ADDR?");
  return resultado.substring(resultado.indexOf(":")+1,resultado.indexOf("\r\n"));
}

bool HC05_Caronte::set_uart(Velocidad velocidad,BitStop bitstop ,Paridad paridad)
{
  String conf;
  String resultado;

  conf=String(velocidad)+","+String(bitstop)+","+String(paridad);
  
  resultado=AT("AT+UART="+conf);
  return AT_isOK(resultado);
}
     
String HC05_Caronte::get_uart()  // UART
{
  String resultado=AT("AT+UART?");
  return resultado.substring(resultado.indexOf(":")+1,resultado.indexOf("\r\n"));
}

bool HC05_Caronte::set_rol(Rol rol)
{
  String resultado=AT("AT+ROLE="+String(rol));
  return AT_isOK(resultado);
}
String HC05_Caronte::get_rol() 
{
  String resultado=AT("AT+ROLE?");
  return resultado.substring(resultado.indexOf(":")+1,resultado.indexOf("\r\n"));
}

bool HC05_Caronte::set_modo(Modo modo)  // Modo de conexión en Rol maestro
{
  String resultado=AT("AT+CMODE="+String(modo));
  return AT_isOK(resultado);
}
String HC05_Caronte::get_modo() 
{
  String resultado=AT("AT+CMODE?");
  return resultado.substring(resultado.indexOf(":")+1,resultado.indexOf("\r\n"));
}

bool HC05_Caronte::set_dirCon(String dir)  // Modo de conexión en Rol maestro
{
  String normalizado = "0134,67,902356";

  // Pasamos la direccion-MAC al formato que necesita HC-05 AABB,CC,DDEEFF (Normal AA:BB:CC:DD:EE:FF)
  normalizado = dir.substring(0,2)+dir.substring(3,5);
  normalizado = normalizado+","+dir.substring(6,8);
  normalizado=normalizado+","+dir.substring(9,11)+dir.substring(12,14)+dir.substring(15);

  String resultado=AT("AT+BIND="+normalizado);
  // Retorno +INQ  <Dir Remota>,<Tipo dispositivo>,<Señal intensidad>
  Serial.println(resultado);
  return AT_isOK(resultado);
}
String HC05_Caronte::get_dirCon() 
{
  String resultado=AT("AT+BIND?");
  return resultado.substring(resultado.indexOf(":")+1,resultado.indexOf("\r\n"));
}

bool HC05_Caronte::reset(void)  // Reseteamos 
{
  String resultado=AT("AT+RESET");
  return AT_isOK(resultado);
}
String HC05_Caronte::escucha(void) 
{
  String msg_conexion="";
  paquete paq;
  
  while(!set_rol(Esclavo)) delay(5000);
  while(!reset()) delay(5000);

  // Ahora esperamos que nos mande un mensaje el Maestro, que sera el retornado.
  while (!Paquete(paq))
  {
    delay(500);
  }
  msg_conexion = msg_conexion + S_paquete(paq);
  
  return msg_conexion;
} 

void HC05_Caronte::conecta(String direccion) 
{
  String resultado;
  
  while(!set_rol(Maestro)) delay(5000);  // Ponemos modo Maestro
  delay(2000);
  while(!set_modo(Fija)) delay(5000);    // Modo direccion Fija
  delay(2000);
  while(!set_dirCon(direccion)) delay(5000);  //Damos direccion
  delay(2000);
  Serial.println("Lanzamos el INIT");
  do
  {
     resultado = AT("AT+CMODE?"); 
     Serial.println("Resultado de INIT"+resultado);
  } while(!AT_isOK(resultado));
  delay(2000);
  while(!reset()) delay(5000);
  delay(2000);
} 


/******************  Funciones privadas ********************************************/
bool HC05_Caronte::AT_isOK(String resultado)
{
  if(resultado.indexOf("OK\r\n")== -1) return false;
  else return true;
}

String HC05_Caronte::AT(String comando)
{
   String retorno="";
   char c;

   if(comando != "AT+RESET") digitalWrite(_Pin_BT_KEY, HIGH);  // Pone el modo
   delay (500) ;
      
   for (int i=0; i < comando.length(); i++)  
   {
      _com->write(comando[i]);
      delay(10);
   }
   // Enviamos el CR+lf necesario para finalizar el comando
   _com->write('\r');   // Envia retorno de carro
   delay(10);
   _com->write('\n');    // Envia Nueva linea
   delay(1500);  // Esperamos un segundo y medio para su procesado.

   while (_com->available()) 
   {
      retorno=retorno+char(_com->read());
      delay(10);
   }

   digitalWrite(_Pin_BT_KEY, LOW);
   delay(1000);
   
   return retorno;
}

bool HC05_Caronte::lee(char &bytes)
{ 
   int bytes_leidos=0;
   char buf;

   bytes_leidos = _com->available();
   if (bytes_leidos ==0) return false;  //No tenemos datos.
   
   buf = _com->read(); // Leemos un caracter 
   bytes = buf;
   
   return true; //El caracter que se lee esta en byte y se retorna por referencia
}

bool HC05_Caronte::envia(char *datos, int longitud)
{ 
   int i;
   char buf;
   for (i=0; i< longitud; i++)
   {
      // Enviamos de byte en byte
      buf = datos[i];
      _com->write(buf);
   }

   return true;
}
