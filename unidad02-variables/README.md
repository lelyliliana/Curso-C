# Unidad 02 — Variables: guardar y cambiar datos

[Inicio](../README.md) · [Anterior: primer programa](../unidad01-primer-programa/README.md) · [Siguiente: tipos](../unidad03-tipos/README.md)

## Antes de comenzar

Debes poder guardar un archivo `.c`, compilarlo y ejecutar el resultado. Si todavía no distingues el fuente del ejecutable, repasa la Unidad 01. Aquí conservarás la estructura de `main` y aprenderás a sustituir un dato fijo por un dato con nombre.

Al terminar podrás declarar una variable entera, darle un valor inicial, mostrarla y seguir sus cambios línea por línea. Todavía no pediremos información por teclado: los datos estarán escritos en el programa.

## 1. Del mensaje fijo al dato con nombre

Hasta ahora podías escribir `printf("Hay 12 libros.\n");`. Si cambia la cantidad, tendrías que buscarla dentro del texto. Una variable permite separar el dato del mensaje:

```c
#include <stdio.h>

int main(void)
{
    int libros = 12;

    printf("Hay %d libros.\n", libros);
    return 0;
}
```

Archivo: [ejemplos/01-variables.c](ejemplos/01-variables.c).

Una **variable** es un objeto que almacena un valor. En estos ejemplos puedes acceder a ella mediante su nombre. Piensa en una casilla etiquetada `libros` que guarda `12`; el dibujo mental ayuda a seguir el programa, aunque no describe por completo la memoria de un computador.

Descompón `int libros = 12;`:

| Parte | Función |
|---|---|
| `int` | Tipo: en este caso, números enteros dentro de un rango finito |
| `libros` | Nombre que elegimos para el dato |
| `= 12` | Inicialización: valor con el que comienza el objeto |
| `;` | Fin de esta declaración |

`12` es un **literal**: un valor escrito directamente en el código. `libros` es un nombre que permite consultar el valor almacenado. No llevan comillas.

## 2. Compilar y ejecutar esta unidad

Abre la terminal indicada para tu sistema en la Unidad 00: en Windows, **MSYS2 UCRT64**. Entra a la carpeta `unidad02-variables` de tu copia del curso con `cd` y tu ruta real. Comprueba con `ls` que aparece `README.md` y la carpeta `ejemplos`.

Crea una carpeta para los ejecutables:

```bash
mkdir -p build
```

`mkdir` crea la carpeta; `-p` permite repetir el comando si ya existe. Guardamos allí los productos de compilación para separarlos de los fuentes.

Usa la fila de tu sistema; compila primero y ejecuta **solo si la compilación termina correctamente**:

| Sistema | Compilar | Ejecutar |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-variables.c -o build/variables` | `./build/variables` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-variables.c -o build/variables.exe` | `./build/variables.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-variables.c -o build/variables` | `./build/variables` |

Salida:

```text
Hay 12 libros.
```

Para los demás archivos cambia la ruta del fuente y el nombre del ejecutable. Por ejemplo, utiliza `ejemplos/02-copias.c` y `build/copias` (con `.exe` en Windows). Mantén las opciones del compilador. Guarda y recompila después de cada modificación.

## 3. Mostrar el valor, no su nombre

En `printf("Hay %d libros.\n", libros);`, la cadena entre comillas describe el mensaje y el argumento después de la coma aporta el dato. `%d` es una **especificación de conversión** que aquí muestra un `int` en decimal.

```c
printf("libros\n");       /* Escribe la palabra libros. */
printf("%d\n", libros);   /* Escribe el valor almacenado. */
```

Un comentario `/* ... */` explica el código a quien lo lee; su contenido no es una instrucción ejecutada. Puedes escribir comentarios en líneas separadas. No anides un comentario de este tipo dentro de otro.

Puedes mostrar dos enteros:

```c
int mesas = 3;
int sillas = 12;
printf("Mesas: %d; sillas: %d\n", mesas, sillas);
```

Los datos corresponden a las conversiones **en el orden escrito**. El primer `%d` recibe `mesas`; el segundo, `sillas`. Un formato que pide un dato sin recibirlo es un error, aunque el programa llegue a compilar. No ejecutes una llamada con advertencias de formato.

## 4. Inicialización y asignación

Inicializar da el primer valor al declarar. Asignar después sustituye el valor actual:

```c
int libros = 12;
printf("Antes: %d\n", libros);
libros = 9;
printf("Despues: %d\n", libros);
```

