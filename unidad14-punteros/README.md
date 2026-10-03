# Unidad 14 — Direcciones, punteros y objetos vivos

[Inicio](../README.md) · [Anterior: cadenas](../unidad13-cadenas/README.md) · [Siguiente: interfaces](../unidad15-interfaces/README.md)

## Objetivo

Hasta ahora una función recibía valores y devolvía resultados. Ahora podrás permitir que una función acceda a un objeto del llamador mediante su dirección. Aprenderás a distinguir el valor, la dirección y el puntero que guarda esa dirección, sin utilizar memoria dinámica todavía.

Necesitas funciones, contratos y variables locales. Al terminar podrás interpretar `&` y `*`, modificar un objeto por un puntero válido, comprobar ausencia con `NULL`, utilizar salidas por puntero y explicar por qué un objeto debe seguir vivo durante el acceso.

## 1. Tres cosas diferentes

Abre [ejemplos/01-direccion.c](ejemplos/01-direccion.c):

```c
int cantidad = 12;
int *acceso = &cantidad;
```

`cantidad` es un objeto que almacena un entero. `&cantidad` obtiene su dirección. `acceso` es otro objeto: una variable de tipo puntero a `int`, inicializada con esa dirección. No almacena una copia del 12.

| Expresión | Qué representa | Resultado inicial |
|---|---|---|
| `cantidad` | Valor del entero | 12 |
| `&cantidad` | Dirección del entero | Depende de la ejecución |
| `acceso` | Dirección almacenada en el puntero | La misma que `&cantidad` |
| `*acceso` | Objeto al que accede el puntero | El entero `cantidad` |
| `&acceso` | Dirección de la variable puntero | Otro objeto, distinto de `cantidad` |

El `*` en una declaración indica el tipo puntero. En una expresión como `*acceso` **desreferencia** el puntero: permite acceder al objeto señalado. El mismo símbolo también es multiplicación en otros contextos, como `a * b`.

`*acceso = 9;` escribe en `cantidad`. No cambia la dirección almacenada en `acceso`. En cambio, asignar otra dirección a `acceso` cambiaría a qué objeto accede después.

Declara cada variable con claridad. `int *a, b;` declara un puntero `a` y un entero `b`, no dos punteros. En este curso usamos declaraciones separadas para evitar esa confusión.

## 2. Construir y observar

Realiza cada paso por separado:

1. Desde la carpeta del curso entra con `cd unidad14-punteros`.
2. Usa `ls` y confirma las carpetas `ejemplos` y `soluciones`.
3. Crea `build` con `mkdir -p build`.
4. Compila según tu sistema; ejecuta después de comprobar que la construcción terminó correctamente.

| Sistema | Construir | Ejecutar después |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-direccion.c -o build/direccion` | `./build/direccion` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-direccion.c -o build/direccion.exe` | `./build/direccion.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-direccion.c -o build/direccion` | `./build/direccion` |

En Windows usa UCRT64. Cada fuente de esta unidad tiene su propio `main`; para los otros cambia fuente y nombre de salida, sin combinarlos.

El programa imprime valor 12, una dirección, valor por puntero 12 y valor posterior 9. La línea de dirección utiliza `%p` y `(void *)acceso`, que adapta un puntero a objeto al tipo requerido por ese formato. No uses `%d` ni conviertas la dirección en un entero para mostrarla.

La representación de `%p` depende de la implementación y la dirección puede cambiar entre ejecuciones. No memorices el número ni lo uses como identidad permanente de un dato. Lo que debes verificar es la relación: el puntero accede al objeto que fue inicializado con 12 y la escritura cambia ese mismo objeto.

## 3. Todos los argumentos siguen pasando por valor

Abre [ejemplos/02-argumentos.c](ejemplos/02-argumentos.c). Contrasta:

```c
void cambiar_copia(int valor);
void cambiar_objeto(int *acceso);
```

La primera función recibe una copia del entero. La segunda recibe una copia de la dirección. **También el puntero se pasa por valor**; no se crea automáticamente una referencia a la variable puntero del llamador.

| Objeto durante la segunda llamada | Qué conserva | Qué puede cambiar |
|---|---|---|
| `cantidad` en `main` | El entero compartido mediante su dirección | `*acceso = 9` cambia su valor |
| `acceso` en `main` | Dirección de `cantidad` | No lo cambia asignar al parámetro local |
| Parámetro `acceso` en la función | Copia de esa dirección | Puede reasignarse dentro de la función |

La función primero escribe 9 en el objeto señalado y después asigna `NULL` a su parámetro local. Esa reasignación no borra ni vuelve nulo el puntero de `main`.

Salida:

```text
Copia local: 9
Tras copia: 12
Tras acceso: 9
El puntero del llamador conserva su direccion.
```

El contrato de `cambiar_objeto` requiere un puntero válido a un `int` modificable que siga vivo. Este primer ejemplo no comprueba argumentos externos: `main` prepara una dirección correcta. El siguiente ejemplo agrega comprobaciones de estados admitidos.

## 4. Puntero nulo y acceso válido

`NULL`, disponible en encabezados como `<stddef.h>`, representa un puntero nulo en el contexto de un puntero. Puede significar «no se proporcionó objeto». Nunca debe desreferenciarse.

