/*  ----------------------------------------------------------------
Fco. Javier Rodriguez Navarro   www.pinguytaz.net

  
Realizamos un problema basico de programación ya que se suele utilizar y es el cambio de variable.
para ello necesitaremos una variable auxiliar.
Si no comprendemos el funcionamiento del programa, toma un vaso con agua, otro con vino y uno vacio
y pasa el vino dondel el agua y el agua donde el vino

----------------------------------------------------------------*/

void setup() 
{
  int a = 28;
  int b = 9;
  int c;
  
  Serial.begin(9600);   // Inicializamos la consola a 9600 de velocidad.
  Serial.println("Cambio variable");
  Serial.println("Tamaño variable a: " + String(sizeof(a)));
  Serial.println("Tamaño variable b: " + String(sizeof(b)));
  
  // Estado inicial
  Serial.println("Valor de a: " + String(a));
  Serial.println("Valor de b: " + String(b));

  Serial.println("Cambio variable");
  c = a;    // Usamos una variable auxiliar
  a = b;    // Cambiamos b a la a
  b = c;    // Cambiamos la a a la b que temporalmente la dejamos en c
  Serial.println("Valor de a: " + String(a));
  Serial.println("Valor de b: " + String(b));
}

void loop() 
{
}
