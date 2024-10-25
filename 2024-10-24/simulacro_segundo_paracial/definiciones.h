#ifndef _DEFINICIONES_H
#define _DEFINICIONES_H

#define CLAVE_BASE 33
#define LARGO_TMENSAJE 1024

typedef enum
{
	MSG_NADIE,
	MSG_PISTA,
	MSG_JUGADOR
} Destinos;

typedef enum
{
	EVT_NINGUNO,
	EVT_CORRO,
	EVT_FIN
} Eventos;

typedef enum
{
	CONEJO,
	GATO,
	PERRO
} Animales;

typedef struct tipo_jugador tjugador;
struct tipo_jugador
{
	int nro_jugador;
	int id_colamensaje;
	int tipo_animal;
};

typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
	long long_dest; // Destinatario
	int int_rte;	// Remitente
	int int_evento; // Numero de nevento
	int pasos;		// mensajse
};

#define DESDE 2
#define HASTA 5
#define CANT_JUGADORES 3

#endif
