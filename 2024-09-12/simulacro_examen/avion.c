#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avion.h"
#include "archivos.h"
#include "semaforo.h"
#include "def.h"
#include "global.h"

int main(int argc, char *argv[]) {
    int nro_avion;
    Avion avion;
    int id_semaforo;
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nro_avion>\n", argv[0]);
        return 1;
    }

    nro_avion = atoi(argv[1]); 
    avion.nro_avion = nro_avion;
    id_semaforo = creo_semaforo();
    while (1)
    {
        printf("Ingrese la ciudad de donde proviene el avion %d: ", nro_avion);
        fgets(avion.ciudad, LARGO_MENSAJE, stdin);
        avion.ciudad[strcspn(avion.ciudad, "\n")] = '\0';
        espera_semaforo(id_semaforo);
        escribir_archivo(ARCHIVO_AVIONES, avion);
        levanta_semaforo(id_semaforo);
    }
    return 0;
}
