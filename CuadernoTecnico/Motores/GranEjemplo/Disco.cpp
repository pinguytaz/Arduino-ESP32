#include "Disco.h"

Disco::Disco(char*montar)
{
    Serial.println("Constructor");
   if (!pdatos.begin(true,"/WEB",10,montar)) // Monta partición 
   {
     while(true);
   }
}

float Disco::cargaPagina(String pagina, char *texto)
{
  int i=0;
  File file = pdatos.open(pagina);
  if(!file)
  {
    return -1;
  }
    
  while(file.available())  texto[i++]=(char) file.read();
  texto[i]=0;  //Ponemos un fin para que pueda tratarse como String.
  file.close();

  return i;
}

void Disco::ficheros()
{
  File root = pdatos.open("/");
  if(!root)
   {
      Serial.println("Fallo al abrir el directorio");
      return ;
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
  root.close();
}


