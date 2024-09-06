#include "archivos.h"
#include <stdlib.h>

static FILE *file = NULL;

int abrir_archivo(const char *path, const char *mode)
{
    if (file != NULL)
    {
        manejar_error("Archivo ya abierto.");
        return -1;
    }
    file = fopen(path, mode);
    if (file == NULL)
    {
        manejar_error("Error al abrir el archivo.");
        return -1;
    }
    return 0;
}

int cerrar_archivo(void)
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
    if (abrir_archivo(path, "w") == 0)
    {
        cerrar_archivo();
        return 0;
    }
    return -1;
}

int borrar_archivo(const char *path)
{
    return remove(path);
}

char *leer_archivo(const char *path)
{
    long size = 0;
    char *content = NULL;
    if (abrir_archivo(path, "r") != 0)
    {
        return NULL;
    }
    size = tamano_archivo(path);
    content = (char *)malloc((size + 1) * sizeof(char));
    if (content == NULL)
    {
        cerrar_archivo();
        manejar_error("Error al reservar memoria.");
        return NULL;
    }
    fread(content, sizeof(char), size, file);
    content[size] = '\0';
    cerrar_archivo();
    return content;
}

int escribir_archivo(const char *path, const char *data)
{
    int result = 0;
    if (abrir_archivo(path, "w") != 0)
    {
        return -1;
    }
    result = fputs(data, file);
    cerrar_archivo();
    return result;
}

int agregar_linea_archivo(const char *path, const char *line)
{
    int result = 0;
    if (abrir_archivo(path, "a") != 0)
    {
        return -1;
    }
    result = fputs(line, file);
    cerrar_archivo();
    return result;
}

int eliminar_linea_archivo(const char *path, int numero_linea)
{
    FILE *temp = NULL;
    char buffer[256];
    int linea_actual = 1;
    if (abrir_archivo(path, "r") != 0)
    {
        return -1;
    }
    temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        manejar_error("Error al abrir el archivo temporal.");
        cerrar_archivo();
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
    cerrar_archivo();
    remove(path);
    rename("temp.txt", path);
    return 0;
}

int insertar_linea_archivo(const char *path, const char *linea, int posicion)
{
    FILE *temp = NULL;
    char buffer[256] = {0};
    int linea_actual = 1;
    if (abrir_archivo(path, "r") != 0)
    {
        return -1;
    }
    temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        manejar_error("Error al abrir el archivo temporal.");
        cerrar_archivo();
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
    cerrar_archivo();
    remove(path);
    rename("temp.txt", path);
    return 0;
}

long tamano_archivo(const char *path)
{
    long size = 0;
    if (abrir_archivo(path, "r") != 0)
    {
        return -1;
    }
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    cerrar_archivo();
    return size;
}

void manejar_error(const char *mensaje)
{
    perror(mensaje);
    exit(EXIT_FAILURE);
}
