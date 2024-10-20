#ifndef _DEFINICIONES_H
#define _DEFINICIONES_H
 


typedef enum
{
	MSG_NADIE,
	MSG_PIENSO,
	MSG_JUGADOR
}Destinos;

typedef enum
{
	EVT_NINGUNO,
     EVT_NUMERO,
     EVT_ACERTO,
     EVT_NO_ACERTO,
     EVT_FINALIZAR
}Eventos;



#define DESDE 1
#define HASTA 99

#endif
