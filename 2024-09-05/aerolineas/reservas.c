#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "archivos.h"
#include "semaforo.h"
#include "def.h"
/* cSpell:disable */


void procesar_lote(void) {
    FILE *archivo = NULL;
    // char linea[LARGO];
    // int vuelos[11] = {0};
    // int i = 0;
    static int secuencia = 0;
    char nuevo_nombre[LARGO];
    archivo = abrir_archivo(ARCHIVO_LOTE, "r");
    if (archivo == NULL) return;

    
    // while (fgets(linea, LARGO, archivo) != NULL) {
    //     int vuelo;
    //     char destino[LARGO];
    //     char nombre[LARGO];
    //     sscanf(linea, "%d %s %s", &vuelo, destino, nombre);
    //     vuelos[vuelo - 1000]++;
    // }
    // leer_archivo(archivo);
    // fclose(archivo);

    printf("VUELO DESTINO PASAJEROS\n");
    // for (i = 0; i < 11; i++) {
    //     if (vuelos[i] > 0) {
    //         printf("%04d %s %s\n", 1000 + i, "DESTINO", vuelos[i]);
    //     }
    // }
    while(final_archivo(archivo) == 0){
        char linea[LARGO] = {0};
        leer_linea(archivo, linea);
        linea[LARGO - 1] = '\0';
        printf("%s", linea);
    }
    cerrar_archivo(archivo);
    secuencia = 0;
    snprintf(nuevo_nombre, LARGO, "lote.%03d.dat", secuencia++);
    renombrar_archivo(ARCHIVO_LOTE, nuevo_nombre);
}

int main(int argc, char *argv[]) {
    int id_semaforo = creo_semaforo();

    while (1) {
        espera_semaforo(id_semaforo); // Espera a que el semáforo esté verde (1)

        if (existe(ARCHIVO_LOTE)) {
            procesar_lote();
        }

        levanta_semaforo(id_semaforo); // Levanta el semáforo para permitir que el sistema de carga agregue nuevos lotes
        usleep(INTERVALO_RESERVAS * 1000);
    }

    return 0;
}
