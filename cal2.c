/* cal2.c -- Calendario en versión de colores.
 * Autor: Luis Colorado.
 * Fecha: 15/1/90.
 * $Log: cal2.c,v $
 * Revision 1.1  1995/09/30 00:32:48  luis
 * Initial revision
 *
 *
 *        Descripcion:
 *        ============
 *
 *        Este programa imprime un calendario del mes o del a$o indicados.
 *        Si el mes contiene el d!a de la fecha actual, ste se escribe entre
 *        corchetes. Su mec nica es como la del anterior, solo que imprime los
 *        datos en colores.
 *
 *        Uso:
 *        ====
 *
 *        cal [a$o | mes] [mes | a$o]
 *
 *        El mes se reconoce por ser un n#mero de 1 a 12 (as! pues, no se
 *        podr  representar un a$o anterior al a$o 13) y el a$o por ser un
 *        n#mero mayor que 12. Cuando no se especifica ning#n par metro, se
 *        asume por defecto el calendario del mes actual del a$o actual. Si
 *        solo se especifica el mes, se entiende el calendario del mes indi-
 *        cado en el a$o actual. Si solo se especifica el a$o, se entiende
 *        un calendario completo del a$o indicado. Si se especifican los dos,
 *        se entender  un calendario del mes y a$o indicados, siempre y cuan-
 *        do uno sea mes y el otro a$o (en caso de que los dos sean meses o
 *        a$os, se considerar  solamente el #ltimo indicado). El calendario
 *        muestra la fecha actual encerr ndola entre corchetes cuando el
 *        calendario es de un solo mes.
 *        El calendario tiene en cuenta la correccion realizada en 1752 para
 *        cambiar del calendario juliano (bisiestos cada cuatro a$os) al
 *        calendario gregoriano (bisiestos m#ltiplos de 4 menos m#ltiplos de
 *        100 menos m#ltiplos de 400) de eliminar los d!as 3 al 13 de septiembre
 *        de 1752. Probar "cal 1752" o "cal 9 1752".
 *
 *        Ejemplos:
 *
 *        C>CAL
 *                 Sep 1989
 *                 --------
 *        Lun Mar Mi Jue Vie S b Dom
 *        ===========================
 *                          1   2   3
 *          4 [ 5]  6   7   8   9  10    <== la fecha actual.
 *         11  12  13  14  15  16  17
 *         18  19  20  21  22  23  24
 *         25  26  27  28  29  30
 *
 *        C>CAL 12
 *                  Dic 1989             <== el mes de diciembre
 *                  --------                 del a$o en curso.
 *        Lun Mar Mi Jue Vie S b Dom
 *        ===========================
 *                          1   2   3
 *          4   5   6   7   8   9  10
 *         11  12  13  14  15  16  17
 *         18  19  20  21  22  23  24
 *         25  26  27  28  29  30
 *
 *        C>CAL 3 1610
 *
 *                 Mar  1610             <== se han indicado los dos
 *                 ---------                 par metros.
 *        Lun Mar Mi Jue Vie S b Dom
 *        ===========================
 *          1   2   3   4   5   6   7
 *          8   9  10  11  12  13  14
 *         15  16  17  18  19  20  21
 *         22  23  24  25  26  27  28
 *         29  30  31
 *
 *         C>CAL 9 1752
 *                  Sep  1752
 *                  ---------
 *         Lun Mar Mi Jue Vie S b Dom
 *         ===========================
 *               1   2  14  15  16  17   <== correccion de 1752.
 *          18  19  20  21  22  23  24
 *          25  26  27  28  29  30
 *
 *         C>CAL 1989                    <== solo se indica el a$o.
 *
 *
 *                                         1989
 *                                         ----
 *
 *                  Ene                    Feb                    Mar
 *                  ---                    ---                    ---
 *         Lu Ma Mi Ju Vi S  Do   Lu Ma Mi Ju Vi S  Do   Lu Ma Mi Ju Vi S  Do
 *         ====================   ====================   ====================
 *                            1          1  2  3  4  5          1  2  3  4  5
 *          2  3  4  5  6  7  8    6  7  8  9 10 11 12    6  7  8  9 10 11 12
 *          9 10 11 12 13 14 15   13 14 15 16 17 18 19   13 14 15 16 17 18 19
 *         16 17 18 19 20 21 22   20 21 22 23 24 25 26   20 21 22 23 24 25 26
 *         23 24 25 26 27 28 29   27 28                  27 28 29 30 31
 *         30 31
 *
 *                  Abr                    May                    Jun
 *                  ---                    ---                    ---
 *         Lu Ma Mi Ju Vi S  Do   Lu Ma Mi Ju Vi S  Do   Lu Ma Mi Ju Vi S  Do
 *         ====================   ====================   ====================
 *                         1  2    1  2  3  4  5  6  7             1  2  3  4
 *          3  4  5  6  7  8  9    8  9 10 11 12 13 14    5  6  7  8  9 10 11
 *         10 11 12 13 14 15 16   15 16 17 18 19 20 21   12 13 14 15 16 17 18
 *         17 18 19 20 21 22 23   22 23 24 25 26 27 28   19 20 21 22 23 24 25
 *         24 25 26 27 28 29 30   29 30 31               26 27 28 29 30
 *
 *
 *                  Jul                    Ago                    Sep
 *                  ---                    ---                    ---
 *         Lu Ma Mi Ju Vi S  Do   Lu Ma Mi Ju Vi S  Do   Lu Ma Mi Ju Vi S  Do
 *         ====================   ====================   ====================
 *                         1  2       1  2  3  4  5  6                1  2  3
 *          3  4  5  6  7  8  9    7  8  9 10 11 12 13    4  5  6  7  8  9 10
 *         10 11 12 13 14 15 16   14 15 16 17 18 19 20   11 12 13 14 15 16 17
 *         17 18 19 20 21 22 23   21 22 23 24 25 26 27   18 19 20 21 22 23 24
 *         24 25 26 27 28 29 30   28 29 30 31            25 26 27 28 29 30
 *         31
 *
 *                  Oct                    Nov                    Dic
 *                  ---                    ---                    ---
 *         Lu Ma Mi Ju Vi S  Do   Lu Ma Mi Ju Vi S  Do   Lu Ma Mi Ju Vi S  Do
 *         ====================   ====================   ====================
 *                            1          1  2  3  4  5                1  2  3
 *          2  3  4  5  6  7  8    6  7  8  9 10 11 12    4  5  6  7  8  9 10
 *          9 10 11 12 13 14 15   13 14 15 16 17 18 19   11 12 13 14 15 16 17
 *         16 17 18 19 20 21 22   20 21 22 23 24 25 26   18 19 20 21 22 23 24
 *         23 24 25 26 27 28 29   27 28 29 30            25 26 27 28 29 30 31
 *         30 31
 *
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
                fprintf (stderr, "%s: 2do. parametro incorrecto.", nomprog);
                exit (1);
             }
             if (i > 12) anio = i;
             else mes = i;
        case 2:
             i = atoi (argv [1]);
             if (i <= 0){
                fprintf (stderr, "%s: 1er. parametro incorrecto.", nomprog);
                exit (1);
             }
             if (i > 12) anio = i;
             else mes = i;
        case 1: /* sin par metros */
             break;
        default:
             fprintf (stderr,
                      "%s: numero incorrecto de parametros",
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
            printf ("\033[1;37mLu Ma Mi Ju Vi Sa Do        Lu Ma Mi Ju Vi Sa Do        Lu Ma Mi Ju Vi Sa Do\n");
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

        printf ("\033[1;33m         %s  %04d\n", cad_meses [mes-1], anio);
        printf ("\033[1;32m         ---------\n");
        printf ("\033[1;37mLun Mar Mie Jue Vie Sab Dom\n");
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

/* fin de cal2.c */
