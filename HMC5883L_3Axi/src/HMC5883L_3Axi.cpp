/* *************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *  
 *  Descripción:Libreria HMC5883L
 *  
 *  Historico:
 *      Creación:  1/8/2015  FJRN
 *                 Feb2021 Correciion errores FJRN
 **************************************************/


#include "HMC5883L_3Axi.h"
#include "Arduino.h"
#include <Wire.h>


boolean HMC5883L_3Axi::inicializa()  
{
   byte IA,IB,IC;
   boolean retorno = true;

   // Tiempo de estabilización
   
   // Identificamos el dispositivo
   IA = lee(IdentificaA);
   IB = lee(IdentificaB);
   IC = lee(IdentificaC);
   if(IA != 72 | IB != 52 | IC != 51) retorno = false;

   setMuestras(HMC5883L_MUESTRA_1); // 1 muestras.
   setVelocidad(HMC5883L_15HZ);  // Ponemos 15Hz
   setMedicion(HMC5883L_FLUJO_NORMAL);  // Polaridad de medicion  
   setGanancia(GAN_1_3GA);  // Ganancia a 1
   setModo(HMC5883L_CONTINUA);  // Modo de medición en continua

   return retorno;
}


/******************************************************
 * setGanancia(int) : Pone las variables para programar la ganancia.
 *                    
 *  Parameto: un entero de 0 a 7 con el rango
 *    GN   Rango   Ganancia    Resolucion    
 *    0       0.88      1370        0.73 
(*    1       1.3       1090        0.92
 *    2       1.9        820        1.22
 *    3       2.5        660        1.52
 *    4       4.0        440        2.27
 *    5       4.7        390        2.56
 *    6       5.6        330        3.03
 *    7       8.1        230        4.35
 *    Se debe elejir un valor de ganancia menor(Mayor GN) cuando la fuerza total del campo provoca desbordamiento 
 *    en uno de los registros de salida de datos (saturación). 
 *    La primera medición después de un cambio de ganancia mantiene una ganancia igual a la configuración anterior,
 *    por lo tanto el valor correcto sera a partir de la segunda lectura.
 *    
 * retorna 0 si todo correcto o -1 si se da un parametro de entrada incorrecto
 */
int HMC5883L_3Axi::setGanancia(hmc5883l_ganancias ganancia)
{
  byte gain_reg; // Valor del registro a poner

  _GN=ganancia;
  
  switch (ganancia) 
  {
    case GAN_0_88GA:
       gain_reg = 0b00000000;
       _resolucion = 0.73;
       _ganancia = 1370;
      break;
   case GAN_1_3GA:
      gain_reg = 0b00100000;
      _resolucion= 0.92;
      _ganancia = 1090;
      break;
   case GAN_1_9GA:
      gain_reg = 0b01000000;
      _resolucion= 1.22;
      _ganancia = 820;
      break;
   case GAN_2_5GA:
      gain_reg = 0b01100000;
      _resolucion= 1.52;
      _ganancia = 660;
      break; 
    case GAN_4GA:
      gain_reg = 0b10000000;
      _resolucion= 2.27;
      _ganancia = 440;
      break;     
    case GAN_4_7GA:
      gain_reg = 0b10100000;
      _resolucion= 2.56;
      _ganancia = 390;
      break;     
    case GAN_5_6GA:
      gain_reg = 0b11000000;
      _resolucion= 3.03;
      _ganancia = 330;
      break;     
    case GAN_8_1GA:
      gain_reg = 0b11100000;
      _resolucion= 4.35;
      _ganancia = 230;
      break;     
    default: 
      return -1;
    break;
  }

  escribe(ConfiguracionRegistroB, gain_reg);   // Configuramos la ganancia en el dispositivo
  leedatos();  // Eliminamos la primera lectura que es con la ganancia anterior
  rangos();  // Calcula los rangos admitidos en esa ganancia

  return 0;
}

/******************************************************
 * setModo(int) : Pone el modo de operación
 *                    
 *  Parameto: un entero de 0 para continuo y 1 para simple
 *   *    
 * retorna 0 si todo correcto o -1 si se da un parametro de entrada incorrecto
 ******************************************************/
 int HMC5883L_3Axi::setModo(hmc5883l_modo tipo)
{
   _modolectura = tipo;
   byte dato;
   
   if (tipo==HMC5883L_CONTINUA) dato = 0b00000000;
   else if (tipo==HMC5883L_SIMPLE) dato = 0b00000001;
   else return -1;  // error en el parametro dado
   escribe(ModoRegistro, dato); 
}


/******************************************************
 * setVelocidad(int) : Velocidad de medicion para continuo
 ******************************************************/
int HMC5883L_3Axi::setVelocidad(hmc5883l_velocidad velocidad)
{
   _velocidad = velocidad;
   byte dato;
   switch (velocidad) {
   case HMC5883L_75HZ:
      _velo_mili = 1000/75;
      break;
   case HMC5883L_30HZ:
      _velo_mili = 1000/30;
      break;
   case HMC5883L_15HZ:
      _velo_mili = 1000/15;
      break;
   case HMC5883L_7_5HZ:
      _velo_mili = 1000/7.5;
      break;
   case HMC5883L_3HZ:
      _velo_mili = 1000/3;
      break;
   case HMC5883L_1_5HZ:
      _velo_mili = 1000/1.5;
      break;
   case HMC5883L_0_75_HZ:
      _velo_mili = 1000/0.75;
      break;
   default: 
      return -1;
    break;
   }

   _velo_mili += 1; // Un milisegundo de guarda

   // Primero leemos el contenido del registro a que es donde se grabaran los datos
   dato=lee(ConfiguracionRegistroA);
   dato &= 0b11100011; // Se mantienen los datos que no corresponden a DO2-DO0 Velocidad
   dato |= (velocidad << 2); // Con el dato de velocidad y dos bits movidos para posicionarlo.

   escribe(ConfiguracionRegistroA,dato);
}


