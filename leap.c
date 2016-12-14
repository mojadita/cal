/* $Id: bisiesto.c,v 1.5 2004/10/12 19:39:31 luis Exp $
 * bisiesto.c -- rutina para comprobar si un año es bisiesto.
 * Autor: Luis Colorado.
 * Fecha: 15/1/90.
 * $Log: bisiesto.c,v $
 */

#include "leap.h"

#define LEAP                          1
#define NORMAL                        0

int leap(int year)
{
     if (year < 1752) {
		if (year % 4 == 0) return LEAP;
		return NORMAL;
	 } /* if */
     if (year % 400 == 0) return LEAP;
     if (year % 100 == 0) return NORMAL;
     if (year % 4 == 0) return LEAP;
	 return NORMAL;
} /* leap */

/* $Id: bisiesto.c,v 1.5 2004/10/12 19:39:31 luis Exp $ */
