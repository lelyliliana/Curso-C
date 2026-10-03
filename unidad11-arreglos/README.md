# Unidad 11 — Arreglos: datos con posiciones y límites

[Inicio](../README.md) · [Anterior: organización](../unidad10-organizacion/README.md) · [Siguiente: recorridos](../unidad12-recorridos/README.md)

## Objetivo

Hasta ahora cada variable guardaba un dato. Si una tienda tiene cuatro productos, escribir `producto1`, `producto2`, `producto3` y `producto4` hace difícil repetir una operación sobre todos. Un **arreglo** reúne varios elementos del mismo tipo y permite seleccionar uno por su posición.

Al terminar podrás declarar e inicializar arreglos de tamaño fijo, recorrerlos con índices válidos, distinguir capacidad de cantidad utilizada y copiar elementos. Necesitas las decisiones y los ciclos de las unidades 05–06. Mantendremos los arreglos dentro de `main`; el paso de arreglos a funciones se explicará junto con punteros, porque no funciona como la copia de un `int`.

## 1. Leer una declaración

Abre [ejemplos/01-posiciones.c](ejemplos/01-posiciones.c):

```c
int existencias[4] = {12, 7, 0, 9};
```

- `int`: tipo de cada elemento.
- `existencias`: nombre del arreglo.
- `[4]`: reserva cuatro elementos, no indica la última posición.
- `{12, 7, 0, 9}`: valores iniciales en orden.

Cada elemento tiene su propio valor. C los dispone contiguamente en el orden del arreglo. No necesitamos conocer direcciones de memoria para comenzar a trabajar con índices.

| Índice | Orden para una persona | Valor inicial |
|---:|---|---:|
| 0 | Primero | 12 |
| 1 | Segundo | 7 |
| 2 | Tercero | 0 |
| 3 | Cuarto | 9 |

`existencias[2]` selecciona el tercer elemento. `existencias[1] = 10;` cambia solo el segundo. Un cero puede ser una existencia válida: no significa que esa posición no exista.

## 2. Compilar y observar un elemento

Trabaja un paso a la vez, como en las unidades anteriores:

1. Entra desde la carpeta del curso con `cd unidad11-arreglos`.
2. Ejecuta `ls` y confirma que están `ejemplos` y `soluciones`.
3. Crea el destino con `mkdir -p build`.
4. Usa el comando de construcción de tu sistema. Si termina con errores, corrígelos antes de ejecutar.

En Windows utiliza la terminal UCRT64 de MSYS2; en macOS, la terminal con las herramientas de línea de comandos instaladas.

| Sistema | Construir | Ejecutar después |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-posiciones.c -o build/posiciones` | `./build/posiciones` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-posiciones.c -o build/posiciones.exe` | `./build/posiciones.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-posiciones.c -o build/posiciones` | `./build/posiciones` |

Salida:

```text
Primero: 12
Tercero: 0
Segundo actualizado: 10
```

Después cambia únicamente el primer valor a 20, guarda, recompila y comprueba cuál línea cambia. No modifiques el tamaño ni los índices durante esta primera prueba.

## 3. El límite pertenece al programa

Para un arreglo de cuatro elementos los índices válidos son **0, 1, 2 y 3**. `existencias[4]` y `existencias[-1]` quedan fuera del arreglo. Ni leer ni escribir esas posiciones es una manera válida de preguntar si hay un dato.

C no realiza una comprobación automática de límites en cada acceso. Un acceso fuera del arreglo puede producir **comportamiento indefinido**: el lenguaje deja de garantizar lo que hará el programa. No hay una salida errónea predecible que podamos usar como demostración, y que una ejecución parezca funcionar no lo hace correcto.

No ejecutes accesos fuera de límites para descubrir «qué había al lado». Aprende a justificar el índice antes del acceso. Si proviene de un entero externo, primero comprueba que no sea negativo y que sea menor que la cantidad admisible; no lo conviertas a un tipo sin signo antes de descartar negativos.

Un arreglo de tamaño fijo no crece porque usemos un índice mayor. Para más datos necesitamos otra estrategia, que se estudiará después. Tampoco utilizamos arreglos de longitud cero ni tamaños variables en este bloque.

## 4. Recorrer sin repetir instrucciones

Abre [ejemplos/02-recorrido.c](ejemplos/02-recorrido.c). Esta declaración deja que el inicializador determine cuatro elementos:

```c
int existencias[] = {12, 7, 0, 9};
```

Los corchetes vacíos aquí permiten inferir el tamaño al **declarar con inicializador**. No crean una colección que cambie de tamaño.

El recorrido usa:

```c
for (size_t i = 0; i < cantidad; i++) {
    printf("Indice %zu: %d\n", i, existencias[i]);
}
```

`size_t` es un tipo entero sin signo apropiado para tamaños e índices; lo declaramos disponible mediante `<stddef.h>`. Su formato de salida es `%zu`. No asumas que es lo mismo que `int` ni uses `%d` para imprimirlo. Tampoco representa negativos: restar uno a cero no produce -1.

