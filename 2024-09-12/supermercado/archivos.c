#include "archivos.h"
#include <stdio.h>
#include <stdlib.h>

FILE *fp;

int inLeerArchivo(void *buffer) { 
    long tamano;
    tamano = inObtenerTamanoArchivo();
    return fread(buffer, 1, tamano, fp);
}

long inObtenerTamanoArchivo(void) {
    long tamano;
    fseek(fp, 0, SEEK_END);   
    tamano = ftell(fp);      
    fseek(fp, 0, SEEK_SET);  
    return tamano;
}
