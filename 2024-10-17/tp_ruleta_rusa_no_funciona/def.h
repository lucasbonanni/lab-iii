#ifndef _DEF_H
#define _DEF_H

#define CLAVE_BASE 33
typedef enum
{
     MSG_NADIE,
     MSG_REVOLVER,
     MSG_JUGADOR
} Destinos;

typedef enum
{
     EVT_NINGUNO,
     EVT_INICIO,
     EVT_DISPARO,
     EVT_SALVADO,
     EVT_FIN
} Eventos;

#define LARGO_MENSAJE 1024
struct tipo_mensajes
{
     long mtype;
     int int_evento;
     int numero_jugador;
     int numero_elegido;
};

typedef struct tipo_mensajes mensaje;

struct dato_jugador
{
    int numero_jugador;
    int id_colamensaje;
};
typedef struct dato_jugador jugador;

#define DESDE 1
#define HASTA 99
#define CANT_JUGADORES 6

#endif
