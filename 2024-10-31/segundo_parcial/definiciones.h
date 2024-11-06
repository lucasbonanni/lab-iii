#ifndef _DEFINICIONES_H
#define _DEFINICIONES_H

#define CLAVE_BASE 33
#define LARGO_TMENSAJE 1024

typedef enum
{
	MSG_NADIE,
	MSG_ESPIRAL,
	MSG_MOSQUITO
} Destinos;

typedef enum
{
	EVT_NINGUNO,
	EVT_AVANZO,
	EVT_SOBREVIVIO,
	EVT_FIN
} Eventos;


typedef struct tipo_jugador tjugador;
struct tipo_jugador
{
	int nro_mosquito;
	int id_colamensaje;
};

typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
	long long_dest; 
	int int_rte;	
	int int_evento; 
	int metros;		
};

#define M_DESDE 3
#define M_HASTA 6

#define H_DESDE 1
#define H_HASTA 4

#define CANT_MOSQUITOS 2

#endif
