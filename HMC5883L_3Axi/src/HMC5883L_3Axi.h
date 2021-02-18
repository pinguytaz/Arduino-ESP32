/* *****************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *  
 *  Descripción: Fichero cabecera HMC5883L
 *  
 *  Historico:
 *      Creación:  1/8/2015  FJRN
 *                 Feb2021 Se corrigen errores y prepar para publicacion  FJRN
 ******************************************************************************/

#include "Arduino.h"

#ifndef HMC5883L_3Axi_H
#define HMC5883L_3Axi_H

//  Definiciones de constantes
  #define Direccion_HMC5883L 0x1E      // Dirección del dispositivo, segun Dataset no es posible modificarlo
  #define ConfiguracionRegistroA 0x00
  #define ConfiguracionRegistroB 0x01
  #define ModoRegistro 0x02
  #define Datos 0x03
  #define IdentificaA 0x0A
  #define IdentificaB 0x0B
  #define IdentificaC 0x0C

// Ganancias
typedef enum
{
    GAN_8_1GA     = 7,
    GAN_5_6GA     = 6,
    GAN_4_7GA     = 5,
    GAN_4GA       = 4,
    GAN_2_5GA     = 3,
    GAN_1_9GA     = 2,
    GAN_1_3GA     = 1,
    GAN_0_88GA    = 0
} hmc5883l_ganancias;

// Tipos de lectura
typedef enum
{
    HMC5883L_SIMPLE          = 1,
    HMC5883L_CONTINUA        = 0,
} hmc5883l_modo;

// Velocidad de lectura en continuo
typedef enum
{
    HMC5883L_75HZ       = 0b110,
    HMC5883L_30HZ       = 0b101,
    HMC5883L_15HZ       = 0b100,
    HMC5883L_7_5HZ      = 0b011,
    HMC5883L_3HZ        = 0b010,
    HMC5883L_1_5HZ      = 0b001,
    HMC5883L_0_75_HZ    = 0b000
} hmc5883l_velocidad;

// Numero de muestras
typedef enum
{
    HMC5883L_MUESTRA_8     = 0b11,
    HMC5883L_MUESTRA_4     = 0b10,
    HMC5883L_MUESTRA_2     = 0b01,
    HMC5883L_MUESTRA_1     = 0b00
} hmc5883l_muestras;

// Flujo de medicion
typedef enum
{
    HMC5883L_FLUJO_NEGATIVAL = 0b10,
    HMC5883L_FLUJO_POSITIVA  = 0b01,
    HMC5883L_FLUJO_NORMAL    = 0b00
} hmc5883l_medicion;


struct coordenadas
{
  float datoX;
  float datoY;
  float datoZ;
  float datoXN;
  float datoYN;
  float datoZN;
} ;

 class HMC5883L_3Axi
{
  public:
    boolean inicializa();
    int setGanancia(hmc5883l_ganancias ganancia);
    int setModo(hmc5883l_modo tipo);
    int setVelocidad(hmc5883l_velocidad);
    int setMuestras(hmc5883l_muestras);
    int setMedicion(hmc5883l_medicion tipo);
    
    coordenadas leedatos(void);
       
  private:
   hmc5883l_ganancias _GN;  // Ganancia configurada
   float _ganancia;
   float _resolucion;
   hmc5883l_velocidad _velocidad;
   float _velo_mili;
   hmc5883l_modo _modolectura;  //Modo lectura configurado
   hmc5883l_muestras _muestras;
   hmc5883l_medicion _medicion;
      
   int _min, _max;  // Rangos de valores que pueden recoger.
   
   void rangos(void);
   void escribe(int registro, byte dato);  // Escribe datos en un registro
   byte lee(int registro);   // Lee datos de un registro
    
};

#endif
