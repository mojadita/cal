/* $Id: cal.c,v 1.10 2015/06/14 21:50:28 luis Exp $
 * cal.c -- programa para imprimir un calendario.
 * Autor: Luis Colorado.
 * Fecha: 15.1.90.
 */

#include <ctype.h>
#include <getopt.h>
#include <langinfo.h>
#include <libintl.h>
#include <locale.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

#include "leap.h"
#include "nextday.h"
#include "weekday.h"

#include "nextday.h"
#include "weekday.h"
#include "leap.h"

#define NMONTHS     12
#define NDAYS       7

#define D(f) __FILE__":%d:%s: " f, __LINE__, __func__
#define ERR(fmt, args...) fprintf(stderr, fmt, ##args)

#define WDTH        20

struct tm today;
time_t now;
int fdow = 1;

struct month_info {
    int     mi_nl_li;
    char   *mi_name;
    size_t  mi_len;
    size_t  mi_strlen;
} months[] = {
    { MON_1, NULL, 0, 0, }, { MON_2, NULL, 0, 0, },
    { MON_3, NULL, 0, 0, }, { MON_4, NULL, 0, 0, },
    { MON_5, NULL, 0, 0, }, { MON_6, NULL, 0, 0, },
    { MON_7, NULL, 0, 0, }, { MON_8, NULL, 0, 0, },
    { MON_9, NULL, 0, 0, }, { MON_10, NULL, 0, 0, },
    { MON_11, NULL, 0, 0, }, { MON_12, NULL, 0, 0, },
};

struct day_info {
    int     di_nl_li;
    char   *di_name;
    size_t  di_l3;
    size_t  di_l2;
} days[] = {
    { DAY_1, NULL, 0, 0, }, { DAY_2, NULL, 0, 0, }, { DAY_3, NULL, 0, 0, },
    { DAY_4, NULL, 0, 0, }, { DAY_5, NULL, 0, 0, }, { DAY_6, NULL, 0, 0, },
    { DAY_7, NULL, 0, 0, },
};

void long_format(int y);
void short_format(int y, int m);

size_t mbstrlen(char *s)
{
    size_t res = 0;
    size_t l = strlen(s);
    mbstate_t st = {0};
    int i = 0;

    ssize_t n;
#if 0
    printf(D("[%s]:"), s);
#endif
    while ((n = mbrlen(s, l, &st)) > 0) {
        res++; l -= n; s += n;
#if 0
        printf("[%d]", n);
#endif
    }
#if 0
    printf("->%d\n", res);
#endif
    return res;
} /* mbstrlen */

size_t howmany(char *s, int nc)
{
    size_t res = 0;
    size_t l = strlen(s);
    mbstate_t st = {0};
    int i;

    size_t n;
#if 0
    printf(D("[%s]:"), s);
#endif
    for (i = 0; (i < nc) && (n = mbrlen(s, l, &st)) > 0; i++, res += n, l -= n, s += n) {
#if 0
        printf("[%d]", n);
#else
        continue;
#endif
    }
#if 0
    printf("->%d\n", res);
#endif
    return res;
} /* howmany */

char *basename(char *s, char c)
{
    char *res = strrchr(s, c);
    if (res) res++;
    else res = s;
    return res;
} /* basename */

void init(void)
{
    int i;
    char *s;
    size_t l;
    struct month_info *p = months;
    struct day_info *q = days;

    for (i = 0; i < NMONTHS; i++, p++) {
        p->mi_name = s = nl_langinfo(p->mi_nl_li);
        p->mi_strlen = strlen(s);
        p->mi_len = mbstrlen(s);
    }

    for (i = 0; i < NDAYS; i++, q++) {
        mbstate_t st = {0};
        q->di_name = s = nl_langinfo(q->di_nl_li);
        q->di_l2 = howmany(q->di_name, 2);
        q->di_l3 = howmany(q->di_name, 3);
    }
} /* init */
        

int main(int argc, char **argv)
{
    int m = 0, y = 0; 
    int i, opt;

    /* ADJUST LOCALE */
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

    init();

    /* PROCESS OPTIONS */
	while((opt=getopt(argc, argv, "V01234567")) != EOF) {
		switch(opt) {
		case 'V':
			printf(D("%s="PACKAGE", %s="VERSION"\n"),
                    gettext("package"), gettext("version"));
			exit(0);
        case '0': case '1': case '2': case '3':
        case '4': case '5': case '6': case '7':
            fdow = opt - '0';
            break;
		} /* switch */
	} /* while */

    /* ADJUST PARAMETER LIST */
    argc -= optind; argv += optind;

    /* PROCESS PARAMETERS */
    switch (argc) {
    default:
        ERR(D("%s\n"), gettext("incorrect number of parameters"));
        exit(1);

    case 2: /* TWO PARAMETERS */
        i = atoi(argv[1]);
        if (i <= 0) {
            ERR(D("%s\n"), gettext("incorrect second parameter"));
		    exit(1);
        } /* if */
        if (i > 12) y = i;
        else m = i;
        /* NO BREAK HERE */
    case 1: /* ONE PARAMETER */
        i = atoi(argv [0]);
        if (i <= 0){
            ERR(D("%s\n"), gettext("incorrect first parameter"));
            exit(1);
        } /* if */
        if (i > 12) y = i;
        else m = i;
        /* NO BREAK HERE */
    case 0: /* NO PARAMETERS */
        break;

    } /* switch */

    /* programa principal */
    time(&now);
	today = *localtime(&now);

    if (!m && y) {
			long_format(y);
	} else {
	    if (!m)
				m = today.tm_mon + 1;
        if (!y)
				y = today.tm_year + 1900;
        short_format(m, y);
    } /* if */
} /* main */

