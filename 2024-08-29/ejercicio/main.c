#include <stdio.h>
#include "clave.h"

int main( int argc, char *argv[] ) {
    key_t  clave = creo_clave();
    printf("Clave: %d\n", clave);
    return 0;
}
