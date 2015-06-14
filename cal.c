/* $Id: cal.c,v 1.10 2015/06/14 21:50:28 luis Exp $
 * cal.c -- programa para imprimir un calendario.
 * Autor: Luis Colorado.
 * Fecha: 15.1.90.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <getopt.h>
#include <libintl.h>
#include <locale.h>
#include <time.h>

#define NMONTHS     12
#define NDAYS       7

#define WDTH        20

#define _(String) String

char *nomprog;
struct tm fecha_hoy;
long hora;
int fdow = 1;

char *cad_meses[] = {
    _("january"), _("february"), _("march"),
    _("april"), _("may"), _("june"),
    _("july"), _("august"), _("september"),
    _("october"), _("november"), _("december"),
};

char *cad_dias3[] = {
    _("sun"), _("mon"), _("tue"), _("wed"),
    _("thu"), _("fri"), _("sat"),
};

char *cad_dias2[] = {
    _("su"), _("mo"), _("tu"), _("we"),
    _("th"), _("fr"), _("sa"),
};

void formato_largo(int y);
void formato_corto(int y, int m);

size_t mbstrlen(char *s)
{
    size_t res = 0;
    size_t l = strlen(s);
    int n;
    while ((n = mblen(s, l)) > 0)
        res++, l -= n, s += n;
    return res;
} /* mbstrlen */

char *basename(char *s, char c)
{
    char *res = strrchr(s, c);
    if (res) res++;
    else res = s;
    return res;
} /* basename */

int main(int argc, char **argv)
{
    int m = 0, y = 0; 
    int i, opt;

    /* ADJUST LOCALE */
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

    /* GET PROGRAM NAME */
    nomprog = basename(argv[0], '/');

    /* PROCESS OPTIONS */
	while((opt=getopt(argc, argv, "V01234567")) != EOF) {
		switch(opt) {
		case 'V':
			printf("%s: %s="PACKAGE", %s="VERSION"\n", nomprog,
                    gettext("package"), gettext("version"));
			exit(0);
        case '0': case '1': case '2': case '3':
        case '4': case '5': case '6': case '7':
            fdow = (opt - '0') % 7;
            break;
		} /* switch */
	} /* while */

    /* ADJUST PARAMETER LIST */
    argc -= optind; argv += optind;

    /* PROCESS PARAMETERS */
    switch (argc) {
    default:
        fprintf(stderr,
                 "%s: %s\n",
                 nomprog,
                 gettext("incorrect number of parameters"));
        exit(1);

    case 2: /* TWO PARAMETERS */
        i = atoi(argv[1]);
        if (i < 0) {
            fprintf(stderr,
                    "%s: %s\n",
                    nomprog,
                    gettext("incorrect second parameter"));
		    exit(1);
        } /* if */
        if (i > 12) y = i;
        else m = i;
        /* NO BREAK HERE */
    case 1: /* ONE PARAMETER */
        i = atoi(argv [0]);
        if (i < 0){
            fprintf(stderr,
                	"%s: %s\n",
                	nomprog,
                    gettext("incorrect first parameter"));
            exit(1);
        } /* if */
        if (i > 12) y = i;
        else m = i;
        /* NO BREAK HERE */
    case 0: /* NO PARAMETERS */
        break;

    } /* switch */

    /* programa principal */
    time(&hora);
	fecha_hoy = *localtime(&hora);

    if (!m && y) {
			formato_largo(y);
	} else {
	    if (!m)
				m = fecha_hoy.tm_mon + 1;
        if (!y)
				y = fecha_hoy.tm_year + 1900;
        formato_corto(m, y);
    } /* if */
} /* main */

