# -*- coding: utf-8 -*-
################################################################################
#  Fco. Javier Rodriguez Navarro 
#  https://www.pinguytaz.net
#
#  Servidor.py: Clase abstracta que almacena información, CSV o BBDD 
#               Esta clase no podra ser instanciada directamente
#
#  Historico:
#     - 26 Noviembre 2022    V1: Creación. 
#
#  Librerias
################################################################################
from abc import ABC
from abc import abstractmethod

class Almacen(ABC):
    # Constructor
    def __init__(self, fichero):
        self.fichero = fichero
        print("Se almacena en: %s" % self.fichero)
        self.abrir()

    # Metodos abstractos que deberemos definir en nuestras clases heredadas

    @abstractmethod
    def graba(self, tiempo, equ, med, val):
        pass

    @abstractmethod
    def abrir(self):
        pass

    @abstractmethod
    def cierra(self):
        pass
