#include "archivos.h"
#include <stdlib.h>
#include "global.h"

/* cSpell:disable */
void manejar_error(const char *mensaje);

FILE *abrir_archivo(const char *path, const char *mode)
{
    FILE *file = NULL;
    file = fopen(path, mode);
    return file;
}

int cerrar_archivo(FILE *file)
{
    if (file == NULL)
    {
        manejar_error("No hay un archivo abierto.");
        return -1;
    }
    fclose(file);
    file = NULL;
    return 0;
}

int crear_archivo(const char *path)
{
    FILE *file = NULL;
    file = abrir_archivo(path, "w");
    if (file != NULL)
    {
        cerrar_archivo(file);
        return 0;
    }
    return -1;
}

int borrar_archivo(const char *path)
{
    return remove(path);
}

void leer_linea(FILE *file, char *buffer)
{
    if (file == NULL)
    {
        manejar_error("No hay un archivo abierto.");
    }
    fgets(buffer, sizeof(buffer), file);
}

int final_archivo(FILE *file)
{
    if (file == NULL)
    {
        manejar_error("No hay un archivo abierto.");
        return -1;
    }
    return feof(file);
}

char *leer_archivo(FILE *file)
{
    long size = 0;
    char *content = NULL;
    if (file == NULL)
    {
        return NULL;
    }
    size = tamano_archivo(file);
    content = (char *)malloc((size + 1) * sizeof(char));
    if (content == NULL)
    {
        cerrar_archivo(file);
        manejar_error("Error al reservar memoria.");
        return NULL;
    }
    fread(content, sizeof(char), size, file);
    content[size] = '\0';
    cerrar_archivo(file);
    return content;
}

void escribir_archivo(const char *filename, Avion avion) {
    FILE *file = abrir_archivo(filename, "a");
    if (file != NULL) {
        fprintf(file, "Avion %d: %s\n", avion.nro_avion, avion.ciudad);
        cerrar_archivo(file);
    }
}

int agregar_linea_archivo(FILE *file, const char *line)
{
    int result = 0;
    result = fputs(line, file);
    return result;
}

int eliminar_linea_archivo(FILE *file, const char *path, int numero_linea)
{
    FILE *temp = NULL;
    char buffer[256];
    int linea_actual = 1;
    if (file == NULL)
    {
        return -1;
    }
    temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        manejar_error("Error al abrir el archivo temporal.");
        cerrar_archivo(file);
        return -1;
    }

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (linea_actual != numero_linea)
        {
            fputs(buffer, temp);
        }
        linea_actual++;
    }
    fclose(temp);
    cerrar_archivo(file);
    remove(path);
    rename("temp.txt", path);
    return 0;
}

int insertar_linea_archivo(FILE *file, const char *path, const char *linea, int posicion)
{
    FILE *temp = NULL;
    char buffer[256] = {0};
    int linea_actual = 1;
    if (file == NULL)
    {
        return -1;
    }
    temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        manejar_error("Error al abrir el archivo temporal.");
        cerrar_archivo(file);
        return -1;
    }

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (linea_actual == posicion)
        {
            fprintf(temp, "%s\n", linea);
        }
        fputs(buffer, temp);
        linea_actual++;
    }
    if (linea_actual == posicion)
    {
        fprintf(temp, "%s\n", linea);
    }
    fclose(temp);
    cerrar_archivo(file);
    remove(path);
    rename("temp.txt", path);
    return 0;
}

long tamano_archivo(FILE *file)
{
    long size = 0;
    if (file == NULL)
    {
        return -1;
    }
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    return size;
}

void manejar_error(const char *mensaje)
{
    perror(mensaje);
    exit(EXIT_FAILURE);
}

int existe(const char *nombre)
{
    FILE *archivo = NULL;
    archivo = abrir_archivo(nombre, "r");
    if (archivo != NULL)
    {
        cerrar_archivo(archivo);
        return 1;
    }
    return 0;
}

void renombrar_archivo(const char *path, const char *nuevo_nombre)
{
    rename(path, nuevo_nombre);
}
