/************************************************************************************************
 * Fco. Javier Rodriguez Navarro   
 * https://www.pinguytaz.net
 *      
 * Teclado_SD.ino: Programa que teclea automaticamente, lo configurado en un Script(payload).
 *                 si esta definido el fichero EJECUTA.TXT se lanzara automaticamente al ejecutarse.
 *                 Desde consola podremos configurar o eliminar el payload "EJECUTA.TXT" así como
 *                 lanzar comandos.
 *                    
 * Historico:
 *       5 Octubre 2020    V1: Creación (no disponible ejecución de Macros, se debe obtimizar)
 * Librerias:
 *     Keyboard
 *     SPI
 *     SD
 ***************************************************************************************************/
#include <Keyboard.h>

#include <SPI.h>
#include <SD.h>

#define LED_ON  13
#define LED_INF 8
#define AUTORUN "EJECUTA.TXT"

boolean autoEjec=false;  // En pricipio no esta.
const String aplicacion="\n\n       Pingûino BADUSB V1.0\n       ---------------------";

// Inicialización: LED, ejecución si existe "ejecuta.txt", carga de ficheros Payloads
void setup() 
{

   // BADUSB dispone de un LED 13 y un LED 8
   pinMode(LED_ON, OUTPUT);
   pinMode(LED_INF, OUTPUT);
   digitalWrite(LED_ON, LOW);
   digitalWrite(LED_INF, LOW);
  
   // Ciclo de retardo, para poder reprogramar Leonardo y ver que todo es OK
   for(int i = 0; i<3; i++)
   {
      digitalWrite(LED_ON, HIGH);
      delay(50);
      digitalWrite(LED_INF, HIGH);
      delay(50);
      digitalWrite(LED_ON, LOW);
      digitalWrite(LED_INF, LOW);
      delay(2000);
  }

  Serial.begin(9600);    // Inicialización del puerto serie.
 
  if (!SD.begin(4)) {  }  

  Keyboard.begin();   //Inicializa teclado.
  // SI existe fichero de autoejecución se ejecuta
  if (SD.exists(AUTORUN))
  {
      autoEjec = true; //Existe autoejecución
      EjecutaScript(AUTORUN);
  }
  
   // Todo inicializado correctamente.
  digitalWrite(LED_ON, HIGH);   // Se queda encendido indicando que es 
  digitalWrite(LED_INF, LOW);  

}
/********************** Bucle de ejecución   *********/
void loop() 
{
    char opcion;
    char comando[100];
    int i = 0;
    char caracter;
        
    Serial.println(aplicacion);
    Serial.println(F("1.- Ejecución Payload cargado en SD"));
    Serial.println(F("2.- Ejecutar comando"));
    if(autoEjec) Serial.println(F("3.- Desactiva Autoarranque"));
    else Serial.println(F("3.- Activa Autoarranque"));
     
    while(Serial.available()<=0) { }   // Espera a ver si se pulsa algo.
  
    opcion = Serial.read();
    while(Serial.available())  { Serial.read(); } // Vacia resto.
      
    if(opcion=='1')payload();
    else if(opcion=='2')
    {
        Serial.print(F("Escriba comando: "));
        while(Serial.available()<=0) { }
        while(Serial.available()>0)
        {
            caracter = Serial.read();
            comando[i++] = caracter;
        }
        comando[i] = '\x00';
        ProcesaComando(comando);
    }
    else if(opcion=='3') autoarranque();
}       

/*******************************************************************************
 * payload()
 *    Opcion de ejecución de un payload cargado
 *******************************************************************************/
void payload()
{
   int ficheros=0;
   String nombre;
   char opcion;

   Serial.println(aplicacion);
   Serial.println(F("          Ficheros PayLoad "));

   ficheros = listaPayloads();
   Serial.print(F("¿Cual ejecutamos?: "));

   if(ficheros > 0) // Recogemos uno.
   {
       while(Serial.available()<=0) { }  //Esperamos opcion
       opcion = Serial.read();
       while(Serial.available()) { Serial.read(); }  // Borra resto.
           
       if(opcion >= '1' && opcion <= (ficheros+48)) //opcion correcta se localiza nombre
       {
           // Obtenemos nombre de fichero
           nombre = nombre_fichero(opcion-48); // el 48 es el ASCII del 0.
           EjecutaScript(nombre);
       }
   }   
}

