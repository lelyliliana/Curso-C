# Unidad 16 — Leer líneas y convertir números completos

[Inicio](../README.md) · [Anterior: interfaces](../unidad15-interfaces/README.md)

## Objetivo

La entrada de la Unidad 07 tenía un rango pequeño y procesaba dígitos durante la lectura. Ahora separarás tres responsabilidades: recibir una línea completa en un arreglo, comprobar su sintaxis y convertirla a un número representable dentro del dominio del problema.

Necesitas punteros, cadenas terminadas, cantidad/capacidad e interfaces compartidas. Al terminar podrás leer enteros con signo y decimales con un contrato explícito, interpretar `strtol`, `strtod`, `errno` y el puntero de final, y rechazar sufijos o líneas demasiado largas sin confundir errores con números válidos.

## 1. Convertir un comienzo no valida toda la entrada

Abre [ejemplos/01-prefijo.c](ejemplos/01-prefijo.c):

```c
const char texto[] = "12abc";
char *fin = NULL;
errno = 0;
const long valor = strtol(texto, &fin, 10);
```

`strtol`, declarada en `<stdlib.h>`, puede convertir el prefijo decimal 12 y detenerse antes de `a`. Ese `long` se imprime con `%ld`. El resultado por sí solo no certifica que toda la cadena fuera un entero. El ejemplo imprime:

```text
Prefijo convertido: 12
Resto: abc
Conversion parcial: no aceptar como entero completo.
```

Es una demostración diagnóstica, no un programa que acepta 12 como respuesta a `12abc`. La aplicación posterior rechazará ese texto completo.

`fin` es una variable puntero a `char`. `&fin` es la dirección de esa variable: permite a la biblioteca escribirle la dirección donde terminó la conversión. En el prototipo de la biblioteca aparece un parámetro `char **`, un puntero a una variable puntero. No necesitamos una matriz ni memoria dinámica para usarlo.

Después, `*fin` consulta el carácter señalado. `fin == texto` indica que no se convirtió ningún número. Un terminador en `*fin` indica final de cadena; un carácter como `a` indica contenido sin convertir. Aunque el tipo de `fin` permita escribir, aquí solo lo leemos: no modificamos un texto recibido como constante.

## 2. Construir el ejemplo del prefijo

Realiza cada paso por separado:

1. Desde la carpeta del curso entra con `cd unidad16-lineas`.
2. Usa `ls` para comprobar `ejemplos`, `proyecto` y `soluciones`.
3. Crea `build` con `mkdir -p build`.
4. Construye el ejemplo y ejecuta solo después de revisar el resultado.

| Sistema | Construir | Ejecutar después |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-prefijo.c -o build/prefijo` | `./build/prefijo` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-prefijo.c -o build/prefijo.exe` | `./build/prefijo.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-prefijo.c -o build/prefijo` | `./build/prefijo` |

Windows usa UCRT64. Los programas del proyecto necesitarán también `entrada.c`; no los construyas como si fueran fuentes independientes del módulo.

## 3. Recibir una línea sin aceptar un prefijo

Consulta [proyecto/entrada.h](proyecto/entrada.h) y [proyecto/entrada.c](proyecto/entrada.c). `leer_linea(char destino[], size_t capacidad)` llena un arreglo del llamador. La capacidad cuenta elementos `char`, incluido el espacio del terminador.

En los controladores `char linea[33]` permite hasta **32 bytes de contenido**, más `\0`. El salto de línea termina la solicitud y no se guarda. Espacios, signos y tabulaciones sí ocupan espacio. Una representación numérica válida que exceda ese límite de línea se rechaza antes de convertir.

| Estado | Significado | Destino después |
|---|---|---|
| `LINEA_OK` | Línea completa, incluso vacía | Cadena terminada |
| `LINEA_FIN` | Fin antes de cualquier contenido | Cadena vacía |
| `LINEA_LARGA` | No cabía todo el contenido y su terminador | Cadena vacía |
| `LINEA_INVALIDA` | Byte nulo recibido o no representable como `char` | Cadena vacía |
| `LINEA_ERROR` | El indicador de error de entrada está activo | Cadena vacía |
| `LINEA_ARGUMENTO` | Destino nulo o capacidad cero | No accede ni consume entrada |

El lector almacena bytes que se pueden representar en `char` sin pérdida. Comprueba `byte > CHAR_MAX` antes de convertir; en el entorno probado, con `char` con signo de ocho bits, eso rechaza bytes mayores que 127. En una implementación con `char` sin signo el límite puede ser otro. La sintaxis numérica sigue admitiendo solo los símbolos básicos que define el conversor.

El byte nulo recibido se rechaza siempre: no debe ocultar un sufijo como si ya fuera el terminador agregado por el programa. Los bytes de control representables pueden llegar al arreglo; la conversión numérica decidirá si su sintaxis los admite. El lector de líneas y el conversor no tienen el mismo contrato.

