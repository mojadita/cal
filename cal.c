/* $Id: cal.c,v 1.6 2004/10/12 19:38:50 luis Exp $
 * cal.c -- programa para imprimir un calendario.
 * Autor: Luis Colorado.
 * Fecha: 15.1.90.
 * $Log: cal.c,v $
 * Revision 1.6  2004/10/12 19:38:50  luis
 * Modificado el estilo del programa.
 *
 * Revision 1.5  2003/04/21 22:21:06  luis
 * *** empty log message ***
 *
 * Revision 1.4  2003/04/21 20:51:48  luis
 * Añadido soporte internacional, para mostrar los mensajes y los meses y días
 * de la semana en el idioma local configurado.
 *
 * Revision 1.3  2000/07/17 00:27:52  luis
 * arreglos de formateo.
 *
 * Revision 1.2  1995/10/06 17:45:23  luis
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/30  00:21:46  luis
 * Initial revision
 *
 * 
 *     Descripción:
 *     ============
 *
 *     Este programa imprime un calendario del mes o del año indicados.
 *     Si el mes contiene el día de la fecha actual, éste se escribe entre
 *     corchetes.
 *
 *     Uso:
 *     ====
 *
 *     cal [año | mes] [mes | año]
 *
 *     El mes se reconoce por ser un número de 1 a 12 (así pues, no se
 *     podrá representar un año anterior al año 13) y el año por ser un
 *     número mayor que 12. Cuando no se especifica ningún parámetro, se
 *     asume por defecto el calendario del mes actual del año actual. Si
 *     solo se especifica el mes, se entiende el calendario del mes indi-
 *     cado en el año actual. Si solo se especifica el año, se entiende
 *     un calendario completo del año indicado. Si se especifican los dos,
 *     se entenderá un calendario del mes y año indicados, siempre y cuan-
 *     do uno sea mes y el otro año (en caso de que los dos sean meses o
 *     años, se considerar  solamente el último indicado). El calendario
 *     muestra la fecha actual encerrándola entre corchetes cuando el
 *     calendario es de un solo mes.
 *     El calendario tiene en cuenta la corrección realizada en 1752 para
 *     cambiar del calendario juliano (bisiestos cada cuatro años) al
 *     calendario gregoriano (bisiestos múltiplos de 4 menos múltiplos de
 *     100 menos múltiplos de 400) de eliminar los días 3 al 13 de septiembre
 *     de 1752. Probar "cal 1752" " "cal 9 1752".
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <libintl.h>
#include <time.h>

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
                	gettext("%s: incorrect 2nd. parameter."),
                	nomprog);
			puts("");
		    exit (1);
        } /* if */
        if (i > 12)
				anio = i;
        else
				mes = i;
    case 2:
        i = atoi (argv [1]);
        if (i <= 0){
            fprintf (stderr,
                	gettext("%s: incorrect 1st. parameter."),
                	nomprog);
			puts("");
            exit (1);
        } /* if */
        if (i > 12)
				anio = i;
        else
				mes = i;
    case 1: /* sin parametros */
        break;
    default:
        fprintf (stderr,
                 gettext("%s: incorrect number of parameters."),
                 nomprog);
		puts("");
        exit (1);
    } /* switch */

    /* programa principal */
	textdomain("cal");
    time (&hora);
	fecha_hoy = *localtime (&hora);
    if (!mes && anio) {
			formato_largo (anio);
	} else {
	    if (!mes)
				mes = fecha_hoy.tm_mon + 1;
        if (!anio)
				anio = fecha_hoy.tm_year + 1900;
        formato_corto (mes, anio);
    } /* if */
} /* main */

/* cadenas correspondientes a los nombres de los meses */
char *cad_meses [] =
       {"January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"};

char *cad_dias [] = {
	"Monday", "Tuesday", "Wednesday", "Thursday",
	"Friday", "Saturday", "Sunday"};

