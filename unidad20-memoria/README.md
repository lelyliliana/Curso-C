# Unidad 20 — Reservar, crecer y liberar memoria

[Inicio](../README.md) · [Anterior: archivos](../unidad19-archivos/README.md) · [Siguiente: recursos](../unidad21-recursos/README.md)

## El problema que resolverás

Hasta ahora una colección cabía en un arreglo de capacidad fija. ¿Qué ocurre si el usuario necesita cinco posiciones hoy y veinte mañana? La memoria dinámica permite solicitar almacenamiento durante la ejecución. No elimina los límites: exige decidir cuánto pedir, comprobar si se obtuvo, inicializar los datos y devolver el bloque cuando deja de utilizarse.

Al terminar podrás construir una colección creciente de números de 0–100, separar cantidad utilizada de capacidad y explicar qué ocurre si no se puede crecer. Necesitas funciones, punteros, estructuras y contratos de las unidades 08–17. Si todavía confundes una dirección con el dato al que apunta, vuelve a la [Unidad 14](../unidad14-punteros/README.md).

## 1. Dos duraciones diferentes

En `int local[3];`, el almacenamiento automático dura mientras se ejecuta su bloque. No se devuelve con `free`. En `int *datos = malloc(...);`, la variable puntero puede ser local, pero el bloque solicitado permanece hasta que se libera. Salir de la función no libera automáticamente ese bloque.

`malloc` devuelve un puntero al almacenamiento o `NULL` si no logra asignarlo. Declaramos la función incluyendo `<stdlib.h>`. En C no añadimos una conversión explícita al resultado de `malloc`: su `void *` se convierte al tipo de puntero necesario. C++ tiene reglas distintas; estamos escribiendo C17.

Una reserva exitosa no trae números inicializados. Antes de leer `datos[i]`, escribe un valor válido. No intentes descubrir su contenido inicial imprimiéndolo: leer valores indeterminados no es una prueba de memoria.

## 2. Primera reserva, paso a paso

1. Desde la carpeta del curso entra con `cd unidad20-memoria`.
2. Crea `build` con `mkdir -p build` en Ubuntu/macOS. En PowerShell utiliza `New-Item -ItemType Directory -Force build`.
3. Abre [01-reservar.c](ejemplos/01-reservar.c) y anticipa su salida.
4. Compila usando la fila de tu sistema.
5. Ejecuta solo si la compilación termina correctamente.

| Sistema | Compilar | Ejecutar |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-reservar.c -o build/reservar` | `./build/reservar` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-reservar.c -o build/reservar.exe` | `./build/reservar.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-reservar.c -o build/reservar` | `./build/reservar` |

Salida esperada: `1`, `2`, `3`, cada uno en una línea. El ejemplo solicita exactamente tres enteros, los escribe, los lee y libera el bloque una sola vez. Si falla la reserva, informa por `stderr` y termina con fracaso antes de acceder al bloque.

`cantidad * sizeof *datos` calcula bytes para los elementos, no el tamaño del puntero. `sizeof *datos` consulta el tamaño de un `int`; no lee el objeto ni necesita que `datos` apunte todavía a una reserva. En este ejemplo la cantidad fija tres es pequeña; una cantidad externa requiere comprobar la multiplicación.

## 3. Tamaño representable y límite del problema

`size_t` representa tamaños y se imprime con `%zu`. Se puede desbordar al multiplicar: el resultado podría ser pequeño aunque la solicitud conceptual fuera enorme. Antes de `n * sizeof *p`, verifica:

```c
if (n > SIZE_MAX / sizeof *p) {
    /* Rechazar antes de multiplicar. */
}
```

`SIZE_MAX` se obtiene de `<stdint.h>`. La división usa un tamaño distinto de cero. No realizamos primero el producto para comprobar después si se desbordó.

Además del límite representable, nuestro problema admite como máximo 1000 números. Es una política visible, no la cantidad total de memoria del equipo. Un tamaño representable puede seguir siendo excesivo o no estar disponible. La comprobación aritmética y el retorno del asignador responden preguntas diferentes.

No provocamos falta de memoria solicitando cantidades gigantescas. Ese ensayo depende del sistema y puede perjudicar otros procesos. Las pruebas de desarrollo pueden simular el fallo de una asignación de tamaño pequeño.

## 4. `calloc` e inicialización

Abre [02-ceros.c](ejemplos/02-ceros.c). Compílalo cambiando el fuente y el nombre de salida del comando anterior; ejecútalo después. Obtendrás tres líneas con `0`.

`calloc(cantidad, sizeof *datos)` reserva y pone los bytes a cero. Para este arreglo de `int`, eso representa enteros cero. No generalices a que bytes cero siempre forman cualquier puntero nulo o cualquier representación de punto flotante en toda plataforma. Para una estructura con punteros, la inicialización de C `struct Numeros lista = {0};` sí establece los valores iniciales correctos de sus miembros, incluido el puntero nulo.

