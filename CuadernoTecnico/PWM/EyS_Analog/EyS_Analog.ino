/*  ----------------------------------------------------------------
Fco. Javier Rodriguez Navarro   www.pinguytaz.net

  
Probamos las entradas analogicas con potenciometros y la salida PWM con
un led RGB
      RGB conectado a PWM (11,10,9)
      Ptocenciometros RGB (A2,A1,A0)


DATOS ALMACENAMIENTO:  32.256 bytes. (Programa) 2.048 (Variables)
      Programa 5.454  bytes (16%)
      V. Globales 276 bytes (13%)
--------------------------------------------------------------------  
*/

const int Rojo = 11; // pin 6 PWM para el rojo
const int Verde = 10; // pin 5 PWM del verde
const int Azul = 9; // pin 3 PWM del azul
const int PRojo = A2;
const int PVerde = A1;
const int PAzul = A0;
int pulsador = 2; // pin 2 asignado al pulsado


void setup() 
{
  // Definimos Pines
  pinMode(Rojo, OUTPUT); 
  pinMode(Verde, OUTPUT);
  pinMode(Azul, OUTPUT);
  pinMode(pulsador, INPUT); // declara pulsador como entrada

  // Apagamos el LED
  analogWrite(Rojo,0);
  analogWrite(Verde,0);
  analogWrite(Azul,0);

  Serial.begin(9600);    // abre el Puerto serie y lanza los primeros envios
  Serial.println("------ INICIO E/S Analogica -----"); 
}

void loop() 
{
  int rojo, verde, azul;
  int a_rojo, a_verde, a_azul;

  if (digitalRead(pulsador) == HIGH)
  {
     rojo = analogRead(PRojo);
     verde = analogRead(PVerde);
     azul = analogRead(PAzul);

     // Escalamos con la funcion map a valores entre 0 y 255.
     a_rojo = map(rojo,0,1023,0,255);
     a_verde = map(verde,0,1023,0,255);
     a_azul = map(azul,0,1023,0,255);

     // Informamos de los cambios para trazar por el serie
     Serial.println("ROJO: "+String(rojo)+" A "+String(a_rojo));
     Serial.println("VERDE: "+String(verde)+" A "+String(a_verde));
     Serial.println("AZUL: "+String(azul)+" A "+String(a_azul));


     // Iluminamos el LED con los valores obtenidos
     analogWrite(Rojo,a_rojo);
     analogWrite(Verde,a_verde);
     analogWrite(Azul,a_azul);

     delay(500); // Dejamos tiempo para soltar el boton
  }
}
