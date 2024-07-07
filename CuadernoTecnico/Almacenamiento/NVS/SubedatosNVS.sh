#! /bin/sh
# Nombre			Tipo			Subtipo			Desplazamiento		Tamaño	Flags
# --------------------------------------------------------------------------------------------------------------------------------
# nvs             	DATA 0x01 		NVS 0x02  		0x9000      		0x5000      	No Encriptada
# otadata         	DATA 0x01 		Fabrica 0x00		0xe000      		0x2000      	No Encriptada
# app0            	APP 0x00  		OTA0      		0x10000     		0x140000    	No Encriptada
# app1            	APP 0x00  		OTA1      		0x150000    		0x140000    	No Encriptada
# spiffs          	DATA 0x01 		Spiffs 0x82		0x290000    		0x160000    	No Encriptada
# coredump        	DATA 0x01 		Coredump 0x03		0x3f0000    		0x10000     	No Encriptad
#Laaplicacion se graba en app0

TAMANO=20480
CSV=Datos.csv
Particion=particion.bin
DIRECCION=0x9000

python ~/esp/esp-idf/components/nvs_flash/nvs_partition_generator/nvs_partition_gen.py generate $CSV $Particion $TAMANO
echo python ~/esp/esp-idf/components/esptool_py/esptool/esptool.py --chip esp32 write_flash -z $DIRECCION $Particion

