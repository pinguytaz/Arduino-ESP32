// Variables Globales
void setup() 
{
   Serial.begin(9600);
   Serial.println("Se inicia el programa 5 suma");
}

void loop() 
{
  int a=10;
  int b=9;
  int z;

  Serial.print("La variable a antes de la funcion es: ");
  Serial.println(a);
  z = suma(a,b);   // Con retorno y envio funcion
  Serial.print("La variable a despues de la funcion es: ");
  Serial.println(a);
  delay(10000);

  Serial.print("La suma es ");
  Serial.println(z);
  
  
}

int suma(int a, int b)
{
  return a+b;
}