[ejemplos/03-validar.c](ejemplos/03-validar.c) define `bool descontar_uno(int *cantidad)`. Primero comprueba `cantidad == NULL`; solo después lee `*cantidad`. Exige un valor de 1 a 100 y descuenta uno. Si rechaza el argumento o el valor, devuelve `false` sin cambiar el entero.

Salida:

```text
Descuento valido: 0
Sin descuento; conserva 0.
Puntero nulo rechazado.
```

Cero es un resultado válido del primer descuento. No se utiliza como señal de error: el éxito se comunica mediante `bool`. El segundo intento falla porque el estado cero ya no permite descontar según ese contrato.

**No nulo no equivale a válido.** Comprobar `NULL` no permite detectar un puntero sin inicializar, un objeto destruido, una dirección inventada, un tipo incompatible o memoria que no puede escribirse. El llamador conserva la responsabilidad de proporcionar un objeto válido con la duración y permisos requeridos.

No ejecutes desreferencias inválidas para observar qué sucede. C no garantiza una excepción recuperable ni un mensaje de error. En este bloque todos los punteros usados para acceso provienen de objetos vivos o de `NULL` comprobado antes de acceder.

## 5. Duración: la dirección no prolonga la vida

Los objetos locales ordinarios existen durante la ejecución de su bloque. Una función auxiliar puede usar `&cantidad` mientras `main` está ejecutándose y el objeto sigue vivo. Guardar una dirección no prolonga esa vida.

Si una función crea `int temporal = 7;` dentro de su cuerpo y devuelve `&temporal`, no entrega una manera válida de consultar ese entero después de volver: el objeto local ya terminó su duración. No construimos ni ejecutamos esa función incorrecta. La solución depende de la responsabilidad: devolver el valor por `return`, escribir en un objeto del llamador o, en un bloque posterior, gestionar otra duración de almacenamiento.

Una dirección a un elemento de un arreglo local tiene la misma limitación: el arreglo debe seguir vivo. Cambiar el valor de un objeto existente no termina su duración, pero salir de su bloque sí termina la de estos objetos locales ordinarios.

Un puntero puede copiarse y varias copias pueden acceder al mismo objeto; por eso debe quedar claro quién puede modificarlo y por cuánto tiempo. Más adelante estudiaremos asignación y liberación de memoria dinámica. Aquí no usamos `malloc` ni `free`.

## 6. Dos significados de `const`

Abre [ejemplos/04-const.c](ejemplos/04-const.c):

```c
const int *lectura = &cantidad;
int *const acceso_fijo = &cantidad;
```

- `const int *lectura`: no permite modificar el entero **a través de ese puntero**. La variable puntero sí podría recibir otra dirección compatible.
- `int *const acceso_fijo`: no permite reasignar ese puntero después de inicializarlo. Sí permite modificar el entero señalado, si ese objeto es modificable.

El ejemplo produce 12 y luego 7 al leer mediante `lectura`. `const int *` no congela un objeto que fue declarado modificable: otro acceso autorizado puede actualizarlo.

Si el objeto original fue declarado `const int`, debes conservar esa restricción. No quites `const` mediante una conversión para intentar escribir. `const` en una interfaz de lectura expresa permisos de acceso; no es una garantía de aislamiento frente a todos los demás accesos.

## 7. Varias salidas y objetos compartidos

[soluciones/05-intercambio.c](soluciones/05-intercambio.c) intercambia dos enteros mediante punteros. Requiere objetos vivos y modificables; comprueba ambos contra `NULL`. Usa un temporal para no perder el primer valor. Si ambos argumentos señalan el mismo objeto, el intercambio deja el valor igual y sigue siendo válido.

[soluciones/06-division.c](soluciones/06-division.c) devuelve éxito mediante `bool` y escribe cociente y resto en dos salidas:

```c
int cociente = -1;
int resto = -1;
bool ok = dividir_con_resto(17, 5, &cociente, &resto);
```

Contrato: objetos de 0 a 100, capacidad de 1 a 100, dos salidas escribibles **distintas**. La función rechaza salidas nulas o iguales y valores fuera del dominio antes de dividir o escribir. Con éxito escribe 3 y 2. Con divisor cero conserva esos resultados anteriores y devuelve `false`.

Los -1 iniciales son valores de prueba para comprobar conservación, no un código de error que deba mezclarse con los resultados. El llamador interpreta primero el `bool`.

## Práctica y cierre

Resuelve [EJERCICIOS.md](EJERCICIOS.md) y consulta luego [SOLUCIONES.md](SOLUCIONES.md).

- [ ] Distingo objeto, valor, dirección y variable puntero.
- [ ] Explico que el parámetro puntero también es una copia.
- [ ] Compruebo ausencia antes de desreferenciar, sin confundirlo con validación completa.
- [ ] Justifico la duración y los permisos del objeto señalado.
- [ ] Distingo puntero a dato constante y puntero constante.
- [ ] Interpreto el estado antes de usar salidas de una función.

Conserva una tabla de los objetos de `main` y de los parámetros durante una llamada. En la [Unidad 15](../unidad15-interfaces/README.md) aplicarás estos conceptos a arreglos y cadenas con cantidad y capacidad explícitas.
