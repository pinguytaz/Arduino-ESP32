# MiBADUSB
[![license](https://www.pinguytaz.net/IMG_GITHUB/gplv3-with-text-84x42.png)](https://github.com/pinguytaz/MiBADUSB/blob/master/LICENSE)
[![Plataforma](https://www.pinguytaz.net/IMG_GITHUB/Arduino_Placa.png)](https://arduino.cc)


__AVISO LEGAL Y RENUNCIA DE RESPONSABILIDADES__
MiBADUSB es un proyecto de código abierto con el unico fin de educación e investigación para desarrolladores de seguridad, y que pueda ayudar a crear contramedidas para las amenzas actuales.

El autor __NO asume ninguna responsabilidad__ por la forma en que elija utilizar cualquiera de los ejecutables/código fuente de cualquier archivo provistos. El autor y cualquier persona afiliada no serán responsables de ninguna pérdida o daño en relación con el uso de CUALQUIER archivo incluido en MiBADUSB. Al utilizar MiBADUSB o cualquier contenido incluido, usted ACEPTA USARLO BAJO SU PROPIO RIESGO. Una vez más, MiBADUSB y TODOS los archivos incluidos son SOLAMENTE para fines de EDUCACIÓN y/o INVESTIGACIÓN. MiBADUSB SOLO está destinada a ser utilizada en sus propios laboratorios de pruebas, o con el consentimiento explícito del propietario de la propiedad que se este probando.


##Acerca de MiBADUSB
Desarrollo para placa "BadUSB(DM3212) 
* ESP8266 Permite la disponibilidad de WIFI
* ATmega32u4 Micro de arduino leonardo que nos permite la gestion del teclado.

 MIBADUSB nos permite realizar pruebas de Pentesting, programando los script en un lenguaje similar al de Rubber Ducky.  
 En la version 2 se elimina menú y solo es ejecución, reduciendo el espacio para en un futuro programa WIFI y asi hacerlo interactivo.

##Compilación
   Deberemos tener instaladas las librerias: "Keyboard by Arduino" y "SD by Arduino, SparkFun".  
   Placa a Seleccionar "Arduino Leonardo"

##Uso
    MiBADUSB nos permite ejecutar Script de tecleo que se almacena en un fichero llamado EJECUTA.txt y se localiza en la tarjeta SD.  
Los comando disponibles son:
* SUELTA     		Libera todas las teclas  
* CADENA <cadena> 	Envia una cadena  
* PAUSA  <tiempo>  	Realizamos una pusa en milisegundos.  
* ENTER      		Enviamos un ENTER  
* CMD   			Se lanza un comando, este envia el ENTER para la ejecución.  

Si no se conoce comando es como si fuera un comentario.


## Enlaces de interes  
* https://github.com/TheMMcOfficial/CJMCU-3212-wifi_ducky  
* https://github.com/spacehuhn/wifi_ducky  
* https://github.com/exploitagency/ESPloitV2  
* https://github.com/joelsernamoreno/badusb_sd_wifi  

__Website__: https://www.pinguytaz.net
   
