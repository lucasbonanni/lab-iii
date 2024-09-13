#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>
#include "clave.h"

key_t creo_clave(int clave_base)
{
    key_t clave;
    clave = ftok("/bin/ls", clave_base);
    if (clave == (key_t)-1)
    {
        exit(-1);
    }
    return clave;
}
