# Ejercicios — Unidad 20

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

## 1. Seguir la duración

El primer ejemplo tiene una variable puntero local y un bloque dinámico. Identifica cuál desaparece al salir del bloque, cuál requiere liberación y qué ocurriría si se olvidara esa liberación. Explica por qué no puedes liberar `&cantidad`.

## 2. Bytes, posiciones y límites

Sin ejecutar reservas gigantes, calcula la cantidad de bytes para diez enteros usando `sizeof`. Explica por qué `sizeof datos` no responde esa pregunta. Para una lista con usados 3 y capacidad 8, señala los índices que puedes leer. ¿Qué debe ocurrir al pedir capacidad 2 o `SIZE_MAX`?

## 3. Crecimiento y rechazo

Con una lista vacía, agrega 0, 100 y 25. Anota cantidad y capacidad tras cada operación. Luego intenta -1 y 101. Comprueba que los rechazos no cambian datos ni cantidad. Prueba reservar cero y liberar dos veces mediante el módulo, explicando por qué eso difiere de llamar dos veces a `free` con una dirección antigua.

## 4. Colección recibida por líneas

Crea un programa que pida cantidad 0–10 y después esa cantidad de valores 0–100. Reutiliza el lector y conversor de la Unidad 16. No publiques suma de una colección incompleta; ante rechazo o fin anticipado, libera lo reservado y termina con fracaso. Con cantidad cero, imprime total cero sin leer elementos.

Entrega fuente, comandos y resultados para `0`, `3` con 0/25/100, cantidad inválida y fin de entrada después de un solo valor. Describe qué haría el programa ante falta de memoria. No inventes lecturas desde direcciones liberadas.
