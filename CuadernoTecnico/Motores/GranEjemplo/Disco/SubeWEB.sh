#! /bin/sh

. $HOME/esp/esp-idf/export.sh
BLOQUE=4096
PAGINA=256
directorio=./WEB
#DIRECCION=0x290000
DIRECCION=0x2f0000
IMAGEN=WEB
#TAMANO=1441792
TAMANO=1048576

#Generamos Subimos datos WEB
~/.arduino15/packages/esp32/tools/mkspiffs/0.2.3/mkspiffs -c $directorio -b $BLOQUE -p $PAGINA -s $TAMANO $IMAGEN.bin
esptool.py --chip esp32 write_flash -z $DIRECCION $IMAGEN.bin	
