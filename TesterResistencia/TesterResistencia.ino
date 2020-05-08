/********************************************************************************   
 * Fco. Javier Rodriguez Navarro   
 * https://www.pinguytaz.net
 *      
 * TesterResistencia.ino: Nos permite medir resistencias y visualizarla en 
 *                        un LCD.
 *                    
 * Historico:
 *       5 Mayo 2020    V1: Creación 
 * Librerias:
 * 
 *******************************************************************************/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4); // Poner la dirección localizada con el scaner I2C 

#define ESCALA 12
#define R2K 6
#define R20K 5
#define R200K 4
#define R1M 3
#define BORNA1 2   // Borna de resistencia a medir, pasa 5V
#define BORNA2 A0   // La otra borna que recoge media.

void setup() 
{
   
  // Para debugear
  Serial.begin(9600);
  Serial.println("Iniciamos programa");

  
  // Pines
  pinMode(ESCALA, INPUT);  // Boton de escala
  pinMode(R2K, INPUT);  // R. Escala 2k2 en principio luego cambia segun escala.
  pinMode(R20K, INPUT);  // R. Escala 22k en principio luego cambia segun escala. 
  pinMode(R200K, INPUT);  // R. Escala 220K en principio luego cambia segun escala.
  pinMode(R1M, INPUT);  // R. Escala 1M en principio luego cambia segun escala.

  pinMode(BORNA1, OUTPUT);  // Borna 5V resistencia a medir¡
  pinMode(BORNA2, INPUT);
  
  // DISPLAY
  formato();
  escala(); // Inicia escala y la imprime.  
}

void loop() 
{
  boolean estado = digitalRead(ESCALA);
  int medida = 0;
  float laescala = 0;
  float voltaje, valor;

  // Control si se pulsa el cambio de escala.
  if(estado)
  {
    while (digitalRead(ESCALA)) {;}
    escala();   // Cambia de escala
  }

  // Mira valor de resistencia
  medida = analogRead(BORNA2);  // Leemos valor
  
  // Conversion
  voltaje = (medida * 5.0) / 1024.0;
  
  //Realizamos la formula del divisor de tensión ((vi/vol)-1)*Esca
  laescala= R_escala();  // Nos da la resistencia de escala en Kohmios
  valor = ((5.0/voltaje)-1) * laescala; 
  
  imp_res(valor);  // Imprime en el Display valor segun escala.
  delay(50);
}

/**************************************************************************
* escala()  Realiza un cambio de escala y cambios de voltajes para 
*           este cambio de escala.
***************************************************************************/
void escala(void)
{
  int laescala;
  int escala;

  // Cambiamos de escala y recogemos resultado
  set_escala(true);
  escala = get_escala();


  lcd.setCursor(8, 2); 

  // Reinicia y baja salida
  digitalWrite(BORNA1,LOW);  //Cortamos
  pinMode(R2K,INPUT);
  pinMode(R20K,INPUT);
  pinMode(R200K,INPUT);
  pinMode(R1M,INPUT);
  
  switch (escala)
  {
    case 0: // 2K
       lcd.print("2K");
       lcd.write(244);  // Caracter de Ohmios
       laescala=R2K;   // Selecciona borna de escala a generar.
       break;
    case 1: // 20K
       lcd.print("20K");     
       lcd.write(244);  // Caracter de Ohmios
       laescala=R20K;   // Selecciona borna de escala a generar.
       break;
    case 2: // 200K
       lcd.print("200K");     
       lcd.write(244);  // Caracter de Ohmios
       laescala=R200K;   // Selecciona borna de escala a generar.
       break;
    case 3: // 1M
       lcd.print("1M");     
       lcd.write(244);  // Caracter de Ohmios
       laescala=R1M;   // Selecciona borna de escala a generar.
       break;
  }
  lcd.print("    ");

  // Se genera la tensión para poder medir la entrada de la borna2.
  digitalWrite(BORNA1,HIGH);
  pinMode(laescala,OUTPUT);  // activa el pin de escala a salida
  digitalWrite(laescala,LOW); // Da un 0 (masa)
}

/**************************************************************************
* set_escala(boolean)  Nos da el valor de la escala
*    Si esta en false no cambia de escala, si esta a true la cambia y retorna
*    por defecto es falso, solo deberia poner true la funcion escala.
******************************************************************************/
int set_escala(boolean cambia)
{
  static int escala = -1;  // El inicio.

  if (cambia)  // Se solicita el cambio de escala
  {
    escala++;
    if (escala > 3) escala = 0; // solo tenemos 0-3 de escalas
  }
  return escala;
}

int get_escala(void)
{
   return set_escala(false);
}

/**************************************************************************
* int R_escala()  Retorna la resistencia utilizada segun en la escala que 
*                 estemos, en Kohm.
***************************************************************************/
float R_escala(void)
{
  int escala = get_escala();  // Recogemos la escala.
  float resistencia = 0;
  switch (escala)
  {
    case 0: // 2K
       resistencia = 2;
       break;
    case 1: // 22K
       resistencia = 20;
       break;
    case 2: // 220K
       resistencia = 200;
       break;
    case 3: // 1M
       resistencia = 1000;
       break;
  }
  return resistencia;
}

/**************************************************************************
* imp_res(valor)  Imprime el valor de la resistencia en el display, se pasa
*                 en ohmios.
*/
void imp_res(float valor)
{
  int escala = get_escala();
  
  lcd.setCursor(13, 3); 
  lcd.print("         ");
  lcd.setCursor(13, 3); 

  if(escala==0) 
  {
    valor = valor*1000;
    if(valor < 1000) lcd.print(valor);
    else lcd.print("ERR");
  }
  else if(valor < 1000)
  {
     lcd.print(valor);
     lcd.print("K");
  }
  else
  { 
     if(escala==3) // Es la de Mega
     {
        lcd.print(valor/1000);
        lcd.print("M");
     }
     else lcd.print("ERR");
  }
  
  lcd.write(244);  // Caracter de Ohmios 
  
  delay(500); //Mantenemos un rato el numero, esto renlentiza la seleccion de escala.
}

/***********************************************************************
 * formato()  Imprime el formato fijo del display 
 */
void formato()
{
  lcd.backlight(); //Activar la retroiluminación.
  lcd.init();   // Iniciar el LCD para trabajar
  lcd.clear();
  lcd.print(" www.pinguytaz.net");
  lcd.setCursor(0, 2); 
  lcd.print("Escala: ");

  lcd.setCursor(0, 3); 
  lcd.print("Resistencia: "); 
}
