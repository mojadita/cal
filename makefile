# makefile -- makefile para el programa cal.com
# Autor: Luis Colorado.
# Fecha: 15/1/90.
# $Log: makefile,v $
# Revision 1.1  1995/09/30 00:30:17  luis
# Initial revision
#

all: cal cal2

cal: cal.o bisiesto.o dia_sema.o siguient.o
	cc -O -o cal cal.o bisiesto.o dia_sema.o siguient.o

cal2: cal2.o bisiesto.o dia_sema.o siguient.o
	cc -O -o cal2 cal2.o bisiesto.o dia_sema.o siguient.o

# fin de makefile.
