# Fuentes Cuaderno Tecnico

[![license](https://www.pinguytaz.net/IMG_GITHUB/gplv3-with-text-84x42.png)] (https://github.com/pinguytaz/Arduino/blob/master/LICENSE)
<BR><BR><BR>

Fuentes, esquemas, enlaces y extra del libro "__¿De 0 a 100 con Arduino y ESP32?__" proxima publicación y titulo proviisional, así como los ejercicios resueltos.  
<BR>

__Enlaces.txt__ 
    Este fichero contiene enlaces de interes para Arduino y ESP: Drivers, Tarjetas adicionales 
  

**/P_Basica**   
   Ejercicios resueltos de los capitulos inicialies de programación  
  
**/ES_Digitales**  
    Este directorio contiene los ejemplos de Entradas y Salidad Digitales.
 
 -   **ES_Digitales**: Ejemplo simple con un boton para ir conmutando los LEDs conectados a la salidas digitales del Arduino
    
 -  **Ej_DosLeds**: Ejemplo de codificación para ambas plataformas, con funciones de preprocesador.  
  
**/E_Analogicas**  
    Este directorio contiene los ejemplos de Entradas analogica  

 -   **SensorTMP36**: Ejemplo de entrada analogica con un sensor de temperatura TMP36.  
 
 -   **TMP36_Display**: Ejemplo anterior usando un display que se conecta por I2C.  
 

**/PWM**  
    Este directorio contiene los ejemplos de uso de PWM  

 -   **EyS_Analog**: Ejemplo que utiliza tres entradas analogicas para regular tres salidas PWM que regulan un LED RGB. Tambien se utiliza una entrada digital, con un botón para pasar los datos de los datos de las entradas analogiaca a sus correspondientes salidas PWM.  
  
  -   **Sonido**: Ejemplo de generación de notas con las intrucciones que tone y ledcWriteTone, para Arduino y ESP32 respectivamente.  
  
  -   **Musica**: Ejemplo interpretación de partituras, y función de unificación para ambos sistemas  


 **/Comunicaciones** 
  Este directorio contiene los ejemplos de comunicaciones: Serie, I2C, WIFI, Bluetooth, etc.  

-  **/EjSerie**: Ejemplo de comunicacion de un Arduino y un ESP32 por el puerto Serie, estan los dos programas  
  
    - "**Ej_SerieArduino**" Espera a recibir informacion ('P'= por el puerto serie para cambiar de color el LED. En este ejemplo podemos ver tambien el uso de PWM para el uso de LED RGBs.  
  
    - "**Ej_SerieESP32**" Espera que se pulse TOUCH para enviar una 'P' al arduino para que cambie el color del LED.  
  
- **/EjI2C**: Ejemplo de comunicacion de un Arduino y un ESP32 mediante I2C.  
  
    - "**Ej_I2CArduino**" Espera a que se pulse un boton para solicitar medida a ESP32, cuando llega se dibuja en el Display y se indorma al ESP32.  
  
    - "**Ej_I2CESP32**" Espera peticion del Arduino y espera que se le informe para cambiar color de LED.  
  
-  **ScanESP32**: Programa Scan I2C para el ESP32, usando TwoWire y configurando los pines.  
  
-  **/BLuetooth**: Ejemplos tratamiento Bluetooth.  
  
    - **ConfigurarHc05**: Nos permite configurar el modulo HC-05 mediante comandos AT.  
    - **BLEscanESP32**: Localiza dispositivos bluettoth-BLE al alcance.  
    - **/BLE**: Ejemplo de comunicacion de un Arduino y un ESP32 mediante I2C.  
      
       - **BLEservidorESP32**: Servidor con dos servicios y uno con caracteristicas de L/E y notificacion.  
       - **BLEclienteESP32**: Cliente que puede obtener datos de dos servidores BLEservidorESP32.  
  
- **/WIFI**: Ejemplos WIFI.  
    - **WIFI_AP** Ejemplo conexión como punto de acceso con un ESP32.  
    - **WIFI_Scan** Programa que realiza un escaneo de la red WIFI.  
    - **WIFI_HTTP** Ejemplo de realizar una solicitud GET y una solicitud POST con formato JSON.  
    - **WIFIServidorWEB** Ejemplo de un servidor WEB en nuestro ESP32 que nos permitira encender o apagar un LED y ademas informara del estado de este y el valor de un potenciometro que simulara ser un sensor de temperatura.  
    - **/WIFI_A_BBDD** Ejemplo de un servidor en python que recibe datos de un cliente ESP32 y los almacena en una BBDD.  
      
       - **Servidor**  Cliente Python que almacena los datos recibidos en una BBDD sqlite3 o en un fichero .CSV.  
       - **Cliente**  ESP32 que toma medidas y las envia a un servidor, en nuestro caso realizado en Python.  



**/Almacenamiento**  
    Este directorio contiene los ejemplos de almacenamiento de datos en dispositivos permanentes como puede ser una EEPROM  

-  **GrabaEEPROM y LeeEEPROM**: Dos simples programas para ver como se graba y leen datos de la EEPROM  

-  **GrabaDatos**: Un programa algo más completo de grabación de varios datos (configuraciones WIFI, etc) con sus funciones de escritura y lectura, para grabar datos comunes de configuración. Ejecutamos una vez el programa con nuestros datos de WIFI por ejemplo y luego solo tendremos que copiar la funcion lectura en nuestros programas de WIFI para disponer de los datos de nuestra red.  

-  **GPreferencias y L_Preferencias**: Ejemplo de uso para grabar datos con libreria Preference.h con dos espacios de nombre, para datos de WIFI y Varios.  

- **Particiones**: Visualizamos las particiones de nuestro dispositivo.  

-  **EjSPIFFS**: Ejemplo de uso del sistema de archivos SPIFFS, tanto en subidasubida de datos desde comandos como el uso de varias particiones SPIFFS.   

-  **EjSPIFFS_ST7735**: Ejemplo de uso del sistema de archivos SPIFFS, leyendo un fichero de texto y dibujos BMP que se visualizan en la pantalla, usando la libreria SPIFFS_ImageReader.  



**/Varios**  
    Este directorio contiene los ejemplos algo mas complejos, como uso display, motores, generar musica.  

- **MotorContinua**: Ejemplo del control de velocidad en un motor de continua con MOSFET (IRPF520) y utilizacion PWM en ESP32.  
-  **EjTouch**:  Ejemplo simple del uso del las entradas capacitativas del ESP32.  
- **InfoESP32**: Nos da información del ISP32, ID, MAC..  
- **Multitarea**: Esquema basico para utilizar los dos nucleos del ESP32.  
- **/Modos**  Este directorio contiene ejemplos de modo de funcionamiento del ESP32  
      -  **LigthSleep**: Ejemplo de sueño ligero que se activa por tiempo.  
      -  **DeepSleep**: Ejemplo de sueño profundo con activación por tiempo, TOUCH, GPIO  
- **EjWS2812B**: Ejemplo de uso de los leds RGB WS2812.  



<br><br><br>

__Website__: <https://www.pinguytaz.net>

