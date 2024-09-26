#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "unistd.h"

#include "def.h"
#include "funciones.h"
#include "archivos.h"
#include "semaforo.h"
#include "clave.h"


int main(int argc, char *argv[]){
    FILE *archivo;
    int nro_avion;
    int id_semaforo;
    char nombre_archivo[20+1] = "Vuelos.dat", linea[BUFFER_SIZE];
    struct avion miAvion;

    if (argc != 2) {
        printf("Ingresar número de Avion -> 1, 2 o 3\n");
        return -1; 
    } else {
        nro_avion = atoi(argv[1]);
        if (nro_avion < 1 || nro_avion > 3) {
            printf("Ingresar número de avion válido -> 1, 2 o 3\n");
            return -2;  
        }
        printf("Avion numero %d seleccionado.\n", nro_avion);
    }
    
    id_semaforo = crear_semaforo(CLAVE_BASE);
    srand(time(NULL));


    while(1){
        esperar_semaforo(id_semaforo);
        archivo = abrir_archivo(nombre_archivo, "a");

        if (archivo != NULL) {
            
            memset(linea,0x00,sizeof(linea));
            sprintf(linea, "%d", nro_avion);
            escribir_linea(archivo,linea);
            printf("Arribo del avion %d ",nro_avion);

            memset(linea,0x00,sizeof(linea));
            generar_nombre_aleatorio(miAvion.ciudad);
            sprintf(linea, "%s", miAvion.ciudad);
            escribir_linea(archivo,linea);
            printf("desde %s\n",linea);

            cerrar_archivo(archivo);
        } else {
            perror ("Error al abrir el archivo\n");
        }
        levantar_semaforo(id_semaforo);
        usleep(500000);


    }


}

