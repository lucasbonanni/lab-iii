#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "funciones.h"
#include "definiciones.h"

#define N 100

int main(int argc, char *argv[]) {
    srand(time(NULL)); // Semilla para el generador de números aleatorios solo desde el mail
    int numero = Aleatorio(1, 9);
    int arreglo[N] = {};
    int aleatorio = AleatorioNoRepetir(1, 9, arreglo, N);
    printf("%d\n", numero);
    printf("%d\n", aleatorio);
    printf("función main\n");
    return 0;
}