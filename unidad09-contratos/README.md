# Unidad 09 — Contratos y responsabilidades: qué promete cada función

[Inicio](../README.md) · [Anterior: funciones](../unidad08-funciones/README.md) · [Siguiente: organización](../unidad10-organizacion/README.md)

## Objetivo

Una función con nombre no es automáticamente reutilizable. Necesitas saber qué admite, qué devuelve y qué efectos produce. En esta unidad separarás el recibo en lectura, validación, cálculo y presentación, conservando las reglas del programa de la Unidad 07.

Un **contrato** es esa promesa explícita entre función y llamador. Una **precondición** es algo que debe cumplirse antes de llamar; una **postcondición**, algo que debe cumplirse al terminar correctamente. No son palabras obligatorias en el código, sino herramientas para razonar y documentar.

## 1. Escribir el contrato antes del cuerpo

Para el recibo mantenemos precio unitario de 125 centavos y cantidad de 0 a 100. El envío es 500, gratuito desde 10 artículos y cero cuando no hay compra.

| Función | Recibe | Devuelve | Precondición | Efectos |
|---|---|---|---|---|
| `cantidad_valida` | Cualquier `int` | `bool` | Ninguna adicional | No lee ni imprime |
| `subtotal_centavos` | Cantidad | Centavos | Cantidad 0–100 | No lee ni imprime |
| `envio_centavos` | Cantidad | 0 o 500 centavos | Cantidad 0–100 | No lee ni imprime |
| `total_centavos` | Cantidad | Subtotal más envío | Cantidad 0–100 | No lee ni imprime |

Archivo: [ejemplos/01-contrato.c](ejemplos/01-contrato.c). `main` comprueba `cantidad_valida` **antes** de llamar los cálculos.

```c
bool cantidad_valida(int cantidad)
{
    return cantidad >= 0 && cantidad <= 100;
}
```

El resultado válido cero no se usa para señalar un fallo. Con cantidad cero, subtotal, envío y total son cero por la regla del problema. Una cantidad -1 se rechaza mediante el validador y no llega al cálculo.

Las funciones de cálculo confían en su precondición; no están diseñadas para recibir cualquier entero. La frontera con los datos externos debe validarla. Convertir una función en `int` no hace que compruebe automáticamente lo que recibe.

### Compilar y ejecutar

Entra a `unidad09-contratos` con la terminal de tu sistema. En Windows usa UCRT64. Comprueba con `ls` y crea `build` con `mkdir -p build`.

| Sistema | Compilar | Ejecutar tras compilar correctamente |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-contrato.c -o build/contrato` | `./build/contrato` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-contrato.c -o build/contrato.exe` | `./build/contrato.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-contrato.c -o build/contrato` | `./build/contrato` |

Con cantidad inicial 9:

```text
Subtotal: 1125 centavos
Envio: 500 centavos
Total: 16.25
```

Cambia a 10 y espera subtotal 1250, envío 0 y total 12.50. Cambia a 101 y espera solo `Cantidad invalida.` con finalización de fallo. Guarda y recompila cada variante. Los archivos de esta unidad siguen siendo programas independientes; para los demás sustituye fuente y nombre del ejecutable, no los reúnas todos.

## 2. Funciones que calculan y funciones que producen efectos

Las funciones de cálculo anteriores solo dependen de sus argumentos y no producen efectos externos. Para el mismo argumento válido devuelven el mismo resultado. Puedes utilizarlas sin iniciar una lectura interactiva.

`leer_cantidad`, en cambio, consume entrada. Dos llamadas consecutivas pueden recibir líneas diferentes. `mostrar_recibo` produce salida. Estos efectos forman parte de sus contratos y deben ser visibles en el diseño.

No pongas el mensaje de solicitud dentro de `subtotal_centavos`, ni una lectura dentro de `mostrar_recibo`. El flujo de la aplicación será:

1. `main` muestra la solicitud.
2. El lector consume y comprueba una línea.
3. `main` interpreta el resultado o el estado recibido.
4. Los cálculos reciben una cantidad válida.
5. La presentación muestra los resultados.

## 3. Una función auxiliar devuelve el control al llamador

En la Unidad 07, un fallo se atendía con `return EXIT_FAILURE;` dentro de `main`. Al extraer el lector, ese mismo `return` ya terminaría la función auxiliar, no el programa. Además, el llamador necesita distinguir fin, error e invalidez.

Archivo: [ejemplos/02-lector.c](ejemplos/02-lector.c). `leer_cantidad(void)` conserva el consumo por bytes, el máximo de ocho y la comprobación antes de multiplicar. Deja de imprimir mensajes y devuelve información a `main`.

Este cambio requiere un contrato de retorno claro: **0–100 significa una cantidad válida; otros resultados nombrados significan estados**. Es una interfaz acotada para este ejercicio, sin utilizar todavía parámetros de salida mediante punteros.

## 4. Nombrar los estados con una enumeración pequeña

Introducimos una primera enumeración para evitar números sin explicación:

```c
enum ResultadoLectura {
    LECTURA_INVALIDA = -1,
    LECTURA_FIN = -2,
    LECTURA_ERROR = -3
};
```

`enum` declara una enumeración y sus nombres de valores. En esta base C17, estos enumeradores tienen valores enteros representables como `int`. Asignamos los tres valores explícitamente y usamos sus **nombres** en las decisiones. El punto y coma cierra la declaración.

