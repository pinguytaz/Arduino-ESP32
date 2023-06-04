/*  ----------------------------------------------------------------
Fco. Javier Rodriguez Navarro   www.pinguytaz.net

  
Funcion de Tabla de multiplicar.
----------------------------------------------------------------*/

void setup() 
{
  Serial.begin(9600);
  tMultiplicar(4);
}

void loop() 
{
}

void tMultiplicar(int a)
{
  for(int i = 1; i<=10; i++)
  {
    Serial.println(String(a)+ "*" + String(i) + "=" + String(a*i));
  }
}