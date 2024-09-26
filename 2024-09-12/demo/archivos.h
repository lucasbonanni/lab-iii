#ifndef _ARCHIVOS
#define _ARCHIVOS



FILE *abrir_archivo(char *nombreArchivo, char *modo);
void cerrar_archivo(FILE *fd);
int leer_linea(FILE *fd, char *buffer, int cantidad);
int escribir_linea(FILE *fd, char *buffer);
int renombrarArchivo(char *nombreViejo, char *nombreNuevo);
int eliminar_archivo(const char *nombre_archivo);

#endif


