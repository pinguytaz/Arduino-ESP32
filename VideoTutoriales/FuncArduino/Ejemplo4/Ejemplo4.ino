// Variables Globales
int g_a=19;

void setup() 
{
   Serial.begin(9600);
   Serial.println("Se inicia el programa 4");
}

void loop() 
{
  int a=0;
  int z=9;

  Serial.print("Valor 'a' antes de funcion ");
  Serial.println(a);
  
  z = func(20);   // Con retorno y envio funcion
  
  Serial.print("Valor 'a' Despues de funcion ");
  Serial.println(a);
  Serial.print("Valor 'z' Despues de funcion ");
  Serial.println(z);
  delay(10000);
}

int func(int a)
{
  switch (a)
  {
     case 1:
        Serial.println("Envia 10");
        return 10;
     case 2:
        Serial.print("Envia ");
        Serial.println(a);
        return a;
  }
  
  Serial.println("No encontro coincidencia en switch, le envio 999");
  return 999;
}
