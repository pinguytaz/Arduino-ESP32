/********************************************************************************   
 * Fco. Javier Rodriguez Navarro   
 * https://www.pinguytaz.net
 *      
 * Display_I2C.ino: Ejemplo Display I2C(PCF8574.
 *                   
 * Historico:
 *       19 Nov 2019    V1: Creación para Displays  "Termometro Arduino" en www.pinguytaz.net
 * 
 * Librerias:
 *            
 * Conexionado conector I2C:
 * GND GND
 * Vcc +5V
 * SDAL PinSDA de Arduino (A4 en UNO) Datos Series.
 * SCL  PinSCL de Arduino (A5 en UNO) Reloj.
 *******************************************************************************/
#include <Wire.h>
//#include <LiquidCrystal_PCF8574.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4); // Poner la dirección localizada con el scaner I2C 

void setup() 
{
  lcd.backlight(); // Ponemos luz trasera
  lcd.init();
}

void loop() 
{
  lcd.clear();
  lcd.print(" www.pinguytaz.net");
  lcd.setCursor(0, 2); // Ponemos el cursos en la linea 1
  lcd.print("Display: ");
  lcd.setCursor(9, 2); 

  lcd.print((millis()/1000)); // Segundos desde el reset.
  lcd.print(" seg.");

  lcd.setCursor(0, 3); 
  lcd.print("Potenciometro: ");
  lcd.print(analogRead(A0));
  delay(1500);
}
