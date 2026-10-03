# Unidad 11 — Ejercicios

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

En cada ejercicio anota capacidad, cantidad utilizada e índices válidos antes de compilar. No pruebes accesos fuera de límites.

## 1. Seleccionar una posición

Sin ejecutar `ejemplos/01-posiciones.c`, predice su salida. ¿Cuál es el índice del cuarto producto? ¿Qué cambia si asignas 15 a `existencias[3]`? ¿Por qué `[4]` no selecciona el cuarto?

## 2. Seguir el recorrido

Haz una tabla con `i`, la condición `i < cantidad` y el valor que se imprime en `ejemplos/02-recorrido.c`. Incluye la comprobación final con `i = 4`. Explica por qué no se accede en esa última comprobación. ¿Qué ocurriría conceptualmente con `<=`? No ejecutes esa versión.

## 3. Ceros y registros

En `ejemplos/03-capacidad.c`, identifica qué posiciones están cargadas al finalizar. Explica la diferencia entre los dos ceros: el dato cargado y un cero en una posición sin cargar. Predice la salida si se omite la segunda inserción completa, conservando solo la de 18.

## 4. Visitas durante una semana

Crea un arreglo constante con `{3, 0, 5, 2, 0, 4, 1}`. Muestra `Dia 1: 3` hasta `Dia 7: 1` mediante un ciclo, calculando la cantidad con `sizeof`. Distingue el día presentado (1–7) del índice (0–6). Todavía no calcules estadísticas.

## 5. Copia independiente

Copia `{4, 0, 7, 2}` a otro arreglo de cuatro elementos con un ciclo. Cambia a 9 la posición 1 de la copia. Imprime ambos valores de cada índice en una línea. El original debe conservar el cero; la copia debe contener 9. Explica por qué la asignación completa entre arreglos no resuelve el ejercicio.

## 6. Inserciones con colección llena

Capacidad 3, arreglo inicial `{4, 0, 0}`, `usados = 1`. Intenta insertar, en orden, las propuestas `{7, 0, 9}`. Cada propuesta necesita comprobación de espacio antes de escribir. Si no cabe, muestra `Sin espacio para 9.` y sigue sin cambiar `usados`. Al final deben quedar tres datos: 4, 7 y 0.

Trabaja después con `usados = 0` y con `usados = 3`, conservando un arreglo inicializado. Predice qué propuestas caben en cada variante. Estas variantes cambian el estado inicial declarado; no obtienen la cantidad de una entrada externa.
