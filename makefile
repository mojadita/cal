# makefile -- makefile para el programa cal.com
# Autor: Luis Colorado.
# Fecha: 15/1/90.
# $Log: makefile,v $
# Revision 1.2  2000/07/17 00:08:08  luis
# Cambio de las llamadas al compilador por sustituciones de variable en el
# Makefile.
#
# Revision 1.1  1995/09/30 00:30:17  luis
# Initial revision
#

all: cal cal2

cal: cal.o bisiesto.o dia_sema.o siguient.o
	$(CC) $(CFLAGS) -o cal cal.o bisiesto.o dia_sema.o siguient.o

cal2: cal2.o bisiesto.o dia_sema.o siguient.o
	$(CC) $(CFLAGS) -o cal2 cal2.o bisiesto.o dia_sema.o siguient.o

# fin de makefile.
