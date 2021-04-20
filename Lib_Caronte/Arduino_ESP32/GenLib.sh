# Generamos libreria Arduino
cp library.properties.Arduino library.properties
rm Lib_Caronte.zip
zip -rv Lib_Caronte.zip examples src keyword.txt library.properties -x  ./src/BlueESP_Caronte.*

#  Generamos la de ESP32
cp library.properties.ESP32 library.properties
rm Lib_Caronte_ESP32.zip
zip -rv Lib_Caronte_ESP32.zip examples src keyword.txt library.properties -x ./src/HC05_Caronte.*
