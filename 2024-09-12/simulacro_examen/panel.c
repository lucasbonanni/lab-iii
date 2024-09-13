#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "archivos.h"
#include "semaforo.h"
#include "def.h"

int main(int argc, char const *argv[]) {
    int id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, 1);
    crear_archivo(ARCHIVO_AVIONES);

    while (1) {
        char *content;
        espera_semaforo(id_semaforo);

        content = leer_archivo(ARCHIVO_AVIONES);
        if (content) {
            printf("%s", content);
            free(content);
        }
        
        levanta_semaforo(id_semaforo);
        usleep(500000);
    }

    return 0;
}
