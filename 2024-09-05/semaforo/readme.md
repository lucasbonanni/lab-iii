Cada proceso (productor y consumidor) sabe el cambio de estado del semáforo mediante las operaciones de espera (`wait`) y señal (`signal`) que se realizan sobre el semáforo. Estas operaciones son gestionadas por el sistema operativo y permiten la sincronización entre los procesos.

### Operaciones de Semáforo

1. **Espera (wait)**: También conocida como `P` (proberen) o `down`, esta operación decrementa el valor del semáforo. Si el valor del semáforo es mayor que cero, el proceso continúa. Si el valor es cero, el proceso se bloquea hasta que el semáforo sea mayor que cero.

2. **Señal (signal)**: También conocida como `V` (verhogen) o `up`, esta operación incrementa el valor del semáforo. Si hay procesos bloqueados esperando en el semáforo, uno de ellos se desbloquea.

### Explicación código

1. **Inicialización del Semáforo**:
    - El productor inicializa el semáforo en 0 (rojo).
    - El consumidor también crea el semáforo, pero no lo inicializa (asume que ya está inicializado por el productor).

2. **Productor**:
    - Escribe datos en el archivo.
    - Levanta el semáforo (`levanta_semaforo`), incrementando su valor a 1 (verde).
    - Espera un intervalo antes de producir la siguiente partida.

3. **Consumidor**:
    - Espera a que el semáforo esté verde (`espera_semaforo`), decrementando su valor a 0 (rojo).
    - Lee y procesa los datos del archivo.
    - Borra el archivo y levanta el semáforo (`levanta_semaforo`), permitiendo que el productor escriba nuevos datos.

Este mecanismo asegura que solo un proceso acceda al archivo a la vez, evitando condiciones de carrera y garantizando la integridad de los datos.
