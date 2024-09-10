#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "archivos.h"
#include "semaforo.h"
#include "def.h"
/* cSpell:disable */


void generar_vuelo(char *cadena, int vuelo) {
    const char *destinos[] = {"BARAJAS", "CARACAS", "LIMA", "BOGOTA", "MIAMI"};
    const char *nombres[] = {"Juan", "Maria", "Pedro", "Ana", "Luis"};
    int destino = rand() % 5;
    int nombre = rand() % 5;
    snprintf(cadena, LARGO, "%04d %s %s\n", vuelo, destinos[destino], nombres[nombre]);
}

int main(int argc, char *argv[]) {
    int i = 0;
    FILE *archivo = NULL;
    int id_semaforo = 0;
    srand(time(NULL));
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, 1); // Inicializa el semáforo en verde (1)

    while (1) {
        espera_semaforo(id_semaforo); // Espera a que el semáforo esté verde (1)

        for (i = 0; i < CANTIDAD_VUELOS; i++) {
            char cadena[LARGO];
            int vuelo = 1000 + rand() % 11;
            if (vuelo == 0) break;
            generar_vuelo(cadena, vuelo);
            archivo = abrir_archivo(ARCHIVO_LOTE, "a");
            escribir_archivo(archivo, cadena);
            
            usleep(INTERVALO_CARGA * 1000);
        }

        levanta_semaforo(id_semaforo); // Levanta el semáforo para permitir que el sistema de reservas procese el lote
        usleep(INTERVALO_CARGA * 1000);
    }

    return 0;
}
