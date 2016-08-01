package=cal
version=2.0
prefix=$(HOME)
bindir=$(prefix)/bin
localedir=$(prefix)/share/locale
langs=en_GB en_GB.UTF-8 en_US es_ES.ISO-8859-1 es_ES.UTF-8 fi_FI fi_FI.UTF-8
targets=cal $(langs:=.mo)

CFLAGS +=	-I/usr/local/include \
		-DPACKAGE=\""$(package)"\" \
		-DVERSION=\""$(version)"\" \
		-DLOCALEDIR=\""$(localedir)"\"
LDFLAGS +=	-L/usr/local/lib

INSTALL = install
RM	= rm -f
IFFLAGS = -m 444
IXFLAGS = -m 111
IDFLAGS = -m 755 -d

cal_objs=cal.o dia_sema.o bisiesto.o siguient.o
cal_libs=-lintl

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

cal: $(cal_objs)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $($@_objs) $($@_libs)

.SUFFIXES: .po .mo

.po.mo:
	msgfmt -o $@ $?

$(package).pot: $(cal_objs:.o=.c)
	xgettext -j -k_ -o $@ $(cal_objs:.o=.c)

$(langs:=.po): $(package).pot
	msgmerge -U $@ $?
