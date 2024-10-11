#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "colas.h"
#include "def.h"
#include "func.h"
#include "semaforo.h"

#define largo 10

void imprimir_menu(void)
{
    printf("1. Consultar saldo\n");
    printf("2. Depositar\n");
    printf("3. Extraer\n");
}

void procesar_evento(mensaje msg)
{
    // int i;
    // char *cadena[largo];
    // dividir_mensaje(msg.char_mensaje, "|", cadena);
    // for (i = 0; cadena[i] != NULL; i++) 
    // {
    //     printf("Mensaje: %s\n", cadena[i]);
    // }
    printf("Mensaje: %s\n", msg.char_mensaje);
}

int main(int argc, char *argv[])
{
    int id_cola_mensajes, cod_cliente, id_evento, importe, id_semaforo;
    mensaje msg;
    mensaje msg_rta;

    id_cola_mensajes = creo_id_cola_mensajes();
    printf("Cola de mensajes creada con id: %d\n", id_cola_mensajes);
    id_semaforo = crear_semaforo(CLAVE_BASE);
    inicializar_semaforo(id_semaforo, VERDE);
    while (1)
    {
        /*Imprimir menu*/
        imprimir_menu();
        /*Leer opción y validar*/
        printf("Ingrese una opcion: ");
        scanf("%d", &id_evento);
        switch (id_evento)
        {
        case 1:
            msg.int_evento = EVT_CONSULTA_SALDO;
            /* Ingresar cod_client */
            printf("Ingrese el codigo de cliente: ");
            scanf("%d", &cod_cliente);
            /* Copiar el cod_cliente al mensaje */
            snprintf(msg.char_mensaje, sizeof(msg.char_mensaje), "%d", cod_cliente);
            sscanf(msg.char_mensaje, "%d", &cod_cliente);
            // printf("Mensaje: %s\n", msg.char_mensaje);
            break;
        case 2:
            msg.int_evento = EVT_DEPOSITO;
            /* Ingresar cod_client */
            printf("Ingrese el codigo de cliente: ");
            scanf("%d", &cod_cliente);
            /* Ingresar importe */
            printf("Ingrese el importe: ");
            scanf("%d", &importe);
            /* Inicializar msg.char_mensaje */
            snprintf(msg.char_mensaje, sizeof(msg.char_mensaje), "%d|%d", cod_cliente, importe);
            /* mensaje cod_cliente|importe */
            sscanf(msg.char_mensaje, "%d|%d", &cod_cliente, &importe);
            break;
        case 3:
            msg.int_evento = EVT_EXTRACCION;
            /* Ingresar cod_client */
            printf("Ingrese el codigo de cliente: ");
            scanf("%d", &cod_cliente);
            /* Ingresar importe */
            printf("Ingrese el importe: ");
            scanf("%d", &importe);
            /* mensaje cod_cliente|importe */
            /* Inicializar msg.char_mensaje */
            snprintf(msg.char_mensaje, sizeof(msg.char_mensaje), "%d|%d", cod_cliente, importe);
            sscanf(msg.char_mensaje, "%d|%d", &cod_cliente, &importe);
            break;
        default:
            printf("Opcion incorrecta\n");
            continue;
        }
        esperar_semaforo(id_semaforo);
        enviar_mensaje(id_cola_mensajes, &msg);
        usleep(SLEEP_DURATION);
        levantar_semaforo(id_semaforo);
        recibir_mensaje(id_cola_mensajes, &msg_rta);
        procesar_evento(msg_rta);
        printf("continuar\n");
        scanf("%d", &cod_cliente);
        system("clear");
    };
    borrar_mensajes(id_cola_mensajes);
    borrar_cola_de_mensajes(id_cola_mensajes);
    return 0;
}
