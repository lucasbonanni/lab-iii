#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "colas.h"
#include "def.h"
#include "func.h"
#include "semaforo.h"

/*Lista de saldos donde el indice es cod_client*/
int saldos[1000];
/*Inicializo 5 saldos*/
void inicializar_saldos(void)
{
    saldos[0] = 1000;
    saldos[1] = 2000;
    saldos[2] = 3000;
    saldos[3] = 4000;
    saldos[4] = 5000;
}

mensaje consulta_saldo(int cod_cliente)
{
    mensaje msg;
    int saldo;
    saldo = saldos[cod_cliente];
    msg.int_evento = EVT_RTA_SALDO;
    snprintf(msg.char_mensaje, sizeof(msg.char_mensaje), "cliente: %d saldo: %d", cod_cliente, saldo);
    // sscanf(msg.char_mensaje, "%d|%d", &cod_cliente, &saldo);
    return msg;
}

mensaje realizar_deposito(int cod_cliente, int importe)
{
    mensaje msg;
    int saldo;
    saldo = saldos[cod_cliente];
    saldo += importe;
    saldos[cod_cliente] = saldo;
    msg.int_evento = EVT_RTA_DEPOSITO_OK;
    snprintf(msg.char_mensaje, sizeof(msg.char_mensaje), "cliente: %d saldo: %d", cod_cliente, saldo);
    // sscanf(msg.char_mensaje, "cliente: %d saldo: %d", &cod_cliente, &saldo);
    return msg;
}

mensaje realizar_extraccion(int cod_cliente, int importe)
{
    mensaje msg;
    int saldo;
    saldo = saldos[cod_cliente];
    if (saldo >= importe)
    {
        saldo -= importe;
        saldos[cod_cliente] = saldo;
        msg.int_evento = EVT_RTA_EXTRACCION_OK;
        /* Inicializar msg.char_mensaje */
            snprintf(msg.char_mensaje, sizeof(msg.char_mensaje), "cliente: %d saldo: %d", cod_cliente, saldo);
        // sscanf(msg.char_mensaje, "cliente: %d saldo: %d", &cod_cliente, &saldo);
    }
    else
    {
        msg.int_evento = EVT_RTA_EXTRACCION_NOK;
        snprintf(msg.char_mensaje, sizeof(msg.char_mensaje),  "%d|Saldo insuficiente", cod_cliente);
        // sscanf(msg.char_mensaje, "%d|Saldo insuficiente", &cod_cliente);
    }
    return msg;
}

mensaje procesar_evento(int id_cola_mensajes, mensaje msg)
{
    mensaje msg_respuesta;
    int cod_cliente, importe;
    char *ptr[10];
    /* Inicializar msg_respuesta */
    msg_respuesta.int_evento = -1;
    /* Eventos */
    switch (msg.int_evento)
    {
        case EVT_CONSULTA_SALDO:
            printf("Consulta de saldo\n");
            cod_cliente = atoi(msg.char_mensaje);
            msg_respuesta = consulta_saldo(cod_cliente);
            // Enviar respuesta
            enviar_mensaje(id_cola_mensajes, &msg_respuesta);
            break;
        case EVT_DEPOSITO:
            printf("Deposito\n");
            // Realizar deposito
            dividir_mensaje(msg.char_mensaje, "|", ptr);
            cod_cliente = atoi(ptr[0]);
            importe = atoi(ptr[1]);
            msg_respuesta = realizar_deposito(cod_cliente, importe);
            // Enviar respuesta
            enviar_mensaje(id_cola_mensajes, &msg_respuesta);
            break;
        case EVT_EXTRACCION:
            printf("Extraccion\n");
            // Realizar extraccion
            dividir_mensaje(msg.char_mensaje, "|", ptr);
            cod_cliente = atoi(ptr[0]);
            importe = atoi(ptr[1]);
            msg_respuesta = realizar_extraccion(cod_cliente, importe);
            break;
        default:
            printf("\nEvento sin definir\n");
            break;
    }
    return msg_respuesta;
}

int main(int argc, char *argv[])
{
    int id_cola_mensajes, id_semaforo;
    mensaje msg;
    mensaje msg_rta;
    id_cola_mensajes = creo_id_cola_mensajes();
    printf("Cola de mensajes creada con id: %d\n", id_cola_mensajes);
    id_semaforo = crear_semaforo(CLAVE_BASE);
    
    while (1)
    {
        esperar_semaforo(id_semaforo);
        // Esperar por un mensaje
        recibir_mensaje(id_cola_mensajes, &msg);
        printf("Mensaje recibido: %s\n", msg.char_mensaje);
        // Procesar el mensaje
        msg_rta = procesar_evento(id_cola_mensajes, msg);
        // Enviar respuesta
        enviar_mensaje(id_cola_mensajes, &msg_rta);
        levantar_semaforo(id_semaforo);
        usleep(SLEEP_DURATION);
        system("clear");
    }
    borrar_mensajes(id_cola_mensajes);
    borrar_cola_de_mensajes(id_cola_mensajes);
}
