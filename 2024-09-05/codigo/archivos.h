#ifndef _ARCHIVOS_H_
#define _ARCHIVOS_H_

#include <stdio.h>

int crear_archivo(const char *path);
int borrar_archivo(const char *path);

char *leer_archivo(const char *path);
int escribir_archivo(const char *path, const char *data);
int agregar_linea(const char *path, const char *linea);

int remover_linea(const char *path, int numero_linea);
int insertar_linea(const char *path, const char *linea, int posicion);
void manejar_error(const char *mensaje);
long tamano_archivo(const char *path);

#endif
