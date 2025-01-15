#! /bin/sh

. $HOME/esp/esp-idf/export.sh
BLOQUE=4096
PAGINA=256
DIRECCION=0x9000
IMAGEN=nvs
#TAMANO=20480
TAMANO=24576

#Generamos las nvs con datos
python ~/esp/esp-idf/components/nvs_flash/nvs_partition_generator/nvs_partition_gen.py generate $IMAGEN.csv $IMAGEN.bin $TAMANO
esptool.py --chip esp32 write_flash -z $DIRECCION $IMAGEN.bin	
