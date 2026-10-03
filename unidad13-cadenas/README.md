# Unidad 13 — Cadenas: texto con terminador y capacidad

[Inicio](../README.md) · [Anterior: recorridos](../unidad12-recorridos/README.md)

## Objetivo

Ya utilizaste `"Hola"` para imprimir, pero todavía no almacenabas ni recorrías texto como datos. Ahora estudiarás cadenas dentro de arreglos de `char`, contarás sus bytes, compararás contenido y recibirás una etiqueta con límites explícitos.

Necesitas los arreglos y recorridos de las unidades 11–12, y la distinción entre `getchar`, fin y error de la Unidad 07. Al terminar podrás explicar por qué el espacio de almacenamiento debe incluir un terminador y por qué una entrada demasiado larga debe rechazarse completa.

## 1. Un carácter y una cadena son objetos diferentes

Abre [ejemplos/01-terminador.c](ejemplos/01-terminador.c):

```c
char inicial = 'C';
char curso[] = "C";
char vacia[] = "";
```

Las comillas simples describen un carácter en estos ejemplos. Las dobles describen un **literal de cadena**. Al inicializar el arreglo `curso`, se almacenan dos elementos:

| Índice de `curso` | Contenido | Función |
|---:|---|---|
| 0 | `'C'` | Texto |
| 1 | `'\0'` | Terminador |

`'\0'` es el carácter nulo, de valor cero. No es `'0'`, el dígito visible; no es un espacio ni un salto de línea, y tampoco es `EOF`. El terminador marca el final de una cadena de C. No aparece al imprimir con `%s`.

Un arreglo de `char` no es automáticamente una cadena válida. Para tratarlo como cadena necesitas un terminador **dentro del espacio accesible**. Por ejemplo, los tres bytes de `{'s', 'o', 'l'}` no contienen un terminador y no deben pasarse a `%s` o `strlen` como si lo tuvieran.

La cadena vacía `""` contiene un terminador en el índice 0. Tiene longitud de texto cero y ocupa al menos ese elemento. No implica un arreglo de longitud cero.

## 2. Construir y observar el terminador

Trabaja cada paso de forma separada:

1. Desde la carpeta del curso entra con `cd unidad13-cadenas`.
2. Confirma los archivos con `ls`.
3. Crea `build` mediante `mkdir -p build`.
4. Compila según tu sistema. Ejecuta solo después de que termine correctamente.

| Sistema | Construir | Ejecutar después |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-terminador.c -o build/terminador` | `./build/terminador` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-terminador.c -o build/terminador.exe` | `./build/terminador.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-terminador.c -o build/terminador` | `./build/terminador` |

En Windows utiliza UCRT64. Para otros ejemplos cambia fuente y nombre de salida; cada fuente se construye por separado.

Salida:

```text
Inicial: C
Curso: C
Capacidad de curso: 2
Capacidad de vacia: 1
El terminador esta en el indice 1.
```

`%c` muestra un carácter; `%s` muestra una cadena terminada. Conserva el formato fijo: `printf("%s\n", texto);` imprime el texto como dato. No conviertas texto recibido en formato mediante `printf(texto);`, porque símbolos como `%` tendrían otra función.

## 3. Capacidad, longitud y bytes

Abre [ejemplos/02-longitud.c](ejemplos/02-longitud.c):

```c
char nombre[12] = "Leli";
const size_t longitud = strlen(nombre);
```

`nombre` reserva doce elementos. Cuatro almacenan las letras y el índice 4 contiene `\0`; los restantes también se inicializan en cero por esta declaración. `<string.h>` proporciona la declaración de `strlen`. Su resultado es `size_t`, que imprimimos con `%zu`.

| Consulta | Resultado | Significado |
|---|---:|---|
| `sizeof nombre` | 12 | Bytes de almacenamiento del arreglo local |
| `strlen(nombre)` | 4 | Bytes anteriores al primer terminador |
| Espacio mínimo para `"Leli"` | 5 | Cuatro bytes de texto y un terminador |

`sizeof(char)` vale 1 por definición del lenguaje. Ese byte de C no tiene que ser universalmente de ocho bits; en el entorno probado sí lo es. Aquí, por ser un arreglo de `char`, su tamaño en bytes coincide con el número de elementos.

`strlen` **no** recibe la capacidad ni comprueba que exista un terminador accesible antes de buscarlo. Solo se llama cuando ya hay una cadena válida. No lo uses para «comprobar» un arreglo sin terminar. En el ejemplo esa garantía viene de la inicialización.

En UTF-8, una letra con tilde puede ocupar varios bytes. `strlen` cuenta bytes, no letras percibidas por una persona, símbolos de pantalla ni posiciones del cursor. Estas prácticas trabajan con letras inglesas, dígitos y símbolos simples en las terminales habituales del curso; no implementan procesamiento general de Unicode.

