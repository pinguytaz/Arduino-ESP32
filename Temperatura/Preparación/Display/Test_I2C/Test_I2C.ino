/********************************************************************************   
 * Fco. Javier Rodriguez Navarro   
 * https://www.pinguytaz.net
 *      
 * Test_I2C.ino: Scanea ID de I2C Display.
 *                   
 * Historico:
 *       19 Nov 2019    V1: Creación para Displays  "Termometro Arduino" en www.pinguytaz.net
 * 
 * Librerias:
 *            Wire.h
 *      
 * Conexionado conector I2C del LCD:
 * GND GND
 * Vcc +5V
 * SDA  PinSDA de Arduino (A4 en UNO) Datos Series.
 * SCL  PinSCL de Arduino (A5 en UNO) Reloj.
 *******************************************************************************/
#include <Wire.h>

void setup() 
{
  Serial.begin(9600); // Habilitamos para que la consola nos muestre el ID.
  Wire.begin();

  Serial.println("Localizando IDs de dispositivos I2C");
  Serial.println("***********************************"); 
}

void loop() 
{
  int count=1;
  byte direccion,error;
  
  for(byte direccion = 0;direccion<127; direccion++)
  {
    Wire.beginTransmission(direccion);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("Dispositivo ");
      Serial.print(count);
      Serial.print(" encontrado en: ");
      count++;
      Serial.print(direccion, DEC);
      Serial.print(" (0x");
      Serial.print(direccion, HEX);
      Serial.println(")");
      delay(10);
    }
    else if (error==4)
    {
      Serial.print("Errot desconocido en:");
      Serial.print(direccion, DEC);
      Serial.print(" (0x");
      Serial.print(direccion, HEX);
      Serial.println(")");
    }
  }
  Serial.println("*******FIN busqueda**************");  

  delay(5000);
}
