/* $Id: cal.c,v 1.3 2000/07/17 00:27:52 luis Exp $
 * cal.c -- programa para imprimir un calendario.
 * Autor: Luis Colorado.
 * Fecha: 15.1.90.
 * $Log: cal.c,v $
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
 *     Descripcion:
 *     ============
 *
 *     Este programa imprime un calendario del mes o del a$o indicados.
 *     Si el mes contiene el d!a de la fecha actual, este se escribe entre
 *     corchetes.
 *
 *     Uso:
 *     ====
 *
 *     cal [a$o | mes] [mes | a$o]
 *
 *     El mes se reconoce por ser un numero de 1 a 12 (asi pues, no se
 *     podra representar un a$o anterior al a$o 13) y el a$o por ser un
 *     numero mayor que 12. Cuando no se especifica ningun parametro, se
 *     asume por defecto el calendario del mes actual del a$o actual. Si
 *     solo se especifica el mes, se entiende el calendario del mes indi-
 *     cado en el a$o actual. Si solo se especifica el a$o, se entiende
 *     un calendario completo del a$o indicado. Si se especifican los dos,
 *     se entendera un calendario del mes y a$o indicados, siempre y cuan-
 *     do uno sea mes y el otro a$o (en caso de que los dos sean meses o
 *     a$os, se considerar  solamente el ultimo indicado). El calendario
 *     muestra la fecha actual encerrandola entre corchetes cuando el
 *     calendario es de un solo mes.
 *     El calendario tiene en cuenta la correccion realizada en 1752 para
 *     cambiar del calendario juliano (bisiestos cada cuatro a$os) al
 *     calendario gregoriano (bisiestos multiplos de 4 menos multiplos de
 *     100 menos multiplos de 400) de eliminar los dias 3 al 13 de septiembre
 *     de 1752. Probar "cal 1752" " "cal 9 1752".
 *
 */

#include <stdio.h>
#include <ctype.h>
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
                	"%s: 2do. parametro incorrecto.",
                	nomprog);
		    exit (1);
        }
        if (i > 12) anio = i;
        else mes = i;
    case 2:
        i = atoi (argv [1]);
        if (i <= 0){
            fprintf (stderr,
                	"%s: 1er. parametro incorrecto.",
                	nomprog);
            exit (1);
        }
        if (i > 12) anio = i;
             else mes = i;
    case 1: /* sin parametros */
        break;
    default:
        fprintf (stderr,
                 "%s: numero incorrecto de parametros",
                 nomprog);
        exit (1);
    }
    /* programa principal */
    time (&hora);
	fecha_hoy = *localtime (&hora);
    if (!mes && anio) formato_largo (anio);
    else {
	    if (!mes) mes = fecha_hoy.tm_mon + 1;
        if (!anio) anio = fecha_hoy.tm_year + 1900;
        formato_corto (mes, anio);
    }
} /* main */

/* cadenas correspondientes a los nombres de los meses */
char *cad_meses [] =
       {"Enero", "Febrero", "Marzo",
        "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre",
        "Octubre", "Noviembre", "Diciembre"};

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
		    lb = strlen (cad_meses [mes [j]]);
		    la = 10 - (lb >> 1);
		    lc = 20 - la - lb;
		    for (k = 0; k < la; k++)
		    	printf (" ");
		    printf ("%s", cad_meses [mes [j]]);
		    if (j != 2) {
			    for (k = 0; k < lc; k++)
				    printf (" ");
			    printf ("        ");
		    }
	    }
        printf ("\n");
        for (j = 0; j < 3; j++) {
	        int la, lb, lc;
		    lb = strlen (cad_meses [mes [j]]);
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
		    }
	    }
	    printf ("\n");
        printf ("Lu Ma Mi Ju Vi Sa Do        "
                "Lu Ma Mi Ju Vi Sa Do        "
            	"Lu Ma Mi Ju Vi Sa Do\n");
        printf ("====================        "
            	"====================        "
            	"====================\n");
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
                                    dia [k] = siguiente (dia [k],
                              	    mes [k] + 1,
                              	    anio);
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
    printf ("--------------------------------------------"
            "--------------------------------\n");
} /* formato_largo */

formato_corto (mes, anio)
{

    int dia, desfase, i, j;
	int la, lb, lc;
	char cad_cab [100];

	sprintf (cad_cab, "%s %04d", cad_meses [mes-1], anio);
	lb = strlen (cad_cab);
	la = 13 - (lb >> 1);
	for (i = 0; i < la; i++) printf (" ");
	printf ("%s\n", cad_cab);
	for (i = 0; i < la; i++) printf (" ");
	for (i = 0; i < lb; i++) printf ("-");
	printf ("\n");
    printf ("Lun Mar Mie Jue Vie Sab Dom\n");
    printf ("===========================\n");
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
            if (resaltado) printf ("[%2d]", dia);
            else printf (" %2d ", dia);
            dia = siguiente (dia, mes, anio);
        }
        if (dia == -1) break;
        if (i % 7 == 6) printf ("\n");
    }
    printf ("\n");
} /* formato_corto */

/* $Id: cal.c,v 1.3 2000/07/17 00:27:52 luis Exp $ */
