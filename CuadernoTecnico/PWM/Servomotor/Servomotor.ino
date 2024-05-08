/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo de programacion de un Servomotor
 *               Se ha utilizado el motor MG-996R (180º)
 *                  Voltaje:	 4,8V - 6V  (600 - 1550mA)
 *                  Torque: 	9Kg
 *                  Velocidad:	0,17s/60º
 *                  Periodo PWM	20ms (Cambio posi cada 20ms minimo)
 *                  Ancho banda muerta 5ms
 *  Librerias:   Servo.h
 *  
 ***********************************************************************************************/
 #include <Servo.h>
 
#define PINMOTOR  9
#define PINBOTON  2

// Declaramos la variable para controlar el servo
Servo servoMotor;
#define PERIODO  20

 
void setup() 
{
  Serial.begin(9600);
  pinMode(PINBOTON, INPUT); // declara pulsador como entrada

  Serial.println("Se inicia");
  Serial.println(digitalRead(PINBOTON));
  servoMotor.attach(PINMOTOR);
}
 
void loop() 
{
  bool val;
  static bool bantiguo = HIGH;
  static int estado=0;
  val =digitalRead(PINBOTON);

  if(bantiguo != val)  // Cambio de estado
  {
    bantiguo = val;
    realiza(estado++);
    delay(1500);   // Evita rebote
  }
  delay(50);
}

void realiza (int estado)
{
  Serial.print("Realiza el estado ");
  Serial.println(estado);
  if(estado == 0)
  {
    Serial.println("Se realiza secuencia de inicializacion dejando en 90");
    Serial.println("Posicionamos de 0 - 180");
    mueve(0,0);
    delay(1000);
    mueve(180,0);
    delay(1000);
    Serial.println("Posicionamos inicio 90 con moviiento");
    mueve(90,0);
  }
  if(estado == 1)
  {
    Serial.println("Secuencia de mover a 60 y despues a 90");
    mueve(45,2);
    delay(2000);
    mueve(150,1);
    delay(2000);
    mueve(35,5);
    delay(10000);
    mueve(90,4);
    delay(2000);
  }
}
void mueve(int angulo, int tiempo)
{
  float espera =0;
  int antiguo = servoMotor.read();
  int amover = abs(antiguo-angulo);

  Serial.println("Movemos desde el "+String(antiguo) +" al angulo "+String(angulo)+ " en "+String(tiempo));
  Serial.println(amover);

  if((tiempo*1000) - (amover*20) <= 0) // Maxima velocidad de giro.
  {
    Serial.print("Rapido "); 
    servoMotor.write(angulo);              
    delay(PERIODO);   // espera waits 15 ms para posicionar 
    return;
  } 
   
  if(antiguo < angulo)   // Avanza
  {
    Serial.print("Alante ");
    for (int pos = antiguo; pos <= angulo; pos += 1) 
    {
      servoMotor.write(pos);              
      delay(tiempo*1000 / amover);   // espera waits 15 ms para posicionar 
    } 
  }
  else
  {
    Serial.print("ATRAS ");
    for (int pos = antiguo; pos >= angulo; pos -= 1) 
    {
      servoMotor.write(pos);              
      delay(tiempo*1000 / amover);   // espera waits 15 ms para posicionar 
    }

   servoMotor.write(angulo);              
   delay(PERIODO);   // espera waits 15 ms para posicionar  
  }
  
  return;
}
