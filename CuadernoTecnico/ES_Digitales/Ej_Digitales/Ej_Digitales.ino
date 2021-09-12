/*  ----------------------------------------------------------------
Fco. Javier Rodriguez Navarro   www.pinguytaz.net

  
Probamos entradas digitales y salidas, con variables y bucles
y la consola serie que permite depurar entre otras cosas.


DATOS ALMACENAMIENTO:  32.256 bytes. (Programa) 2.048 (Variables)
      Programa 3.132  (9%)
      V. Globales 288 bytes  (14%)
--------------------------------------------------------------------  
*/

int pulsador = 2; // pin 2 asignado al pulsado
int ledAmarillo = 4; // pin 4 asignado para el LED amarillo
int ledVerde = 6; // pin 4 asignado para el LED verde
int ledNaranja = 8; // pin 6 asignado para el LED naranja
int ledAzul = 10; // pin 8 asignado para el LED azul
int ledRojo = 12; // pin 10 asignado para el LED rojo
int luce=0; // 0 ninguno,1 rojo,2 azul,3 naranja,4 verde,5 azul

void setup() 
{
  Serial.begin(9600);    // abre el Puerto serie y lanza los primeros envios
  Serial.println("-----------");  
  Serial.println("---- INICIO -------");  
  Serial.println("-----------");  

  // Definimos Pines
  pinMode(pulsador, INPUT); // declara pulsador como entrada
  pinMode(ledAmarillo, OUTPUT); // declara LED como salida  
  pinMode(ledVerde, OUTPUT); // declara LED como salida  
  pinMode(ledNaranja, OUTPUT); // declara LED como salida  
  pinMode(ledAzul, OUTPUT); // declara LED como salida
  pinMode(ledRojo, OUTPUT); // declara LED como salida 

  
  // Reinicia los LEDs.
  digitalWrite(ledAmarillo, HIGH);
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledNaranja, HIGH);
  digitalWrite(ledAzul, HIGH);
  digitalWrite(ledRojo, HIGH);
  delay(1000);
  digitalWrite(ledAmarillo, LOW);
  delay(500);
  digitalWrite(ledVerde, LOW);
  delay(500);
  digitalWrite(ledNaranja, LOW);
  delay(500);
  digitalWrite(ledAzul, LOW);
  delay(500);
  digitalWrite(ledRojo, LOW);
  delay(500);

}

void loop() 
{
   int val = 0;
   val =digitalRead(pulsador);

   if (val == HIGH)
   {
       Serial.print("Cambia a ");  
       cambia();
   }

}

/************************************************************
 * Enciendo todos y los apaga poco a poco, luego deja encendido
 * el siguiente.
 ************************************************************/
void cambia()
{
     luce++;
     if (luce > 5) luce = 1;

     // Primero encendemos y apagamos todas
     digitalWrite(ledAmarillo, HIGH);
     digitalWrite(ledVerde, HIGH);
     digitalWrite(ledNaranja, HIGH);
     digitalWrite(ledAzul, HIGH);
     digitalWrite(ledRojo, HIGH);
     delay(1000);
     digitalWrite(ledAmarillo, LOW);
     digitalWrite(ledVerde, LOW);
     digitalWrite(ledNaranja, LOW);
     digitalWrite(ledAzul, LOW);
     digitalWrite(ledRojo, LOW);
     delay(500);

     switch (luce) 
     {
       case 1: 
          digitalWrite(ledAmarillo, HIGH);
          Serial.println("Amarillo"); 
          break;
      case 2: 
          digitalWrite(ledVerde, HIGH);
          Serial.println("Verde"); 
          break;
      case 3: 
          digitalWrite(ledNaranja, HIGH);
          Serial.println("Naranja"); 
          break;
      case 4: 
          digitalWrite(ledAzul, HIGH);
          Serial.println("Azul"); 
          break;
      case 5: 
          digitalWrite(ledRojo, HIGH);
          Serial.println("Rojo"); 
          break;
     }
     
}


