# makefile -- makefile para el programa cal.com
# Autor: Luis Colorado.
# Fecha: 15/1/90.
# $Log: makefile,v $
# Revision 1.3  2003/04/21 21:03:16  luis
# Incluidas reglas en el makefile para soportar la construcción de los ficheros
# .mo
#
# Revision 1.2  2000/07/17 00:08:08  luis
# Cambio de las llamadas al compilador por sustituciones de variable en el
# Makefile.
#
# Revision 1.1  1995/09/30 00:30:17  luis
# Initial revision
#

all: cal es_ES.mo en_US.mo

.SUFFIXES: .po .mo

cal: cal.o bisiesto.o dia_sema.o siguient.o
	$(CC) $(CFLAGS) -o cal cal.o bisiesto.o dia_sema.o siguient.o

.po.mo:
	msgfmt $< -o $@

#cal2: cal2.o bisiesto.o dia_sema.o siguient.o
#	$(CC) $(CFLAGS) -o cal2 cal2.o bisiesto.o dia_sema.o siguient.o

# fin de makefile.