El ciclo comienza en 0. Con `cantidad` igual a 4, entra con 0, 1, 2 y 3. Cuando `i` llega a 4, la condición falla **antes** de acceder. Usar `i <= cantidad` incluiría una posición que no existe. Al salir, `i` declarado en el `for` deja de estar disponible fuera de él.

Compila este archivo por separado, cambiando fuente y ejecutable en la tabla anterior. Salida:

```text
Indice 0: 12
Indice 1: 7
Indice 2: 0
Indice 3: 9
Elementos: 4
```

## 5. Contar elementos con `sizeof`

En el ejemplo anterior:

```c
const size_t cantidad = sizeof existencias / sizeof existencias[0];
```

`sizeof existencias` da el tamaño total del arreglo en **bytes de C**. `sizeof existencias[0]` da el tamaño de un elemento, también en bytes. Dividir los tamaños da el número de elementos: no necesitamos suponer que un `int` tiene cuatro bytes.

En estos arreglos fijos `sizeof` consulta el tipo y no lee el valor del elemento. La expresión no depende de que el primer valor sea 12 o 0.

Esta fórmula funciona aquí porque `existencias` sigue siendo el **arreglo declarado en ese ámbito**. No la generalices a un puntero ni a un parámetro escrito con corchetes: al estudiar funciones que reciben arreglos veremos por qué necesitan una cantidad explícita. `sizeof` tampoco cuenta cuántos datos utilizamos realmente.

## 6. Inicializar antes de leer

```c
int datos[5] = {0};
```

Inicializa los cinco elementos en cero. Si se escriben menos valores que el tamaño, los restantes se inicializan en cero; por ejemplo, `{4, 7}` deja tres ceros en un arreglo de cinco.

En cambio, `int datos[5];` dentro de una función no inicializa sus elementos automáticamente. Debes escribir cada elemento antes de leerlo. En estas prácticas inicializamos de forma explícita para poder concentrarnos en el recorrido. Eso no convierte los ceros en registros cargados.

Para un tamaño fijo nombrado usamos `enum { CAPACIDAD = 5 };`, una constante entera como las de la Unidad 09. Una variable local `const int capacidad = 5;` no es una expresión constante entera en C por el simple hecho de ser `const`; no la utilizamos para presentar estos arreglos como fijos.

## 7. Capacidad y cantidad utilizada

Abre [ejemplos/03-capacidad.c](ejemplos/03-capacidad.c). Su contrato es:

```text
0 <= usados <= CAPACIDAD
Datos presentes: índices desde 0 hasta usados - 1, si usados > 0.
```

La **capacidad** es el espacio disponible. `usados` es la cantidad de registros cargados. Si hay cinco casillas reservadas y dos datos, recorre `i < usados`, no `i < CAPACIDAD`, para mostrar los registros.

Insertar al final requiere este orden:

1. Comprobar `usados < CAPACIDAD`.
2. Escribir `datos[usados]`.
3. Incrementar `usados`.

Si `usados == CAPACIDAD`, el índice de la siguiente inserción ya queda fuera. No incrementes primero ni escribas antes de comprobar espacio. El ejemplo verifica ambas inserciones y produce:

```text
Capacidad: 5; usados: 2
Dato 0: 18
Dato 1: 0
```

El segundo dato vale cero y está cargado. Las otras posiciones inicializadas en cero no están cargadas. Es `usados`, y no el contenido, lo que distingue esos casos. Una colección vacía se representa con capacidad positiva y `usados = 0`.

## 8. Copiar y conservar el orden

Un arreglo no admite una asignación completa como `copia = original;`. Puedes inicializar al declararlo o copiar sus elementos con un ciclo. [soluciones/05-copia.c](soluciones/05-copia.c) copia cuatro elementos a otro arreglo de la misma capacidad y después cambia solo la copia.

Antes de copiar, asegura que el destino tiene espacio para **todos** los elementos. En este ejercicio ambas capacidades son cuatro. Un ciclo correcto para el origen también necesita un límite correcto para el destino.

No confundas una copia de valores con una referencia a los mismos datos. Estudiaremos referencias y parámetros de arreglos al introducir punteros.

## Práctica y cierre

Resuelve [EJERCICIOS.md](EJERCICIOS.md) antes de abrir [SOLUCIONES.md](SOLUCIONES.md). Todos los fuentes de esta unidad tienen su propio `main`: compila uno por vez.

- [ ] Relaciono el primer elemento con el índice 0.
- [ ] Justifico que cada índice es menor que el límite del arreglo.
- [ ] Imprimo `size_t` con `%zu`.
- [ ] Distingo capacidad y cantidad utilizada, incluso con datos que valen cero.
- [ ] Compruebo espacio antes de escribir una inserción.
- [ ] Copio elementos a un destino con capacidad suficiente.

Conserva una tabla de seguimiento de índices y una captura de la inserción rechazada por falta de espacio. En la [Unidad 12](../unidad12-recorridos/README.md) usarás esas mismas reglas para resolver problemas con colecciones.
