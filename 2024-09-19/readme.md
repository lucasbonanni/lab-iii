# Primer parcial

## Enunciados
Tu mercado por precio:
En un mercado de barrio quieren automatizar el control de las cajas, por lo que solicitan realizar un sistema de derivación de los
productos. En total tienen 2 cajas. Una de las cajas es para productos con costo total
menor a $20000 y la otra para mayores o iguales a $20000
Todos los compradores hacen una única fila y a su turno, van a la caja que necesiten, de
acuerdo al dinero que cuesten en total sus productos.
Se puede contar con un array (arreglo) de estructuras que cuente con el precio y la descripción del producto.
Realizar un menu para el derivador que permita el ingreso por teclado de la
descripción del producto y del precio.
Dependiendo si es menor a $20000, o igual o mayor, se dirigirá a la caja 1 o 2. Se contará con un proceso por cada caja (2 cajas).
Para comunicar debe utilizarse semáforo y archivos.
Cada 500ms cada caja debe chequear si tiene un nuevo comprador.
En total son 3 procesos corriendo en forma simultanea.
Se debe mostrar la actividad de cada proceso.

Consignas
1) Leer todo el enunciado.
2) Resolver el ejercicio.
3) Enviar las resolución como respuesta a esta actividad en archivo comprimido .tar
o .tar.gz
Condiciones de corrección (si no se cumple lo siguiente, no se corrige)
• El programa debe compilar sin errores.
• El programa debe correr sin errores de memoria.
• Debe estar correctamente identado.
• Utilizar constantes.
Puntos a tener en cuenta
• Los nombres de las variables deben ser descriptivos de su función (sobre todo en el
main).
• Comentar el código todo lo posible.
• Toda variable o arreglo definido en forma dinámica debe ser liberado al finalizar el
programa.
