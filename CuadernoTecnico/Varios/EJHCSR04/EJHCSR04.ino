/*  ----------------------------------------------------------------
Fco. Javier Rodriguez Navarro   www.pinguytaz.net

  
Ejemplo Uso del sensor HC-SR04

----------------------------------------------------------------*/
// Definicion de pines
const int Trig = 10 ; // Lanza la señal SALIDA
const int Echo = 9; // Recibe el echo de la señal. ENTRADA


void setup()  
{
   Serial.begin(9600);
   pinMode(Trig,OUTPUT);
   pinMode(Echo,INPUT);
   digitalWrite(Trig,LOW); // Inicializamos 
}

void loop()  
{
   digitalWrite(Trig, HIGH);//envió del pulso de 10 microsegundos.
   delayMicroseconds(10);  
   digitalWrite(Trig, LOW);//Se espera recibir

    
   // Esperamos que nos llege
   long tiempo;
   long distancia;

    tiempo = pulseIn(Echo, HIGH); //Esperamos y cronometra, 0 es sin respuesta.
    distancia = tiempo/ 29 / 2;
    
    Serial.println("Tiempo: "+ String(tiempo) );
    Serial.println("Distancia: "+ String(distancia) + " cm");
    delay(1000);          //Hacemos una pausa de 100ms
   
}
