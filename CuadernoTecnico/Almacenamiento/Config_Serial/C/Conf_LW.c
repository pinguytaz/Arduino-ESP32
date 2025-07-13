/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejecutable de configuración por el puerto serie
 *               Programa en C preparado para plataforma Linux y Windows
 *               La version Windows con compilación cruzada de MinGW
 *               Formato del fichero:  lineas <R> <V> <A> <Comentario>
 *               se pasara por el puerto serie 
 *                 una linea con el número de lineas \n
 *                 lineas con <R> <V> <A>
 *
 **********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
// Definicion de Windows
#include <windows.h>
    #define SERIAL_TYPE HANDLE
    #define SERIAL_INVALID INVALID_HANDLE_VALUE
    #define SERIAL_SEND(fd, data, len) WriteFile(fd, data, len, &bytesWritten, NULL)
    #define SERIAL_RECV(fd, data, len) ReadFile(fd, data, len, &bytesRead, NULL)
#else
// Definicion de Linux
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
    #define SERIAL_TYPE int
    #define SERIAL_INVALID -1
    #define SERIAL_SEND(fd, data, len) write(fd, data, len)
    #define SERIAL_RECV(fd, data, len) read(fd, data, len)
#endif

// Variables globales para el descriptor y buffers de Windows
SERIAL_TYPE serialPort;
#ifdef _WIN32
DWORD bytesWritten, bytesRead;
#endif

// Prototipos de funciones, que nos permiten abrir o cerrar el puerto segun sea Linux o Windows
int aperturaPuerto(const char *puerto);
void cierrePuerto();

#define MAX_ESTADOS 50
typedef struct 
{
  int rojo;
  int verde;
  int azul;
} t_led;


int main(int argc, char *argv[]) 
{
    char linea[256]; 
    t_led estados[MAX_ESTADOS];
    int numEstados=0;

    if (argc < 3) 
    {
        printf("Uso: %s <puerto>\n", argv[0]);
        #ifdef _WIN32
        printf("Ejemplo Windows: %s COM3 <fichero Conf>\n", argv[0]);
        #else
        printf("Ejemplo Linux: %s /dev/ttyUSB0 <fichero Conf>\n", argv[0]);
        #endif

        return 1;
    }

    // Lo primero es leer el fichero de configuración y generar las lineas que se se enviaran
    // Formato de la line del fichero <R> <V> <A> <Comentario>
    // Solo se enviara los valores de rojo, verde y azul. Antes enviaremos el numLineas

    FILE *f = fopen(argv[2], "r");
    if (!f) 
    {
        perror("No se pudo abrir el fichero");
        return -1;
    }

    int i = 0;
    while (fgets(linea, sizeof(linea), f) && i < MAX_ESTADOS) 
    {
        int r, v, a;
        char comentario[256];

        // Leer los tres enteros y el comentario (puede tener espacios)
        int n = sscanf(linea, "%d %d %d %[^\n]", &r, &v, &a, comentario);
        if (n >= 4) 
        {
            //printf("Comentario: %s\n", comentario);
            estados[i].rojo = r;
            estados[i].verde = v;
            estados[i].azul = a;
            i++;
        } 
        else 
        {
            printf("Línea mal formada: %s", linea);
        }
    }
    fclose(f);
    numEstados = i;

    /*    Debug para ver que lee bien fichero
    for(int i=0;i<numEstados;i++)
    {
       printf("Linea %d: R:%d V:%d A:%d\n",i, estados[i].rojo,estados[i].verde,estados[i].azul);
    }
    printf("El total de lineas correctas %d\n",i+1);
    */

    // Iniciamos la comunicación
    if (aperturaPuerto(argv[1]) != 0) 
    {
        fprintf(stderr, "No se pudo abrir el puerto serie.\n");
        return 1;
    }

    char enviar = '#';
    char recibido = 0;

    printf("Enviamos #\n");
    SERIAL_SEND(serialPort, &enviar, 1);

    printf("Esperamos |\n");
    do 
    {
        SERIAL_RECV(serialPort, &recibido, 1);
        printf("Recibe %c\n",recibido);
    } while (recibido != '|');

    printf("Comenzamos la configuración de %d estados\n",numEstados);
    sprintf(linea, "%d\n",numEstados);
    SERIAL_SEND(serialPort, linea, strlen(linea));
    for(int i=0;i<numEstados;i++)
    {
       sprintf(linea, "%d %d %d\n",estados[i].rojo,estados[i].verde,estados[i].azul);
       printf("Enviamos %d: %s",i,linea);
       SERIAL_SEND(serialPort, linea, strlen(linea));
       #ifdef _WIN32
          Sleep(2000);
       #else
          sleep(2);
       #endif
    }

    cierrePuerto();

    printf("Terminada configuración reinicia arduino\n");
    return 0;
}

// --- Implementación de apertura y cierre multiplataforma ---
int aperturaPuerto(const char *puerto) 
{
#ifdef _WIN32
    char port_name[32];
    snprintf(port_name, sizeof(port_name), "\\\\.\\%s", puerto);

    serialPort = CreateFileA(port_name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (serialPort == INVALID_HANDLE_VALUE) 
    {
        printf("Error abriendo el puerto %s\n", puerto);
        return 1;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    GetCommState(serialPort, &dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    SetCommState(serialPort, &dcbSerialParams);

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(serialPort, &timeouts);

    Sleep(2000); // Esperar a que Arduino reinicie
#else
    serialPort = open(puerto, O_RDWR | O_NOCTTY);
    if (serialPort == -1) 
    {
        perror("No se pudo abrir el puerto serie");
        return 1;
    }

    sleep(5); // Esperar a que Arduino reinicie

    struct termios options;
    tcgetattr(serialPort, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    tcsetattr(serialPort, TCSANOW, &options);

    tcflush(serialPort, TCIOFLUSH);

#endif
    return 0;
}

void cierrePuerto() 
{
#ifdef _WIN32
    if (serialPort != INVALID_HANDLE_VALUE) 
    {
        CloseHandle(serialPort);
    }
#else
    if (serialPort != -1) 
    {
        close(serialPort);
    }
#endif
}

