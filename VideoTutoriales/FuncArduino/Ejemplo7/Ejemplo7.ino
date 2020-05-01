/********************************************************************************   
 * Fco. Javier Rodriguez Navarro   
 * https://www.pinguytaz.net
 *      
 * Ejemplo7.ino: Este ejemplo nos permite explicar:
 *                    1.- No recoger parametro retornado o usarlo en if
 *                    2.- variables estaticas (static)
 *                    3.- Constantes y #define.
 *                    
 * Historico:
 *       1 Mayo 2020    V1: Creación para video clase funciones arduino
 * Librerias:
 * 
 *******************************************************************************/

//Definición de los pines
const int LED_R = 7;
const int LED_N = 4;
const int LED_V = 2;
#define PULSADOR 12


void setup() 
{
  // Configuramos pines
  pinMode(LED_R, OUTPUT);
  pinMode(LED_N, OUTPUT);
  pinMode(LED_V, OUTPUT);

  pinMode(PULSADOR, INPUT);

  // Definimos consola
  Serial.begin(9600);

  // Comprobamos conexión de Leds.
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_N, HIGH);
  digitalWrite(LED_V, HIGH);
  delay(500);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_N, LOW);
  digitalWrite(LED_V, LOW);
}


void loop() 
{
  boolean estado = digitalRead(PULSADOR);
  
  if (estado)
  {
    while (digitalRead(PULSADOR)) {;}// Espera a que soltemos boton.
    cambia();
    delay(50);  // Evita rebotes.
  }

  // led = 12;  // Explicacion de las esticas versus Globales
  //LED_R=9;  //Explicación error no constante y DEFINE
}

/********************************************************************************   
 * void cambia(void) Alterna led encendido, el primero en encenderse es el rojo.
 * *****************************************************************************/
int cambia()
{
  static int led=0;  //Mantendra estado, explicar static

  switch (led)
  {
    case 0: 
       digitalWrite(LED_R,HIGH);
       digitalWrite(LED_N,LOW);
       digitalWrite(LED_V,LOW);
       led++;
       break;
    case 1: 
       digitalWrite(LED_R,LOW);
       digitalWrite(LED_N,HIGH);
       digitalWrite(LED_V,LOW);
       led++;
       break;
    case 2: 
       digitalWrite(LED_R,LOW);
       digitalWrite(LED_N,LOW);
       digitalWrite(LED_V,HIGH);
       led=0;
       break;
    default:  // Seria un error ya que nunca deberia llegar aqui.
       digitalWrite(LED_R,HIGH);
       digitalWrite(LED_N,LOW);
       digitalWrite(LED_V,HIGH);
       led = 0;
  }
  return led;
}
