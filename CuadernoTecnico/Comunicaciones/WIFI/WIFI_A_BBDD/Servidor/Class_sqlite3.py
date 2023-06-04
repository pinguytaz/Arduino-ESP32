# -*- coding: utf-8 -*-
################################################################################
#  Fco. Javier Rodriguez Navarro 
#  https://www.pinguytaz.net
#
#  Servidor.py: Clase que hereda de Almacen y salva datos en BBDD SQLite3
#  Para crear la tabla necesaria
#    sqlite3 fichero.db 
#    'create table medidas(id INTEGER PRIMARY KEY ASC, fecha TEXT, hora TEXT,
#                          equipo INTEGER, medida INTEGER, valor TEXT)'
#  Historico:
#     - 26 Noviembre 2022    V1: Creación. 
#
#  Librerias
################################################################################
import Almacen
import sqlite3
from datetime import date
from datetime import datetime

class Class_sqlite3(Almacen.Almacen):
    bbdd = None

    def graba(self, tiempo, equ, med, val):
        fecha = str(tiempo.day) + "-" + str(tiempo.month) + "-" + str(tiempo.year)
        hora = str(tiempo.hour) + ":" + str(tiempo.minute) + ":" + str(tiempo.second)
        
        # Realizamos insercción del registro
        sentencia = "INSERT INTO medidas(fecha,hora,equipo,medida,valor) VALUES('" +fecha+"','"+hora+"',"+str(equ)+","+str(med)+",'"+val+"')"
        self.bbdd.execute(sentencia)
        self.bbdd.commit()

    def cierra(self):
        self.bbdd.close()

    def abrir(self):
        #Abrimos BBDD, esta debe tener la tabla medidas con la estructura correcta.
        self.bbdd = sqlite3.connect(self.fichero)
        
      
    

