#include <string.h>
#include "func.h"

void dividir_mensaje(char mensaje[], const char *separador, char *result[])
{
    char *p;
    int i = 0;
    p = strtok(mensaje, separador);
    while (p != NULL)
    {
        result[i++] = p;
        p = strtok(NULL, separador);
    }
    result[i] = NULL;
}
