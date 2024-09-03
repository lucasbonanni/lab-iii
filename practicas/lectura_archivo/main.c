#include <archivos.h>

const char* file_name = "archivo.txt";

int main( int argc, char *argv[] ) {
    file_write(file_name, "Hola mundo\n");
    file_append_line(file_name, "Segunda linea");
    return 0;
}