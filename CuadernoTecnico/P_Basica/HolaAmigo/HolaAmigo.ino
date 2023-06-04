/*  ----------------------------------------------------------------
Fco. Javier Rodriguez Navarro   www.pinguytaz.net

  
Mi primer programa 
    Imprime un saludo al principio y luego cada 15 segundo un estoy vivo.

----------------------------------------------------------------*/

void setup() 
{
  // Codigo de inicialización
  Serial.begin(9600);   // Inicializamos la consola a 9600 de velocidad.
  Serial.println("Hola amigo");

}

void loop() 
{
  // Se repita coninuamente
  unsigned long tiempo;
  delay(15000);
  tiempo = millis();
  Serial.print(tiempo/1000);
  Serial.println(" --> Estoy vivo han pasado 15 segundos");
}
