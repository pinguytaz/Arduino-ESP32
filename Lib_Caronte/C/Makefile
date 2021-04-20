#########################################
#  MakeFile Libreria Lib_Caronte y ejemplos.
##########################################

CC	=g++
C	=gcc
CCFLAGS	=-Wall -g -pedantic -Wno-write-strings
CFLAGS	=-Wall -g -pedantic

LIBDIR	=./lib
BINDIR	=./bin
SRCDIR	=./src
OBJDIR	=./obj

LIBS	=-L $(LIBDIR) -lCaronte 

all: Maestro Esclavo E_Inventor

E_Inventor: $(SRCDIR)/E_Inventor.cpp libCaronte
	$(CC) $(SRCDIR)/E_Inventor.cpp -o $(BINDIR)/E_Inventor.out $(CCFLAGS) $(LIBS) -I $(LIBDIR) -lbluetooth

Maestro: $(SRCDIR)/Maestro.cpp libCaronte
	$(CC) $(SRCDIR)/Maestro.cpp -o $(BINDIR)/Maestro.out $(CCFLAGS) $(LIBS) -I $(LIBDIR) -lbluetooth

Esclavo: $(SRCDIR)/Esclavo.cpp libCaronte
	$(CC) $(SRCDIR)/Esclavo.cpp -o $(BINDIR)/Esclavo.out $(CCFLAGS) $(LIBS) -I $(LIBDIR) -lbluetooth

libCaronte: Caronte Blue_Caronte Null_Caronte
	ar -crs $(LIBDIR)/libCaronte.a $(OBJDIR)/Caronte.o $(OBJDIR)/Blue_Caronte.o $(OBJDIR)/Null_Caronte.o
Caronte: $(SRCDIR)/Caronte.cpp
	$(CC) $(SRCDIR)/Caronte.cpp -c -o $(OBJDIR)/Caronte.o $(CCFLAGS) -I $(LIBDIR)

Null_Caronte: $(SRCDIR)/Null_Caronte.cpp
	$(CC) $(SRCDIR)/Null_Caronte.cpp -c -o $(OBJDIR)/Null_Caronte.o $(CCFLAGS) -I $(LIBDIR)

Blue_Caronte: $(SRCDIR)/Blue_Caronte.cpp
	$(CC) $(SRCDIR)/Blue_Caronte.cpp -c -o $(OBJDIR)/Blue_Caronte.o $(CCFLAGS) -I $(LIBDIR) -lbluetooth


Busca: $(SRCDIR)/Busca.c
	$(C) $(SRCDIR)/Busca.c -o $(BINDIR)/Busca.out $(CFLAGS) $(LIBS) -lbluetooth

clean:
	rm -rf $(OBJDIR)/*.o
	rm -rf $(LIBDIR)/*.a
	rm -rf $(BINDIR)/Maestro.out

