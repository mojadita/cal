/* $Id: dia_sema.c,v 1.2 2000/07/17 00:27:52 luis Exp $
 * dia_sema.c -- rutinas para calcular el dia de la semana de una fecha dada.
 * Autor: Luis Colorado.
 * Fecha: 15/1/90.
 * $Log: dia_sema.c,v $
 * Revision 1.2  2000/07/17 00:27:52  luis
 * arreglos de formateo.
 *
 * Revision 1.1  1995/09/30 00:26:39  luis
 * Initial revision
 *
 *
 *        Descripcion:
 *        ============
 *
 *        Este fichero contiene la descripcion de tres subrutinas para el
 *        c lculo del d!a de la semana.
 *        dia_1_ene () calcula el dia de la semana del 1 de enero del a$o
 *        pasado como par metro.
 *        dia_1_mes () calcula el d!a de la semana de 1 del mes indicado como
 *        primer par metro y del a$o indicado como 2' par metro.
 *        dia_semana () calcula el d!a de la semana de una fecha indicada como
 *        tres enteros. Esta subrutina no se utiliza en el programa cal pero
 *        puede ser utilizada por otros programas como subrutina de librer!a.
 *
 *        Uso:
 *        ====
 *
 *        int dia_1_ene (anio)
 *        int anio;
 *
 *        int dia_1_mes (mes, anio)
 *        int mes, anio;
 *
 *        int dia_semana (dia, mes, anio)
 *        int dia, mes, anio;
 *
 *        Valor devuelto:
 *        ===============
 *
 *        El valor devuelto se corresponde con el d!a de la semana de la fecha.
 *           -- El 0 corresponde al lunes.
 *           -- El 1 corresponde al martes.
 *           -- "  2      "      "  miercoles.
 *           -- "  3      "      "  jueves.
 *           -- "  4      "      "  viernes.
 *           -- "  5      "      "  s bado.
 *           -- "  6      "      "  domingo.
 *
 *        Errores:
 *        ========
 *
 *        No se contemplan, es deber del usuario identificarlos y evitarlos.
 *        El introducir una fecha erronea, como el 35 de enero, produce resul-
 *        tados, aunque es un error calcular esta fecha.
 *
 *        Ejemplo:
 *        ========
 *
 *        dia_nac = dia_semana (dia_nacim, mes_nacim, anio_nacim);
 *
 */

int dia_1_ene (anio)
{

     if (anio <= 1752) {
        int g_4; /* grupos de cuatro a$os */

        anio--;
        g_4 = anio / 4;
        anio %= 4;
        return (g_4 * 5 + anio + 5) % 7;
     }
     else {
        int g_100, g_4; /* grupos de cien a$os y de 4 resp. */

        anio--;
        anio %= 400;
        g_100 = anio / 100;
        anio %= 100;
        g_4 = anio / 4;
        anio %= 4;
        return ((g_100 + g_4) * 5 + anio) % 7;
     }
}

int dia_1_mes (mes, anio)
{
        static int dias_mes [12] [3] = {
         /* normal, bisiesto, 1752 */
            0,      0,        0, /* ENERO */
            3,      3,        3, /* FEBRERO */
            3,      4,        4, /* MARZO */
            6,      0,        0, /* ABRIL */
            1,      2,        2, /* MAYO */
            4,      5,        5, /* JUNIO */
            6,      0,        0, /* JULIO */
            2,      3,        3, /* AGOSTO */
            5,      6,        6, /* SEPTIEMBRE */
            0,      1,        4, /* OCTUBRE */
            3,      4,        0, /* NOVIEMBRE */
            5,      6,        2  /* DICIEMBRE */
        };
        mes--;
        if (anio == 1752)
           return (dia_1_ene (anio) + dias_mes [mes][2]) % 7;
        if (bisiesto (anio))
           return (dia_1_ene (anio) + dias_mes [mes][1]) % 7;
        return (dia_1_ene (anio) + dias_mes [mes][0]) % 7;
}

int dia_semana (dia, mes, anio)
{
      return (dia_1_mes (mes, anio) +
              dia +
              (dia > 2 && mes == 9 && anio == 1752 ? 2 : -1)
             ) % 7;
}

/*^$Id: dia_sema.c,v 1.2 2000/07/17 00:27:52 luis Exp $ */
