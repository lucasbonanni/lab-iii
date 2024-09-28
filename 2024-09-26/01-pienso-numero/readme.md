# “Pienso un número”
El juego se llama “Pienso un Numero”.
Se trata de un proceso PIENSO y otro JUGADOR (1 sólo jugador).
Ambos procesos utilizan MEMORIA COMPARTIDA:

```c
struct juego
{
    charnombre_jugador[LARGO_NOMBRE];
    intnumero_pensado. // 0=indica sin número, del 1 a 99 número a verificar.
    intestado_acierto // 0=No acierto, 1=acierto.
}
```

Proceso PIENSO: (MSG_PIENSO)
1. “Piensa un número”, genera en forma aleatoria un número del 1 al 99 y lo guarda
en una variable local intlocal_pienso_un_numero;
2. Inicializa la MEMORIA COMPARTIDA y el SEMÁFORO.
3. Espera el semáforo.
    1. Si numero_pensado<> 0 y estado_acierto =0
        1. Si numero_pensado = local_pienso_un_numero.
        Actualiza estado_acierto = 1
        2. Si numero_pensado<>local_pienso_un_numero.
        Actualiza numero_pensado = 0 y estado_acierto =0
4. Libero el SEMÁFORO.
5. Si hubo acierto, muestra por pantalla el nombre del jugador (sacarlo de MEMORIA
COMPARTIDA) ganador y finaliza.
6. Si no hubo acierto, regresa al punto 3.
---

Proceso JUGADOR: <br>
Solicita por teclado el nombre del jugador y lo graba en MEMORIA COMPARTIDA.
1. Espera el semáforo.
2. Verifica de MEMORIA COMPARTIDA:
   1. Si numero_pensado = 0 y estado_acierto =0
      1. Genera un número al azar de 1 al 99 (no repetitivos).
      2. Actualiza la variable numero_pensado con el número generado.
    2. Si numero_pensado<> 0 y estada_acierto=1
        1. Acertó, muestra por pantalla la cantidad de intentos.
3. Liberar el semáforo.
4. Si no hubo acierto, repite desde el punto 1.
5. Si hubo acierto, finaliza.
