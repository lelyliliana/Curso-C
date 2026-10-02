# Unidad 02 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Seguir una copia

| Después de… | `original` | `copia` |
|---|---:|---:|
| Declarar `original` | 4 | No declarada |
| Declarar `copia` | 4 | 4 |
| `original = 7;` | 7 | 4 |
| `copia = 2;` | 7 | 2 |

Salida: `7 4`, salto de línea, `7 2`, salto de línea. Para copiar el valor actual escribe `copia = original;`. Cambiar `copia` tampoco cambia `original`.

## 2. Elegir nombres

`total_libros` y `edad` son válidos. `3mesas` comienza con un dígito; `return` es una palabra reservada; `mi edad` contiene un espacio. C distingue mayúsculas: usar `Edad` cuando solo declaraste `edad` provoca un diagnóstico de nombre no declarado.

## 3. Ficha

Fuente completo: [soluciones/03-ficha.c](soluciones/03-ficha.c). Las declaraciones son `int edad = 19;` e `int lecciones = 2;`; cada `printf` recibe la variable después del formato. Para la variante cambia a `int lecciones = 3;` y recompila. Editar solo el fuente no modifica el ejecutable anterior.

## 4. Inventario

Fuente completo: [soluciones/04-inventario.c](soluciones/04-inventario.c). El registro se crea cuando las existencias valen 15. La actualización a 11 deja el registro en 15 hasta copiar nuevamente. Si la primera copia se hiciera después de la actualización, el registro empezaría en 11 y no conservaría el 15 anterior.

## 5. Reparaciones

```c
int mesas = 3;
mesas = 5;
printf("Mesas: %d\n", mesas);
```

Declaramos una vez y luego asignamos. La segunda declaración en el mismo bloque era una redefinición.

```c
int libros = 8;
printf("%d\n", libros);
```

El valor inicial corresponde al dato conocido. No leemos antes de inicializar.

```c
int sillas = 12;
printf("Sillas: %d\n", sillas);
```

El `%d` necesitaba el argumento entero. Se añadió una impresión para comprobar también el cambio de `mesas`. Los tres fragmentos corregidos se pueden colocar, en ese orden, dentro de un `main` como los de la guía; imprimen `Mesas: 5`, `8` y `Sillas: 12` en líneas separadas.

## 6. Capacidad y asistentes

```c
const int capacidad = 20;
int asistentes = 12;
```

Los asistentes pueden actualizarse con otra asignación. La capacidad no debe cambiar durante esta ejecución. Si su valor inicial estaba mal escrito, corrige la inicialización en el fuente y recompila: `const` restringe las modificaciones del objeto durante la ejecución, no la edición del archivo por quien programa.
