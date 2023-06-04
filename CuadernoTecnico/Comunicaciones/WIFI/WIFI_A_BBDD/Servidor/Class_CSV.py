# -*- coding: utf-8 -*-
################################################################################
#  Fco. Javier Rodriguez Navarro 
#  https://www.pinguytaz.net
#
#  Servidor.py: Clase que hereda de Almacen y salva datos en un fichero con formato CSV
#               Los campos se separan por ';' y este se podra abrir con un excell.
#               Formato: Fecha:Hora:Dispo:Medida:Dato
#  Historico:
#     - 26 Noviembre 2022    V1: Creación. 
#
#  Librerias
################################################################################
from datetime import date
from datetime import datetime
import Almacen

class Class_CSV(Almacen.Almacen):
     #Variables privadas de la clase
    fp = None

    def graba(self, tiempo, equ, med, val):
        fecha = str(tiempo.day) + "-" + str(tiempo.month) + "-" + str(tiempo.year)
        hora = str(tiempo.hour) + ":" + str(tiempo.minute) + ":" + str(tiempo.second)
        
        registro = fecha + ";" + hora + ";" + str(equ) + ";" + str(med) + ";" + val + "\n"
        #print(registro)
        
        self.fp.write(registro)

    def cierra(self):
        close(self.fp)
        
    def abrir(self):
        # Abre fichero en modo añadir
        self.fp = open(self.fichero,'a')