El ciclo recorre `i < longitud`, sin imprimir el terminador. La primera letra se puede cambiar porque `nombre` es un arreglo modificable, inicializado con el contenido del literal. No intentamos modificar directamente un literal de cadena: hacerlo tiene comportamiento indefinido.

Salida completa del ejemplo:

```text
Texto: Leli
Capacidad: 12
Longitud: 4
Indice 0: L
Indice 1: e
Indice 2: l
Indice 3: i
Modificado: Meli
```

## 4. Comparar contenido

Abre [ejemplos/03-comparacion.c](ejemplos/03-comparacion.c). Dos cadenas con el mismo texto pueden estar almacenadas en objetos diferentes. `==` entre sus nombres no realiza una comparación letra por letra.

`strcmp`, declarada en `<string.h>`, compara dos cadenas válidas:

- Resultado cero: mismo contenido hasta sus terminadores.
- Resultado negativo: la primera precede a la segunda según la comparación de bytes.
- Resultado positivo: la primera sigue a la segunda.

No exige devolver exactamente -1 o 1. Para comprobar igualdad usa `strcmp(a, b) == 0`. No compara por longitud solamente ni aplica reglas de orden alfabético del español. Mayúsculas y minúsculas son distintas en este contrato. Las dos cadenas deben estar correctamente terminadas antes de llamar.

Salida del ejemplo:

```text
Las dos primeras son iguales.
Mayuscula y minuscula son diferentes.
```

Los argumentos sin índice, como `strlen(nombre)` o `strcmp(primera, segunda)`, permiten a estas funciones acceder al comienzo del texto. Eso **no copia el arreglo completo** como un argumento entero. Aquí utilizamos las funciones de biblioteca con cadenas locales válidas; en el siguiente bloque estudiaremos la conversión a puntero y cómo escribir nuestras propias interfaces con capacidad explícita.

## 5. Recibir una etiqueta sin perder los límites

Abre [ejemplos/04-etiqueta.c](ejemplos/04-etiqueta.c). Su contrato es deliberadamente pequeño:

| Propiedad | Regla |
|---|---|
| Tamaño del texto | De 1 a 12 símbolos de un byte admitidos |
| Símbolos permitidos | Letras inglesas A–Z y a–z, dígitos 0–9, `_` y `-` |
| Espacios, tildes y otros símbolos | Rechazados |
| Línea vacía | Rechazada |
| Final de solicitud | Salto de línea `\n` o fin de entrada después de texto |
| Fin inmediato sin datos | Cierre normal, sin etiqueta |
| Error de lectura | Fallo, sin resultado parcial |
| Texto demasiado largo | Rechazo de toda la solicitud; no se acepta su prefijo |
| Número de solicitudes | Una; no es un menú permanente |

No es un lector universal de nombres propios: `Ana Maria` y `José` no cumplen estas reglas. Son etiquetas como `sensor_2` o `A-7`. Cualquier símbolo permitido puede ser el primero; el contrato también admite solo dígitos o solo guiones. Otra aplicación podría imponer un patrón más estricto.

El arreglo tiene trece elementos:

```c
enum { MAXIMO = 12, CAPACIDAD = MAXIMO + 1 };
char etiqueta[CAPACIDAD] = {0};
```

Los índices 0–11 pueden guardar texto. El índice 12 queda disponible para el terminador si se aceptan doce símbolos. Antes de escribir otro símbolo se comprueba `usados < CAPACIDAD - 1`. Finalmente se escribe `etiqueta[usados] = '\0';`, dentro del arreglo.

## 6. Seguir el lector por responsabilidades

Primero estudia `simbolo_permitido(int byte)`. Es una función que recibe un entero por valor y devuelve un `bool`, como ya conoces. Dentro tiene un arreglo constante con todos los símbolos aceptados. Lo recorre hasta `sizeof permitidos - 1` para no aceptar el terminador de ese literal. Compara por igualdad; no necesita asumir que todas las letras están contiguas en cualquier codificación de C.

Después sigue la lectura en `main`:

1. `getchar()` devuelve un `int`; no se almacena directamente en `char`, porque aún podría ser `EOF`.
2. Si el byte no está permitido, la solicitud queda marcada como inválida.
3. Si ya no queda espacio para texto y terminador, también se marca inválida.
4. Solo se guarda un símbolo permitido, con espacio y sin invalidez anterior.
5. Aunque quede inválida, el ciclo continúa hasta salto de línea o fin/error. No crece el arreglo ni se sigue aumentando `usados`.
6. Al terminar, se comprueba error de lectura antes de aceptar datos.
7. Se distingue fin sin datos de línea vacía; luego se rechazan invalidez y ausencia de texto.
8. Solo en la rama válida se termina y se presenta la cadena.

`(char)byte` es una conversión explícita: se realiza después de verificar que ese valor corresponde a uno de los caracteres básicos de la lista, que puede representarse en `char`. No convierte cualquier byte recibido ni convierte `EOF`.

