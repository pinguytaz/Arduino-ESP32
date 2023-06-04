/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo de utilizacion de Touch
 **************************************************************************************************/
#define UMBRAL  20
#define PIN_TOUCH T3                

void setup() 
{
  Serial.begin(115200);  // Velocidad de visualización de la consola.
}

void loop() 
{
 
  if (pulsado(PIN_TOUCH)) Serial.println(":  Se ha tocado el cable");
  else Serial.println(":  No se esta tocando");
  
  delay(1000);
}

boolean pulsado(int Touch)
{
  boolean retorno = false;
  int valor = touchRead(Touch);
  Serial.print(valor);

  if (valor < UMBRAL ) retorno = true;

  return retorno;
}
