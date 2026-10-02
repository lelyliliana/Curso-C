# Unidad 04 — Ejercicios y pequeño proyecto

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

Antes de ejecutar: escribe entradas fijas, fórmula, unidades y resultado esperado. Si modificas valores, comprueba que los cálculos caben en sus tipos y que no divides por cero.

## 1. Predecir operaciones

Anota el resultado y explica la agrupación de `2 + 3 * 4`, `(2 + 3) * 4`, `10 - 3 - 2`, `9 / 4` y `9 % 4`.

Después sigue estas dos instrucciones: `int saldo = 10;` y `saldo = saldo - 3;`. ¿Cuál es el valor final? ¿Por qué la segunda instrucción no es una ecuación matemática?

## 2. Rectángulo

Crea `rectangulo.c`: `double ancho = 3.5;` y `double alto = 2.0;`, ambos en metros. Calcula el área y el perímetro y muestra dos decimales.

```text
Area: 7.00 m2
Perimetro: 11.00 m
```

Comprueba también ancho 1.0 y alto 1.0: área 1.00 m2 y perímetro 4.00 m. Explica por qué las unidades del área y el perímetro son distintas.

## 3. Reparar una división

Un programa declara `int total = 5;`, `int personas = 2;` y `double promedio = total / personas;`. Muestra 2.00, pero queremos 2.50.

Escribe dos correcciones que conviertan un operando **antes** de dividir. Explica por qué `(double)(total / personas)` no resuelve el problema. No cambies el divisor a cero para experimentar.

## 4. Cajas completas

Modifica `ejemplos/03-reparto.c` dejando `por_caja = 5`. Guarda y recompila para cada caso:

| Objetos | Cajas completas esperadas | Sobrantes esperados |
|---:|---:|---:|
| 0 | 0 | 0 |
| 4 | 0 | 4 |
| 5 | 1 | 0 |
| 17 | 3 | 2 |

¿Tres cajas completas bastan para guardar los 17 objetos? Justifica con palabras, sin añadir condiciones que aún no has aprendido.

## 5. Tiempo y unidades

Modifica `ejemplos/04-tiempo.c` para 0, 59, 60 y 135 minutos. Predice horas, minutos restantes y segundos. ¿Por qué guardar el resultado de minutos por 60 en una variable llamada `horas` sería un error de significado aunque compile?

## 6. Promedio de tres notas

Crea `promedio.c` con notas enteras 7, 8 y 8. Guarda su suma y calcula un promedio `double` convirtiendo antes de dividir por 3. Muestra:

```text
Suma: 23
Promedio: 7.67
```

Prueba también 6, 6 y 6: suma 18 y promedio 6.00. Estas notas se limitan a enteros entre 0 y 10. Mostrar dos decimales no significa que el resultado matemático 23/3 sea exactamente 7.67.

## 7. Proyecto: recibo

Crea `recibo.c` con precio, cantidad y envío en las unidades indicadas en la guía. Calcula subtotal y total; separa el total en unidades y centavos para mostrar:

```text
Subtotal: 3750 centavos
Envio: 500 centavos
Total: 42.50
```

No escribas `42.50` directamente en el mensaje. Debe salir del cálculo. Usa `%02d` para la parte de centavos.

Comprueba también estos casos editando las inicializaciones, guardando y recompilando:

| Precio en centavos | Cantidad | Envío en centavos | Subtotal | Total mostrado |
|---:|---:|---:|---:|---|
| 1250 | 3 | 500 | 3750 | `42.50` |
| 1005 | 1 | 0 | 1005 | `10.05` |
| 999 | 2 | 1 | 1998 | `19.99` |
| 0 | 0 | 0 | 0 | `0.00` |

Trabaja solo con estos casos conocidos: no se implementa validación para entradas arbitrarias. Explica por qué el segundo caso necesita relleno con cero y por qué elegir enteros no elimina el riesgo de desbordamiento.
