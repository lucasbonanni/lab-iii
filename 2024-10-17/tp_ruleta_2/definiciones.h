#ifndef _DEFINICIONES_H
#define _DEFINICIONES_H
 
#define CLAVE_BASE 33

typedef enum
{
	MSG_NADIE,
	MSG_REVOLVER,
	MSG_JUGADOR
}Destinos;

typedef enum
{
     EVT_NINGUNO,
     EVT_INICIO,
     EVT_DISPARO,
     EVT_SALVADO,
     EVT_FIN
}Eventos;



#define DESDE 1
#define HASTA 6
#define CANT_JUGADORES 6

#endif
