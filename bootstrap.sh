# $Id: bootstrap.sh,v 1.1 2004/12/04 21:37:07 luis Exp $
# AUTHOR: Luis Colorado <luis.colorado@hispalinux.es>
# DATE: sáb dic  4 21:33:12 CET 2004

aclocal
libtoolize
automake --add-missing --foreign
autoconf

# $Id: bootstrap.sh,v 1.1 2004/12/04 21:37:07 luis Exp $
