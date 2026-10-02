# Unidad 03 — Tipos: qué datos puede representar un programa

[Inicio](../README.md) · [Anterior: variables](../unidad02-variables/README.md) · [Siguiente: expresiones](../unidad04-expresiones/README.md)

## Punto de partida y objetivo

Ya sabes declarar un `int`, inicializarlo y mostrarlo con `%d`. Ahora necesitas representar una temperatura con fracción y una letra. No basta con cambiar el dato: también debes elegir un tipo adecuado y el formato que lo muestra.

Al terminar podrás elegir entre `int`, `double` y `char` para problemas sencillos, reconocer `float`, consultar límites y explicar cuándo una conversión pierde información. No tienes que memorizar todos los tipos de C en esta unidad.

## 1. Tres datos diferentes

Archivo: [ejemplos/01-tipos.c](ejemplos/01-tipos.c).

```c
#include <stdio.h>

int main(void)
{
    int personas = 12;
    double temperatura = 23.5;
    char grupo = 'B';

    printf("Personas: %d\n", personas);
    printf("Temperatura: %.1f C\n", temperatura);
    printf("Grupo: %c\n", grupo);
    return 0;
}
```

| Dato | Tipo elegido | Motivo |
|---|---|---|
| 12 personas | `int` | Contamos unidades enteras |
| 23.5 grados | `double` | Necesitamos valores con fracción |
| Una letra de grupo | `char` | Un carácter sencillo del conjunto básico |

`int` también admite negativos, dentro de su rango. `double` es un tipo de **punto flotante**: representa un conjunto finito de números, generalmente aproximados. No almacena todos los números reales posibles.

`char` es técnicamente un tipo entero que también usamos para caracteres. En este primer recorrido elegimos letras ASCII sencillas. Una letra visible como `ñ`, o un emoji, puede requerir varios bytes en UTF-8; no intentes guardarla como si siempre cupiera en un único `char`.

### Compilar desde esta carpeta

En la terminal de tu sistema, entra a `unidad03-tipos`, comprueba con `ls` que estás allí y crea `build` con `mkdir -p build`, como en la unidad anterior.

| Sistema | Compilar | Ejecutar después de compilar correctamente |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-tipos.c -o build/tipos` | `./build/tipos` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-tipos.c -o build/tipos.exe` | `./build/tipos.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-tipos.c -o build/tipos` | `./build/tipos` |

Salida:

```text
Personas: 12
Temperatura: 23.5 C
Grupo: B
```

Para los otros fuentes sustituye la ruta y el nombre del ejecutable. En Windows conserva `.exe`; en macOS usa `clang`. Los comandos no se ejecutan dentro del archivo `.c`.

## 2. Las comillas y el punto decimal tienen significado

```c
int personas = 12;
double temperatura = 23.5;
char grupo = 'B';
```

- `12` es un literal entero.
- `23.5` es un literal de tipo `double`. En el fuente de C escribimos el punto decimal, no `23,5`.
- `'B'` es una constante de carácter que en C tiene tipo `int`; su valor se puede almacenar en este `char`. Las comillas simples señalan un carácter básico.
- `"B"` es una cadena de texto, un objeto diferente. No se asigna a un `char` como reemplazo de `'B'`. Las cadenas se estudiarán con arreglos.

El tipo de una variable no cambia con una asignación. Una variable declarada `int` sigue siendo `int` cuando recibe un valor que originalmente era `double`: el valor se convierte antes de almacenarse.

## 3. El formato debe corresponder al dato

| Dato que mostraremos | Formato en `printf` | Ejemplo |
|---|---|---|
| `int` | `%d` | `printf("%d\n", personas);` |
| `double` | `%f` o una precisión como `%.1f` | `printf("%.1f\n", temperatura);` |
| Carácter básico almacenado en `char` | `%c` | `printf("%c\n", grupo);` |

`%.1f` muestra una cifra después del punto; `%.2f`, dos. Es una decisión de **presentación**: no convierte el objeto en un número almacenado con exactamente una o dos cifras decimales.

Con `double temperatura = 23.5;`, `%f` muestra `23.500000` en estos ejemplos; `%.2f` muestra `23.50`. No modificamos la configuración regional del programa, por lo que estas salidas usan el punto decimal de la configuración inicial de C.

No uses `%d` para mostrar un `double`, ni `%f` para mostrar un `int`. `printf` no deduce el formato correcto a partir del dato. Una incompatibilidad de argumentos y formato puede producir **comportamiento indefinido**: C deja de garantizar lo que hará el programa. No es un procedimiento de conversión ni un resultado extraño que debas aceptar.

Un `char` con las letras que usamos se promociona a `int` al pasarlo a `printf`; por eso `%c` es la opción correcta para mostrar esa letra. No necesitas añadir una conversión manual.

## 4. `float`, `double` y precisión

También existe `float`, otro tipo de punto flotante. `double` dispone de al menos tanta precisión y rango como `float`; en equipos habituales ofrece más. Empezaremos con `double` para cálculos con fracciones, sin asumir un tamaño universal.

```c
float medida_corta = 0.1f;
double medida = 0.1;
```

El sufijo `f` hace que `0.1f` sea un literal de tipo `float`. Sin él, `0.1` tiene tipo `double`. Los decimales como 0.1 no tienen representación exacta en los formatos binarios habituales: piensa en la dificultad de escribir un tercio con un número finito de cifras decimales.

Archivo: [ejemplos/02-precision.c](ejemplos/02-precision.c).

