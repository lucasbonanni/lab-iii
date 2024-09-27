#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "clave.h"
#include "semaforo.h"
#include "archivos.h"
#include "def.h"

int main(int argc, char *argv[])
{
    int numero_cajero;
    FILE *archivo;
    char descripcion[100];
    int price;
    int id_semaforo;
    char nombre_archivo[20];
    numero_cajero = atoi(argv[1]);
    sprintf(nombre_archivo, "cajero%d.txt", numero_cajero);
    printf("Caja %d: %s\n", numero_cajero, nombre_archivo);
    id_semaforo = crear_semaforo(CLAVE_BASE);
    inicializar_semaforo(id_semaforo, VERDE);

    while (access(nombre_archivo, F_OK) != 0){
        printf("Esperando al derivador.\n");
        usleep(1000000);
    }

    while (1)
    {
        esperar_semaforo(id_semaforo);
        archivo = abrir_archivo(nombre_archivo, "r");
        if (archivo) {
            while (fscanf(archivo, "%s %d", descripcion, &price) != EOF) {
                printf("Caja %d: producto %s precio %d\n", numero_cajero, descripcion, price);
            }
            cerrar_archivo(archivo);
        }
        levantar_semaforo(id_semaforo);
        usleep(500000); /* 500ms */
    }

    return 0;
}
