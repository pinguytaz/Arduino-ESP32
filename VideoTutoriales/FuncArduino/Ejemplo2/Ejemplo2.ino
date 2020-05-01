// Variables Globales
int g_a=19;

void setup() 
{
   Serial.begin(9600);
   Serial.println("Se inicia el programa 2");
}

void loop() 
{
  int a=0;

  Serial.print("Valor 'a' antes de funcion ");
  Serial.println(a);
  a = func();   // Con retorno.
  Serial.print("Valor 'a' Despues de funcion ");
  Serial.println(a);
  delay(10000);
}

int func(void)
{
  int z = 23;

  switch (z)
  {
     case 1:
        Serial.println("Envia 10");
        return 10;
     case 2:
        Serial.print("Envia ");
        Serial.println(z);
        return z;
  }
  
  Serial.println("No encontro coincidencia en switch, le envio 999");
  return 999;
}
