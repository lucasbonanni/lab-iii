#ifndef _ARCHIVOS_H_
#define _ARCHIVOS_H_

#include <stdio.h>
#include "global.h"
/* cSpell:disable */


FILE *abrir_archivo(const char *path, const char *mode);
int cerrar_archivo(FILE *file);
int crear_archivo(const char *path);
int borrar_archivo(const char *path);
void leer_linea(FILE *file, char *buffer);
int final_archivo(FILE *file);
char* leer_archivo(const char *filename);
void escribir_archivo(const char *filename, Avion avion);
int agregar_linea_archivo(FILE *file, const char *line);
int eliminar_linea_archivo(FILE *file, const char *path, int numero_linea);
int insertar_linea_archivo(FILE *file, const char *path, const char *linea, int posicion);
long tamano_archivo(FILE *file);
int existe(const char *nombre);
void renombrar_archivo(const char *path, const char *nuevo_nombre);
#endif
