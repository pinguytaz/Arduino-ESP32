#ifndef CartesianoX_H
#define CartesianoX_H
#include <Arduino.h>

//#define RETARDO 50
typedef enum
{
   DRIVE_L298N = 0,
   DRIVE_POLOLU = 1
} Tipos_Driver;

typedef enum
{
   MPaP_ = 0,
} Error_CartesianoX;


class CartesianoX
{
  private:
    Tipos_Driver _driver;
    int _pasos;
    int _pps;
    long retardo;
    int secuencia;
    int xActual;
    
    // Datos para Pololu
    int _pin_paso;
    int _pin_dir;

    // Datos para L298 4 Hilos
    int _pin_M1;
    int _pin_M2; 
    int _pin_M3;
    int _pin_M4;
    int _pin_FinCarrera;
    int sec4[4][4] =  {{HIGH,HIGH,LOW,LOW}, {LOW,HIGH,HIGH,LOW}, {LOW,LOW,HIGH,HIGH}, {HIGH,LOW,LOW,HIGH}};
    
    void paso(void);

    public:
     CartesianoX(int, int, int);
     void Inicia(int ,int , int, int );
     void avanza(void);
     void retrocede(void);
     void irA(int);
     int get_X(void);
};

#endif