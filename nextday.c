/* $Id: siguient.c,v 1.5 2015/06/14 21:01:22 luis Exp $
 * siguient.c -- routine to calculate next day to the one
 * provided.
 * Author: Luis Colorado.
 * Date: 1990.01.15
 */

#define       JAN        1
#define       FEB        2
#define       MAR        3
#define       APR        4
#define       MAY        5
#define       JUN        6
#define       JUL        7
#define       AUG        8
#define       SEP        9
#define       OCT       10
#define       NOV       11
#define       DEC       12


int next_day(int day, int month, int year)
{
    if (year < 1)
        return -1;

    /* la excepción */
    if (year == 1752 && month == 9 && day == 2)
            return 14;

    switch (month){
    case JAN: case MAR: case MAY: case JUL:
    case AUG: case OCT: case DEC:
         if (day < 1 || day >= 31)
                 return -1;
         return ++day;
    case APR: case JUN: case SEP: case NOV:
         if (day < 1 || day >= 30)
                 return -1;
         return ++day;
    case FEB:
         if (bisiesto (year)){
            if (day < 1 || day >= 29)
                    return -1;
         } /* if */
         else
            if (day < 1 || day >= 28)
                    return -1;
         return ++day;
    default:
         return -1;
    } /* switch */
} /* siguiente */

/* $Id: siguient.c,v 1.5 2015/06/14 21:01:22 luis Exp $ */