La función sigue consumiendo hasta `\n` o fin/error cuando detecta longitud excesiva o contenido inválido. Al devolver un rechazo borra el prefijo almacenado colocando `\0` en el índice 0. Un error de lectura tiene prioridad; luego se interpreta invalidez de byte y después longitud excesiva.

Una línea vacía terminada por Enter es `LINEA_OK` para el lector, pero no es un número válido. Fin inmediato es `LINEA_FIN`, un estado diferente. Una línea válida que termina por fin sin salto también se puede convertir.

La capacidad proporcionada debe corresponder a memoria modificable real. El lector comprueba cero y nulidad, pero no descubre si el llamador declara más espacio del que tiene. Tampoco proporciona tiempo de espera: una entrada abierta sin terminador puede mantenerlo consumiendo indefinidamente.

## 4. Comprobar sintaxis antes de convertir

Los conversores reciben una cadena ya terminada, una salida separada y límites del dominio. Rechazan argumentos comprobables inválidos y no cambian la salida si devuelven `false`.

Contrato del entero:

```text
Espacios o tabulaciones opcionales alrededor.
Un signo + o - opcional.
Uno o mas digitos decimales.
Ningun otro contenido.
```

Contrato del decimal:

```text
Espacios o tabulaciones opcionales alrededor.
Un signo + o - opcional.
Uno o mas digitos.
Punto opcional; si aparece, debe seguir al menos un digito.
Exponente e o E opcional, con signo opcional y uno o mas digitos.
```

| Texto | Entero | Decimal |
|---|---|---|
| `0`, `-7`, `+12` | Sintaxis admitida | Sintaxis admitida |
| ` 12 ` | Admitida | Admitida |
| `12.5` | Rechazada | Admitida |
| `1e2` | Rechazada | Admitida |
| `.5` o `1.` | Rechazada | Rechazada por este contrato |
| `12abc`, `1 2`, signo solo | Rechazada | Rechazada |
| `0x10`, `nan`, `inf` | Rechazada | Rechazada |
| `1,5` | Rechazada | Rechazada |

«Sintaxis admitida» no significa todavía «valor aceptado»: faltan representabilidad y rango. Nuestro contrato decimal exige `0.5` en lugar de `.5`, y `1.0` en lugar de `1.`. La biblioteca puede aceptar formatos más amplios; una aplicación puede definir un subconjunto claro.

`entrada.c` recorre la sintaxis mediante auxiliares `static`. Las que devuelven una posición señalan un lugar dentro de la **cadena del llamador**, que sigue viva; no devuelven la dirección de un arreglo local destruido. La validación puede avanzar hasta el terminador, pero no más allá.

## 5. Representabilidad, rango y salida por puntero

Para el entero:

1. Comprobar argumentos y sintaxis completa.
2. Inicializar `errno = 0` inmediatamente antes de llamar a `strtol`.
3. Convertir con base **10** explícita, obteniendo un `long` y la posición final.
4. Rechazar `ERANGE`, ausencia de conversión o contenido restante distinto de los espacios/tabulaciones finales permitidos.
5. Comparar el `long` contra los límites `int` del dominio.
6. Solo entonces convertir a `int` y escribir `*resultado`.

`errno`, declarada mediante `<errno.h>`, permite consultar errores de biblioteca. Un cero devuelto por `strtol` puede ser una conversión correcta de `"0"`; no sirve por sí solo como indicador de error. Una conversión exitosa tampoco tiene que borrar un error anterior: por eso se reinicia antes de cada llamada.

Los límites del dominio son `int`, así que aceptar el `long` dentro de ellos garantiza que la conversión posterior a `int` puede representarlo. No conviertas primero y compruebes después. Una entrada demasiado grande para `long` produce rechazo por `ERANGE`; una que cabe en `long` pero supera el dominio también se rechaza.

Para el decimal se utiliza `strtod`. Además de las verificaciones anteriores, se exige `isfinite(valor)` y límites finitos, usando `<math.h>`. Se rechazan valores infinitos, NaN y errores de rango, incluido subdesbordamiento señalado por `ERANGE`. No convertimos un decimal fuera del contrato en cero como sustituto.

Los programas conservan la configuración numérica inicial **C**, que usa punto decimal; no llaman a `setlocale`. No basta cambiar el texto de la gramática si más adelante una aplicación cambia la configuración numérica: la validación y la biblioteca deben concordar. Estas funciones declaran esa precondición para decimales.

El `double` sigue siendo aproximado. Imprimir con `%.2f` redondea la presentación; un valor pequeño válido como `0.001` puede verse como `0.00` sin ser un error. El rango se comprueba con el valor convertido, antes de esa presentación. No usamos decimales aproximados para sustituir el recibo exacto en centavos del curso.

