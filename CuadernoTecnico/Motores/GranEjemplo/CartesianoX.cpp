#include "CartesianoX.h"

CartesianoX::CartesianoX(int pasos, int pps, int pin_FinCarrera )
{
  _pasos = pasos;
  _pps = pps;
  retardo = 60L*1000L/920;
  _pin_FinCarrera = pin_FinCarrera;
}
void CartesianoX::Inicia(int pin_M1 ,int pin_M2, int pin_M3, int pin_M4)
{
  _driver = DRIVE_L298N;
  _pin_M1 = pin_M1;
  _pin_M2 = pin_M2; 
  _pin_M3 = pin_M3;
  _pin_M4 = pin_M4;
  secuencia = -1;
  
  pinMode(_pin_M1, OUTPUT);   
  pinMode(_pin_M2, OUTPUT);
  pinMode(_pin_M3, OUTPUT);
  pinMode(_pin_M4, OUTPUT);
  pinMode(_pin_FinCarrera, INPUT);

   // Nos colocamos en 0
  while (digitalRead(_pin_FinCarrera)) 
  {
    retrocede(); 
    delay(250);
  }
  xActual = 0;
}

void CartesianoX::avanza(void)
{
  if(++secuencia > 3) secuencia=0;
  paso();
  xActual++;
}

void CartesianoX::retrocede(void)
{
  if(--secuencia < 0 ) secuencia=3;
  paso();
  xActual--;
}

void CartesianoX::paso(void)
{
  switch(_driver) 
  {
    case DRIVE_L298N:
      // Motor Bibolar de 4 Hilos
      digitalWrite(_pin_M1, sec4[secuencia][0]); // Los pines se activan en secuencia
      digitalWrite(_pin_M2, sec4[secuencia][1]);
      digitalWrite(_pin_M3, sec4[secuencia][2]);
      digitalWrite(_pin_M4, sec4[secuencia][3]);    
      delay(retardo);
      digitalWrite(_pin_M1, LOW); // Ponemos en reposo las bobinas
      digitalWrite(_pin_M2, LOW);
      digitalWrite(_pin_M3, LOW);
      digitalWrite(_pin_M4, LOW);    
      delay(retardo);
      break;
    case DRIVE_POLOLU:
      Serial.println("No implementado Pololu");
      break;
  }
}
int CartesianoX::get_X(void ){ return xActual; }
void CartesianoX::irA(int x)
{
   Serial.println("Vamos de " + String(xActual) + " a "+String(x)) ;
   if (xActual == x) return;
   if (x > xActual) 
   {
      int golpes = x-xActual;
      for (int i =0; i< golpes ; i++) avanza();
   }
   else 
   {
      int golpes = xActual-x;
      for (int i =0; i < golpes; i++) retrocede();
   }
   xActual = x;
}
