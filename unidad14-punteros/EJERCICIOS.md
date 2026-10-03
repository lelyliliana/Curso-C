# Unidad 14 — Ejercicios

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

Escribe primero qué objeto señala cada puntero, quién puede modificarlo y cuánto dura. No ejecutes desreferencias de punteros nulos, sin inicializar o fuera de duración.

## 1. Valor y dirección

Predice las líneas de `ejemplos/01-direccion.c` que contienen valores. ¿Por qué no se puede exigir una dirección concreta en la salida? Distingue `cantidad`, `&cantidad`, `acceso`, `*acceso` y `&acceso`.

## 2. Copias durante una llamada

Sigue `ejemplos/02-argumentos.c`. Explica por qué la asignación a `valor` no cambia `cantidad`, pero la asignación a `*acceso` sí. ¿Por qué `acceso = NULL` dentro de la auxiliar no vuelve nulo el puntero de `main`?

## 3. Rechazo antes de escribir

En `ejemplos/03-validar.c`, prueba valores iniciales 100, 1, 0, -1 y 101, cambiando solo el inicializador y recompilando. El primer descuento solo debe aceptar 100 y 1. Para los otros debe conservar el valor. No cambies el objeto por una dirección inventada para «probar validez».

## 4. Lectura y duración

Explica la salida de `ejemplos/04-const.c`. Clasifica sin ejecutar: escribir mediante `lectura`, reasignar `acceso_fijo` y modificar el entero mediante `acceso_fijo`. Explica también por qué devolver la dirección de una variable local ordinaria no permite seguir usándola después de volver.

## 5. Intercambiar

Crea `bool intercambiar(int *a, int *b)`: rechaza `NULL` antes de tocar las salidas, intercambia dos enteros mediante un temporal y admite que ambos punteros señalen el mismo entero. Con 4 y 9 espera 9 y 4. El caso nulo debe conservar el objeto válido que recibió.

## 6. Cociente y resto

Crea `bool dividir_con_resto(int objetos, int capacidad, int *cociente, int *resto)`. Objetos 0–100, capacidad 1–100, salidas válidas, modificables y distintas. Devuelve `false` sin modificar salidas ante un dato inválido, un puntero nulo o dos salidas iguales.

Con (17, 5) espera (3, 2); con (0, 5), (0, 0); con (100, 1), (100, 0). Rechaza capacidad cero, objetos 101 y `&resultado` como ambas salidas. Comprueba que el valor previo de las salidas permanece cuando hay rechazo.
