#include <stdio.h>
#include <stdlib.h>

// Puntero de archivo global
FILE *archivo;

// Función genérica para abrir un archivo
void abrir_archivo(const char *nombreArchivo, const char *modo) {
    archivo = fopen(nombreArchivo, modo);
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }
}

// Función genérica para cerrar un archivo
void cerrar_archivo() {
    if (fclose(archivo) != 0) {
        perror("Error al cerrar el archivo");
        exit(EXIT_FAILURE);
    }
    archivo = NULL;
}

// Verifica si un archivo existe
int existe(const char *nombreArchivo) {
    abrir_archivo(nombreArchivo, "r");
    if (archivo != NULL) {
        cerrar_archivo();
        return 1;
    }
    return 0;
}

// Escribe contenido en un archivo
void escribir(const char *nombreArchivo, const char *contenido, const char *modo) {
    abrir_archivo(nombreArchivo, modo);
    fprintf(archivo, "%s", contenido);
    cerrar_archivo();
}

// Lee contenido de un archivo
char *leer(const char *nombreArchivo, size_t size) {
    abrir_archivo(nombreArchivo, "r");
    char *contenido = malloc(size);
    if (contenido == NULL) {
        perror("Error al asignar memoria");
        cerrar_archivo();
        exit(EXIT_FAILURE);
    }
    if (fgets(contenido, size, archivo) == NULL) {
        perror("Error al leer el archivo");
        free(contenido);
        cerrar_archivo();
        exit(EXIT_FAILURE);
    }
    cerrar_archivo();
    return contenido;
}

// Muestra el contenido de un archivo
void mostrar(const char *nombreArchivo) {
    abrir_archivo(nombreArchivo, "r");
    char linea[1000];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s", linea);
    }
    cerrar_archivo();
}

// Borra un archivo
void borrar(const char *nombreArchivo) {
    if (remove(nombreArchivo) != 0) {
        perror("Error al borrar el archivo");
        exit(EXIT_FAILURE);
    }
}