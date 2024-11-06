#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int* ptr = NULL;
    ptr = (int*)malloc(sizeof(int));
    *ptr = 5;
    printf("Value of ptr: %d\n", *ptr);
    return 0;
}
