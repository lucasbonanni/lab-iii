#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "archivos.h"
#include "def.h"

FILE *abrir_archivo(char *nombreArchivo, char *modo) {
    FILE *archivo = fopen(nombreArchivo, modo);
    return archivo;
}

void cerrar_archivo(FILE *fd) {
    fclose((FILE *)fd);
}


int leer_linea(FILE *fd, char *buffer, int cantidad) {
    size_t longitud;
    if (fgets(buffer, cantidad, fd) != NULL) {
        longitud = strlen(buffer);
        if (longitud > 0 && buffer[longitud - 1] == '\n') {
            buffer[longitud - 1] = '\0';
            return 1;
        }
    }
    return 0;
}


int escribir_linea(FILE *fd, char *buffer) {
    return fprintf(fd, "%s\n", buffer);
}


int renombrarArchivo(char *nombreViejo, char *nombreNuevo) {
    return rename(nombreViejo, nombreNuevo);
}

int eliminar_archivo(const char *nombre_archivo) {
    if (remove(nombre_archivo) == 0) {
        return 0; // Indica éxito
    } else {
        perror("Error al eliminar el archivo");
        return -1;
    }
}
