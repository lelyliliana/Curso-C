# Soluciones razonadas — Primer programa

[Ejercicios](EJERCICIOS.md) · [Unidad 01](README.md)

Consulta después de intentar. Puedes resolver de otra manera si respetas el objetivo y puedes explicar tu programa.

## 1. Predicción

```text
A
BC
```

Hay dos líneas con texto. La llamada que muestra `B` no termina la línea y la llamada que muestra `C` continúa allí. No aparecen espacios porque no se escribieron dentro de las cadenas.

## 2. Tarjeta

Una solución está en [soluciones/02-tarjeta.c](soluciones/02-tarjeta.c):

```c
#include <stdio.h>

int main(void)
{
    printf("====================\n");
    printf("Nombre: Ana\n");
    printf("Meta: aprender C\n");
    printf("====================\n");
    return 0;
}
```

Las cuatro llamadas producen las cuatro líneas. Los signos `=` son texto: aquí no representan una asignación. La diferencia entre texto y operadores se estudiará cuando introduzcamos variables.

Para comprobar el archivo del repositorio desde la carpeta `unidad01-primer-programa` en Ubuntu:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic soluciones/02-tarjeta.c -o tarjeta
```

Ejecuta `./tarjeta`. En Windows, desde UCRT64, usa `-o tarjeta.exe` y luego `./tarjeta.exe`; en macOS utiliza `clang`.

## 3. Tabla

El archivo [soluciones/03-tabla.c](soluciones/03-tabla.c) utiliza una llamada por fila. En `1    | Escribir` hay cuatro espacios después del dígito, de manera que la barra queda en la misma columna que la cabecera.

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic soluciones/03-tabla.c -o tabla
```

Ejecuta `./tabla` en Ubuntu. Aplica las sustituciones de compilador y extensión indicadas para tu sistema.

Una cadena que contenga todas las filas separadas por `\n` también sería válida. No necesitas una solución idéntica si muestra lo solicitado.

## 4. Errores

Omitir el punto y coma rompe la sintaxis del programa. El compilador puede señalar el inicio de la instrucción siguiente, porque allí detecta que algo no encaja. Revisa también la línea anterior.

Escribir `aprnder` dentro de una cadena sigue siendo texto válido para C. El compilador no conoce tu intención de escribir `aprender`: la comprobación humana del resultado detecta el problema.

Por eso un programa puede compilar y devolver cero, y aun así no cumplir el objetivo.

## 5. Explicación posible

Escribo y guardo el archivo con el editor. Desde la terminal invoco GCC o Clang para construir el ejecutable. Si cambio el fuente, debo volver a compilar porque el ejecutable anterior no se modifica solo. Después inicio ese ejecutable desde la carpeta donde se generó. `\n` introduce un salto de línea. `return 0;` informa una finalización exitosa, pero debo comparar la salida para saber si resolví el problema.

Si tu explicación diferencia esas acciones, aunque utilice otras palabras, alcanzaste el objetivo.
