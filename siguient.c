/* $Id: siguient.c,v 1.3 2003/04/21 20:51:48 luis Exp $
 * siguient.c -- rutina para calcular el día siguiente a uno dado de un
 * mes determinado y un año determinado.
 * Autor: Luis Colorado.
 * Fecha: 15/1/90.
 * $Log: siguient.c,v $
 * Revision 1.3  2003/04/21 20:51:48  luis
 * Añadido soporte internacional, para mostrar los mensajes y los meses y días
 * de la semana en el idioma local configurado.
 *
 * Revision 1.2  2000/07/17 00:27:52  luis
 * arreglos de formateo.
 *
 * Revision 1.1  1995/09/30 00:28:59  luis
 * Initial revision
 *
 *
 *        Descripción:
 *        ============
 *
 *        Esta función devuelve el valor del día siguiente al día especifi-
 *        cado. Ésto se implementa con una función pues hay excepciones.
 *        Así, el día siguiente al 2 de septiembre de 1.752 no es el 3, sino
 *        el 14, debido a que se eliminaron 11 días para corregir el desfase
 *        introducido por el calendario anterior.
 *
 */

#define       ENE        1
#define       FEB        2
#define       MAR        3
#define       ABR        4
#define       MAY        5
#define       JUN        6
#define       JUL        7
#define       AGO        8
#define       SEP        9
#define       OCT       10
#define       NOV       11
#define       DIC       12


int siguiente (int dia, int mes, int anio)
{
         if (anio < 1) return -1;
         /* la excepción */
         if (anio == 1752 && mes == 9 && dia == 2) return 14;
         switch (mes){
         case ENE: case MAR: case MAY: case JUL:
         case AGO: case OCT: case DIC:
              if (dia < 1 || dia >= 31) return -1;
              return ++dia;
         case ABR: case JUN: case SEP: case NOV:
              if (dia < 1 || dia >= 30) return -1;
              return ++dia;
         case FEB:
              if (bisiesto (anio)){
                 if (dia < 1 || dia >= 29) return -1;
              }
              else
                 if (dia < 1 || dia >= 28) return -1;
              return ++dia;
         default:
              return -1;
         }
} /* siguiente */

/* $Id: siguient.c,v 1.3 2003/04/21 20:51:48 luis Exp $ */
