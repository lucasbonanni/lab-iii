#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "caja.h"
#include "archivos.h"
#include "semaforo.h"
#include "global.h"

void procesar_caja(int min_unidades, int max_unidades) {
    Producto producto;
    FILE *file;
    // long tamano;
    // char buffer[sizeof(Producto)];
    int id_semaforo = creo_semaforo();

    while (1) {
        espera_semaforo(id_semaforo);
        file = fopen(ARCHIVO_PRODUCTOS, "r");
        if (file != NULL) {
            while (fread(&producto, sizeof(Producto), 1, file)) {
                // Process product based on units (dummy units for example)
                int unidades = rand() % 20 + 1; // Random units between 1 and 20
                if (unidades >= min_unidades && unidades <= max_unidades) {
                    printf("Caja %d: Producto: %s, Precio: %.2f, Unidades: %d, Total: %.2f\n",
                           min_unidades, producto.descripcion, producto.precio, unidades, producto.precio * unidades);
                }
            }
            fclose(file);
            borrar_archivo(ARCHIVO_PRODUCTOS);
        }
        levanta_semaforo(id_semaforo);
        usleep(100000); // 100 ms
    }
}

int main(int argc, char *argv[]) {
    int min_unidades;
    int max_unidades;
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <min_unidades> <max_unidades>\n", argv[0]);
        return 1;
    }

    min_unidades = atoi(argv[1]);
    max_unidades = atoi(argv[2]);

    procesar_caja(min_unidades, max_unidades);

    return 0;
}
