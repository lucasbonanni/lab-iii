#ifndef _ARCHIVOS_H_
#define _ARCHIVOS_H_

#include <stdio.h>
/* cSpell:disable */


FILE *abrir_archivo(const char *path, const char *mode);
int cerrar_archivo(FILE *file);
int crear_archivo(const char *path);
int borrar_archivo(const char *path);
char *leer_linea(FILE *file, char *buffer);
int final_archivo(FILE *file);
char *leer_archivo(FILE *file);
int escribir_archivo(FILE *file, const char *data);
int agregar_linea_archivo(FILE *file, const char *line);
int eliminar_linea_archivo(FILE *file, const char *path, int numero_linea);
int insertar_linea_archivo(FILE *file, const char *path, const char *linea, int posicion);
long tamano_archivo(FILE *file);
#endif
