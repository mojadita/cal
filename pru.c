#include <libintl.h>
#include <stdio.h>
#include <stdlib.h>
#include <langinfo.h>
#include <locale.h>

#define P(f, x) do { printf("[%s] => " f "\n", #x, (x)); } while (0)

int main()
{
    setlocale(LC_ALL, "");
    P("%s", nl_langinfo(CODESET));
    P("%s", nl_langinfo(DAY_1));
    P("%s", nl_langinfo(DAY_2));
    P("%s", nl_langinfo(DAY_3));
    P("%s", nl_langinfo(DAY_4));
    P("%s", nl_langinfo(DAY_5));
    P("%s", nl_langinfo(DAY_6));
    P("%s", nl_langinfo(DAY_7));
    P("%s", nl_langinfo(ABDAY_1));
    P("%s", nl_langinfo(ABDAY_2));
    P("%s", nl_langinfo(ABDAY_3));
    P("%s", nl_langinfo(ABDAY_4));
    P("%s", nl_langinfo(ABDAY_5));
    P("%s", nl_langinfo(ABDAY_6));
    P("%s", nl_langinfo(ABDAY_7));
    P("%s", nl_langinfo(MON_1));
    P("%s", nl_langinfo(MON_2));
    P("%s", nl_langinfo(MON_3));
    P("%s", nl_langinfo(MON_4));
    P("%s", nl_langinfo(MON_5));
    P("%s", nl_langinfo(MON_6));
    P("%s", nl_langinfo(MON_7));
    P("%s", nl_langinfo(MON_8));
    P("%s", nl_langinfo(MON_9));
    P("%s", nl_langinfo(MON_10));
    P("%s", nl_langinfo(MON_11));
    P("%s", nl_langinfo(MON_12));
    P("%s", nl_langinfo(ABMON_1));
    P("%s", nl_langinfo(ABMON_2));
    P("%s", nl_langinfo(ABMON_3));
    P("%s", nl_langinfo(ABMON_4));
    P("%s", nl_langinfo(ABMON_5));
    P("%s", nl_langinfo(ABMON_6));
    P("%s", nl_langinfo(ABMON_7));
    P("%s", nl_langinfo(ABMON_8));
    P("%s", nl_langinfo(ABMON_9));
    P("%s", nl_langinfo(ABMON_10));
    P("%s", nl_langinfo(ABMON_11));
    P("%s", nl_langinfo(ABMON_12));
    return EXIT_SUCCESS;
} /* main */