/******************************************************************************
 * String nombre_fichero(int opcion)
 *         Obtiene el nombre del fichero seleccionado por parametro.
 *****************************************************************************/
 String nombre_fichero(int opcion)
 {
     File dir = SD.open("/");
     int i=1;
     String nombre="";
    
     while (nombre == "")
     {
         File entrada =  dir.openNextFile(); // Recorrido fichero
         if (!entrada.isDirectory()) // Solo trata ficheros.
         {
             if(i==opcion)  // Se ejecuta dichero.
             {
                 nombre = String(entrada.name());
             }
             i++;
         }
         entrada.close();
    }

    dir.close();
    return nombre;
}

/******************************************************************************* 
 *  autoarranque() 
 *       Activa o desactiva el autoarranque (Fichero EJECUTA.TXT)
 *******************************************************************************/
void autoarranque()
{
    int ficheros=0;
    String nombre;
    char opcion;
    File archivo;
    File fp_ejecuta; 
    char c;
            
    if(autoEjec) // Esta activado
    {
        SD.remove(AUTORUN);
        Serial.println(F("Autorun Desactivado"));
        autoEjec = false;
    }
    else  // Como esta desactivado, se solicita
    {
        Serial.println(aplicacion);
        Serial.println(F("          Activar Autorun "));

        ficheros = listaPayloads();
        Serial.println(F("¿Cual activamos?: "));

        if(ficheros > 0) // Recogemos uno.
        {
            while(Serial.available()<=0) { }  //Esperamos opcion
            opcion = Serial.read();
            while(Serial.available()) { Serial.read(); }  // Borra resto.
           
            if(opcion >= '1' && opcion <= (ficheros+48)) //opcion correcta se localiza nombre
            {
                 // Obtenemos nombre de fichero
                 nombre = nombre_fichero(opcion-48); // el 48 es el ASCII del 0.
                 archivo = SD.open(nombre, FILE_READ);
                 fp_ejecuta = SD.open(AUTORUN, FILE_WRITE); 
                 c = archivo.read();
                 while(c != -1) //Leemos hasta el final
                 {
                     fp_ejecuta.write(c);
                     c = archivo.read(); 
                 }
                 archivo.close();
                 fp_ejecuta.close();
                 Serial.println("Fichero de autorun: "+ nombre+" ACTIVADO");
                 autoEjec = true;
            }
        }   
    }
}
 
/*******************************************************************************
 * int listaPayloads()  
 *       Lista los fichero Payloads, Retorna el numero de ficheros
 *******************************************************************************/
int listaPayloads(void)
{
    File dir = SD.open("/");
    int i=1;

    Serial.println(F("Lista de ficheros disponibles"));

    while (true) 
    {
       File entrada =  dir.openNextFile();
       if (!entrada)  break;   // No tenemos más archivos 
      
       if (!entrada.isDirectory())
       {
           Serial.print(i++);
           Serial.println(".- "+String(entrada.name()));
       }
       entrada.close();
    }

    dir.close();
    return (i-1);
}


/*******************************************************************************
 * EjecutaScript
 *     Ejecuta los comandos de Script.
 *******************************************************************************/
void EjecutaScript(String fichero) 
{
  File nFichero = SD.open(fichero,FILE_READ);
  char caracter;
  char comando[255];
  int i = 0;  // Indice del comando.
  
  if (nFichero)
  {
      Serial.println("Ejecutamos el fichero: "+fichero);
      while (nFichero.available())   //Mientras existan datos.
      {
         caracter = nFichero.read();
         digitalWrite(LED_INF, HIGH);
         
         if ((caracter == (13)) || (caracter == '\n')) // Fin de la linea
         {   
             comando[i] = '\x00'; // Ponemos el final.
             if (strlen(comando) > 0) 
             {
                 ProcesaComando(comando);
             }
             i=0;
         }
         else comando[i++] = caracter;
         digitalWrite(LED_INF, LOW);         
      }
      Serial.println(F("Fin ejecución Script\n"));
      nFichero.close();
  }
  else 
  {
    Serial.println(F("Error al abrir el archivo "));
    Serial.println(fichero);
  }
}

/**********************************************************************************
 * ProcesaComando(comando)  
 *        Ejecutamos el comando enviado.
 **********************************************************************************/
