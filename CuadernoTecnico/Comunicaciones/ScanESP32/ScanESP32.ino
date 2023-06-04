

#include <Wire.h>
#define I2C_Freq 100000

#define SDA_0 21
#define SCL_0 22
#define SDA_1 18
#define SCL_1 19

TwoWire I2C_0 = TwoWire(0);

void setup()
{
  Serial.begin (115200);  
  I2C_0.begin (SDA_0,SCL_0, I2C_Freq); 
}

void loop()
{
  byte error, direccion;
  
  Serial.println ("I2C scanner.  ...");
  byte dispositivos = 0;

  for ( direccion = 1; direccion < 127; direccion++)
  {
    I2C_0.beginTransmission (direccion);    
    error = I2C_0.endTransmission ();
    if( error == 0)  // OK, dispositivo encontrado
    {
      Serial.print ("Direccion encontrada: ");
      Serial.print (direccion, DEC);
      Serial.print (" (0x");
      Serial.print (direccion, HEX);     
      Serial.println (")");
      dispositivos++;
    }
    else if (error == 4)
    {
      Serial.print ("Error desconocido en : ");
      Serial.print (direccion, HEX);     
    }
  }
  Serial.print ("Encontrados ");      
  Serial.print (dispositivos, DEC);        // numbers of devices
  Serial.println (" dispositivo(s).");

  delay(1000);
}
