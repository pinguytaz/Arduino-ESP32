# Libreria Lib_Caronte
[![license](https://www.pinguytaz.net/IMG_GITHUB/gplv3-with-text-84x42.png)]

<img src=https://github.com/pinguytaz/Arduino/blob/master/HMC5883L_3Axi/extras/Montaje.jpg width="200" />

__Lib_Caronte__ es una libreria de código abierto con con protocolo de comunicación (LibCaronte) que facilite la comunicación entre deistintos dispositivos y canale, en un principio se genera para Arduino, C++(entorno Linux) y AppInventor y el canal de comunicación Bluetooh.
Los diversos canales de comunicación como RS232, I2C o Etehernet tendran cabida en esta libreria y solo nos preocuparemos de saber si emitimos/recibimos una cadena de caracteres, un número o un bloque de Bytes.


__¿Porque Lib_Caronte?__
La hemos llamado Caronte por el barquero encargado de guiar las almas, en nuestro caso nos ayudara a comunicar datos entre dispositivos de forma sencilla y comun.


__Prtocolo__
El protocolo de comunicación es muy sencillo y se conforma de paquetes con el siguiente formato:
             "#C<ID><long><Datos>"
Los dos primeros caracteres "#C" identifican que se trata de un paquete LibCaronte.
Despues tendremos un 


ID(3)T(1)(Paquete de maximo 255 bytes)

ID: 3 Caracteres que identifican el dispositivo que envia 
T : 1 Byte que indica el tamaño del paquete


__Funciones__
Lib_Caronte(Serie,TX,RX,Baudios)
Lib_Caronte(Bluetooth,TX,RX,Baudios,Nombre,PIN,<M|E>)
Lib_Caronte(I2C)

R_Paquete()    Retorna una estructura con el paquete. Si ID="" no hay paquete.
T_Paquete(String)  Envia una cadena



__Website__: https://www.pinguytaz.net
   

