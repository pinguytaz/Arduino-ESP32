/********************************************************************************   
 * Fco. Javier Rodriguez Navarro   
 * https://www.pinguytaz.net
 *      
 * E_Analogicas.ino: Programa ejemplo de uso de entradas analogicas.
 *                   Veremos por consola las variaciones de temperatura con TMP36
 *                   y las de un potenciometro.
 *                   
 * Historico:
 *       15 Nov 2019    V1: Creación para Entrada Analogicas  "Termometro Arduino" en www.pinguytaz.net
 * 
 * Librerias:
 * 
 *******************************************************************************/
// Definimos los nombres simbolicos de los pines
// Entradas analogicas
#define Sensor    A0
#define Potenciometro   A1


void setup() 
{
  Serial.begin(9600);   // Abrimos puerto para la consola.
  Serial.println("Iniciamos ejemplo E_Analogicas");
  Serial.println("******************************");
}

void loop() 
{
  int sondeo = 5;  // Tiempo de sondeo en segundos
  float valSensor, valPot;
  float volSensor, volPot;
  float temperatura;
  int tiempo;
  
  //valSensor= analogRead(Sensor);
  //valPot= analogRead(Potenciometro);
  //delay(100);

  // Sensor de Temperatura
  valSensor= analogRead(Sensor);
  Serial.print("Temperatura: ");
  Serial.print(valSensor);
  Serial.print(" , ");

  //volSensor = (valSensor/1024.0)*5.0;
  volSensor = (valSensor * 5.0)/1024.0;  // Seria conversion a voltios.
  //volSensor = valSensor*(5000/1024.0);  // Da milivoltios
  Serial.print(volSensor);
  Serial.print(" V, ");

  //temperatura = (volSensor - .5) *100;
  temperatura = (volSensor * 100) - 50;
  Serial.print(temperatura);
  Serial.println("ºC");
 
  
  // Potenciometro
  valPot= analogRead(Potenciometro);
  Serial.print("Potenciometro: ");
  Serial.print(valPot);
  Serial.print(" , ");
  
  volPot = (valPot*5.0)/1024.0;
  Serial.print(volPot);
  Serial.print(" V    ");

  tiempo=map(valPot,0,1023,1,10);   //Realiza una conversión para valor entre 1-10.
  Serial.print(tiempo);
  Serial.println(" ¿minuto 1-10?");


  Serial.println("******************************");
  Serial.println("");
 
  //Pausa de sondeo.
  delay(sondeo*1000);
}
