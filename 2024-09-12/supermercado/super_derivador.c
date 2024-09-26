#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "super_derivador.h"
#include "archivos.h"
#include "semaforo.h"
#include "global.h"

void ingresar_producto(void) {
    Producto producto;
    FILE *file;
    int id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, 1); 

    printf("Ingrese la descripcion del producto: ");
    fgets(producto.descripcion, sizeof(producto.descripcion), stdin);
    producto.descripcion[strcspn(producto.descripcion, "\n")] = '\0';

    printf("Ingrese el precio del producto: ");
    scanf("%f", &producto.precio);
    getchar();

    espera_semaforo(id_semaforo);
    file = fopen(ARCHIVO_PRODUCTOS, "a");
    if (file != NULL) {
        fwrite(&producto, sizeof(Producto), 1, file);
        fclose(file);
    }
    levanta_semaforo(id_semaforo);
    usleep(100000);
}

int main(int argc, char *argv[]) {
    int opcion;

    while (1) {
        printf("1. Ingresar producto\n");
        printf("2. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Consume newline character

        if (opcion == 1) {
            ingresar_producto();
        } else if (opcion == 2) {
            break;
        } else {
            printf("Opcion invalida\n");
        }
    }

    return 0;
}
