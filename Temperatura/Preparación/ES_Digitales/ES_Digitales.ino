/********************************************************************************   
 * Fco. Javier Rodriguez Navarro   
 * https://www.pinguytaz.net
 *      
 * ES_Digitales.ino: Programa ejemplo de uso de E/S Digitales.
 *                   Cuatro LEDs que se encienden según la combinación en la que se
 *                   pulsen los botones (Uno Rojo siempre encendido)
 * Historico:
 *       14 Nov 2019    V1: Creación para Entrada "Termometro Arduino" en www.pinguytaz.net
 * 
 * Librerias:
 * 
 *******************************************************************************/
// Definimos los nombres simbolicos de los pines
// Salidas digitales
#define LED_Rojo    2
#define LED_Verde   3
#define LED_Naranja 4
#define LED_Azul    5

// Entradas digitales
#define Boton_1     8
#define Boton_2     9


// Inicialización de pines y confirmación de LEDs.
void setup() 
{
  int leds[4] ={LED_Rojo, LED_Verde, LED_Naranja, LED_Azul};
  
  // Definimos los modos de los pines.
  pinMode(LED_Rojo, OUTPUT);
  pinMode(LED_Verde, OUTPUT);
  pinMode(LED_Naranja, OUTPUT);
  pinMode(LED_Azul, OUTPUT);
  pinMode(Boton_1, INPUT);
  pinMode(Boton_2, INPUT);

  // Encendemos y apagamos todos para confirmar funcionamiento
  digitalWrite(LED_Rojo,HIGH);
  digitalWrite(LED_Verde,HIGH);
  digitalWrite(LED_Naranja,HIGH);
  digitalWrite(LED_Azul,HIGH);
  delay(500);
  digitalWrite(LED_Rojo,LOW);
  digitalWrite(LED_Verde,LOW);
  digitalWrite(LED_Naranja,LOW);
  digitalWrite(LED_Azul,LOW);
  for (int i = 0;i<4; i = i +1)
  {
    digitalWrite(leds[i],HIGH);
    delay(500);
    digitalWrite(leds[i],LOW);
    delay(250);
  }
  digitalWrite(LED_Rojo,HIGH);
  
}

// Bucle infinito, que comprueba botones y enciende LEDs
void loop() 
{
  int valor=0;  // Por defecto todos apagado

  if (digitalRead(Boton_1)) valor = valor + 1;
  if (digitalRead(Boton_2)) valor = valor + 2;

  // Encendemos los leds (B1=Verde, B2=Naranga y B1B2=Azul)
  // Se utiliza una codificación binaria (1,2,3 y 0 ninguno)
  switch(valor)
  {
    case 0:
       digitalWrite(LED_Verde,LOW);
       digitalWrite(LED_Naranja,LOW);
       digitalWrite(LED_Azul,LOW);
       break;
    case 1:
       digitalWrite(LED_Verde,HIGH);
       digitalWrite(LED_Naranja,LOW);
       digitalWrite(LED_Azul,LOW);
       break;
    case 2:
       digitalWrite(LED_Verde,LOW);
       digitalWrite(LED_Naranja,HIGH);
       digitalWrite(LED_Azul,LOW);
       break;
    case 3:
       digitalWrite(LED_Verde,LOW);
       digitalWrite(LED_Naranja,LOW);
       digitalWrite(LED_Azul,HIGH);
       break;
  }
}
