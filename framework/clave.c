#include <sys/ipc.h>
#include <sys/types.h> // Add this line to include the header file that defines 'key_t'
#include <stdlib.h>

key_t creo_clave(int clave_base);
{
    key_t clave;
    clave = ftok("/bin/ls", clave_base);
    if (clave == (key_t)-1)
    {
        //perror("Error al crear la clave");
        exit(-1);
    }
    return clave;
}
