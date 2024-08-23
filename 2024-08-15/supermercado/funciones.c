#include <stdlib.h>


int Aleatorio(int a, int b){
    return rand () % (b-a+1) + a; // Éste está entre M y N
}


int buscarRepetido(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; // Return the index of the target
        }
    }
    return -1; // Target not found
}

int AleatorioNoRepetir(int a, int b, int *arreglo, int size){
    int num = Aleatorio(a, b);
    while(buscarRepetido(arreglo, size, num) != -1){
        num = Aleatorio(a, b);
    }
    return num;
}