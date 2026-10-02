# Unidad 04 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Operaciones y actualización

| Expresión | Agrupación o explicación | Resultado |
|---|---|---:|
| `2 + 3 * 4` | `2 + (3 * 4)` | 14 |
| `(2 + 3) * 4` | La suma está agrupada | 20 |
| `10 - 3 - 2` | `(10 - 3) - 2` | 5 |
| `9 / 4` | División de enteros, truncada hacia cero | 2 |
| `9 % 4` | Resto: `9 = 2 * 4 + 1` | 1 |

El saldo queda en 7. La asignación obtiene el resultado con el valor anterior y lo almacena; no afirma que 10 sea igual a 10 menos 3.

## 2. Rectángulo

Fuente completo: [soluciones/02-rectangulo.c](soluciones/02-rectangulo.c). Área: `ancho * alto`. Perímetro: `2.0 * (ancho + alto)`. El área multiplica dos longitudes, por lo que se expresa en metros cuadrados; el perímetro suma longitudes de los lados y se expresa en metros. Con lados 1.0 y 1.0 obtenemos 1.00 y 4.00, respectivamente.

## 3. División

```c
double promedio = (double)total / personas;
```

O, en lugar de esa línea:

```c
double promedio = total / (double)personas;
```

En cada alternativa participa un operando `double` antes de dividir. `(double)(total / personas)` convierte el resultado entero 2 y produce 2.0. Se perdió la fracción antes del cast. Declara una sola de las alternativas en tu programa, no dos variables `promedio` en el mismo bloque.

## 4. Cajas

Los cuatro resultados son los de la tabla del enunciado. En el caso de 17, tres cajas contienen 15; los dos objetos restantes requieren otra caja si debemos guardar todo. El cociente responde cuántas cajas están completas, no cuántas necesitamos en total.

## 5. Tiempo

| Minutos totales | Horas | Minutos restantes | Segundos |
|---:|---:|---:|---:|
| 0 | 0 | 0 | 0 |
| 59 | 0 | 59 | 3540 |
| 60 | 1 | 0 | 3600 |
| 135 | 2 | 15 | 8100 |

Multiplicar minutos por 60 produce segundos. Llamarlo `horas` no cambia la unidad ni la fórmula; solo introduce un nombre engañoso que el compilador no sabe evaluar.

## 6. Promedio

Fuente completo: [soluciones/06-promedio.c](soluciones/06-promedio.c). Sumamos primero, con paréntesis conceptuales claros, y convertimos la suma a `double` antes de dividir. La suma 23 es pequeña y representable. La salida 7.67 es la presentación con dos decimales de un promedio aproximado, no una nueva regla para redondear todas las notas.

Con 6, 6 y 6 obtenemos suma 18 y promedio 6.00. Si intentaras generalizar a números grandes, deberías revisar también la suma: convertir su resultado después no protege una suma entera que ya desbordó.

## 7. Recibo

Fuente completo: [soluciones/07-recibo.c](soluciones/07-recibo.c).

```c
int subtotal_centavos = precio_centavos * cantidad;
int total_centavos = subtotal_centavos + envio_centavos;
int unidades = total_centavos / 100;
int centavos = total_centavos % 100;
```

Con los datos iniciales: 1250 por 3 da 3750, más 500 da 4250; cociente 42 y resto 50. Con 1005, el cociente es 10 y el resto 5: `%02d` muestra `05`, por eso la línea dice `10.05` y no `10.5`.

Los casos adicionales producen las salidas del enunciado, incluido `0.00`. Todos son no negativos y sus productos y sumas caben en `int`. Guardar centavos permite aritmética exacta en esas unidades **dentro del rango**; no da un rango infinito ni establece reglas de impuestos, descuentos o conversión monetaria.

Para revisar tu solución, no mires solo la última línea: contrasta también subtotal y envío. Dos errores podrían compensarse y producir por casualidad el total esperado.