```c
#include <stdio.h>

int main(void)
{
    float medida_corta = 0.1f;
    double medida = 0.1;

    printf("float, 17 decimales: %.17f\n", medida_corta);
    printf("double, 17 decimales: %.17f\n", medida);
    printf("double, 2 decimales: %.2f\n", medida);
    return 0;
}
```

Una salida habitual, obtenida en el entorno de verificación del curso, es:

```text
float, 17 decimales: 0.10000000149011612
double, 17 decimales: 0.10000000000000001
double, 2 decimales: 0.10
```

Las últimas cifras dependen de la representación y del entorno; esta salida no es una exigencia universal del lenguaje. El objetivo es observar que mostrar `0.10` puede ocultar una aproximación. No significa que la variable se haya vuelto exacta.

Al pasar `float` a `printf`, su valor se promociona a `double`; `%f` sirve también aquí. Esa promoción no recupera la precisión que ya se perdió al almacenar el `float`. Estas reglas son para **salida con `printf`**; no las traslades a funciones de entrada que aún no hemos estudiado.

Para cantidades que deben ser exactas, como centavos de dinero, puede convenir representar unidades enteras con un rango apropiado. Lo practicaremos con cantidades pequeñas en la próxima unidad. También los enteros tienen límites.

## 5. Tamaño y rango no son lo mismo

Un tipo ocupa cierta cantidad de memoria y admite ciertos valores. No presupongas que `int` ocupa siempre cuatro bytes ni que `double` ocupa siempre ocho. Consulta la implementación en la que trabajas.

Archivo: [ejemplos/03-limites.c](ejemplos/03-limites.c).

```c
#include <limits.h>
#include <stdio.h>

int main(void)
{
    printf("Bytes de int: %zu\n", sizeof(int));
    printf("Bytes de double: %zu\n", sizeof(double));
    printf("Bytes de char: %zu\n", sizeof(char));
    printf("Bits por byte: %d\n", CHAR_BIT);
    printf("INT_MIN: %d\n", INT_MIN);
    printf("INT_MAX: %d\n", INT_MAX);
    return 0;
}
```

- `<limits.h>` proporciona nombres como `INT_MIN`, `INT_MAX` y `CHAR_BIT`. Son macros definidas por la implementación; aquí las usamos como valores ya disponibles, sin escribir nuestras propias macros.
- `sizeof` es un operador que informa el tamaño en **bytes de C**. `sizeof(char)` siempre es 1; `CHAR_BIT` indica cuántos bits tiene ese byte. En los equipos habituales son ocho, pero no fijamos ese número como regla universal.
- El resultado de `sizeof` tiene tipo `size_t`, un tipo entero sin signo destinado a tamaños; lo mostramos con `%zu`. No lo sustituimos por `%d`.

Salida obtenida con GCC en el equipo de verificación:

```text
Bytes de int: 4
Bytes de double: 8
Bytes de char: 1
Bits por byte: 8
INT_MIN: -2147483648
INT_MAX: 2147483647
```

En otra plataforma algunos valores pueden variar. Guarda tu salida con el nombre del compilador utilizado. **No calcules `INT_MAX + 1` para probar el límite**: desbordar un entero con signo durante una operación provoca comportamiento indefinido, no una vuelta al comienzo garantizada.

Existen otros tipos enteros, como `long`, y variantes sin signo. Elegir uno sin signo no sustituye validar un dato ni evita todos los errores. Los estudiaremos cuando necesitemos sus propiedades; en estos ejercicios mantendremos cantidades pequeñas y representables.

## 6. Conversión explícita y pérdida de información

Una **conversión** obtiene un valor de otro tipo. Una conversión explícita, también llamada *cast*, escribe el tipo de destino entre paréntesis:

```c
double duracion = 3.75;
int horas_completas = (int)duracion;
```

Archivo: [ejemplos/04-conversiones.c](ejemplos/04-conversiones.c).

Salida completa:

```text
Duracion: 3.75
Horas completas: 3
Original tras convertir: 3.75
Negativo convertido: -3
```

Al convertir un valor finito representable como `3.75` a `int`, se descarta la parte fraccionaria: el resultado es 3. Con `-3.75` obtenemos -3. Es truncamiento hacia cero, **no redondeo al entero más cercano**.

La conversión no cambia `duracion`, que sigue siendo un `double` con su valor original. El objeto nuevo `horas_completas` recibe el entero convertido.

Sin el cast, `int horas_completas = duracion;` realizaría esta conversión implícitamente. Escribimos el cast para hacer visible una pérdida intencional de fracción. Un cast no valida: si el valor es demasiado grande para el destino, o no es finito, convertirlo a `int` no es una solución segura. Aquí los valores son fijos, pequeños y conocidos.

Pasar un entero pequeño como 3 a `double` conserva su valor en estos ejemplos. No generalices que convertir cualquier entero, por enorme que sea, a punto flotante siempre conserva todos sus dígitos.

## Práctica y cierre

Resuelve [EJERCICIOS.md](EJERCICIOS.md) y compara con [SOLUCIONES.md](SOLUCIONES.md).

- [ ] Elijo un tipo a partir del significado del dato.
- [ ] Distingo `'B'`, `"B"`, `12` y `12.0`.
- [ ] Hago corresponder argumentos y formatos de `printf`.
- [ ] Distingo decimales mostrados y precisión almacenada.
- [ ] Consulto tamaños y límites sin provocar un desbordamiento.
- [ ] Explico qué pierde una conversión y qué conserva el objeto original.

Continúa con [Unidad 04 — Expresiones y cálculos](../unidad04-expresiones/README.md).
