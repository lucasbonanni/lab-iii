#ifndef _ARCHIVOS_H_
#define _ARCHIVOS_H_

#include <stdio.h>

void existe(char *nombreArchivo);
void escribir(char *nombreArchivo, char *contenido, char *modo);
char *leer(char *nombreArchivo, int *size);
void mostrar(char *nombreArchivo);
void borrar(char *nombreArchivo);


#endif