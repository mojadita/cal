# makefile -- makefile para el programa cal.com
# Autor: Luis Colorado.
# Fecha: 15/1/90.
# $Log: makefile,v $
# Revision 1.4  2004/07/17 09:45:29  luis
# Cambiado makefile para soportar los targets clean e install.
#
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

TARGETS=cal es_ES.mo en_US.mo
INSTALLBIN=/usr/bin
INSTALLMO=/usr/share/locale
INSTALL=/usr/bin/install


all: $(TARGETS)

.SUFFIXES: .po .mo

cal_objs=cal.o bisiesto.o dia_sema.o siguient.o
cal: $(cal_objs)
	$(CC) $(CFLAGS) -o cal $(cal_objs)

.po.mo:
	msgfmt $< -o $@

#cal2: cal2.o bisiesto.o dia_sema.o siguient.o
#	$(CC) $(CFLAGS) -o cal2 cal2.o bisiesto.o dia_sema.o siguient.o

clean:
	$(RM) $(TARGETS) $(cal_objs)

install:
	$(INSTALL) --owner=bin --group=bin --mode=444 -D \
		es_ES.mo $(INSTALLMO)/es_ES/LC_MESSAGES/cal.mo
	$(INSTALL) --owner=bin --group=bin --mode=444 -D \
		en_US.mo $(INSTALLMO)/en_US/LC_MESSAGES/cal.mo
	$(INSTALL) --owner=bin --group=bin --mode=111 \
		cal $(INSTALLBIN)/cal

# fin de makefile.
