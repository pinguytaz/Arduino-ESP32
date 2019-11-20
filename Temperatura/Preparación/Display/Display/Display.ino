/********************************************************************************   
 * Fco. Javier Rodriguez Navarro   
 * https://www.pinguytaz.net
 *      
 * Display.ino: Programa ejemplo de uso de un display 16x2 compatible HD44780
 *                   
 * Historico:
 *       18 Nov 2019    V1: Creación para Displays  "Termometro Arduino" en www.pinguytaz.net
 * 
 * Librerias:
 *            LiquidCrystal
 *      
 * Conexionado:
 * LCD1 VSS GND
 * LCD2 VCC +5V
 * LCD3 Contraste a centro potenciometro 10K (extremos +5V y GND)
 * LCD4 RS pin pin 12
 * LCD5 R/W a masa solo escribiremos.
 * LCD6 Enable pin 11
 * LCD7-10 Bus datos D0-D3 8 Bits libres
 * LCD11-14 D4 pin 5 - D7 pin 3 
 * LCD15  LED+ a 5V con resistencia 220 Ohm.
 * LCD16 LED- a Masa
 *******************************************************************************/
#include <LiquidCrystal.h>

// Inicializamos la libreria con los pines
// (RS, EN, d4,d5,d6,d7)   Tambien tenemos constructor de 8Bits, y uso R/W hoy a masa es W
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() 
{
  // Definimos el tipo de LCD, 16 columnas y 2 filas
  lcd.begin(16, 2);
  lcd.print("pinguytaz.net");
}

void loop() 
{
  lcd.setCursor(0, 1); // Ponemos el cursos en la linea 1
  lcd.print("Display: ");
  lcd.setCursor(9, 1); 

  lcd.print((millis()/1000)); // Segundos desde el reset.
  lcd.print(" seg.");
  delay(1500);
}
