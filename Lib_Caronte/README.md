# Libreria Lib_Caronte
[![license](https://www.pinguytaz.net/IMG_GITHUB/gplv3-with-text-84x42.png)] (https://github.com/pinguytaz/Arduino/blob/master/LICENSE)

<img src=https://github.com/pinguytaz/Arduino/blob/master/Lib_Caronte/Img/Logo.png width="75" />

__Lib_Caronte__ es una libreria de código abierto con con protocolo de comunicación (LibCaronte) que facilite la comunicación entre deistintos dispositivos y canale, en un principio se genera para Arduino, C++(entorno Linux) y AppInventor y el canal de comunicación Bluetooh.
Los diversos canales de comunicación como RS232, I2C o Etehernet tendran cabida en esta libreria y solo nos preocuparemos de saber si emitimos/recibimos una cadena de caracteres, un número o un bloque de Bytes.


__¿Porque Lib_Caronte?__
La hemos llamado Caronte por el barquero encargado de guiar las almas, en nuestro caso nos ayudara a comunicar datos entre dispositivos de forma sencilla y comun.


__Prtocolo__
El protocolo de comunicación es muy sencillo y se conforma de paquetes con el siguiente formato:

             "#C<ID(3)><long(1)><Datos>"  Cabecera de 6 Bytes y los Datos

*Los dos primeros caracteres "#C" identifican que se trata de un paquete LibCaronte.
*Despues tendremos un indentificador del quien envia mensage de 3-bytes
*En tercer lugar tendra un bytes con el numero de datos a enviar
*Por ultimo los datos que se envian con un maximo de 255.


__Funciones__



__Website__: https://www.pinguytaz.net
   