`calloc` también puede fallar. No sustituye la comprobación de `NULL`, los límites del problema ni la liberación. Elegir `malloc` o `calloc` depende de qué datos necesitas inicializar; no hacemos reservas enormes solo porque una función parezca cómoda.

## 5. Crecer sin perder la reserva anterior

`realloc(p, bytes)` solicita un bloque de otro tamaño. Con tamaño positivo, si falla devuelve `NULL` y el bloque anterior permanece válido. Si tiene éxito, conserva el contenido del tramo común; los bytes añadidos no están inicializados.

El patrón de [numeros.c](proyecto/numeros.c) utiliza un puntero temporal:

```c
int *nuevo = realloc(lista->datos, capacidad * sizeof *lista->datos);
if (nuevo == NULL) return false;
lista->datos = nuevo;
lista->capacidad = capacidad;
```

No escribimos directamente el retorno en el único puntero propietario antes de comprobarlo: un fallo haría perder la dirección que aún necesitamos liberar. Tras el éxito usamos únicamente el puntero devuelto. Aunque el bloque parezca estar en la misma dirección, no conservamos ni comparamos punteros anteriores a esa reserva; reconstruimos los accesos desde el nuevo propietario. Los punteros a elementos del bloque también dejan de servir tras un crecimiento exitoso.

`realloc(NULL, tamaño_positivo)` permite la primera reserva. Evitamos `realloc(p, 0)` y las reservas de tamaño cero: una solicitud de capacidad cero en nuestro módulo no asigna, y liberar tiene su propia operación explícita.

## 6. Una colección con contrato

La interfaz [numeros.h](proyecto/numeros.h) agrupa `datos`, `usados` y `capacidad`. Inicializa cada colección con `{0}` y utiliza sus funciones; no inventes un puntero ni edites los metadatos.

| Operación | Comportamiento |
|---|---|
| `reservar_numeros` | Aumenta capacidad, sin cambiar cantidad ni valores; una solicitud menor no reduce |
| `agregar_numero` | Valida 0–100, crece si hace falta y publica el nuevo elemento al final |
| `liberar_numeros` | Libera el bloque y restablece puntero nulo y cantidades cero |

Solo las posiciones anteriores a `usados` contienen valores publicados. Tener capacidad ocho y cantidad cinco no autoriza leer las otras tres. La reserva empieza en dos y crece al doble, hasta 1000. No se promete una capacidad concreta como contrato general; el ejemplo muestra la política actual.

El módulo comprueba nulidad y forma de los metadatos, pero no puede certificar que una dirección arbitraria sea válida, tenga la extensión declarada o pertenezca al llamador. La propiedad exclusiva es una precondición. Copiar `struct Numeros` por asignación copiaría la dirección, no los números; dos supuestos propietarios podrían intentar liberar el mismo bloque. La siguiente unidad enseña cómo copiar correctamente.

## 7. Ejecutar el proyecto

1. Mantén la terminal en `unidad20-memoria` y `build` creado.
2. Compila `proyecto/main.c` junto con `proyecto/numeros.c`.
3. Ejecuta el resultado.

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/main.c proyecto/numeros.c -o build/numeros
```

En Windows añade `.exe` a la salida y ejecútala con `./build/numeros.exe`. En macOS usa `clang`. En Ubuntu/macOS ejecuta `./build/numeros`.

Salida:

```text
Usados: 5; capacidad: 8
0
25
100
40
60
Tras liberar: 0 0
```

La liberación pone a nulo el puntero propietario, pero no arregla otras copias de su dirección. Nunca uses un préstamo después de que se libera el bloque. `free(NULL)` no hace nada; `free` sobre un objeto automático, una dirección interior o un bloque ya liberado tiene comportamiento indefinido.

## 8. Verificar y practicar

1. Compila `proyecto/pruebas_numeros.c` junto con `proyecto/numeros.c`, con salida `build/pruebas_numeros` o `.exe`.
2. Ejecuta. Espera `Pruebas de numeros: OK.`.
3. Revisa por qué los datos siguen iguales tras rechazar el elemento 1001 y una capacidad imposible.
4. Resuelve [EJERCICIOS.md](EJERCICIOS.md) antes de consultar [SOLUCIONES.md](SOLUCIONES.md).

Las pruebas llaman funciones fuera de `assert` y después comprueban resultados. Rechazan compilar con `NDEBUG` para evitar una ejecución que omita las comprobaciones. No garantizan todas las asignaciones posibles.

- [ ] Calculo bytes sin confundir puntero y elemento.
- [ ] Valido tamaño antes de multiplicar y compruebo el retorno.
- [ ] Distingo reserva de datos inicializados.
- [ ] Conservo el propietario ante fallo de crecimiento.
- [ ] Libero una vez y descarto préstamos vencidos.
- [ ] Explico cantidad cero sin reservar ni leer posiciones.

Continúa con la [Unidad 21](../unidad21-recursos/README.md): una colección de registros tendrá copia independiente, transferencia de propiedad y limpieza ante fallos.
