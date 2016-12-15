/* $Id: cal2.c,v 1.3 2003/04/21 20:51:48 luis Exp $
 * cal2.c -- Calendario en versión de colores.
 * Autor: Luis Colorado.
 * Fecha: 15/1/90.
 */

#include <stdio.h>
#include <ctype.h>
#include <time.h>

#include "nextday.h"
#include "leap.h"
#include "weekday.h"

char *nomprog;

struct tm fecha_hoy;
long hora;

main (argc, argv)
char *argv [];
{
        int mes = 0;
        int anio = 0;
        int i;

        nomprog = argv [0];
        switch (argc) {
        case 3:
             i = atoi (argv [2]);
             if (i <= 0) {
                fprintf (stderr,
					gettext("%s: 2do. parametro incorrecto."),
					nomprog);
                exit (1);
             }
             if (i > 12) anio = i;
             else mes = i;
        case 2:
             i = atoi (argv [1]);
             if (i <= 0){
                fprintf (stderr,
					gettext("%s: 1er. parametro incorrecto."),
					nomprog);
                exit (1);
             }
             if (i > 12) anio = i;
             else mes = i;
        case 1: /* sin par metros */
             break;
        default:
             fprintf (stderr,
                      gettext("%s: numero incorrecto de parametros"),
                      nomprog);
             exit (1);
        }
        /* programa principal */
        time (&hora);
	memcpy (&fecha_hoy, localtime (&hora), sizeof fecha_hoy);
        if (!mes && anio) formato_largo (anio);
        else {
             if (!mes) mes = fecha_hoy.tm_mon + 1;
             if (!anio) anio = fecha_hoy.tm_year + 1900;
             formato_corto (mes, anio);
        }
}

/* cadenas correspondientes a los nombres de los meses */
char *cad_meses [] =
       {"Ene", "Feb", "Mar",
        "Abr", "May", "Jun",
        "Jul", "Ago", "Sep",
        "Oct", "Nov", "Dic"};

formato_largo (anio)
{
        int dia [3], desfase[3], mes [3], i, j, k, l;

        printf ("\n\n");
        printf ("\033[1;33m                                    %04d\n", anio);
        printf ("\033[0;32m                                    ====\n");
        printf ("\033[0;31m----------------------------------------------------------------------------\n");
        for (i = 0; i < 3; i++) {
            mes [i] = i;
            dia [i] = 1;
            desfase [i] = dia_1_mes (mes [i] + 1,anio);
        }
        for (i = 0; i < 4; i++) {
            /* imprimimos las tres cabeceras */
            printf ("\n");
            printf ("\033[1;33m         %s                         %s                         %s\n",
                    cad_meses [mes [0]],
                    cad_meses [mes [1]],
                    cad_meses [mes [2]]);
            printf ("\033[1;32m         ---                         ---                         ---\n");
            printf ("\033[1;37m%s\n",
				gettext("Lu Ma Mi Ju Vi Sa Do        Lu Ma Mi Ju Vi Sa Do        Lu Ma Mi Ju Vi Sa Do"));
            printf ("\033[1;31m====================        ====================        ====================\n");
            printf ("\033[0;36m");
            for (j = 0; j < 6; j++){  /* fila */
                for (k = 0; k < 3; k++) {  /* mes */
                    for (l = 0; l < 7; l++) { /* columna */
                        if (desfase [k]) {
                           desfase [k]--;
                           printf ("   ");
                        }
                        else {
                           if (dia [k] == -1)
                              printf ("   ");
                           else {
                              printf ("%2d ", dia [k]);
                              dia [k] = siguiente (dia [k], mes [k] + 1, anio);
                           }
                        }
                    }
                    if (k != 2) printf ("       ");
                }
                printf ("\n");
            }
            for (j = 0; j < 3; j ++) {
                mes [j] += 3;
                dia [j] = 1;
                desfase [j] = dia_1_mes (mes [j] + 1, anio);
            }
        }
        printf ("\033[0;31m----------------------------------------------------------------------------\033[0m\n");
}

formato_corto (mes, anio)
{

        int dia, desfase, i, j;

        printf ("\033[1;33m         %s  %04d\n", gettext(cad_meses [mes-1]), anio);
        printf ("\033[1;32m         ---------\n");
        printf ("\033[1;37m%s\n", gettext("Lun Mar Mie Jue Vie Sab Dom"));
        printf ("\033[1;31m===========================\n");
        printf ("\033[1;36m");
        dia = 1;
        desfase = dia_1_mes (mes, anio);
        for (i = 0;;i++) {
              int resaltado;
              if (desfase) {
                 printf ("    ");
                 desfase--;
              }
              else {
                   resaltado = (anio == fecha_hoy.tm_year + 1900 &&
                                dia == fecha_hoy.tm_mday &&
                                mes == fecha_hoy.tm_mon + 1);
                   if (resaltado) printf ("\033[0;33m[\033[1;34m%2d\033[0;33m]\033[1;36m", dia);
                   else printf (" %2d ", dia);
                   dia = siguiente (dia, mes, anio);
              }
              if (dia == -1) break;
              if (i % 7 == 6) printf ("\n");
        }
        printf ("\033[0m\n");
}

/* $Id: cal2.c,v 1.3 2003/04/21 20:51:48 luis Exp $ */
