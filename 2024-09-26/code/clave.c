#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "clave.h"

key_t crear_clave_ipc(int id) {
    key_t clave;
    clave = ftok("/bin/ls", id);
    if (clave == (key_t) -1) {
        printf("No se pudo crear la clave IPC\n");
        exit(-1);
    }
    return (clave);
}

