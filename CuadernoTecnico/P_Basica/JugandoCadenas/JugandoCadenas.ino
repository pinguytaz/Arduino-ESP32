/*  ----------------------------------------------------------------
Fco. Javier Rodriguez Navarro   www.pinguytaz.net

  
Jugando con las cadenas de caracteres y arrays

----------------------------------------------------------------*/
void setup() 
{
  char Caracteres[5] = {'1','c','A','d','6'};
  String cadena = "1cAd6";

    
  Serial.begin(9600);   // Inicializamos la consola a 9600 de velocidad.

  // Podemos ver la diferencia de un caracter que el el nulo \0 que se añade en las cadenas.
  Serial.println("Tamaño de Caracteres: " + String(sizeof(Caracteres)));
  Serial.println("Tamaño de cadenas: " + String(sizeof(cadena)));

  }
} 
  

void loop() 
{
   
}