La función devuelve `int`, porque también necesita representar cantidades de 0 a 100. No devuelve una variable del tipo de la enumeración para cada cantidad. Los nombres sirven aquí para clasificar resultados fuera del dominio numérico válido.

| Resultado de `leer_cantidad` | Significado | Acción del llamador de una solicitud |
|---|---|---|
| 0–100 | Línea válida | Utilizar la cantidad |
| `LECTURA_INVALIDA` | Línea recibida que viola el contrato | Mostrar rechazo y finalizar con fallo |
| `LECTURA_FIN` | Fin antes de recibir cualquier byte | Cerrar normalmente sin inventar cantidad |
| `LECTURA_ERROR` | Error de lectura | Mostrar error y finalizar con fallo |

Los estados no son cantidades negativas ni lecturas «corregidas». No los sumes ni los conviertas a cantidad cero. Si ampliáramos el dominio para admitir negativos, esta estrategia necesitaría revisarse: estado y dato no podrían compartir los mismos valores. Más adelante estudiaremos resultados compuestos y otras interfaces.

## 5. El lector conserva el contrato de entrada

Admite uno a ocho dígitos básicos, con ceros iniciales, cantidad de 0 a 100, salto `\n` o fin tras los dígitos. Rechaza signos, espacios, fracciones, caracteres adicionales, línea vacía y exceso de longitud. No almacena toda la línea ni convierte un prefijo válido en solicitud válida.

Cada llamada inicializa sus variables locales. Al terminar una línea inválida la ha consumido hasta su terminador; la siguiente llamada comienza en la línea siguiente. Si el flujo llega a fin después de dígitos válidos, esa última cantidad es válida; una llamada posterior devuelve `LECTURA_FIN`.

El lector no reinicia automáticamente un flujo que ya terminó o falló. El controlador decide si vuelve a leer. Sigue esperando una línea mientras la entrada esté abierta: no se añadió un tiempo máximo ni un presupuesto total de lectura.

Compila `ejemplos/02-lector.c` como `build/lector` o `.exe`. Con entrada 42, la salida coincide con el ejemplo de cantidad anterior. Comprueba también 101, línea vacía y fin de entrada. El comportamiento visible se conserva aunque cambió quién lo implementa.

## 6. Refactorizar el recibo completo

Archivo: [ejemplos/03-recibo.c](ejemplos/03-recibo.c). Contiene el lector, los cálculos, `mostrar_recibo` y `main`. Compílalo como `build/recibo` o `.exe`.

`main` interpreta primero los estados. Después comprueba `cantidad_valida(resultado)` para verificar que un resultado del lector cumple también la precondición del cálculo. Finalmente llama a `mostrar_recibo`.

La presentación obtiene subtotal, envío y total mediante las funciones de cálculo y los muestra. `total_centavos` reutiliza `subtotal_centavos` y `envio_centavos`; no mantiene otra copia de sus reglas dentro de su cuerpo.

Con entrada 10:

```text
Cantidad de 0 a 100, solo digitos (maximo 8).
Subtotal: 1250 centavos
Envio: 0 centavos
Total: 12.50
```

Un **refactor** cambia la organización interna conservando el comportamiento acordado. Comprueba el programa de la Unidad 07 y esta versión con las mismas entradas: resultados válidos, mensajes de rechazo, cierre sin datos y estados de finalización. No basta con que el nuevo archivo compile.

Si necesitas modificar una regla de negocio, es otro cambio de comportamiento: primero cambia el contrato y los casos esperados. No lo escondas dentro de la reorganización.

## 7. Primeras comprobaciones con `assert`

Una función de cálculo se puede comprobar sin teclado. En [la solución de rango](soluciones/04-rango.c) usamos `<assert.h>`:

```c
assert(en_rango(0, 0, 100));
assert(!en_rango(101, 0, 100));
```

`assert` comprueba una condición. Si falla, diagnostica y termina anormalmente el programa; si todas pasan, el programa continúa. No reemplaza la validación de entradas externas. Un usuario que escribe 101 debe recibir el rechazo previsto, no provocar una aserción de programación.

Las aserciones pueden desactivarse con `NDEBUG`. Por eso no deben contener tareas necesarias, como `getchar`, incrementos o asignaciones. En estas pruebas solo observan resultados de funciones sin efectos. El archivo rechaza una compilación con `NDEBUG` mediante una comprobación del preprocesador; la Unidad 10 explica las directivas implicadas.

Estas pruebas comprueban la función de rango de ese archivo. No prueban automáticamente todos los demás ejemplos por tener nombres o fórmulas parecidos. En la siguiente unidad el programa y sus pruebas reutilizarán **la misma implementación** del cálculo, enlazada desde un archivo compartido.

## Práctica y cierre

Resuelve [EJERCICIOS.md](EJERCICIOS.md) y compara con [SOLUCIONES.md](SOLUCIONES.md).

- [ ] Escribo precondiciones, resultados y efectos de cada función.
- [ ] Valido antes de llamar un cálculo con dominio acotado.
- [ ] Distingo un estado de lectura y una cantidad, incluido cero.
- [ ] Explico por qué un `return` auxiliar no termina todo el programa.
- [ ] Compruebo varias llamadas del mismo lector sin conservar estado local anterior.
- [ ] Distingo refactor, cambio de regla y prueba de equivalencia.

Continúa con [Unidad 10 — Organización en varios archivos](../unidad10-organizacion/README.md).