El `int` aparece en la declaración; no se repite al cambiar la misma variable. Declarar otra vez `int libros` en este mismo bloque provoca una redefinición, no una actualización.

`=` significa **asignar** en estas instrucciones. No es una pregunta sobre si dos valores son iguales. Las comparaciones llegarán cuando aprendamos decisiones.

Una asignación no recupera el valor anterior: si lo necesitas, guárdalo antes en otra variable.

## 5. Una copia no se actualiza sola

Archivo: [ejemplos/02-copias.c](ejemplos/02-copias.c).

```c
#include <stdio.h>

int main(void)
{
    int libros = 12;
    int copia = libros;

    libros = 9;
    printf("Libros: %d\n", libros);
    printf("Copia: %d\n", copia);

    copia = libros;
    printf("Copia actualizada: %d\n", copia);
    return 0;
}
```

Predice los tres resultados antes de ejecutar. Traza el estado siguiendo el orden de las instrucciones:

| Después de… | `libros` | `copia` |
|---|---:|---:|
| `int libros = 12;` | 12 | Todavía no declarada |
| `int copia = libros;` | 12 | 12 |
| `libros = 9;` | 9 | 12 |
| `copia = libros;` | 9 | 9 |

Salida:

```text
Libros: 9
Copia: 12
Copia actualizada: 9
```

`copia` recibió el valor que `libros` tenía en ese momento. No quedó conectada automáticamente a sus cambios. Cada nueva actualización requiere otra asignación.

## 6. Nombres que explican el problema

Utiliza nombres como `libros`, `cantidad_libros` o `asientos_disponibles`. Para este curso elegiremos letras ASCII, dígitos y guion bajo; comenzaremos con una letra. Evitaremos espacios, tildes y nombres que comienzan con guion bajo, algunos de los cuales están reservados.

| Nombre | Evaluación |
|---|---|
| `cantidad_libros` | Válido y descriptivo |
| `libros2` | Válido; el dígito no es el primer carácter |
| `2libros` | Inválido: comienza por un dígito |
| `cantidad libros` | Inválido: contiene un espacio |
| `int` | Inválido como nombre: es una palabra reservada |
| `x` | Válido; poco informativo para este problema |

C distingue mayúsculas y minúsculas: `libros` y `Libros` son nombres diferentes. Elige una escritura consistente.

Todas las variables de esta unidad se declaran dentro de las llaves de `main`. Utilízalas después de declararlas y antes de cerrar ese bloque. Más adelante estudiaremos el alcance con varios bloques y funciones.

## 7. Datos que no deben cambiar

Si la capacidad de una sala permanece fija durante esta ejecución, puedes expresarlo con `const`:

```c
const int capacidad = 20;
int ocupados = 12;
printf("Capacidad: %d\n", capacidad);
printf("Ocupados: %d\n", ocupados);
ocupados = 9;
printf("Ocupados ahora: %d\n", ocupados);
```

Archivo completo: [ejemplos/03-constantes.c](ejemplos/03-constantes.c).

Salida:

```text
Capacidad: 20
Ocupados: 12
Ocupados ahora: 9
```

`const` impide modificar ese objeto mediante una asignación como `capacidad = 25;`; el compilador debe diagnosticarla. No significa que toda aparición de `const` sea una constante utilizable en cualquier lugar del lenguaje: aquí solo necesitamos expresar un dato que no vamos a modificar.

## 8. Un valor inicial debe tener significado

No leas una variable local a la que todavía no diste un valor. Este fragmento es **incorrecto y no se debe ejecutar**:

```c
int libros;
printf("%d\n", libros); /* Lectura sin inicializacion. */
```

No hay una salida válida que debas adivinar ni garantía de que comience en cero. El compilador puede avisar, pero la ausencia de aviso no lo hace correcto. Usa `int libros = 12;` si hay doce libros. Usa cero solo cuando signifique realmente «ningún libro», no para esconder que desconoces el dato.

## Práctica y cierre

Resuelve [EJERCICIOS.md](EJERCICIOS.md), después consulta [SOLUCIONES.md](SOLUCIONES.md).

- [ ] Distingo tipo, nombre, literal y valor almacenado.
- [ ] Uso `%d` con un dato entero y explico el orden de los argumentos.
- [ ] Puedo seguir dos variables con una tabla de estado.
- [ ] Sé por qué una copia conserva un valor anterior.
- [ ] Inicializo antes de leer y uso `const` cuando corresponde.

Cuando puedas explicar el ejemplo de las copias sin ejecutarlo, continúa con [Unidad 03 — Tipos de datos](../unidad03-tipos/README.md).
