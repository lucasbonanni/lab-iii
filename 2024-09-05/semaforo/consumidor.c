#include "def.h"
#include "semaforo.h"
#include "archivos.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char cadena[LARGO]; /* Un array lo suficientemente grande como para guardar la l�nea m�s larga del fichero */
    int cant_producto = 0;
    FILE *archivo = 0;
    int id_semaforo;
    id_semaforo = creo_semaforo();

    while (1)
    {
        espera_semaforo(id_semaforo);

        archivo = abrir_archivo(ARCHIVO_PRODUCTO, "r");
        if (archivo != NULL)
        {
            printf("\nCONSUMIMOS\n");
            while (!final_archivo(archivo))
            {
                char *linea;
                linea =leer_linea(archivo, cadena);
                if (linea != NULL)
                {
                    printf("%s", linea);
                }
                cant_producto++;
            }
            cerrar_archivo(archivo);
            if (cant_producto > 0)
            {
                printf("\nBORRAMOS\n");
                borrar_archivo(ARCHIVO_PRODUCTO);
                // crear_archivo(ARCHIVO_PRODUCTO);
                cant_producto = 0;
                levanta_semaforo(id_semaforo);
            }
        }
        else
        {
            // perror("Error al abrir producto.txt");
            printf("\nESPERAMOS\n");
            usleep(INTERVALO_PARTIDA * 1000);
        };
    }
    return 0;
}
