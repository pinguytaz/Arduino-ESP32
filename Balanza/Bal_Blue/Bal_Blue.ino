/*******************************************************************************************
 *  Autor: Fco. Javier Rodriguez Navarro
 *  WEB: www.pinguytaz.net
 *
 *  Descripción: Balanza de piezas con HX711 con comunicación Bluetooth a App-Movil
 *               La comunicacion de Bluetooth se realiza con la libreria Caronte.
 *               El Maestro sera nuestro movil con una aplicacion generada con AppInventor.
 *               La apliación se ha realizado para ser compatible con Arduino y ESP32
 *               
 *  Historico:
 *      Creación:  1.0 Abril 2021  FJRN
 *
 *  Librerias utilizadas:
 *       HX711.h:  Libreria HX711 de Bogdan Necula, para leer el ADC de 24-Bits que se conecta a la 
 *                 celula de carga. 
 *       Lib_Caronte: Libreria Caronte para la comunicación BlueTooth con la aplicación movil.
 *
 **************************************************************************************************/
//   Dejar la plataforma para la que va a ser utilizada la Balanza
//#define PLAT_ARDUINO
#define PLAT_ESP32

/***************************** Librerias, Pines y constantes  *************************/
#include <HX711.h>
#if defined(PLAT_ARDUINO)
  #include <HC05_Caronte.h>
#else
  #include <BlueESP_Caronte.h>
#endif

// Conexiones de la balanza al circuito HX711 y Bluetooth si procede
#if defined(PLAT_ARDUINO)
   #define  PIN_BT_TX 10
   #define  PIN_BT_RX 11
   #define  PIN_BT_KEY 9
   #define PIN_DT 3  // Conexion a DT del HX711
   #define PIN_SCK 2   // Conexion a SCK del HX711
#else
   #define PIN_DT  19  // Conexion a DT del HX711
   #define PIN_SCK  18   // Conexion a SCK del HX711
#endif

//#define escala_inicial  3092.f
#define escala_inicial  30340.f  // Escala para pesar CDs

#define tara_inicial  2


/********************* Declaración objetos ************************/
HX711 balanza;    // Definimos la Balanza

//  Definimos el canal de comunicacion, mediante Caronte (Bluetooth)
#if defined(PLAT_ARDUINO)
   HC05_Caronte BT("B1A");   // Definimos el canal Bluetooh 
#else
   BlueESP_Caronte BT("B1E");
#endif


void setup()
{
   String msg_conexion="";  

   //  Definimos la velocidad de nuestra consola, para Debug y configuramos canal. 
   #if defined(PLAT_ESP32)
      Serial.begin(115200);
      Serial.println("Ejecutando balanza en ESP32");
      BT.begin("ESP32Bal");  // Nombre Bluetooth que debemos parear en el movil
   #else
     Serial.begin(9600);
     BT.begin(PIN_BT_TX, PIN_BT_RX, PIN_BT_KEY);  // Tenemos configurado nuestro modulo HC05
     Serial.println("Ejecutando balanza en Arduino");
   #endif

   // Inicializamos la balanza Con datos iniciales, lo logico es tararla para el tipo de piezas
   balanza.begin(PIN_DT, PIN_SCK);
   balanza.set_scale(escala_inicial);    
   balanza.tare(tara_inicial);                

   // Esperamos a que se conecte el Maestro
   msg_conexion = msg_conexion + BT.escucha();
   Serial.println("Conectados a: "+msg_conexion);
   BT.T_paquete("Balanza a la escucha de sus ordenes");  // Enviamos mensage al Maestro de confirmación de conexión
}
  
void loop() 
{
   paquete paq;   // Donde nos llegaran los datos.
   String comando;
   int piezas;
   long lectura;
   String nombre_piezas;
   String msg="";

   if(BT.Paquete(paq))  // Miramos si datos de la aplicación movil.
   {
      comando = BT.S_paquete(paq);
      // Comando posibles Balanza(realiza peso) y Calibra(Realiza una calibración)
      if(comando=="Balanza") //  Realiza pesada de piezas
      {
         Serial.println("Se solicita realizar pesada");
         piezas = pesa();
         Serial.println("Se pesan: "+String(piezas));
         BT.T_paquete(piezas);
      }
      else if(comando=="Calibra") // Calibración y tara.
      {
         Serial.println("Se solicita calibrar la balanza");

         // Solicita al movil que informe de liberar la balanza
         BT.T_paquete("Libera");

         // Esperamos a que nos respondan que se ha liberado la balanza y que nos digan las piezas con y unidades de estas con las que se realiza la Tara.
         while (BT.disponibles() <=0) {delay(1000);} // Esperamos respuesta de bandeja limpia y unidades a poner.
         BT.Paquete(paq);  // Recoge piezas.
         piezas = BT.I_paquete(paq);  // Nos llega el numero de piezas a poner en la balanza para su Tara
         Serial.println("Piezas de calibracion"+String(piezas));
         
         while (BT.disponibles() <=0) {delay(1000);}// Esperamos el nombre de las unidades
         BT.Paquete(paq);    // Recogemos el nombre de las piezas
         nombre_piezas = BT.S_paquete(paq);  
         Serial.println("Nombre de las piezas "+String(nombre_piezas));

         // Tara a 0 ya que se ha debido liberar balanza
         balanza.set_scale(0);
         balanza.tare(2); 

         // Solicitamos que se coloquen las piezas
         msg=msg+String(piezas) + " de "+nombre_piezas;
         BT.T_paquete(msg);   // Envia descripción de lo que se debe colocar

         while (BT.disponibles() <=0) {delay(1000);} // Esperamos que se coloquen
         BT.Paquete(paq);  //Recogemos OK de colocadas
         nombre_piezas = BT.S_paquete(paq);
         Serial.println("Piezas puestas "+String(nombre_piezas));

         // Se calibra
         lectura=balanza.get_value(20);
         balanza.set_scale(lectura/piezas);
         Serial.println("La escala escrita es: "+String(lectura/piezas));

         BT.T_paquete("Echo");  //Enviamos confirmación de que se realizo el escalado..       
      }
      else Serial.println("Comando desconocido, no hacemos nada");
   }      
   delay(1000); // Una espera de 5 segundos.
}

/*************************************************************************************
 * int pesa()  Realiza una pesada de piezas y la retorna
 *************************************************************************************/
int pesa(void)
{
   int unidades=87;

   while(!balanza.is_ready());
   
   unidades = round(balanza.get_units(10));
   
   return unidades;
}