formato_largo (anio)
{
    int dia [3], desfase[3], mes [3], i, j, k, l;
	char cad [10];

	sprintf (cad, "%d", anio);
    printf ("\n\n");

	for (i = 0; i < 38 - strlen (cad) / 2; i++)
		printf (" ");

	printf ("%s\n", cad);

	for (i = 0; i < 38 - strlen (cad) / 2; i++)
		printf (" ");

	for (i = 0; i < strlen (cad); i++)
		printf ("=");

    printf ("\n----------------------------------"
        	"------------------------------------------\n");

    for (i = 0; i < 3; i++) {
        mes [i] = i;
        dia [i] = 1;
        desfase [i] = dia_1_mes (mes [i] + 1,anio);
    }
    for (i = 0; i < 4; i++) {
        /* imprimimos las tres cabeceras */
        printf ("\n");
        for (j = 0; j < 3; j++) {
	        int la, lb, lc;

		    lb = strlen (gettext(cad_meses [mes [j]]));
		    la = 10 - (lb >> 1);
		    lc = 20 - la - lb;
		    for (k = 0; k < la; k++) {
		    	printf (" ");
			} /* for */
		    printf ("%s", gettext(cad_meses [mes [j]]));
		    if (j != 2) {
			    for (k = 0; k < lc; k++) {
				    printf (" ");
				} /* for */
			    printf ("        ");
		    } /* if */
	    } /* for */
        printf ("\n");

        for (j = 0; j < 3; j++) {
	        int la, lb, lc;

		    lb = strlen (gettext(cad_meses [mes [j]]));
		    la = 10 - (lb >> 1);
		    lc = 20 - la - lb;
		    for (k = 0; k < la; k++)
		        printf (" ");
		    for (k = 0; k < lb; k++)
			    printf ("-");
		    if (j != 2) {
			    for (k = 0; k < lc; k++)
				    printf (" ");
			    printf ("        ");
		    } /* for */
	    } /* for */
	    printf ("\n");
		for (j = 0; j < 3; j++) {
			if (j) printf("        ");
			for (k = 0; k < 7; k++) {
				printf("%s%0.2s",
					k ? " " : "",
					gettext(cad_dias[k]));
			} /* for */
		} /* for */
		printf("\n");
        printf ("====================        "
            	"====================        "
            	"====================\n");
        for (j = 0; j < 6; j++){  /* fila */
            for (k = 0; k < 3; k++) {  /* mes */
                for (l = 0; l < 7; l++) { /* columna */
                    if (desfase [k]) {
                        desfase [k]--;
                        printf ("   ");
                    } else {
                        if (dia [k] == -1) {
                            printf ("   ");
						} else {
                            printf ("%2d ", dia [k]);
                                    dia [k] = siguiente (dia [k],
                              	    mes [k] + 1,
                              	    anio);
                        } /* if */
                    } /* if */
                } /* for */
                if (k != 2)
						printf ("       ");
            } /* for */
            printf ("\n");
        } /* for */
        for (j = 0; j < 3; j ++) {
            mes [j] += 3;
            dia [j] = 1;
            desfase [j] = dia_1_mes (mes [j] + 1, anio);
        } /* for */
    } /* for */
    printf ("--------------------------------------"
			"--------------------------------------\n");
} /* formato_largo */

formato_corto (mes, anio)
{

    int dia, desfase, i, j;
	int la, lb, lc;
	char cad_cab [100];

	sprintf (cad_cab,
		"%s %04d",
		gettext(cad_meses [mes-1]), anio);
	lb = strlen (cad_cab);
	la = 13 - (lb >> 1);
	for (i = 0; i < la; i++) printf (" ");
	printf ("%s\n", cad_cab);
	for (i = 0; i < la; i++) printf (" ");
	for (i = 0; i < lb; i++) printf ("-");
	printf ("\n");
	for (i = 0; i < 7; i++)
		printf("%s%0.3s", i ? " " : "", gettext(cad_dias[i]));
	printf("\n");
    printf ("===========================\n");
    dia = 1;
    desfase = dia_1_mes (mes, anio);
    for (i = 0;;i++) {
        int resaltado;

        if (desfase) {
            printf ("    ");
            desfase--;
        } else {
            resaltado = (anio == fecha_hoy.tm_year + 1900 &&
                          dia == fecha_hoy.tm_mday &&
                          mes == fecha_hoy.tm_mon + 1);
            if (resaltado)
					printf ("[%2d]", dia);
            else
					printf (" %2d ", dia);
            dia = siguiente (dia, mes, anio);
        } /* if */
        if (dia == -1) break;
        if (i % 7 == 6) printf ("\n");
    } /* for */
    printf ("\n");
} /* formato_corto */

/* $Id: cal.c,v 1.6 2004/10/12 19:38:50 luis Exp $ */