## 6. Construir la aplicación de enteros

Fuentes: [main_entero.c](proyecto/main_entero.c) y [entrada.c](proyecto/entrada.c), con interfaz [entrada.h](proyecto/entrada.h). Desde `unidad16-lineas`:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/main_entero.c proyecto/entrada.c -o build/entero
```

En macOS utiliza `clang`; en UCRT64 usa salida `build/entero.exe`. Después ejecuta `./build/entero` o su variante `.exe`. Escribe `-25` y Enter:

```text
Entero de -1000 a 1000; linea de hasta 32 bytes.
Entero: -25
```

Reinicia para cada caso: acepta -1000, 0, 1000, `+12` y espacios alrededor. Rechaza -1001, 1001, `12abc`, `1.5`, un signo solo y línea vacía. Fin sin número cierra normalmente con `Fin sin numero.`. Una solicitud inválida finaliza con fallo; no se muestra un número aceptado.

Para generar una entrada sin salto final desde las terminales del curso:

```bash
printf '%s' '-25' | ./build/entero
```

En UCRT64 cambia el ejecutable a `.exe`. Ese `printf` pertenece a la terminal; `|` conecta su salida al programa. Usamos formato fijo `%s` para que `-25` sea un argumento de texto. El resultado debe seguir siendo -25. `printf ''` produce fin inmediato sin datos.

Un `\r` recibido como contenido no pertenece a los espacios finales admitidos y hará fallar la conversión. Una biblioteca en modo texto puede traducir CRLF antes de entregarlo; no se afirma haber probado esa traducción de Windows con una ejecución de Ubuntu.

## 7. Construir la aplicación decimal y las pruebas

Primero construye el decimal:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/main_decimal.c proyecto/entrada.c -o build/decimal
```

Aplica las variantes de sistema indicadas. Ejecuta y escribe `1.25e2`:

```text
Decimal de -50 a 150; punto decimal; hasta 32 bytes.
Decimal: 125.00
```

Admite -50 y 150; rechaza valores fuera de ese rango, `nan`, `inf`, `.5`, `1.`, coma decimal y exponentes incompletos. Un exponente demasiado grande o pequeño que produce `ERANGE` también se rechaza.

Después construye las pruebas compartidas en otro paso:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/pruebas_entrada.c proyecto/entrada.c -o build/pruebas_entrada
```

Ejecuta: espera `Pruebas de conversion: OK.`. Sus casos llaman a los conversores de `entrada.c`; no contienen otra implementación. No necesitan teclado ni combinan sus fuentes con los `main` interactivos. `#error` impide construir con aserciones desactivadas.

Las pruebas de conversión no demuestran por sí solas el consumo de líneas largas, fin o error de lectura. También debes probar las aplicaciones completas con entradas, porque lectura y conversión son responsabilidades distintas.

## 8. Reintentos y colección completa

Los ejercicios reutilizan `entrada.c`:

- [soluciones/04-reintentos.c](soluciones/04-reintentos.c): hasta tres solicitudes; un rechazo consume su línea antes de intentar otra. Fin cierra normalmente, error de lectura detiene con fallo y un tercer rechazo agota los intentos.
- [soluciones/05-coleccion.c](soluciones/05-coleccion.c): solicita exactamente tres enteros 0–100 en líneas separadas. Incrementa la cantidad utilizada solo después de convertir con éxito y presenta la suma únicamente cuando recibió los tres.

En una colección obligatoria, fin antes del tercer dato es cierre incompleto y termina con fallo. No se publica una suma parcial como si fuera completa. El máximo total es 300, representable en `int`.

Los pasos de construcción y los resultados están en [SOLUCIONES.md](SOLUCIONES.md). Resuelve primero [EJERCICIOS.md](EJERCICIOS.md).

## Práctica y cierre

- [ ] Distingo línea completa, sintaxis, conversión y dominio.
- [ ] Explico por qué un prefijo numérico no valida el sufijo.
- [ ] Interpreto `&fin` como dirección de una variable puntero.
- [ ] Reinicio y consulto `errno` en la conversión correspondiente.
- [ ] Compruebo rango antes de convertir `long` a `int`.
- [ ] Rechazo valores decimales no finitos y errores de rango.
- [ ] Pruebo lectura y conversión por separado y también integradas.
- [ ] Conservo resultados ante rechazo y no acepto una colección incompleta.

Conserva casos de entero negativo, límite válido, sufijo inválido, línea larga y fin incompleto. El siguiente bloque estudiará estructuras, enumeraciones y archivos para agrupar y conservar datos; todavía no está publicado. La memoria dinámica tendrá su propia explicación y comprobaciones posteriores.
