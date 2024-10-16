#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "func.h"

void dividir_mensaje(char mensaje[], const char *separador, char *result[])
{
    char *token;
    int i = 0;

    token = strtok(mensaje, separador);
    while (token != NULL) {
        result[i++] = token;
        token = strtok(NULL, separador);
    }
    result[i] = NULL;
}

char* create_message(int cod_cliente, int saldo, char *formato)
{
    char *message = (char*)malloc(LARGO_TMENSAJE * sizeof(char));
    if (message != NULL) {
        sprintf(message, formato, cod_cliente, saldo);
    }
    return message;
}
