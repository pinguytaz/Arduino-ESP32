/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo simple del uso de SPIFFS
 *               SPIFFS
 *  Librerias:   SPIFSS
 *  
 *  Cargas: Debemos cargar los ficherosTexto.txt
 ***********************************************************************************************/
#include "FS.h"
#include "SPIFFS.h"

void listDir(fs::FS &fs)
{
    Serial.printf("Contenido\n");

    File root = fs.open("/");
    if(!root)
    {
        Serial.println("Fallo al abrir el directorio");
        return;
    }
    
    File file = root.openNextFile();
    while(file)
    {
      Serial.print("  Fichero: ");
      Serial.print(file.name());
      Serial.print("\tTamaño: ");
      Serial.println(file.size());
      file = root.openNextFile();
    }
}

void leeFichero(fs::FS &fs, const char * fichero)
{
    File file = fs.open(fichero);
    if(!file)
    {
      Serial.printf("Fallo al abrie el fichero %s\n",fichero);
      return;
    }

    Serial.printf("Leemos %s\n",fichero);
    while(file.available()) Serial.write(file.read());
    
    file.close();
}

void setup() 
{
  Serial.begin(115200);
  fs::SPIFFSFS pdatos;
  fs::SPIFFSFS pdatosweb;

  // bool begin(bool formatOnFail=false, const char * basePath="/spiffs", uint8_t maxOpenFiles=10, const char * partitionLabel=NULL);
  if (!pdatos.begin(true,"/datos",10,"datos")) // Abre particion de datos
  {
     Serial.println("No se monta particion datos");
     return;
  }
  if (!pdatosweb.begin(true,"/datosweb",10,"datosWEB")) // Abre particion de datosWEB
  {
     Serial.println("No se monta particion datosWEB");
     return;
  }

  listDir(pdatos);
  leeFichero(pdatos,"/Texto.txt");
  listDir(pdatosweb);
  leeFichero(pdatosweb,"/Texto.txt");
}
void loop() 
{

}
