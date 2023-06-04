/*  ----------------------------------------------------------------
Fco. Javier Rodriguez Navarro   www.pinguytaz.net

  
Podemos ver el comportamiento de las variables globales, locales y estaticas.

----------------------------------------------------------------*/
int a = 19;

void setup() 
{
  int a = 28;
  
  Serial.begin(9600);   // Inicializamos la consola a 9600 de velocidad.
  Serial.println("Valor de a en el setup: " + String(a) + " Vemos que es la local pues se ha declarado");
}

void loop() 
{
   static int b = 0;   // Tendremos un control de las veces que se ejecuta el loop
   int c = 33;     // 
   Serial.println("Valor de a: " + String(a++) + " Vemos que es la global pues no esta declarada en este bloque y se usa la global.");    // Este es el peligro de la globales a veces descontrol
   Serial.println("Valor de b: " + String(b++) + " Vemos que se va incrementando como la global pero solo la tocamos nosotros");    // Para contador mejor una estatica
   Serial.println("Valor de c: " + String(c++) + " Vemos que nunca aumenta ya que se inicializa cada vez que entra.");    

  delay(15000);  // Una pausa de 15 segundos.
}
