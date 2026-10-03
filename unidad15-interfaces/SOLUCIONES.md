# Unidad 15 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Ajuste de tipo

La cantidad se calcula en `main`, donde `datos` es el arreglo de tres enteros. En la auxiliar el parámetro se ajusta a puntero; `sizeof` no recupera el tamaño original. `NULL` con cero es válido porque no se accede ni se forma una dirección con él. Un tamaño escrito en corchetes de un parámetro ordinario no convierte ese puntero en un arreglo copiado ni entrega metadatos de extensión.

## 2. Un elemento después

`datos + 1` señala el segundo elemento, cuyo valor es cero. `datos + cantidad` señala el límite inmediatamente posterior al tercero. El ciclo termina antes de leerlo. Avanzar una unidad depende del tipo de elemento; no se suma manualmente un número de bytes ni se modifica el tipo del puntero.

## 3. Colección

En [proyecto/pruebas_coleccion.c](proyecto/pruebas_coleccion.c), puedes agregar datos `{100}`, `{100, 100, 100, 100, 100}`, `{-1}` y `{0}`. Las sumas son 100 y 500, el mínimo del único cero es cero y el caso -1 conserva la salida inicial 77 con `false`. Usa cantidades 1 o 5 según el objeto declarado. La suma de una colección vacía es éxito con cero; su mínimo es rechazo con resultado intacto.

## 4. Copia

Cinco letras requieren seis elementos; seis letras requieren siete. La comprobación ocurre antes de la primera escritura. Una cadena vacía requiere un terminador y cabe en un elemento. Un puntero nulo no señala siquiera ese terminador, por lo que se rechaza antes de llamar a `strlen`.

## 5. Implementación del filtro

Interfaz: [soluciones/filtro.h](soluciones/filtro.h). Implementación: [soluciones/filtro.c](soluciones/filtro.c). Controlador: [soluciones/main_filtro.c](soluciones/main_filtro.c).

Desde `unidad15-interfaces`, primero construye:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic soluciones/main_filtro.c soluciones/filtro.c -o build/filtro
```

En macOS usa `clang`; en UCRT64 usa salida `build/filtro.exe`. Luego ejecuta el resultado. Salida:

```text
Seleccionadas: 3
Valor: 8
Valor: 10
Valor: 5
```

El primer recorrido valida y cuenta; el segundo escribe solo si la colección completa cabe. No usa la capacidad como longitud de datos del origen. En resultado vacío no desreferencia el destino nulo de capacidad cero.

## 6. Pruebas compartidas

Fuente: [soluciones/pruebas_filtro.c](soluciones/pruebas_filtro.c). Construye en un paso separado:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic soluciones/pruebas_filtro.c soluciones/filtro.c -o build/pruebas_filtro
```

Aplica las variantes de sistema indicadas y ejecuta. Espera `Pruebas de filtro: OK.`. Los casos rechazos usan valores previos 70, 71, 72 y cantidad 99 para comprobar que no cambiaron. Esos valores de prueba no son registros aceptados ni códigos de error; permiten detectar una escritura accidental.

Ambos ejecutables enlazan `filtro.c`. Una copia independiente del algoritmo en las pruebas podría permanecer correcta mientras la implementación usada por la aplicación se rompe. Compartir la implementación hace que los casos se apliquen a la misma función.

## Evidencia de cierre

Conserva los dos comandos, las salidas y la explicación de un caso que no cabe. Identifica las precondiciones de memoria real que las comprobaciones de cantidad por sí solas no pueden demostrar.
