//##############################################################################
// Variables Globales
int g_a=19;

void setup() 
{
   Serial.begin(9600);
   Serial.println("Se inicia el programa 1");
   delay(5000);
}

void loop() 
{
  int a=0;
  func();   // Sin retorno ni parametros
  Serial.println("En loop");

  delay(10000);

}

void func(void)
{
  Serial.println("En la funcion");
}
