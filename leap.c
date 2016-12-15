/* $Id: leap.c,v 1.5 2004/10/12 19:39:31 luis Exp $
 * leap.c -- routine to check if a year is leap.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: 15/jan/1990.
 */

#include "leap.h"

int leap (int year)
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

/* $Id: leap.c,v 1.5 2004/10/12 19:39:31 luis Exp $ */