void ProcesaComando(char* comando)
{
  int cod_tecla;
     
  Serial.println("Ejecutamos: " + String(comando));
  digitalWrite(LED_INF, HIGH);

  // SUELTA Suelta todas las teclas, ideal combinación de teclas presionada
  if (Localiza(comando, "SUELTA")) 
  {
      Keyboard.releaseAll(); // Libera todas 
  }
  // CADENA <caracteres>  Enviamos una cadena de caracteres 
  if (Localiza(comando, "CADENA ")) 
  {
    Keyboard.print(comando + 7);
  }
  // PAUSA <msegundos>  Realizamos una pausa
  if (Localiza(comando, "PAUSA ")) 
  {
    delay(atoi(comando+6));
  }
  // ENTER   Envia ENTER
  if (Localiza(comando, "ENTER ")) 
  {
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
  }
  // CMD
  if (Localiza(comando, "CMD ")) 
  {
    Keyboard.println(comando + 4);
  }
  // KEY <codigo de tecla>  (Texto, o decinal ¿HEX 0x?) y se mantiene pulsada
  if (Localiza(comando, "KEY ")) 
  {
    cod_tecla = Decodifica(comando + 4);
    if (cod_tecla > 0) Keyboard.press(cod_tecla);
  }
  
  digitalWrite(LED_INF, LOW);
}

/*************************************************************************
 * int i Localiza(char* cadena, char const* objetivo)
 * 
 *        Devolvera true si el patron esta al principio de la cadena.
 *************************************************************************/
int Localiza(char* cadena, char const* objetivo) 
{
  int i=0;
  boolean j = true;
  for (i = 0; i < strlen(objetivo); i++) 
  {
    if (cadena[i] != objetivo[i]) 
    {
       j=false;
       
    }
  }
  return j;
}

/**************************************************************************
 * int Decodifica(string tecla) 
 *       Convertimos codigo de press.
 **************************************************************************/
int Decodifica(String tecla)
{
  int retorno = -1;
  if (tecla == "KEY_LEFT_CTRL") retorno = 0x80;
  if (tecla == "KEY_LEFT_SHIFT") retorno = 0x81;
  if (tecla == "KEY_LEFT_ALT") retorno = 0x82;
  if (tecla == "KEY_LEFT_GUI") retorno = 0x83;
  if (tecla == "KEY_RIGHT_CTRL") retorno = 0x84;
  if (tecla == "KEY_RIGHT_SHIFT") retorno = 0x85;
  if (tecla == "KEY_RIGHT_ALT") retorno = 0x86;
  if (tecla == "KEY_RIGHT_GUI") retorno = 0x87;
  if (tecla == "KEY_UP_ARROW") retorno = 0xDA;
  if (tecla == "KEY_DOWN_ARROW") retorno = 0xD9;
  if (tecla == "KEY_LEFT_ARROW") retorno = 0xD8;
  if (tecla == "KEY_RIGHT_ARROW") retorno = 0xD7;
  if (tecla == "KEY_BACKSPACE") retorno = 0xB2;
  if (tecla == "KEY_TAB") retorno = 0xB3;
  if (tecla == "KEY_RETURN") retorno = 0xB0;
  if (tecla == "KEY_ESC") retorno = 0xB1;
  if (tecla == "KEY_INSERT") retorno = 0xD1;
  if (tecla == "KEY_DELETE") retorno = 0xD4;
  if (tecla == "KEY_PAGE_UP") retorno = 0xD3;
  if (tecla == "KEY_PAGE_DOWN") retorno = 0xD6;
  if (tecla == "KEY_HOME") retorno = 0xD2;
  if (tecla == "KEY_END") retorno = 0xD5;
  if (tecla == "KEY_CAPS_LOCK") retorno = 0xC1;
  if (tecla == "KEY_F1") retorno = 0xC2;
  if (tecla == "KEY_F2") retorno = 0xC3;
  if (tecla == "KEY_F3") retorno = 0xC4;
  if (tecla == "KEY_F4") retorno = 0xC5;
  if (tecla == "KEY_F5") retorno = 0xC6;
  if (tecla == "KEY_F6") retorno = 0xC7;
  if (tecla == "KEY_F7") retorno = 0xC8;
  if (tecla == "KEY_F8") retorno = 0xC9;
  if (tecla == "KEY_F9") retorno = 0xCA;
  if (tecla == "KEY_F10") retorno = 0xCB;
  if (tecla == "KEY_F11") retorno = 0xCC;
  if (tecla == "KEY_F12") retorno = 0xCD;
  if (retorno == -1)  // No es simbolo, convertimos string
  {
      String cadena = String(tecla);
      retorno = cadena.toInt(); 
  }

  return retorno;
}
