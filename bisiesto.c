/* $Id: bisiesto.c,v 1.4 2004/10/12 19:38:50 luis Exp $
 * bisiesto.c -- rutina para comprobar si un a�o es bisiesto.
 * Autor: Luis Colorado.
 * Fecha: 15/1/90.
 * $Log: bisiesto.c,v $
 * Revision 1.4  2004/10/12 19:38:50  luis
 * Modificado el estilo del programa.
 *
 * Revision 1.3  2003/04/21 20:51:48  luis
 * A�adido soporte internacional, para mostrar los mensajes y los meses y d�as
 * de la semana en el idioma local configurado.
 *
 * Revision 1.2  2000/07/17 00:27:52  luis
 * arreglos de formateo.
 *
 * Revision 1.1  1995/09/30 00:24:06  luis
 * Initial revision
 *
 *
 *        Descripci�n:
 *        ============
 *
 *        Esta subrutina permite determinar si un a�o es bisiesto. Para ello
 *        se tiene en cuenta que los a�os anteriores a 1752 se reg�an por el
 *        calendario ant�guo seg�n el cu�l, eran bisiestos los a�os m�ltiplos
 *        de 4. En los a�os posteriores a 1752, son bisiestos los a�os m�lti-
 *        plos de 4 que no sean m�ltiplos de 100 salvo los m�ltiplos de 400
 *        que s� ser�n bisiestos. Para corregir el desfase introducido, se
 *        eliminaron los d�as 3 al 13 de septiembre del a�o 1752, inclusives
 *        los dos.
 *
 *        Uso:
 *        ====
 *
 *        A la rutina se le pasa un entero indicando el a�o a consultar.
 *
 *        Valor devuelto:
 *        ===============
 *
 *        La rutina devuelve 1 si el a�o es bisiesto y 0 en caso contrario.
 *
 *        Prototipo:
 *        ==========
 *
 *        int bisiesto (anio)
 *        int anio;
 *
 *        El prototipo no se encuentra en ning�n fichero de cabecera, por ser
 *        �sta una funci�n de par�metros enteros y valor devuelto entero.
 *
 *        Ejemplo:
 *        ========
 *
 *        if (bisiesto (anio_nacim))
 *           printf ("Ud. naci� en un a�o bisiesto.\n");
 *
 */


#define BISIESTO                      1
#define NORMAL                        0

int bisiesto (anio)
{
     if (anio < 1752) {
		if (anio % 4 == 0) return BISIESTO;
		return NORMAL;
	 } /* if */
     if (anio % 400 == 0) return BISIESTO;
     if (anio % 100 == 0) return NORMAL;
     if (anio % 4 == 0) return BISESTO;
	 return NORMAL;
} /* bisiesto */

/* $Id: bisiesto.c,v 1.4 2004/10/12 19:38:50 luis Exp $ */