void long_format(int year)
{
    int day[3], offset[3], month[3], i, j, k, l;
    int hl[3], ml[3], tl[3];
	char str [10];
    ssize_t n;

	n = sprintf(str, "%d", year);

    printf("\n\n%*s\n", 38 + (int)n/2, str);
    printf("%*.*s\n", 38 + (int)n/2, (int)n, "============");

    printf("\n--------------------------------------"
        	 "--------------------------------------\n");

    for (i = 0; i < 3; i++) {
        month[i] = i;
        day[i] = 1;
        offset[i] = (first_month_day(month[i] + 1, year) - fdow + 7)%7;
    } /* for */

    for (i = 0; i < 4; i++) {
        /* imprimimos las tres cabeceras */
        printf("\n");
        for (j = 0; j < 3; j++) { /* MONTH NAME */
            struct month_info *p = months + month[j];
	        ml[j] = p->mi_len; 
            hl[j] = (WDTH>>1) - (ml[j]>>1);
            tl[j] = WDTH - hl[j] - ml[j];
		    printf("%s%*s%s%*s",
                    j ? "        " : "",
                    hl[j], "", p->mi_name,
                    j < 2 ? tl[j] : 0, "");
	    } /* for */
        printf("\n");
        for (j = 0; j < 3; j++) { /* UNDERLINE */
            printf("%s%*s%.*s%*s",
                    j ? "        " : "",
                    hl[j], "", ml[j], "===================",
                    j < 2 ? tl[j] : 0, "");
	    } /* for */
	    printf("\n");

		for (j = 0; j < 3; j++) { /* MONTH HEADER */
            struct month_info *p = months + month[j];
			if (j) printf("        ");
			for (k = 0; k < 7; k++) {
				printf("%s%.*s",
					k ? " " : "",
                    (int)days[(k + fdow)%7].di_l2,
                    days[(k + fdow)%7].di_name);
			} /* for */
		} /* for */
		printf("\n");
        printf("====================        "
               "====================        "
               "====================\n");
        for (j = 0; j < 6; j++){  /* fila */
            for (k = 0; k < 3; k++) {  /* month */
                if (k) printf("        ");
                for (l = 0; l < 7; l++) { /* columna */
                    if (l) printf(" ");
                    if (offset[k]) {
                        offset[k]--;
                        printf("  ");
                    } else {
                        if (day [k] == -1) {
                            printf("  ");
						} else {
                            printf("%2d",
                                    day [k]);
                            day[k] = next_day(
                                    day[k], month[k] + 1, year);
                        } /* if */
                    } /* if */
                } /* for */
            } /* for */
            printf("\n");
        } /* for */
        for (j = 0; j < 3; j ++) {
            month[j] += 3;
            day[j] = 1;
            offset[j] = (first_month_day(month[j] + 1, year) - fdow + 7)%7;
        } /* for */
    } /* for */
    printf("--------------------------------------"
		   "--------------------------------------\n");
} /* long_format */

void short_format(int month, int year)
{

    int day, offset, i, j;
	int la, lb, lc;
	char head_str [100];
    struct month_info *p = months + (month-1);

	sprintf(head_str, "%s %d", p->mi_name, year);
	lb = mbstrlen(head_str);
	la = 13 - (lb >> 1);
	printf("%*s%s\n", la, "", head_str);
    printf("%*s%.*s\n", la, "", lb, "----------------");
	for (i = 0; i < 7; i++)
		printf("%s%.*s",
                i ? " " : "",
                (int)days[(i + fdow)%7].di_l3,
                days[(i + fdow)%7].di_name);
	printf("\n");
    printf("===========================\n");
    day = 1;
    offset = (first_month_day(month, year) - fdow + 7) % 7;
    for (i = 0;;i++) {
        int highlight;

        if (offset) {
            printf("    ");
            offset--;
        } else {
            highlight = (year == today.tm_year + 1900 &&
                          day == today.tm_mday &&
                          month == today.tm_mon + 1);
            if (highlight)
					printf("[%2d]", day);
            else
					printf(" %2d ", day);
            day = next_day(day, month, year);
        } /* if */
        if (day == -1) break;
        if (i % 7 == 6) printf("\n");
    } /* for */
    printf("\n");
} /* short_format */

/* $Id: cal.c,v 1.10 2015/06/14 21:50:28 luis Exp $ */
