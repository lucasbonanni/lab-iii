#include <sys/ipc.h>
#include <sys/types.h> // Add this line to include the header file that defines 'key_t'
#include <stdlib.h>

key_t creo_clave(int CLAVE_BASE)
{
    key_t clave;
    clave = ftok("/bin/ls", CLAVE_BASE);
    if (clave == (key_t)-1)
    {
        //perror("Error al crear la clave");
        exit(-1);
    }
    return clave;
}
