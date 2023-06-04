#! /bin/sh

BLOQUE=4096
PAGINA=256
directorio=./datos
imagen=Particion_datos.img
DIRECCION=0x100000
TAMANO=1048576

directorioWEB=./datosWEB
imagenWEB=Particion_datosWEB.img
DIRECCIONWEB=0x200000
TAMANOWEB=2031616

echo "Creamos imagen $imagen"
~/.arduino15/packages/esp32/tools/mkspiffs/0.2.3/mkspiffs -c $directorio -b $BLOQUE -p $PAGINA -s $TAMANO $imagen

echo "Creamos imagen $imagenWEB"
~/.arduino15/packages/esp32/tools/mkspiffs/0.2.3/mkspiffs -c $directorioWEB -b $BLOQUE -p $PAGINA -s $TAMANOWEB $imagenWEB

#Subimos imagenes al ESP32
echo "Sube imagen $imagen"
~/.arduino15/packages/esp32/tools/esptool_py/4.5.1/esptool.py --chip esp32 write_flash -z $DIRECCION $imagen

echo "Sube imagen $imagenWEB"
~/.arduino15/packages/esp32/tools/esptool_py/4.5.1/esptool.py --chip esp32 write_flash -z $DIRECCIONWEB $imagenWEB
~/.arduino15/packages/esp32/hardware/esp32/2.0.9/tools/gen_esp32part.py --verify Part2SPIF.csv Particiones.img


#Generamos particiones
#~/.arduino15/packages/esp32/hardware/esp32/2.0.9/tools/gen_esp32part.py Part2SPIF.csv Particiones.img
#~/.arduino15/packages/esp32/tools/esptool_py/4.5.1/esptool.py --chip esp32 write_flash 0x8000 Particiones.img


