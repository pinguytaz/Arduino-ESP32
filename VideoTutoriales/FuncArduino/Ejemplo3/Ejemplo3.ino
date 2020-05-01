// Variables Globales
int g_a=19;

void setup() 
{
   Serial.begin(9600);
   Serial.println("Se inicia el programa 3");
}

void loop() 
{
  int a=0;

  Serial.print("Valor 'a' antes de funcion ");
  Serial.println(a);
  
  a = func();   // Con retorno y envio funcion
  
  Serial.print("Valor 'a' Despues de funcion ");
  Serial.println(a);
  delay(10000);
}

int func(void)
{
  int a= 23;
  
  Serial.print("Valor 'a' dentro de la funcion ");
  Serial.println(a);

  
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
