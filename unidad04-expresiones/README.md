# Unidad 04 — Expresiones: calcular con sentido

[Inicio](../README.md) · [Anterior: tipos](../unidad03-tipos/README.md)

## Qué vas a construir

Ya sabes almacenar datos y elegir tipos. Ahora puedes obtener datos nuevos: total de objetos, promedio de notas, cajas completas y horas a partir de minutos. Terminarás con un recibo pequeño que representa dinero en centavos enteros.

Los datos seguirán escritos en el fuente. Trabajar con entrada del usuario requerirá comprobar que los valores son válidos, una habilidad del próximo bloque. En esta unidad los valores de los ejemplos son conocidos y pequeños.

## 1. Expresión, operador y operandos

Una **expresión** describe un cálculo o produce un valor. En `3 + 4`, `+` es el operador y 3 y 4 son sus operandos. Una variable también puede participar:

```c
int libros = 3;
int revistas = 4;
int total = libros + revistas;
```

Primero se obtiene el resultado de `libros + revistas`; después se inicializa `total` con 7. Los valores de `libros` y `revistas` se conservan.

| Operador | Operación | Ejemplo | Resultado |
|---|---|---|---:|
| `+` | Suma | `7 + 3` | 10 |
| `-` | Resta | `7 - 3` | 4 |
| `*` | Multiplicación | `7 * 3` | 21 |
| `/` | División | `7 / 3` | 2, al dividir dos enteros |
| `%` | Resto de división entera | `7 % 3` | 1 |

En C usamos `*`, no la letra `x`, para multiplicar. `^` no significa elevar a una potencia: es otro operador que estudiaremos más adelante. Para calcular el cuadrado de un valor pequeño puedes multiplicarlo por sí mismo.

Archivo: [ejemplos/01-operaciones.c](ejemplos/01-operaciones.c). Incluye suma, resta, producto y dos formas de agrupar un cálculo.

### Compilar y comparar

Entra con tu terminal a `unidad04-expresiones`; confirma con `ls` que ves `ejemplos` y crea la carpeta de salida con `mkdir -p build`.

| Sistema | Compilar | Ejecutar después de compilar correctamente |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-operaciones.c -o build/operaciones` | `./build/operaciones` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-operaciones.c -o build/operaciones.exe` | `./build/operaciones.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-operaciones.c -o build/operaciones` | `./build/operaciones` |

Salida:

```text
Suma: 10
Resta: 4
Producto: 21
Sin parentesis: 14
Con parentesis: 20
```

Para los demás ejemplos y soluciones cambia la ruta del fuente y el nombre del ejecutable, manteniendo las opciones. No ejecutes un binario anterior cuando la nueva compilación haya fallado.

## 2. Precedencia y agrupación

Los operadores no tienen todos la misma prioridad. En los cálculos sencillos de esta unidad:

1. Los paréntesis permiten indicar una agrupación.
2. `*`, `/` y `%` tienen la misma precedencia y se agrupan de izquierda a derecha.
3. `+` y `-` tienen menor precedencia y también se agrupan de izquierda a derecha.

Por eso `2 + 3 * 4` significa `2 + (3 * 4)` y produce 14. `(2 + 3) * 4` produce 20. `10 - 3 - 2` significa `(10 - 3) - 2` y produce 5.

Para un promedio no es suficiente escribir `nota1 + nota2 / 2.0`: esa expresión divide solo `nota2`. Escribe `(nota1 + nota2) / 2.0` si quieres dividir la suma.

La **agrupación** de operadores no garantiza el orden temporal de evaluación de todas las partes de una expresión. Aquí usamos lecturas de variables y cálculos sin modificaciones dentro de los operandos. Para cambiar variables, utilizamos instrucciones separadas. Esa separación permite seguir el estado sin depender de reglas que todavía no has estudiado.

## 3. Actualizar a partir del valor anterior

```c
int disponibles = 12;
disponibles = disponibles - 3;
printf("Disponibles: %d\n", disponibles);
```

Salida: `Disponibles: 9`, seguida de salto de línea. El lado derecho utiliza el valor anterior, 12, calcula 9 y luego lo almacena. No es una ecuación matemática que deba cumplirse simultáneamente.

No repitas `int` en la actualización y no cambies `disponibles` varias veces dentro de una misma expresión. Más adelante veremos abreviaturas como `+=` e incrementos cuando trabajemos con ciclos.

## 4. La división depende de los operandos

Archivo: [ejemplos/02-division.c](ejemplos/02-division.c).

```c
int piezas = 5;
int personas = 2;

int reparto_entero = piezas / personas;
double resultado_tardio = piezas / personas;
double reparto_decimal = (double)piezas / personas;
double conversion_tardia = (double)(piezas / personas);
```

Aunque el destino sea `double`, `piezas / personas` divide dos `int`: produce 2. Guardar ese resultado en `double` produce 2.0, no recupera la fracción perdida.

En `(double)piezas / personas` convertimos **antes** de dividir. El cálculo utiliza punto flotante y produce 2.5. En `(double)(piezas / personas)` convertimos **después**: ya se obtuvo 2 mediante división entera.

Salida completa del ejemplo:

```text
Division entera: 2
Destino double: 2.00
Conversion antes: 2.50
Conversion despues: 2.00
```

También puedes escribir `5.0 / 2` o `5 / 2.0`: al intervenir un `double`, el otro operando entero se convierte para este cálculo. En cambio, `5 / 2` sigue siendo división entera.

Con enteros negativos la división trunca hacia cero: `-7 / 3` es -2. No redondea al entero más cercano ni siempre hacia abajo. En todos estos casos suponemos un divisor distinto de cero y un resultado representable.

