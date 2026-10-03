# Unidad 06 — Ejercicios

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

Primero predice cuántas vueltas habrá y cuáles son el primer y último valores. Después guarda, compila y contrasta la salida completa.

## 1. Trazar un `while`

Ejecuta `ejemplos/01-while.c` con inicio 1, 3 y 4. Anota número de vueltas, número de comprobaciones y valor final de `paso`. Explica el riesgo de quitar su actualización, sin ejecutar esa variante sin fin.

## 2. Revisar el acumulador

En `ejemplos/02-for.c`, cambia el valor inicial de `limite` de 5 a 1 y después a 0. Predice las sumas y el mensaje completo. ¿Por qué inicializar `suma` dentro del cuerpo impediría acumular correctamente varias vueltas?

## 3. Comparar controles

Explica la salida de `ejemplos/03-do-while.c`. Cambia ambas condiciones de `< 0` a `< 3`: ¿cuántas vueltas realiza cada ciclo? En `ejemplos/04-saltos.c`, justifica qué ocurre con 2, 7, 8 y 9, incluyendo si hay impresión y actualización.

## 4. Tabla de multiplicar

Crea `tabla.c` con tabla inicial 7. Admite tablas de 1 a 10 y rechaza las demás antes de repetir. Imprime diez filas, factores de 1 a 10:

```text
7 x 1 = 7
7 x 2 = 14
```

Continúa hasta `7 x 10 = 70`. Comprueba también tablas 1, 10, 0 y 11. La letra `x` en el mensaje es texto; el cálculo usa `*`.

## 5. Suma hasta un límite

Crea `suma.c` con un límite entre 0 y 100. Suma los enteros desde 1 hasta el límite inclusive. Para límite cero no hay términos y la suma es cero.

| Límite | Salida |
|---:|---|
| 0 | `Suma: 0` |
| 1 | `Suma: 1` |
| 5 | `Suma: 15` |
| 100 | `Suma: 5050` |
| -1, 101 | `Limite invalido.` y fallo |

Usa un ciclo, no una fórmula que evite practicar el recorrido. Explica el papel de cada variable.

## 6. Cuenta descendente

Crea `cuenta.c`: inicio entre 0 y 10, imprime desde ese valor hasta cero inclusive y luego `Despegue.`. Para inicio 3:

```text
3
2
1
0
Despegue.
```

Comprueba inicio 0, 1, 10 y -1. ¿Cuántas filas numéricas hay con inicio cero? ¿Cuál es el valor del contador después de actualizarlo tras imprimir cero? Usa `int`, como en el curso.
