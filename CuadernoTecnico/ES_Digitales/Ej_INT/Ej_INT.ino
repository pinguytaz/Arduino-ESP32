/********************************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro                                                                *
 *  WEB: www.pinguytaz.net                                                                              *
 *       https://github.com/pinguytaz                                                                   *
 *                                                                                                      *
 *  Descripción: Ejemplo de desarrollo en Arduino de la ina ISR (Interruption Service Rutine)           *
 *               se describen en el capitulo 7.1.4                                                      *
 *               Este ejemplo pretender mostrar el uso interrupciones externas en lugar de estar        *
 *               mirando constantemente el valor del boton y cambiando el estado de la entrada          *
 *                                                                                                      *
 *  Historico:                                                                                          *
 *      Creación:  1.0 Enero 2025  FJRN                                                               *
 *                                                                                                      *
 ********************************************************************************************************/

// Variables que cambian en la funcion para indicar que existe un cambion, luego en loop otra vez false.
volatile bool cambio0=false;
volatile int contador=0;
volatile bool cambio1=false;

void setup()
{
   Serial.begin(9600);
   pinMode(2, INPUT_PULLUP);
   pinMode(3, INPUT_PULLUP);

   // Definimos las interrupciones con sus funciones CallBack
   attachInterrupt(digitalPinToInterrupt(2), funcionISR0, CHANGE);     // Se produce cuando existe un cambio.
   attachInterrupt(digitalPinToInterrupt(3), funcionISR1, CHANGE);     // Se produce cuando existe un cambio.
   
   Serial.println("******** Comenzamos el programa *******");
}

void loop()
{
   if(cambio0)  // Existe uncambio en el pin D2 por lo que leemos valor eimprimimos.
   {
       Serial.print("Cambio realizado en D2 a ");
       Serial.println(digitalRead(2));
       Serial.print("El contador en ");  // Nos marca cambios y rebotes.
       Serial.println(contador);
       contador=0;  // Serestablece a 0 y asi vemos cuantos cambios antes de realizar un ciclo de bucle.
       cambio0=false;
   }

   if(cambio1)  // Existe uncambio en el pin D3 por lo que leemos valor eimprimimos.
   {
       Serial.print("Cambio realizado en D3 a ");
       Serial.println(digitalRead(3));
       cambio1=false;
   }
   delay(10000);
}

//    Funcion de llamada de la interrupción 0 cuando se realice un cambio en la entrada D2
void funcionISR0()
{
    cambio0=true;
    contador++;    
}

//    Funcion de llamada de la interrupción 1 cuando se realice un cambio en D3
void funcionISR1()
{
    cambio1=true;
}
