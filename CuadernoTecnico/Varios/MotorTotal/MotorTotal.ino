/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo total con placa L298
 *               El programa controla la velocidad y dirección del motor con un potenciometro
 *               mitad hacia una dirección la otra mitad al otro, ademas tiene un boton
 *               que indica si se para o pone en marcha.
 ***********************************************************************************************/
#define MINV 33

int ENA = 3;  // La potencia y activación se controla con ENAB por lo tanti quitar el Jumper de ENB.
// Control de la dirección 10 Alante, 01 Atras.
int IN1 = 4;  
int IN2 = 5;  
int BOTON = 8;

void setup() 
{
  Serial.begin(9600);
  pinMode(ENA, OUTPUT); 
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);  
  pinMode(BOTON, INPUT); 

  analogWrite(ENA,0);
}

void loop() 
{
  static bool estado=false;
  int velocidad ;
  
  int tempo =  analogRead(A1);
  //Serial.println("Leido: "+String(tempo));
  velocidad = map(tempo, 0,1023,-100,100);
  //Serial.println("Velocidad: "+String(velocidad));


  int boton = digitalRead(BOTON);
  //Serial.println(boton);
  if (boton )
  {
    //Serial.println("Cambio estado");
    estado = !estado;
    if(estado) {mueve(velocidad);}
    else { parar(); }
    delay(1000);
  }
  if (estado) mueve(velocidad);
  delay(50);
}

void parar() {analogWrite(ENA,0);}
void mueve(int velocidad)
{
    if (velocidad > 100 || velocidad < -100)  {return; } 
    // Ponemos la dirección
    if (velocidad < 0)
    {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      velocidad = velocidad * -1;
    }
    else
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
    velocidad = velocidad + MINV;
    analogWrite(ENA,velocidad);
}

