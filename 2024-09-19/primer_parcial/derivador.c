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
    Producto producto;
    FILE *archivo1, *archivo2;
    int id_semaforo;
    char linea[BUFFER_SIZE];
    id_semaforo = crear_semaforo(CLAVE_BASE);

    while (1)
    {
        printf("Ingrese la descripcion: ");
        scanf("%s", producto.descripcion);
        printf("Ingrese el precio: ");
        scanf("%d", &producto.precio);
        
        esperar_semaforo(id_semaforo);
        if (producto.precio < PRECIO_LIMITE) {
            archivo1 = abrir_archivo(ARCHIVO_CAJERO_1, "a");
            memset(linea,0x00,sizeof(linea));
            sprintf(linea, "%s %d", producto.descripcion, producto.precio);
            escribir_linea(archivo1,linea);
            cerrar_archivo(archivo1);
        } else {
            archivo2 = abrir_archivo(ARCHIVO_CAJERO_2, "a");
            memset(linea,0x00,sizeof(linea));
            sprintf(linea, "%s %d", producto.descripcion, producto.precio);
            escribir_linea(archivo2,linea);
            cerrar_archivo(archivo2);
        }
        levantar_semaforo(id_semaforo);
        usleep(500000); /* 500ms */
    }

    return 0;
}
