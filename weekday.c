/* $Id: weekday.c,v 1.6 2015/06/14 21:44:37 luis Exp $
 * day_sema.c -- routines to calculate weekday.
 * Autor: Luis Colorado.
 * Fecha: 1990.01.15
 */

#include "leap.h"
#include "weekday.h"

int first_year_day(int year)
{

    int res;

     if (year <= 1752) {
        int g_4; /* grupos de cuatro años */

        year--;
        g_4 = year / 4;
        year %= 4;
        res = (g_4 * 5 + year + 6) % 7;
     } else {
        int g_100, g_4; /* grupos de cien años y de 4 resp. */

        year--;
        year %= 400;
        g_100 = year / 100;
        year %= 100;
        g_4 = year / 4;
        year %= 4;
        res = ((g_100 + g_4) * 5 + year + 1) % 7;
     } /* if */
     return res;
} /* first_year_day */

int first_month_day(int month, int year)
{
        static int days_month[12][3] = {
         /* normal, leap,    1752 */
            {0,      0,        0,}, /* ENERO */
            {3,      3,        3,}, /* FEBRERO */
            {3,      4,        4,}, /* MARZO */
            {6,      0,        0,}, /* ABRIL */
            {1,      2,        2,}, /* MAYO */
            {4,      5,        5,}, /* JUNIO */
            {6,      0,        0,}, /* JULIO */
            {2,      3,        3,}, /* AGOSTO */
            {5,      6,        6,}, /* SEPTIEMBRE */
            {0,      1,        4,}, /* OCTUBRE */
            {3,      4,        0,}, /* NOVIEMBRE */
            {5,      6,        2,}, /* DICIEMBRE */
        };
        month--;
        if (year == 1752)
           return (first_year_day(year) + days_month[month][2]) % 7;

        if (leap(year))
           return (first_year_day(year) + days_month[month][1]) % 7;
        return (first_year_day(year) + days_month[month][0]) % 7;
} /* first_month_day */

int week_day (int day, int month, int year)
{
      return (first_month_day(month, year) + day +
              (day > 2 && month == 9 && year == 1752 ? 2 : 6)
             ) % 7;
} /* week_day */

/* $Id: day_sema.c,v 1.6 2015/06/14 21:44:37 luis Exp $ */
