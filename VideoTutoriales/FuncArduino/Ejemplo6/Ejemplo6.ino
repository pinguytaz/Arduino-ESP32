void setup() 
{
   Serial.begin(9600);
   Serial.println("Se inicia el programa 6 referencia");
}

void loop() 
{
  int a=10;
  int b=3;
  
  Serial.print("La variable a antes de la funcion es: ");
  Serial.println(a);
  Serial.print("La variable b antes de la funcion es: ");
  Serial.println(b);
  
  potencia(a,b);   
  
  Serial.print("La variable a despues de la funcion es: ");
  Serial.println(a);
  Serial.print("La variable b despues de la funcion es: ");
  Serial.println(b);
  
  delay(10000);

}

void potencia(int &a, int b)
{
  int z = a;
  for(int i = 1; i < b ; i++)
  {
     z = z * a;  
  }
  a=z;
  
}
