/* $Id: siguient.c,v 1.2 2000/07/17 00:27:52 luis Exp $
 * siguient.c -- rutina para calcular el día siguiente a uno dado de un
 * mes determinado y un año determinado.
 * Autor: Luis Colorado.
 * Fecha: 15/1/90.
 * $Log: siguient.c,v $
 * Revision 1.2  2000/07/17 00:27:52  luis
 * arreglos de formateo.
 *
 * Revision 1.1  1995/09/30 00:28:59  luis
 * Initial revision
 *
 *
 *        Descripcion:
 *        ============

 *        Esta funcion devuelve el valor del d!a siguiente al d!a especifi-
 *        cado. Esto se implementa con una funcion pues hay excepciones.
 *        As!, el d!a siguiente al 2 de septiembre de 1.752 no es el 3 sino
 *        el 14, debido a que se eliminaron 11 d!as para corregir el desfase
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


int siguiente (dia, mes, anio)
{
         if (anio < 1) return -1;
         /* la excepcion */
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
}

/* $Id: siguient.c,v 1.2 2000/07/17 00:27:52 luis Exp $ */
