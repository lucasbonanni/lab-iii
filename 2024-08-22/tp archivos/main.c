#include <stdio.h>
#include <stdlib.h>

#define PRODUCTOS_POR_LOTE 10
#define ARCHIVO_PRODUCTOS "producto.txt"

// Declaración de funciones con prototipo
void producir_productos(void);
void consumir_productos(void);

int main(void) {
    int opcion;

    do {
        printf("\n1. Producir productos\n");
        printf("2. Consumir productos\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");
        if (scanf("%d", &opcion) != 1) {
            fprintf(stderr, "Error al leer la opción. Saliendo...\n");
            exit(1);
        }

        switch (opcion) {
        case 1:
            producir_productos();
            break;
        case 2:
            consumir_productos();
            break;
        case 3:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opción no válida. Intente nuevamente.\n");
            break;
        }
    } while (opcion != 3);

    return 0;
}

// Definición de la función para producir productos
void producir_productos(void) {
    FILE *archivo_produccion;
    int i;

    archivo_produccion = fopen(ARCHIVO_PRODUCTOS, "w");
    if (archivo_produccion == NULL) {
        fprintf(stderr, "Error al abrir el archivo para producción.\n");
        exit(1);
    }

    for (i = 1; i <= PRODUCTOS_POR_LOTE; i++) {
        if (fprintf(archivo_produccion, "PRODUCTO-%02d\n", i) < 0) {
            fprintf(stderr, "Error al escribir en el archivo.\n");
            fclose(archivo_produccion);
            exit(1);
        }
    }

    fclose(archivo_produccion);
    printf("Productos producidos y almacenados en %s.\n", ARCHIVO_PRODUCTOS);
}

// Definición de la función para consumir productos
void consumir_productos(void) {
    FILE *archivo_consumo;
    char linea[50];

    archivo_consumo = fopen(ARCHIVO_PRODUCTOS, "r");
    if (archivo_consumo == NULL) {
        fprintf(stderr, "Error al abrir el archivo para consumo.\n");
        exit(1);
    }

    printf("Consumiendo productos:\n");
    while (fgets(linea, sizeof(linea), archivo_consumo) != NULL) {
        printf("%s", linea);
    }

    if (ferror(archivo_consumo)) {
        fprintf(stderr, "Error al leer el archivo.\n");
        fclose(archivo_consumo);
        exit(1);
    }

    fclose(archivo_consumo);
}
