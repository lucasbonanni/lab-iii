#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "funciones.h"
#include "semaforo.h"
#include "archivos.h"
#include "def.h"
#include "time.h"
#include "unistd.h"

int main(int arg, char *argv[]){
    FILE *archivo;
    int id_semaforo,numeroVuelo,i=0;
    char nombre_archivo[BUFFER_SIZE] = "Vuelos.dat", ciudadVuelo[BUFFER_SIZE],numVue[BUFFER_SIZE],nombre_archivo_nuevo[BUFFER_SIZE];

    id_semaforo = crear_semaforo(CLAVE_BASE);
    inicializar_semaforo(id_semaforo, VERDE);
    
    /*Borra el archivo si existe por alguna ejecucion pasada */
    if (access("Vuelos.dat", F_OK) == 0) {
        eliminar_archivo("Vuelos.dat");
    }

    /*Comprueba que algun proceso avion se este ejecutando antes de entrar al while*/
    while (access("Vuelos.dat", F_OK) != 0){
        printf("Esperando la ejecucion los de aviones.\n");
        usleep(1000000);
    }

    while(1){
        esperar_semaforo(id_semaforo);
        archivo = abrir_archivo(nombre_archivo, "r");

        if (archivo != NULL) {
                printf("Leyendo el archivo %s\n", nombre_archivo);
                
                while (!feof(archivo)) {

                    memset(numVue, 0x00, BUFFER_SIZE);
                    /*if para que no lea la linea final y lo tome como valido*/
                    if (leer_linea(archivo, numVue, BUFFER_SIZE) == 1) {
                        numeroVuelo = atoi(numVue); 
                        printf("Avion: %d ",numeroVuelo);

                        memset(ciudadVuelo, 0x00, BUFFER_SIZE);
                        leer_linea(archivo, ciudadVuelo,BUFFER_SIZE);
                        printf("arriba desde %s\n",ciudadVuelo);
                    }
                }
                /*Renombra el archivo para evitar que lo vuelva a leer y a su vez tenga historial de los ya leidos*/
                memset(&nombre_archivo_nuevo[0], 0x00,sizeof(nombre_archivo_nuevo));
                sprintf(nombre_archivo_nuevo,"VuelosLeidos%03d.dat", i);
                renombrarArchivo(nombre_archivo, nombre_archivo_nuevo);
                i++;
        } else {
            printf("No hay nuevas llegadas de vuelos en el aeropuerto.\n");
        }
        levantar_semaforo(id_semaforo);
        printf("Espera del semaforo.\n");
        usleep(5000000);
    }

}