/******************************************************
 * setMuestras(int) : Numero de muestras para obtener valor
 ******************************************************/
 int HMC5883L_3Axi::setMuestras(hmc5883l_muestras muestras)
{
   _muestras = muestras;
   byte dato;
   
   // Primero leemos el contenido del registro a que es donde se grabaran los datos
   dato=lee(ConfiguracionRegistroA);
   dato &= 0b10011111; // Se mantienen los datos que no corresponden a MA01-MA00 valor de muestras
   dato |= (muestras << 5) ;

   escribe(ConfiguracionRegistroA,dato);
}


/*******************************************************
 *  setMedicion(int) : Indica si el tipo de medición o si es un test (positivo o negativo
 *
 ******************************************************/
 int HMC5883L_3Axi::setMedicion(hmc5883l_medicion tipo)
 {
    
    _medicion = tipo;
    byte dato;
   
    // Primero leemos el contenido del registro a que es donde se grabaran los datos
    dato=lee(ConfiguracionRegistroA);
    dato &= 0b00000011; // Se mantienen los datos que no corresponden a MS01 - MS00 Flujo
    dato |= tipo;

    escribe(ConfiguracionRegistroA,dato);
}

/*******************************************************
 *  leedatos() : Lee las coordenadas X,Y,Z
 *
 * retorna -2 Error en la lectura
 ******************************************************/
 coordenadas HMC5883L_3Axi::leedatos(void)
 {
    coordenadas datos;
    byte DXRA, DXRB;
    byte DYRA, DYRB;
    byte DZRA, DZRB;
    int16_t tempo;
    float t1;

   // Si el modo de lectura es simple se envia modo ante de leer.
   if (_modolectura==HMC5883L_SIMPLE) setModo(HMC5883L_SIMPLE);

   // Nos posicionamos en el registro de datos
   Wire.beginTransmission(Direccion_HMC5883L);
   Wire.write(Datos);   // Nos posicionamos en el registro de datos
   Wire.endTransmission();
  
   Wire.beginTransmission(Direccion_HMC5883L);
   Wire.requestFrom(Direccion_HMC5883L,6);
   //delay(_velo_mili);
   while(Wire.available() < 6){};

   // Leemos X
   DXRA = Wire.read();
   DXRB = Wire.read();
   datos.datoX = (int16_t)DXRA << 8 | DXRB;
   datos.datoXN = datos.datoX * _resolucion;  // Normalizamos segun ganancia
   
   // Leemos Z
   DZRA = Wire.read();
   DZRB = Wire.read();
   datos.datoZ = DZRA << 8 | DZRB;
   datos.datoZN = datos.datoZ * _resolucion;

   // Leemos Y
   DYRA = Wire.read();
   DYRB = Wire.read();
   datos.datoY = DYRA << 8 | DYRB;
   datos.datoYN = datos.datoY * _resolucion;
   Wire.endTransmission();
  // delay(_velo_mili);

   // Colocamos el puntero en el primer registro si la lectura es continua
   if (_modolectura==HMC5883L_CONTINUA)
   {
      Wire.beginTransmission(Direccion_HMC5883L);
      Wire.endTransmission();
      delay(_velo_mili);
   }

   return datos;
 }

//    ******************  Privadas   **************

 /*******************************************************
 *  rangos() : Calcula los valores segun la ganacia
 *
 * retorna -1 si todo fue infroctuoso y sino el mejor GN que se a configurado
 ******************************************************/
 void HMC5883L_3Axi::rangos(void)
 {
    _min=243*(_ganancia/390);
    _max=575*(_ganancia/390);
 }


/******************************************************
 * escribe(int, byte) : Escribe un dato en un registro.
 *                    
 *  Parameto: Registro y dato a escribir.
 * 
 * 
 *****************************************************/
void HMC5883L_3Axi::escribe(int registro, byte dato)
{
   Wire.beginTransmission(Direccion_HMC5883L);
   Wire.write(registro);
   Wire.write(dato);
   Wire.endTransmission();
   delay(_velo_mili);
}

/******************************************************
 * byte lee(int) : Lee los datos de un registro
 *****************************************************/
byte HMC5883L_3Axi::lee(int registro)
{
   byte valor;
   // Nos posicionamos en el registro
   Wire.beginTransmission(Direccion_HMC5883L);
   Wire.write(registro);
   Wire.endTransmission(); 
   delay(_velo_mili);

   // Leemos datos del registro.
   Wire.beginTransmission(Direccion_HMC5883L);
   Wire.requestFrom(Direccion_HMC5883L,1);
   
   while(!Wire.available()) {};
   
   valor = Wire.read();

   Wire.endTransmission();
   delay(_velo_mili);
   return valor;
}