## 5. Cociente y resto responden preguntas distintas

Tenemos 17 objetos y cada caja admite 5. ¿Cuántas cajas se llenan por completo? ¿Cuántos objetos quedan fuera de esas cajas completas?

Archivo: [ejemplos/03-reparto.c](ejemplos/03-reparto.c).

```c
int objetos = 17;
const int por_caja = 5;
int cajas_completas = objetos / por_caja;
int sobrantes = objetos % por_caja;
```

Salida:

```text
Cajas completas: 3
Objetos sobrantes: 2
```

Podemos comprobarlo a mano: tres cajas de cinco contienen quince objetos; quedan dos. `%` trabaja con operandos enteros y obtiene el resto, **no un porcentaje**. No puedes escribir `3.5 % 2.0`.

Para estos valores no negativos y divisor positivo, el resto va de cero a `por_caja - 1`. Si permitimos negativos, no interpretes automáticamente el resto como «cantidad sobrante»:

| Expresión | Resultado |
|---|---:|
| `7 / 3` | 2 |
| `7 % 3` | 1 |
| `-7 / 3` | -2 |
| `-7 % 3` | -1 |

Cuando el cociente es representable y el divisor no es cero, se cumple `a = (a / b) * b + a % b`. En el caso negativo: `-7 = (-2) * 3 + (-1)`. Usaremos cantidades no negativas para cajas y minutos.

Si la pregunta cambia a «¿cuántas cajas necesito para guardar todos los objetos?», tres cajas no bastan cuando sobran dos. No confundas cajas completas con cajas necesarias; resolveremos esa decisión al estudiar condiciones.

## 6. Cálculos con unidades

Archivo: [ejemplos/04-tiempo.c](ejemplos/04-tiempo.c).

```c
int minutos_totales = 135;
const int minutos_por_hora = 60;
int horas = minutos_totales / minutos_por_hora;
int minutos_restantes = minutos_totales % minutos_por_hora;
int segundos_totales = minutos_totales * 60;
```

Salida:

```text
Horas: 2
Minutos restantes: 15
Segundos totales: 8100
```

El nombre de una variable debe ayudar a identificar su unidad. `minutos_totales` y `segundos_totales` no son intercambiables aunque ambos sean `int`. El compilador no sabe que uno representa minutos y el otro segundos.

Antes de programar escribe la relación: una hora son sesenta minutos, un minuto son sesenta segundos. Después calcula a mano al menos un caso. Para modificar este ejemplo sin estudiar aún rangos grandes, usa minutos entre 0 y 500: el mayor producto es 30000, representable incluso en un `int` cuyo máximo sea 32767.

## 7. Calcular con límites conocidos

El lenguaje no transforma automáticamente un tipo pequeño en otro mayor cuando el resultado no cabe. Un cálculo entre dos `int` se realiza con el tipo correspondiente a esos operandos aunque después quieras guardarlo en un tipo diferente.

No ejecutes divisiones por cero ni pruebes qué ocurre al desbordar enteros con signo. Su comportamiento es indefinido. En implementaciones habituales donde el negativo mínimo tiene mayor magnitud que el máximo positivo, `INT_MIN / -1` tampoco cabe; el resto `INT_MIN % -1` comparte el problema del cociente no representable. No son ejemplos para experimentar ejecutándolos.

Para los programas de esta unidad comprobamos los valores fijos, los productos y los divisores antes de ejecutar. Eso no equivale a tener una aplicación preparada para cualquier entrada. En el próximo bloque necesitaremos decisiones y validación para rechazar valores que no cumplen el contrato del problema.

## 8. Pequeño proyecto: recibo en centavos

Construirás un recibo con precio por unidad de 1250 centavos, cantidad 3 y envío de 500 centavos. Representar todos esos datos como enteros conserva exactamente las unidades que elegimos.

Diseña primero:

| Dato | Valor | Unidad |
|---|---:|---|
| Precio unitario | 1250 | Centavos por artículo |
| Cantidad | 3 | Artículos |
| Envío | 500 | Centavos |
| Subtotal | 3750 | Centavos |
| Total | 4250 | Centavos |

Para mostrar el total, separa unidades completas con `/ 100` y centavos con `% 100`. El formato `%02d` imprime un entero con ancho mínimo de dos posiciones, rellenando con ceros a la izquierda. Así 5 centavos se muestran `05`. El ancho mínimo no recorta números más largos ni modifica el valor.

```c
printf("Total: %d.%02d\n", unidades, centavos);
```

La moneda hipotética de este ejercicio tiene cien centavos por unidad. No se aplican descuentos, impuestos ni conversiones monetarias. Si aparecieran, harían falta reglas de redondeo explícitas y una revisión de rangos. No añadas datos negativos a este modelo: su separación y presentación se diseñaron para cantidades no negativas.

Consulta el enunciado completo en [EJERCICIOS.md](EJERCICIOS.md). Intenta resolverlo antes de abrir [SOLUCIONES.md](SOLUCIONES.md).

## Criterios para terminar

- [ ] Explico qué tipo tienen los operandos de una división.
- [ ] Uso paréntesis para expresar una fórmula y justifico su agrupación.
- [ ] Actualizo una variable usando su valor anterior.
- [ ] Distingo cociente, resto, porcentaje y fracción.
- [ ] Verifico unidades, rango y divisor en los casos conocidos.
- [ ] Construí el recibo y comprobé más de un caso.

El siguiente bloque desarrollará entrada validada, decisiones y ciclos. Todavía no está publicado. Conserva tus fuentes, los casos que comprobaste y una explicación de la división que produce 2.00 aunque su destino sea `double`.
