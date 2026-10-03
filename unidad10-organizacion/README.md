# Unidad 10 — Organizar un programa en varios archivos

[Inicio](../README.md) · [Anterior: contratos](../unidad09-contratos/README.md)

## Objetivo

El recibo ya tiene funciones con responsabilidades claras. Ahora las separarás en archivos y aprenderás cómo se construye **un solo programa** a partir de ellos. No cambiaremos su entrada ni su política de envío durante esa separación.

Al terminar podrás distinguir un encabezado de una implementación, compilar y enlazar varios fuentes, compartir un cálculo con sus pruebas y diagnosticar una implementación que falta. No necesitas instalar una herramienta de construcción nueva: comenzaremos con comandos explícitos del compilador.

## 1. Leer el mapa del proyecto

El material completo está en [proyecto](proyecto/main.c). Antes de compilar abre cada archivo y reconoce su responsabilidad:

| Archivo | Contenido | Responsabilidad |
|---|---|---|
| [main.c](proyecto/main.c) | Solicitud, interpretación de estados y presentación | Coordinar la aplicación |
| [entrada.h](proyecto/entrada.h) | Estados y prototipo del lector | Declarar la interfaz de entrada |
| [entrada.c](proyecto/entrada.c) | Definición de `leer_cantidad` | Consumir y validar una línea |
| [recibo.h](proyecto/recibo.h) | Prototipos y precondición de los cálculos | Declarar la interfaz de cálculo |
| [recibo.c](proyecto/recibo.c) | Validación de cantidad y cálculos | Implementar la regla del recibo |
| [pruebas_recibo.c](proyecto/pruebas_recibo.c) | Otro `main`, con aserciones | Probar el mismo cálculo sin teclado |

El programa interactivo utiliza `main.c`, `entrada.c` y `recibo.c`. El programa de pruebas utiliza `pruebas_recibo.c` y **ese mismo `recibo.c`**. Son dos ejecutables con un `main` cada uno.

No agregamos otra copia del cálculo dentro de las pruebas. Si cambias `recibo.c` y vuelves a construir ambos ejecutables, ambos utilizarán el cambio.

## 2. Un encabezado anuncia; un fuente implementa

En `recibo.h` aparecen prototipos, por ejemplo:

```c
int total_centavos(int cantidad);
```

En `recibo.c` está su definición, con cuerpo. El encabezado permite que el compilador conozca la firma al procesar otro fuente. El enlazador debe encontrar después la implementación.

Cada implementación incluye su propio encabezado: `recibo.c` comienza con `#include "recibo.h"`. Eso permite detectar desacuerdos entre lo anunciado y lo definido. No reescribas a mano un prototipo ligeramente diferente en cada archivo.

`#include "recibo.h"` pide un encabezado del proyecto. `#include <stdio.h>` pide uno de la biblioteca mediante las rutas de la herramienta. Las rutas exactas de búsqueda dependen del compilador; el patrón del proyecto funciona con los comandos documentados.

No incluyas `recibo.c` desde `main.c` ni compiles el `.h` como si fuera otro fuente del ejecutable. Incluye la interfaz y pasa los `.c` apropiados al compilador. Evitamos definiciones de funciones ordinarias y variables globales compartidas en estos encabezados.

`recibo.h` incluye `<stdbool.h>` porque declara una función que devuelve `bool`. Quien incluya el encabezado debe poder comprenderlo sin adivinar que faltaba incluir otra biblioteca antes.

## 3. Proteger una inclusión repetida

Los encabezados tienen una **guarda de inclusión**:

```c
#ifndef CURSO_C_RECIBO_H
#define CURSO_C_RECIBO_H

/* Declaraciones del encabezado. */

#endif
```

Estas líneas son directivas del **preprocesador**, que actúa antes de la compilación propiamente dicha. No son decisiones que se ejecuten al usar el programa:

1. `#ifndef` pregunta si el nombre aún no está definido.
2. `#define` lo define como marca; no creamos una variable de ejecución.
3. El contenido del encabezado se procesa una vez en esa unidad de traducción.
4. `#endif` cierra la condición. Una nueva inclusión con la marca ya definida omite ese contenido.

Cada encabezado usa una marca propia. Copiar la misma marca a dos encabezados distintos podría ocultar las declaraciones de uno. No confundas esta protección con una garantía de que una función se definió una sola vez en todo el programa: esa es otra responsabilidad.

En los archivos de pruebas también verás `#ifdef NDEBUG` seguido de `#error`: si se intenta construir con aserciones desactivadas, se solicita un diagnóstico y la compilación falla. No se finge haber pasado pruebas que no se ejecutaron.

## 4. Construir el recibo en un comando

Entra con tu terminal a `unidad10-organizacion`. Comprueba con `ls` que ves `proyecto`, crea `build` con `mkdir -p build` y usa la fila de tu sistema. En Windows usa UCRT64.

| Sistema | Construir | Ejecutar después de construir correctamente |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/main.c proyecto/entrada.c proyecto/recibo.c -o build/recibo` | `./build/recibo` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/main.c proyecto/entrada.c proyecto/recibo.c -o build/recibo.exe` | `./build/recibo.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic proyecto/main.c proyecto/entrada.c proyecto/recibo.c -o build/recibo` | `./build/recibo` |

Se compilan tres fuentes y se enlazan sus resultados para obtener un ejecutable. No se generan tres programas independientes ni empieza una ejecución por cada fuente.

Escribe 10 y Enter. La salida del programa debe ser:

```text
Cantidad de 0 a 100, solo digitos (maximo 8).
Subtotal: 1250 centavos
Envio: 0 centavos
Total: 12.50
```

