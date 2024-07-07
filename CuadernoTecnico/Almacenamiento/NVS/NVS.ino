/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Ejemplo uso de NVS Preference.h cambiando los datos desde comando
 *
 * Los datos los añadimos en la partición NVS para que sean leido desde este programa
 * esto se realiza desde Subadatos.sh
 ***********************************************************************************************/
 /*   Codigo para borrado total de la particion NVS
  #include <nvs_flash.h>
  void setup() {
      nvs_flash_erase(); // Erase the NVS partition
      nvs_flash_init();     // Initialize the NVS partition
      while(true);
  }
  void loop() {}
*/

#include <Preferences.h>
Preferences D_DATOS;

void setup() 
{
  Serial.begin(115200);

   String campo1, campo2, autor;

   D_DATOS.begin("prueba", false);
   campo1 = D_DATOS.getString("Campo1","campo1 por defecto");
   campo2 =D_DATOS.getString("Campo2","campo2 por defecto");
   autor = D_DATOS.getString("Autor","autor por defecto");
   D_DATOS.end();

   Serial.println(campo1);
   Serial.println(campo2);
   Serial.println(autor);
}

void loop() {

}
