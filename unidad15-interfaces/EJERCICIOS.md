# Unidad 15 — Ejercicios

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

Para cada función escribe qué memoria proporciona el llamador, qué cantidad se pasa y qué cambia ante éxito o rechazo.

## 1. Parámetro y cantidad

En `ejemplos/01-parametro.c`, identifica dónde se calcula la cantidad. Explica por qué no debemos trasladar la fórmula de `sizeof` al parámetro. ¿Qué precondición permite `mostrar(NULL, 0)`? ¿Por qué escribir `[3]` en el parámetro no mediría el arreglo recibido?

## 2. Límite de un arreglo

Traza `ejemplos/02-limite.c`. Indica el elemento señalado por `datos + 1` y el papel de `datos + cantidad`. Explica por qué el último se puede formar y comparar, pero no leer mediante `*`. No ejecutes ese acceso inválido.

## 3. Pruebas de colección

Construye aplicación y pruebas como ejecutables distintos. Añade casos a las pruebas compartidas: un dato de valor 100, cinco valores 100, un dato -1 y resultado inicial 77. Espera sumas 100 y 500; ante -1 espera rechazo y salida 77. Añade también mínimo de un único cero. No necesitas declarar una cantidad mayor que la memoria legible para esos casos.

## 4. Capacidad de cadena

Prueba `copiar_texto` con destino de seis `char` y origen `"abcde"`: cabe exactamente con el terminador. Prueba `"abcdef"`: debe rechazarse conservando el texto anterior. Con origen vacío y destino de un elemento espera éxito. Distingue un origen vacío de `NULL`. Origen y destino no se solapan.

## 5. Filtro con capacidad explícita

Crea la interfaz `filtrar_minimo` descrita en la guía. Origen: de cero a cinco enteros 0–100; destino: capacidad indicada; resultado de cantidad por `size_t *`. Conserva orden, admite resultados vacíos y devuelve `false` sin cambiar destino ni cantidad si los datos son inválidos o no caben todos.

Con `{8, 2, 0, 10, 5}`, umbral 5 y destino de tres elementos, espera `{8, 10, 5}` y cantidad 3. Con umbral 0 no caben cinco en ese destino y debe conservar sus valores anteriores. Con umbral 101 y destino nulo de capacidad cero espera éxito y cantidad cero.

## 6. Verificar la misma implementación

Crea un `main` de presentación y otro de pruebas que enlacen el mismo `filtro.c`. En las pruebas cubre lleno, vacío, rechazo por capacidad, un 101 y argumentos nulos. Ejecuta las llamadas fuera de `assert` y conserva el control que impide desactivar las aserciones al construir las pruebas. Explica qué diferencia hay entre probar el módulo y copiar otra versión del algoritmo dentro del programa de pruebas.
