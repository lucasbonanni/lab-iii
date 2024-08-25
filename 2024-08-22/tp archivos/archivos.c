#include <stdio.h>
#include <stdlib.h>

int existe(char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    int existe = 0;
    if (archivo != NULL) {
        existe = 1;
    }
    fclose(archivo);
    return existe;
}

void escribir(char *nombreArchivo, char *contenido, char *modo) {
    FILE *archivo = fopen(nombreArchivo, modo);
    fprintf(archivo, "%s", contenido);
    fclose(archivo);
}

char *leer(char *nombreArchivo, int *size) {
    FILE *archivo = fopen(nombreArchivo, "r");
    char *contenido = malloc(size);
    fgets(contenido, size, archivo);
    fclose(archivo);
    return contenido;
}

void mostrar(char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    char linea[1000];
    while (fgets(linea, 1000, archivo) != NULL) {
        printf("%s", linea);
    }
    fclose(archivo);
}

void borrar(char *nombreArchivo) {
    remove(nombreArchivo);
}