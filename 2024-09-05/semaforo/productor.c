#include "def.h"
#include "semaforo.h"
#include "archivos.h"
#include <unistd.h>
#include <string.h>
/* cSpell:disable */

int main(int argc, char *argv[])
{
    char cadena[LARGO]; /* Un array lo suficientemente grande como para guardar la l�nea m�s larga del fichero */
    int nro_producto = 0, nro_partida = 0;
    FILE *archivo = NULL;
    int id_semaforo = 0;

    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, ROJO);
    // crear_archivo(ARCHIVO_PRODUCTO);


    while (1)
    {
        printf("\nPRODUCIMOS-PARTIDA-%04d\n", nro_partida);
        crear_archivo(ARCHIVO_PRODUCTO);

        nro_producto = 0;
        for (nro_producto = 0; nro_producto < CANTIDAD_PARTIDA; nro_producto++)
        {
            archivo = abrir_archivo(ARCHIVO_PRODUCTO, "a");
            if (archivo != NULL)
            {
                // String concatenation using strcpy and strcat
                snprintf(cadena, LARGO, "PRODUCIMOS-PARTIDA-%04d--PRODUCTO-%04d\n", nro_partida, nro_producto);
                agregar_linea_archivo(archivo, cadena);
                usleep(INTERVALO_PRODUCTO * 1000);
                cerrar_archivo(archivo);
            }
        }
        nro_partida++;
        printf("\nESPERAMOS\n");

        levanta_semaforo(id_semaforo);
        usleep(INTERVALO_PARTIDA * 1000);
    }
    return 0;
}
