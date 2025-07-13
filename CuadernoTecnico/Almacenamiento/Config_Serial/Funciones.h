/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Definicion de las funciones utilizadas en el proyecto
 *  Funciones:
 *      programarEEPROM()   Espera y recoge datos del puerto serie, que introducira en la EEPROM
 *      leerEEPROM()        Lee datos de la EEPROM que se guardan en las variables globales
 *
 **********************************************************************************************/
#include <EEPROM.h>

#define MAX_ESTADOS 50
typedef struct 
{
  int rojo;
  int verde;
  int azul;
} t_led;

t_led estados[MAX_ESTADOS];
int numEstados=0;

/**********************  Lectura de una linea que llega por puerto Serie que termina en \n   ************************/
String leerLinea() 
{
  String linea = "";
  while (true) 
  {
    if (Serial.available()) 
    {
      char c = Serial.read();
      if (c == '\n') break;     // Cuando llegamos al fin de linea salimos del bucle
      if (c != '\r') linea += c;  // Algunos sistemas meten retorno de carro no le hacemos caso.
    }
  }
  return linea;
}


/********************  Funcion que programa la EEPROM de los datos que llegan datos por el puerto Serial  
    Protocolo espera # y envia |
    byte con el numero de lineas terminada en \n
    <R> <G> <B>   
**************************/
void programarEEPROM() 
{
  int direccion = 0;
  bool esperandoInicio = true;
  
  //Serial.println("Esperamos el #");
  digitalWrite(13, LOW);
  while (esperandoInicio)
  {
    
    while (!Serial.available());  // Esperamos datos.
    char c = Serial.read();  // Lee un caracter
    
    if (c == '#') // Si es la '#' enviara un '|' para dar OK y se pondra a leer datos
    {
      delay(500);  // Tiempo para recibir posible suciedad.
      while (Serial.available()) Serial.read();  // Limpiamos datos en buffer antes de solicitar datos
      Serial.write('|');

      esperandoInicio = false;   // como llego y se envio el OK salimos del bucle para empezar a recibir datos.
    }  
  }

  // Empezamos a recoger datos.
  //Serial.println("REcogemos datos");
  String linea = leerLinea();
  int numLineas = linea.toInt();
  //EEPROM.write(direccion++, numLineas);  // Seria la que usariamos para grabar un caracter, pero es un entero lo que grabaremos
  EEPROM.put(direccion, numLineas); direccion += sizeof(int);   //Graba el numero de linea y avanzamos 2 para siguientes datos.

  //Serial.println("Leeremos " + String(numLineas));

  // Empezamos a recoger lineas para ir grabando la EEPROM
  for (int i = 0; i < numLineas; i++)     // Leemos el numero de lineas que se enviaran
  {
    digitalWrite(13, LOW);
    String linea = leerLinea();
    linea.trim();   // Limpiamos de espacios al principio y final de la cadena.
    
    //Serial.println(linea);
    int primerEspacio = linea.indexOf(' ');
    int segundoEspacio = linea.indexOf(' ', primerEspacio + 1);
    
    int vRojo =  linea.substring(0, primerEspacio).toInt();
    int vVerde = linea.substring(primerEspacio + 1, segundoEspacio).toInt();
    int vAzul = linea.substring(segundoEspacio + 1).toInt();

    //Serial.println("Valores de linea " + String(i+1) + " Rojo: "+ String(vRojo)  + " Verde: "+ String(vVerde) + " Azul: " + String(vAzul));
    EEPROM.put(direccion, vRojo); direccion += sizeof(int);   //Graba el valor del rojo
    EEPROM.put(direccion, vVerde); direccion += sizeof(int);   //Graba el valor del verde
    EEPROM.put(direccion, vAzul); direccion += sizeof(int);   //Graba el valor del azul
  }
  digitalWrite(13, HIGH);
      
}

/*********************  Lectura de la EPROM y almacenamiento en Arrays ****************************************/
void leerEEPROM() 
{
  int direccion = 0;
  EEPROM.get(direccion, numEstados); direccion += sizeof(int);
  //Serial.println("Tenemos :" + String(numEstados) + " estados");
  
  for (int i = 0; i < numEstados; i++) 
  {
    EEPROM.get(direccion, estados[i].rojo); direccion += sizeof(int);
    EEPROM.get(direccion, estados[i].verde); direccion += sizeof(int);
    EEPROM.get(direccion, estados[i].azul); direccion += sizeof(int);
  }
}

