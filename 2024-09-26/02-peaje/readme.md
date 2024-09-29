# Ejercicio 2: Simulación de peaje
Un PEAJE posee M vías (M es recibido por parámetro) representadas por un vector en
memoria compartida.

```c
int vehiculos_en_cola[CANTIDAD_DE_VIAS]; //cantidad de vehículos en cola por vía.
```

Además, existe otro proceso que simula a los autos: AUTOS
El proceso PEAJE atiende a una vía por vez cada N ms (N aleatorio entre 100 y 5000ms).
Atiende siempre en un orden establecido VIA 1,2,3,4…M (y vuelve a empezar) restando un
vehículo de la vía correspondiente. Si encuentra una vía con más de 10 vehículos en cola,
deberá liberarla (pone la cantidad en 0).
El proceso PEAJE lleva un archivo con la cantidad de veces que tuvo que realizar una
liberación (más de 10 vehículos en cola). Sólo con la cantidad de veces.
El proceso PEAJE muestra en pantalla en cada ciclo el total de vehículos en cola en cada vía:
VIA [1]: 5 Vehículos.
VIA [2]: 3 Vehículos.
VIA [3]: 3 Vehículos.
El proceso AUTOS verifica qué vía tiene menos vehículos y suma uno a la cantidad en la vía
seleccionada. Esto lo repite cada N ms (N aleatorio entre 400 y 600ms).
EL proceso AUTOS debe mostrar por pantalla la vía seleccionada en cada caso.

Ambos procesos PEAJE y AUTOS reciben por parámetro la cantidad de vías disponibles (M).
Realizar la solución utilizando MEMORIA COMPARTIDA y SEMÁFAROS (siempre que sea
necesario). 
En total son 2 procesos corriendo en forma simultánea. Se debe mostrar la
actividad de cada proceso. 
El PEAJE, es quien inicializa el semáforo y los datos de inicio. 

## Proceso Peaje
- PEAJE posee M vías (M es recibido por parámetro) representadas por un vector en
memoria compartida.
- El proceso PEAJE atiende a una vía por vez cada N ms (N aleatorio entre 100 y 5000ms)
- Atiende siempre en un orden establecido VIA 1,2,3,4…M (y vuelve a empezar) restando un
vehículo de la vía correspondiente
- Si encuentra una vía con más de 10 vehículos en cola, deberá liberarla (pone la cantidad en 0)
- El proceso PEAJE muestra en pantalla en cada ciclo el total de vehículos en cola en cada vía:

```shell
    VIA [1]: 5 Vehículos.
    VIA [2]: 3 Vehículos.
    VIA [3]: 3 Vehículos.
```
- El PEAJE, es quien inicializa el semáforo y los datos de inicio. 


## Proceso Auto
- reciben por parámetro la cantidad de vías disponibles (M).
- El proceso AUTOS verifica qué vía tiene menos vehículos y suma uno a la cantidad en la vía
seleccionada. Esto lo repite cada N ms (N aleatorio entre 400 y 600ms).
- EL proceso AUTOS debe mostrar por pantalla la vía seleccionada en cada caso.
