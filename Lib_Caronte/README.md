# Libreria Lib_Caronte
<img src=https://github.com/pinguytaz/Arduino/blob/master/Lib_Caronte/Img/Logo.png width="75" />

[![license](https://www.pinguytaz.net/IMG_GITHUB/gplv3-with-text-84x42.png)] (https://github.com/pinguytaz/Arduino/blob/master/LICENSE)


__Lib_Caronte__ es una libreria de código abierto con con protocolo de comunicación (LibCaronte) que facilite la comunicación entre deistintos dispositivos y canale, en un principio se genera para Arduino, C++(entorno Linux) y AppInventor y el canal de comunicación Bluetooh.
Los diversos canales de comunicación como RS232, I2C o Etehernet tendran cabida en esta libreria y solo nos preocuparemos de saber si emitimos/recibimos una cadena de caracteres, un número o un bloque de Bytes.


__¿Porque Lib_Caronte?__
La hemos llamado Caronte por el barquero encargado de guiar las almas, en nuestro caso nos ayudara a comunicar datos entre dispositivos de forma sencilla y comun.


__Prtocolo__
El protocolo de comunicación es muy sencillo y se conforma de paquetes con el siguiente formato:

             "#C<ID(3)><long(1)><Datos>"  Cabecera de 6 Bytes y los Datos

- Los dos primeros caracteres "#C" identifican que se trata de un paquete LibCaronte.
- Despues tendremos un indentificador del quien envia mensage de 3-bytes
- En tercer lugar tendra un bytes con el numero de datos a enviar
- Por ultimo los datos que se envian con un maximo de 255.


__Utilización__
Las funciones basicas para el uso del la libreria "LibCaronte" son las siguiente:
- Lo primero es crear nuestro objeto LibCaronte, y dependera del canal que se utilice, en este caso tenemos HC05_Caronte(Arduino con HC05) o BlueESP-Caronte(para el Bluetooth del ESP32) segun se añadan canales se definiran clases que heredaran de la clase padre Caronte con las funciones basicas de uso.
- Despues iniciamos el objeto con los parametros necesarios, y estos dependeran de cada una de las clases, así en HC05 especificamos los pines y por ejemplo para ESP32 solo el nombre del dispositivo Bluetooth.
- Desde este momento ya podremos utilizar los metodos comunes de uso:
    - get_ID()   Nos da nuestro ID.
    - T_paquete(String | char | int | float)  Transmite un paquete con el dato suministrado.
    - lee_ID(paq)  Nos da el ID del remitente del paquete.
    - S_paquete(paq), I_paquete(paq) o f_paquete(paq) nos da el datos del paquete.
    - paq es una estructura con los siguiente datos:
       - ID[3]
       - Tam   Tamaño del paquete.
       - Datos[]
     


Para un mejor uso se puede ver los ejemplos y un ejemplo de uso de esta libreria fuera de este repositorio es la **balanza de piezas** que se comunica con una aplicación por bluetooth con una aplicación movil (desarrollada en AppInventor)

__Website__: https://www.pinguytaz.net