Los casos 0, 1, 9, 100 y los rechazos de entrada deben conservar el comportamiento de la Unidad 09. Sigue siendo una sola solicitud, con entero acotado, máximo de ocho bytes y consumo hasta terminador. No se añadió conversión general de números ni un menú permanente.

## 5. Ver las etapas con archivos objeto

Una **unidad de traducción** es, de forma simplificada para este proyecto, un fuente `.c` con el contenido incorporado por sus inclusiones tras el preprocesamiento. Cada una se compila por separado.

`-c` pide compilar sin realizar el enlace final. Produce un **archivo objeto** `.o`, que puede contener referencias todavía por resolver. No lo ejecutamos como un programa de consola.

Para explorar las etapas, desde esta misma carpeta, ejecuta **un paso y comprueba su resultado antes del siguiente**. Los comandos de compilación son iguales en Ubuntu y UCRT64; en macOS sustituye `gcc` por `clang`.

Primero compila la coordinación:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -c proyecto/main.c -o build/main.o
```

Confirma que existe `build/main.o`. Después compila la lectura:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -c proyecto/entrada.c -o build/entrada.o
```

Confirma ese objeto. Después compila el cálculo:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -c proyecto/recibo.c -o build/recibo.o
```

Solo cuando los tres pasos terminen correctamente, enlaza:

```bash
gcc build/main.o build/entrada.o build/recibo.o -o build/recibo_objetos
```

En Windows usa salida `build/recibo_objetos.exe`; en macOS usa `clang`. Ejecuta `./build/recibo_objetos` o su variante `.exe` y compara con la construcción de un comando.

Las opciones de C17 y advertencias se aplicaron al compilar los fuentes. El último comando recibe los objetos ya compilados. Si modificas `recibo.c`, vuelve a compilar su objeto y a enlazar. Si modificas un encabezado, vuelve a compilar los fuentes que lo incluyen y a enlazar. Para empezar, reconstruir los tres es una estrategia clara; más adelante automatizaremos dependencias con Make.

## 6. Qué significa `static` en esta presentación

`main.c` define `static void mostrar_recibo(int cantidad)`. En una función a nivel de archivo, `static` limita su enlace a esa unidad de traducción. No exponemos esa función como parte de `recibo.h`, porque es un detalle de presentación del controlador.

Eso no quiere decir que la función se ejecute una sola vez ni que guarde estado entre llamadas. El uso de `static` en una variable local tiene otras propiedades y se estudiará al abordar almacenamiento y duración. Aquí no usamos variables locales estáticas ni estado global mutable.

## 7. Probar el cálculo que realmente se usa

Construye el ejecutable de pruebas **en un paso separado**, desde `unidad10-organizacion`:

| Sistema | Construir pruebas | Ejecutar |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/pruebas_recibo.c proyecto/recibo.c -o build/pruebas` | `./build/pruebas` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/pruebas_recibo.c proyecto/recibo.c -o build/pruebas.exe` | `./build/pruebas.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic proyecto/pruebas_recibo.c proyecto/recibo.c -o build/pruebas` | `./build/pruebas` |

Salida esperada:

```text
Pruebas del recibo: OK.
```

Se comprueban límites del validador, subtotal, envío y total, incluida la frontera 9/10. El cálculo se enlaza desde `recibo.c`; no se copia dentro del archivo de pruebas. No incluimos `main.c` ni `entrada.c`, porque este ejecutable tiene su propio `main` y no necesita teclado.

Estas pruebas verifican cálculos y validación de cantidad. No demuestran por sí solas que el lector consuma una línea inválida correctamente, ni que todos los mensajes sean los acordados: conserva también las pruebas de integración con entradas completas. No definas `NDEBUG` en esta construcción.

## 8. Diagnosticar según la etapa

| Síntoma | Etapa probable | Qué revisar |
|---|---|---|
| No encuentra `recibo.h` | Preprocesamiento | Ruta, nombre e inclusión |
| La definición contradice el prototipo | Compilación | Firma del encabezado y definición |
| No encuentra `leer_cantidad` al construir | Enlace | Si falta `entrada.c` o su objeto |
| Hay dos definiciones de `main` | Enlace | Si reuniste aplicación y pruebas en un ejecutable |
| Se muestra el resultado anterior | Flujo de construcción | Guardado, reconstrucción y éxito antes de ejecutar |
| Falla una aserción | Ejecución de pruebas | Caso esperado y regla implementada |

Un encabezado correcto permite compilar una llamada, pero no entrega su cuerpo al enlazador. Un archivo objeto creado correctamente tampoco garantiza que el enlace final haya pasado.

No uses `proyecto/*.c` para construir este proyecto: esa selección reuniría los dos `main`. Los comandos enumeran los fuentes según el ejecutable deseado.

## Práctica y cierre

Resuelve [EJERCICIOS.md](EJERCICIOS.md); [SOLUCIONES.md](SOLUCIONES.md) incluye una política alternativa de envío con sus pruebas y comandos completos.

- [ ] Explico qué contiene cada `.h` y cada `.c`.
- [ ] Construyo aplicación y pruebas como ejecutables separados.
- [ ] Distingo errores de preprocesamiento, compilación, enlace y ejecución.
- [ ] Reutilizo una implementación en lugar de copiarla dentro de sus pruebas.
- [ ] Reconstruyo lo necesario al cambiar un fuente o encabezado.
- [ ] Conservo el comportamiento al organizar y actualizo contrato y pruebas al cambiar una regla.

El siguiente bloque abordará arreglos, recorridos y cadenas con límites. Todavía no está publicado. Conserva el proyecto, los comandos que utilizaste y al menos una evidencia de diagnóstico de enlace.
