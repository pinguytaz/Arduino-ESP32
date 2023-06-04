# -*- coding: utf-8 -*-
################################################################################
#  Fco. Javier Rodriguez Navarro 
#  https://www.pinguytaz.net
#
#  Servidor.py: Servidor que espera datos de medidas de dispositivos (ESP32, Arduino, etc) y
#               los almacena en CSV o almacena en Base de Datos SQLite3
#               Escucha en el puerto 2809, pero este podra cambiarse en código.
#
#  Historico:
#     - 26 Noviembre 2022    V1: Creación. 
#
################################################################################
import sys
import requests
import socket
from datetime import date
from datetime import datetime

# Clases heredadas de Almacen, que permiten almacenar los datos en un fichero CSV o una BBDD sqlite3
import Class_CSV
import Class_sqlite3
import Almacen

# Puerto por el que escucha.
PORT = 2809

#    Inicio programa
def main(argv):

    # Analisis y validación de los parametros que recibimos.
    # se esperan dos parametros.
    parametros = len(argv)-1
    if (parametros != 2): 
        print ("Uso: python %s [csv | sql] <fichero.csv o bbdd>" % argv[0])
        exit(-1)

    # El primer parametro indica el tipo de almacen csv o sql
    if (argv[1] != "csv" and argv[1] != "sql"):
        print ("Tipo de archivado csv(formato ;) o sql (Base de datos SQLite3")
        exit(-1)

    # Instanciamos una clase, con el nombre del fichero como parametro, segun el tipo de almacenamiento seleccionado como primer parametro.
    # Ambas clases heredan de almacen (abstracta) por eso el interfaz es igual en ambas y solo varia el como almacena.
    # el objeto por lo tanto queda almacenado en 'almacen'
    if (argv[1] == "csv"): almacen = Class_CSV.Class_CSV(argv[2])
    elif (argv[1] == "sql"): almacen = Class_sqlite3.Class_sqlite3(argv[2])

    # Abrimos el servidor para iniciar escucha.
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(('0.0.0.0', PORT))
    s.listen(0)  #Numero de conexiones entrantes que aceptamos.
        
    # Bucle infinito, aceptando conexiones, ya que acepta una y si es el formato esperado, almacena datos cierra y espera otra.
    while True:
        # Esperamos una conexión
        (cliente, direccion) = s.accept()
        print("Se conectan desde la direccion ",str(direccion[0]),":",str(direccion[1]))

        # Una vez que nos conectamos recibimos los datos enviados.
        data = cliente.recv(1024)
        print(data)

        # Validamos que es un mensaje de nuestro protocolo.
        if (data[0]== 35 and data[1]== 87):
            #Procedemos a su analisis #w<equipo><medida><long><valor>
            equipo = data[2]
            medida = data[3]
            longitud = data[4]
            #print("MSG del equipo",equipo,"y la medida",medida," con longitud del dato",longitud)
            valor = data[5:longitud+5].decode('UTF-8')
            #print("DATOS: ",valor)

            # Obtenemos datos del dia y hora que se garbaran en el almacen.
            actual = datetime.now()

            # llamamos al metodo de graba de Almacen (puede ser cvs o BBDD) con los datos a salvar.
            almacen.graba(actual,equipo,medida,valor)
        else:
            print("Paquete errorneo")
        
        #Cerramos conexión con el cliente una vez salvado los datos.
        cliente.close()

    # Se cierra el socket, y el almacen.
    # En teoria nunca llegara a esta parte salvo que crearamos un mensaje de cierre de servidor
    # Como es para una PoC (Prueba de concepto) no lo realizaremos es una mejora.
    s.close()
    almacen.close()


################# Lanzamiento de la funcion principal ##########################
if __name__ == "__main__":
    main(sys.argv)
