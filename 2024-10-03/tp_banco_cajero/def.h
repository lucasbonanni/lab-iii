#ifndef _DEF_H
#define _DEF_H

#define ROJO 0
#define VERDE 

#define CLAVE_BASE 33
#define SEMAFORO0 0

#define LARGO_TMENSAJE 1024
#define INTERVALO_PEDIDOS 2000

struct tipo_mensajes
{
	int 	int_evento;						//Numero de nevento
	char 	char_mensaje[LARGO_TMENSAJE];	//mensajse
};

typedef struct tipo_mensajes mensaje;

/*Eventos disponibles:
[01] EVT_CONSULTA_SALDO
Permite consultar el saldo de un cliente, como parámetro lleva COD_CLIENTE (código del
cliente)
[02] EVT_DEPOSITO
Permite realizar un depósito, como parámetros lleva |COD_CLIENTE|IMPORTE (código del
cliente, importe a depositar).
[03] EVT_EXTRACCION
Permite realizar una extracción, como parámetros lleva |COD_CLIENTE|IMPORTE (código del
cliente, importe a extraer).
[04] EVT_RTA_SALDO
Responde con el saldo del cliente “|COD_CLIENTE|SALDO”
[04] EVT_RTA_SALDO_NOK
Responde con el saldo del cliente “|COD_CLIENTE|ERROR”, donde ERROR es un texto con el
error (por ejemplo: cliente no encontrado).
[05] EVT_RTA_DEPOSITO_OK
Responde con el saldo del cliente después del depósito “|COD_CLIENTE|SALDO”
[06] EVT_RTA_DEPOSITO_NOK
Responde con el saldo del cliente después del depósito “|COD_CLIENTE|ERROR”, ” donde
ERROR es un texto con el error (por ejemplo: cliente no encontrado).
[07] EVT_RTA_EXTRACCION_OK
Responde con el saldo del cliente después de la extracción “|COD_CLIENTE|SALDO”
[08] EVT_RTA_EXTRACCION_NOK
Responde con el saldo del cliente después del depósito “|COD_CLIENTE|ERROR”, donde
ERROR es un texto con el error (por ejemplo: cliente no encontrado).
*/

typedef enum
{
	EVT_CONSULTA_SALDO,
	EVT_RTA_SALDO,
	EVT_RTA_SALDO_NOK,
	EVT_DEPOSITO,
	EVT_RTA_DEPOSITO_OK,
	EVT_RTA_DEPOSITO_NOK,
	EVT_EXTRACCION,
	EVT_RTA_EXTRACCION_OK,
	EVT_RTA_EXTRACCION_NOK
}Eventos;

#endif