`hubo_datos` registra si se recibió algún byte de contenido, aun cuando fuera inválido. `usados` cuenta únicamente los símbolos almacenados antes de cualquier rechazo: **no** es un contador de la longitud total de una línea rechazada. Para decidir aceptación se comprueba también `invalida`.

Con `sensor_2` y Enter:

```text
Etiqueta de 1 a 12: letras inglesas, digitos, _ o -.
Etiqueta: sensor_2
Longitud: 8
```

Con trece letras, un espacio o un byte nulo recibido:

```text
Etiqueta de 1 a 12: letras inglesas, digitos, _ o -.
Etiqueta invalida.
```

Una entrada que empieza con texto válido y después contiene un símbolo inválido se rechaza completa. Un byte nulo recibido no puede ocultar un sufijo detrás de una cadena aparentemente más corta: la lista lo rechaza.

## 7. Probar finales y líneas completas

Compila `ejemplos/04-etiqueta.c` con salida `build/etiqueta` (o `.exe`). Prueba un caso, observa el resultado y reinicia el programa para el siguiente.

| Entrada | Resultado esperado |
|---|---|
| `A` y Enter | Etiqueta válida, longitud 1 |
| `abcdefghijkl` y Enter | Válida, longitud 12 |
| `abcdefghijklm` y Enter | Inválida: supera 12 |
| `sensor_2` y Enter | Válida |
| `sensor 2` y Enter | Inválida: contiene espacio |
| Solo Enter | Inválida: línea vacía |
| Fin antes de escribir | `Fin sin etiqueta.`, cierre normal |
| Texto válido seguido de fin sin salto | Válido |

En Ubuntu/macOS se puede generar fin en una línea vacía con Ctrl+D. En Windows UCRT64 suele utilizarse Ctrl+Z seguido de Enter; el tratamiento de la consola puede variar. Para verificar un texto sin salto final de forma reproducible, desde esas terminales con intérprete de comandos compatible:

```bash
printf 'A-7' | ./build/etiqueta
```

En UCRT64 usa `./build/etiqueta.exe`. El `printf` del comando es una herramienta de la terminal, no una llamada dentro de tu fuente. El símbolo `|` conecta su salida a la entrada del programa. Se espera etiqueta `A-7` con longitud 3. Para probar fin inmediato utiliza `printf ''` en lugar de `printf 'A-7'`.

El lector procesa la primera línea; las siguientes no son solicitudes de este programa. Un `\r` que llegue como byte de contenido se rechaza. Una biblioteca de entrada en modo texto puede traducir los finales CRLF antes de que `getchar` los vea; no presentamos las pruebas de Ubuntu como ejecución de una consola de Windows.

El límite del arreglo limita la memoria, **no el tiempo total de espera**. Una fuente abierta que nunca termine puede mantener el programa esperando mientras consume datos. Esta práctica no implementa límites temporales, comunicación por red ni defensa completa frente a una entrada sin final.

## 8. Copiar con espacio para terminar

[soluciones/04-copia.c](soluciones/04-copia.c) copia una cadena válida a otro arreglo. Antes de escribir comprueba:

```c
if (longitud >= sizeof destino) {
    /* Rechazar: no queda espacio para texto y terminador. */
}
```

Aceptar exige `longitud < capacidad`. Después copia los bytes de texto y agrega `destino[longitud] = '\0';`. La comparación evita necesitar una suma que pudiera desbordarse en contratos mayores. Aquí el origen es un literal inicializador válido y el destino es un arreglo local de seis bytes.

Si el texto no cabe, el programa falla sin imprimir una copia parcial. No utilizamos `strcpy` sin comprobar espacio ni presentamos `strncpy` como una solución automática: una copia limitada tampoco garantiza por sí sola que el resultado sea una cadena terminada.

## Práctica y cierre

Resuelve [EJERCICIOS.md](EJERCICIOS.md) y consulta luego [SOLUCIONES.md](SOLUCIONES.md). Encontrarás conteo de dígitos y comprobación de palíndromo sobre etiquetas válidas.

- [ ] Distingo `'C'`, `"C"`, `'0'`, `'\0'`, salto de línea y `EOF`.
- [ ] Reservo espacio para el terminador.
- [ ] No llamo a funciones de cadenas antes de garantizar su terminación.
- [ ] Distingo capacidad, bytes de texto y caracteres de una persona.
- [ ] Comparo contenido con `strcmp`, usando cero o el signo de su resultado.
- [ ] Rechazo toda la entrada demasiado larga o inválida y no publico un prefijo.
- [ ] Distingo fin normal, solicitud vacía y error de lectura.

Conserva una evidencia de longitud 12 aceptada y 13 rechazada. El siguiente bloque estudiará direcciones, punteros y funciones que reciben arreglos con límites explícitos; todavía no está publicado.
