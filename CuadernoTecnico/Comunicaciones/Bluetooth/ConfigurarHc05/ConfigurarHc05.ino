/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Programa para configurar con comandos AT el modulo HC-05
 *            
 *               
 ******************************************************************************************/
#include <SoftwareSerial.h> 
 
// Creamos el objeto
SoftwareSerial BT(10,11); //RX, TX.

// Definicion de pines
const int Pvcc = 8; // Alimentación
const int Pkey = 9; // Se pone a nivel alto para comandos,KEY


void setup() 
{
  
  //BT.begin(9600); //Velocidad modulo Bluetooth
  Serial.begin(9600); // Velocidad consola.
  BT.begin(38400);  // Velocidad del equipo HC-05
  
  // Definiciónn de Pines
  pinMode(Pvcc, OUTPUT); // AlimentaciÃ³n y preparar Reset,
  pinMode(Pkey, OUTPUT); // Al poner en HIGH forzaremos el modo AT
  
  modo_Comando(HIGH); // Activamos modo comando. en LOW se pone modo comunicación
  delay(1000); 
}

void loop() 
{
   char cmd[20];
   int i =0;
   
   while(Serial.available() > 0)
   {
      char a = Serial.read();
      if(a!= '\n' && a != '\r') cmd[i] = a;  //Los fines de lineas se quitan
      i++;
      cmd[i] = '\0';  //Fin cadena.
      delay(50);
   }

   if (i > 0)  // Tenemos un comando a enviar
   {
      Serial.println(comando((char*)cmd));
   }
   
}

//////////////////////////////////////////////////////
//   Modo_Comando(HIGH-Comamdo, LOW-Transmisión)
//     
//   Reinicia el modulo en modo comando o transmisión
/////////////////////////////////////////////////////
void modo_Comando(boolean modo)
{
  digitalWrite(Pvcc, LOW); // Apaga el modulo
  delay (500) ;
  digitalWrite(Pkey, modo);  // Pone el modo
  delay (500) ;
  digitalWrite(Pvcc, HIGH); // Enciendo el modulo en el estado.

  if (modo) Serial.println("Activamos el modo comando del HC-05");
  else Serial.println("Activamos el modo transmisiÃ³n");
}
  
/////////////////////////////////////////////////////////
//   Comando(String comando)
//
//       Envia un comando al dispositivos, acordarse de poner en modo comando.
/////////////////////////////////////////////////////////
String comando(String at)
{
  String resultado = "";

  Serial.println("Enviamos: " + at);
      
  // Vacia Buffer del dispositivo
  while (BT.available() > 0) Serial.write(BT.read());

  escribe(at);
 
  delay(1000);  // Esperamos un segundo ya que no se puede enviar antes otro.

  resultado = lee();
  return resultado;
}


//////////////////////////////////////////////////////
//   Escribe(String cadena)
//     
//   Envia al dispositivo una cadena
/////////////////////////////////////////////////////
void escribe(String cadena)
{
   char c;

   
   for (int i=0; i < cadena.length(); i++) 
   {
       c = cadena[i];
       BT.write(c);
    }

  // Enviamos el CR+lf necesario para finalizar el comando
  BT.write('\r');  
  BT.write('\n');
}

//////////////////////////////////////////////////////
//   String lee()
//     
//   Recibe datos.
/////////////////////////////////////////////////////
String lee()
{
  String resultado="";
  char c;
  
  while(BT.available() > 0)
  {
       c = BT.read();
       resultado = resultado + c;    
  }
  return resultado;
}
