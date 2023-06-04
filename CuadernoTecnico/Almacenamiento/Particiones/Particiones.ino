#include "esp_partition.h"
#include "esp_log.h"

// Nombre del tipo
static const char* get_type_str(esp_partition_type_t type)
{
    switch(type) 
    {
        case ESP_PARTITION_TYPE_APP:    
            return "APP 0x00";
        case ESP_PARTITION_TYPE_DATA:
            return "DATA 0x01";
        case ESP_PARTITION_TYPE_ANY:
            return "Cualquier tipo 0xFF";
        default:
            return "Tipo desconocido"; // type not used in this example
    }
}

// Nombre del subtipo
String get_subtype_str(esp_partition_subtype_t subtype)
{
   switch(subtype) 
    {
      // Subtipo APP
      case ESP_PARTITION_SUBTYPE_APP_FACTORY:
            return "Fabrica 0x00";
      case ESP_PARTITION_SUBTYPE_APP_TEST:
            return "TEST 0x20";
      // Subtipos DATA
      case ESP_PARTITION_SUBTYPE_DATA_NVS:
            return "NVS 0x02";
      case ESP_PARTITION_SUBTYPE_DATA_NVS_KEYS:
            return "NVS_KEY 0x04";
      case ESP_PARTITION_SUBTYPE_DATA_EFUSE_EM:
            return "efuse 0x05";
      case ESP_PARTITION_SUBTYPE_DATA_PHY:
            return "PHY 0x01";
      case ESP_PARTITION_SUBTYPE_DATA_COREDUMP:
            return "Coredump 0x03";
      case ESP_PARTITION_SUBTYPE_DATA_UNDEFINED:
            return "No definida 0x06";
      case ESP_PARTITION_SUBTYPE_DATA_ESPHTTPD:
            return "ESPHTTPD 0x80";
      case ESP_PARTITION_SUBTYPE_DATA_FAT:
            return "FAT 0x81";
      case ESP_PARTITION_SUBTYPE_DATA_SPIFFS:
            return "Spiffs 0x82";
      case ESP_PARTITION_SUBTYPE_ANY:
            return "Cualquier tipo 0xFF";
      default:
           if((int) subtype >= ESP_PARTITION_SUBTYPE_APP_OTA_MIN && (int) subtype <= ESP_PARTITION_SUBTYPE_APP_OTA_MIN+16)
           {
              char tempo[20];
              sprintf(tempo,"OTA%d",(int) subtype -ESP_PARTITION_SUBTYPE_APP_OTA_MIN);
              return String(tempo) ;
           }
           else return "Subtipo desconocido"; 
    }
}

// Encontrar particiones
static void find_partition(esp_partition_type_t type, esp_partition_subtype_t subtype, const char* name)
{
    log_i("Localiza particion tipo %s, subtipo %s, etiqueta %s...", get_type_str(type), get_subtype_str(subtype), name == NULL ? "NULL (unspecified)" : name);
    const esp_partition_t * part  = esp_partition_find_first(type, subtype, name); 
    if (part != NULL) 
    {
       log_i("\tlocalizada etiqueta '%s' desplazamiento 0x%x con tamaño 0x%x", part->label, part->address, part->size); 
    }
    else 
    {
        log_i("\tParticion no encontrada");
    }
}

void setup() 
{
   Serial.begin(115200);
   
  /*
  log_i("Encontramos particiones");
  // Tipos DATA
  find_partition(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_OTA, NULL);
  find_partition(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, NULL);
  find_partition(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_FAT, NULL);
  find_partition(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_SPIFFS, NULL);

  // Tipos APP  
  find_partition(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_FACTORY, NULL);
  find_partition(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_OTA_0, NULL);
  find_partition(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_OTA_1, NULL);  // OTAs hasta 15
  find_partition(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_TEST, NULL);
  */


  // Imprimimos la tabla de particiones
  esp_partition_iterator_t it;
  Serial.println("Nombre\t\t\tTipo\t\t\tSubtipo\t\t\tDesplazamiento\t\tTamaño\tFlags");
  Serial.println("--------------------------------------------------------------------------------------------------------------------------------");
  it = esp_partition_find(ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, NULL);
  for (; it != NULL; it = esp_partition_next(it)) 
  {
     const esp_partition_t *part = esp_partition_get(it);
     Serial.printf("%-16s\t%-10s\t\t%-10s\t\t0x%-10x\t\t0x%-10x\t", part->label, get_type_str(part->type),get_subtype_str(part->subtype)
                                                     , part->address, part->size);
     if(part->encrypted) Serial.printf("Encriptada\n");
     else Serial.printf("No Encriptada\n");
  }
  esp_partition_iterator_release(it);

}

void loop() 
{

}