void formato_largo(int anio)
{
    int dia[3], desfase[3], mes[3], i, j, k, l;
    int hl[3], ml[3], tl[3];
	char cad [10];
    size_t n;

	n = sprintf(cad, "%d", anio);

    printf("\n\n%*s\n", 38 + n/2, cad);
    printf("%*.*s\n", 38 + n/2, n,
            "============");

    printf("\n--------------------------------------"
        	 "--------------------------------------\n");

    for (i = 0; i < 3; i++) {
        mes[i] = i;
        dia[i] = 1;
        desfase[i] = (dia_1_mes(mes [i] + 1, anio) - fdow + 7)%7;
    } /* for */

    for (i = 0; i < 4; i++) {
        /* imprimimos las tres cabeceras */
        printf("\n");
        for (j = 0; j < 3; j++) { /* MONTH NAME */
	        ml[j] = mbstrlen(gettext(cad_meses[mes[j]])); 
            hl[j] = (WDTH>>1) + (ml[j]>>1);
            tl[j] = WDTH - hl[j];
		    printf("%s%*s%*s",
                    j ? "        " : "",
                    hl[j], gettext(cad_meses[mes[j]]),
                    tl[j], "");
	    } /* for */
        printf("\n");
        for (j = 0; j < 3; j++) { /* UNDERLINE */
            printf("%s%*.*s%*s",
                    j ? "        " : "",
                    hl[j], ml[j], "===================",
                    tl[j], "");
	    } /* for */
	    printf("\n");

		for (j = 0; j < 3; j++) { /* MONTH HEADER */
			if (j) printf("        ");
			for (k = 0; k < 7; k++) {
				printf("%s%s",
					k ? " " : "",
					gettext(cad_dias2[(k + fdow)%7]));
			} /* for */
		} /* for */
		printf("\n");
        printf("====================        "
               "====================        "
               "====================\n");
        for (j = 0; j < 6; j++){  /* fila */
            for (k = 0; k < 3; k++) {  /* mes */
                if (k) printf("        ");
                for (l = 0; l < 7; l++) { /* columna */
                    if (l) printf(" ");
                    if (desfase[k]) {
                        desfase[k]--;
                        printf("  ");
                    } else {
                        if (dia [k] == -1) {
                            printf("  ");
						} else {
                            printf("%2d",
                                    dia [k]);
                            dia[k] = siguiente(
                                    dia[k], mes[k] + 1, anio);
                        } /* if */
                    } /* if */
                } /* for */
            } /* for */
            printf("\n");
        } /* for */
        for (j = 0; j < 3; j ++) {
            mes[j] += 3;
            dia[j] = 1;
            desfase[j] = (dia_1_mes(mes[j] + 1, anio) - fdow + 7)%7;
        } /* for */
    } /* for */
    printf("--------------------------------------"
		   "--------------------------------------\n");
} /* formato_largo */

void formato_corto(int mes, int anio)
{

    int dia, desfase, i, j;
	int la, lb, lc;
	char cad_cab [100];

	sprintf(cad_cab,
		"%s %04d",
		gettext(cad_meses [mes-1]), anio);
	lb = mbstrlen(cad_cab);
	la = 13 + (lb >> 1);
	printf("%*s\n", la, cad_cab);
    printf("%*.*s\n", la, lb, "----------------");
	for (i = 0; i < 7; i++)
		printf("%s%s",
                i ? " " : "",
                gettext(cad_dias3[(i + fdow)%7]));
	printf("\n");
    printf("===========================\n");
    dia = 1;
    desfase = (dia_1_mes(mes, anio) - fdow + 7) % 7;
    for (i = 0;;i++) {
        int resaltado;

        if (desfase) {
            printf("    ");
            desfase--;
        } else {
            resaltado = (anio == fecha_hoy.tm_year + 1900 &&
                          dia == fecha_hoy.tm_mday &&
                          mes == fecha_hoy.tm_mon + 1);
            if (resaltado)
					printf("[%2d]", dia);
            else
					printf(" %2d ", dia);
            dia = siguiente(dia, mes, anio);
        } /* if */
        if (dia == -1) break;
        if (i % 7 == 6) printf("\n");
    } /* for */
    printf("\n");
} /* formato_corto */

/* $Id: cal.c,v 1.10 2015/06/14 21:50:28 luis Exp $ */
