# $Id$
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Fri Dec 16 00:30:07 EET 2016
# Copyright: (C) 2016 LUIS COLORADO.  All rights reserved.
#

package=cal
version=2.0

OS              != uname -o

prefix          ?= /usr/local
bindir          ?= $(prefix)/bin
localedir       ?=$(prefix)/share/locale

langs-FreeBSD   ?=en_GB en_GB.UTF-8 en_US es_ES.ISO-8859-1 es_ES.UTF-8 es_ES fi_FI fi_FI.UTF-8
langs-GNU/Linux ?=en_GB en_GB.UTF-8 en_US es_ES.ISO-8859-1 es_ES.UTF-8 es_ES fi_FI fi_FI.UTF-8

langs           ?= $(langs-$(OS))

targets         ?=cal $(langs:=.mo)


CFLAGS  += -I/usr/local/include \
		-DPACKAGE=\""$(package)"\" \
		-DVERSION=\""$(version)"\" \
		-DLOCALEDIR=\""$(localedir)"\"

LDFLAGS +=	-L/usr/local/lib

INSTALL ?= install
RM	    ?= rm -f
IFFLAGS ?= -m 444
IXFLAGS ?= -m 111
IDFLAGS ?= -m 755 -d

cal_libs-FreeBSD   ?= -lintl
cal_libs-GNU/Linux ?= 

cal_objs=cal.o weekday.o leap.o nextday.o
cal_libs= $(cal_libs-$(OS))

.PHONY: all clean install deinstall uninstall

all: $(targets)
clean:
	$(RM) $(targets) $(foreach i, $(targets), $($(i)_objs))
install: $(targets)
	$(INSTALL) $(IDFLAGS) $(localedir)
	$(INSTALL) $(IDFLAGS) $(bindir)
	$(INSTALL) $(IXFLAGS) cal $(bindir)
	-for l in $(langs); \
	do	echo INSTALL $${l}.mo "-->" $(localedir)/$${l}/LC_MESSAGES/$(package).mo; \
		$(INSTALL) $(IDFLAGS) $(localedir)/$${l}/LC_MESSAGES; \
		$(INSTALL) $(IFFLAGS) $${l}.mo $(localedir)/$${l}/LC_MESSAGES/$(package).mo; \
	done
deinstall uninstall:
	$(RM) $(bindir)/cal
	-@for l in $(langs); \
	do \
		echo $(RM) $(localedir)/$${l}/LC_MESSAGES/$(package).mo; \
		$(RM) $(localedir)/$${l}/LC_MESSAGES/$(package).mo; \
	done

cal: $(cal_objs)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $($@_objs) $($@_libs)

.SUFFIXES: .po .mo

.po.mo:
	msgfmt -o $@ $?

$(package).pot: $(cal_objs:.o=.c)
	xgettext -j -k_ -o $@ $(cal_objs:.o=.c)

$(langs:=.po): $(package).pot
	msgmerge -U $@ $?

.depend:
	$(CC) -MM $(cal_objs:.o=.c) >$@

-include .depend
