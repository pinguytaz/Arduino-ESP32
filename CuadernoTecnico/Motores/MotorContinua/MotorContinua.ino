
/************************************************************************
 *    Fco. Javier Rodriguez Navarro   www.pinguytaz.net
 *    
 *    Ejemplo de movimiento de Motor continua con MOSFET y PWM.
 *    
 *************************************************************************/
#define MOTOR   3
#define VELOCIDAD A0

void setup()  // configuracion placa
{
   // También cambiaríamos la velocidad del puerto de consola segun plataforma
   pinMode(MOTOR, OUTPUT);
   
   Serial.begin(9600);
}

void loop()  //Se repite indefinidamente,
{
   int potenciometro, velocidad;

  Serial.println("Inicio Ejemplo de motor continua");
  
  // Leemos Potenciometro
  potenciometro = analogRead(VELOCIDAD);
  velocidad = map(potenciometro,0,1023,0,10);

  Serial.print("Leido: ");
  Serial.print(potenciometro);
  Serial.print(" velocidad: ");
  Serial.println(velocidad);

  // Ponemos la velocidad en el motor.
  analogWrite(MOTOR,velocidad*25);

  delay(1500);
}
