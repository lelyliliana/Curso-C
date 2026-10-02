# Unidad 01 — Tu primer programa en C

[Unidad anterior: entorno](../unidad00-entorno/README.md) · [Inicio del curso](../README.md) · [Ejercicios](EJERCICIOS.md) · [Soluciones](SOLUCIONES.md)

## Objetivo y punto de partida

Vas a construir un programa que muestra un saludo. Parece pequeño, pero con él aprenderás el ciclo completo de trabajo: **escribir → guardar → compilar → ejecutar → comprobar**.

Al terminar podrás explicar las partes básicas de ese programa, mostrar varias líneas, modificar mensajes y distinguir un error de compilación de un resultado incorrecto.

Necesitas haber terminado la Unidad 00: el compilador responde y sabes dónde está tu archivo. Todavía no utilizaremos variables, entrada del teclado, decisiones ni ciclos. No tendrás que adivinar conceptos que aún no se han explicado.

## 1. Definir qué queremos conseguir

**Problema:** mostrar un mensaje que confirme que nuestro programa comenzó a ejecutarse.

**Resultado esperado:** la terminal muestra una línea con `Hola, mundo!` y vuelve a aceptar comandos.

No necesitamos que el programa pregunte nada. Tampoco necesita mantener una ventana abierta: utilizaremos una terminal que seguirá visible cuando termine.

Antes de escribir código, distinguir lo que quieres lograr del mecanismo para lograrlo ayuda a detectar errores posteriores.

## 2. Escribir el programa

Abre `hola.c`, que preparaste en la Unidad 00, y reemplaza su contenido por:

```c
#include <stdio.h>

int main(void)
{
    printf("Hola, mundo!\n");
    return 0;
}
```

También puedes consultar el [archivo del ejemplo](ejemplos/01-hola.c). Si utilizas el archivo del repositorio, guarda una copia llamada `hola.c` en tu carpeta de práctica para seguir los comandos de esta guía.

Guarda el archivo antes de continuar. El compilador lee lo guardado en el disco, no los cambios pendientes que ves en el editor.

## 3. Entender cada parte

### `#include <stdio.h>`

`stdio.h` es un encabezado de la biblioteca estándar para entrada y salida. Esta línea permite que el compilador conozca, entre otras cosas, la declaración de `printf`.

En esta etapa basta saber que necesitamos ese encabezado para utilizar `printf` correctamente. `#include` no imprime y no lleva punto y coma. Tampoco debe confundirse con copiar toda una biblioteca al código: durante la construcción del programa también interviene el enlazado.

### `int main(void)`

Define la función por la que comienza este programa de consola, en el entorno de escritorio utilizado por el curso.

- `main` es su nombre y se escribe en minúsculas.
- `void`, entre paréntesis, indica que esta forma de la función no recibe parámetros.
- `int` indica que devuelve un valor entero. Aquí lo utilizaremos para informar cómo terminó el programa.

No necesitas dominar todavía las funciones: más adelante construirás las tuyas. Utiliza esta estructura y comprende qué papel cumple.

### Las llaves `{` y `}`

Delimitan el cuerpo de la función. Las instrucciones que aparecen dentro pertenecen a `main`. Deben estar equilibradas: una llave que abre tiene una que cierra.

La sangría de cuatro espacios ayuda a ver el contenido del bloque. No hace que `printf` funcione, pero facilita que otra persona lea tu programa.

### `printf("Hola, mundo!\n");`

Llama a una función de salida. El texto entre comillas dobles es el mensaje que queremos mostrar. El punto y coma termina esta instrucción.

`\n` es una secuencia de escape que representa un salto de línea. Son dos caracteres escritos en el código para representar ese efecto; el programa no muestra una barra y una letra `n` en su lugar.

Usamos comillas rectas `"`, no comillas tipográficas `“ ”` que algunos procesadores de texto insertan automáticamente.

En estos primeros mensajes evita `%`: `printf` interpreta ese carácter como inicio de una especificación de formato. Cuando necesites mostrar un porcentaje literal se escribe `%%`. En una unidad posterior aprenderás a mostrar valores con formatos.

### `return 0;`

Termina `main` y devuelve cero al entorno que inició el programa. En este contexto, cero comunica una finalización exitosa. **No imprime un cero en pantalla.**

No garantiza que el resultado sea correcto: puedes devolver cero y haber escrito un mensaje equivocado. La salida debe comprobarse con respecto al objetivo del programa.

## 4. Estar en la carpeta correcta

Abre la terminal indicada por tu sistema. Ejecuta `pwd` y después `ls`.

Debes estar dentro de `practicas-c/unidad01`, y `ls` debe mostrar `hola.c`. Si no aparece, revisa la [Unidad 00](../unidad00-entorno/README.md#6-entender-dónde-está-trabajando-la-terminal).

Los comandos siguientes suponen que estás en esa carpeta. No contienen rutas a otros archivos.

## 5. Compilar

En **Ubuntu**:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic hola.c -o hola
```

En **macOS**:

```bash
clang -std=c17 -Wall -Wextra -Wpedantic hola.c -o hola
```

En **Windows, desde MSYS2 UCRT64**:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic hola.c -o hola.exe
```

| Parte | Significado |
|---|---|
| `gcc` o `clang` | Invoca la herramienta de compilación |
| `-std=c17` | Selecciona el estándar C17 para esta práctica |
| `-Wall -Wextra -Wpedantic` | Solicita grupos de advertencias y diagnósticos; no detecta todos los defectos posibles |
| `hola.c` | Indica el archivo fuente que debe leer |
| `-o hola` o `-o hola.exe` | Establece el nombre del archivo de salida |

El comando solicita construir un ejecutable: de manera simplificada, se procesa el fuente, se compila y se enlaza con lo necesario para usar la biblioteca estándar. En unidades posteriores observarás estas etapas con más detalle.

Si todo salió bien, normalmente no aparece ningún mensaje: el indicador regresa. Ejecuta `ls` y comprueba que existe el ejecutable.

**Si hay errores, no continúes con la ejecución.** Lee el primero, corrige, guarda y compila otra vez. Puede existir un ejecutable de una compilación anterior; ejecutarlo tras un fallo nuevo te mostraría una versión vieja.

No uses `-o hola.c`: el archivo de salida debe tener un nombre diferente del fuente.

## 6. Ejecutar

En Ubuntu o macOS:

```bash
./hola
```

En Windows, desde MSYS2 UCRT64:

```bash
./hola.exe
```

`./` indica que el ejecutable está en la carpeta actual. El compilador construye el programa y este segundo comando lo inicia; son acciones diferentes.

Salida esperada:

```text
Hola, mundo!
```

El indicador que reaparece después pertenece a la terminal, no al mensaje de tu programa. El programa ya terminó. No agregues `system("pause")` para mantener una ventana: la terminal es suficiente.

## 7. Cambiar, guardar y reconstruir

Reemplaza solamente el texto `Hola, mundo!` por `Estoy aprendiendo C.`. Conserva el salto de línea, las comillas, los paréntesis y el punto y coma.

1. Guarda el archivo.
2. Repite el comando de compilación para tu sistema.
3. Verifica que no hay errores.
4. Ejecuta otra vez.

Ahora debes ver:

```text
Estoy aprendiendo C.
```

Editar el `.c` no cambia automáticamente el ejecutable. Si sigues viendo el saludo anterior, comprueba que guardaste, que compilaste sin errores y que ejecutas el archivo de la misma carpeta.

## 8. Mostrar instrucciones en secuencia

Abre [02-presentacion.c](ejemplos/02-presentacion.c):

```c
#include <stdio.h>

int main(void)
{
    printf("Me llamo Ana.\n");
    printf("Estoy aprendiendo C.\n");
    printf("Quiero construir programas utiles.\n");
    return 0;
}
```

En este programa las llamadas se realizan en el orden escrito, de arriba hacia abajo. Anticipa la salida antes de ejecutarlo.

Guárdalo como `presentacion.c` en tu carpeta de práctica. Compila cambiando los nombres de entrada y salida:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic presentacion.c -o presentacion
```

En macOS sustituye `gcc` por `clang`; en Windows usa `-o presentacion.exe`. Ejecuta `./presentacion` o `./presentacion.exe`, respectivamente.

Salida esperada:

```text
Me llamo Ana.
Estoy aprendiendo C.
Quiero construir programas utiles.
```

Este ejemplo no solicita el nombre al usuario: `Ana` es texto fijo. Mostrar una palabra y leerla desde el teclado serán aprendizajes diferentes.

## 9. Experimentar con saltos de línea

Abre [03-saltos.c](ejemplos/03-saltos.c). Sus llamadas son:

```c
printf("Uno");
printf("Dos\n");
printf("Tres\n\n");
printf("Fin\n");
```

No reemplazan al programa completo: deben estar dentro de `main` y el archivo necesita el encabezado y la finalización que ya conoces. El ejemplo enlazado contiene todo el programa.

Guarda una copia como `saltos.c`, compílala con la misma estructura de comando y ejecuta el resultado.

Salida esperada:

```text
UnoDos
Tres

Fin
```

La primera llamada no incluye un salto de línea. La segunda continúa en esa misma línea. Después de `Tres`, dos saltos producen una línea vacía antes de `Fin`.

No hace falta un `printf` diferente para cada línea: una misma cadena puede contener varios `\n`. Al comenzar los separamos para observar qué aporta cada instrucción.

## 10. Aprender de los errores

| Síntoma | Posible causa | Primer paso |
|---|---|---|
| `gcc` no se reconoce | Herramienta ausente o terminal diferente | Volver a la guía de instalación |
| `hola.c: No such file or directory` | Carpeta o nombre incorrectos | Revisar `pwd`, `ls` y extensión |
| `missing terminating " character` | Falta una comilla de cierre | Revisar la cadena y la línea anterior |
| `expected ';' ...` | Falta un punto y coma | Revisar la instrucción y la línea anterior |
| Mensaje sobre `printf` no declarado | Falta `stdio.h` o hay un error en su nombre | Revisar `#include <stdio.h>` |
| La ejecución muestra el texto antiguo | Ejecutable anterior | Guardar y confirmar compilación exitosa |
| El programa ejecuta pero dice algo incorrecto | Error en el contenido o razonamiento | Comparar salida real y salida esperada |

Los mensajes exactos cambian según compilador y versión. La línea señalada puede ser donde el compilador descubrió el problema, no donde comenzó.

### Práctica de diagnóstico guiada

Guarda una copia de tu programa correcto con otro nombre antes de experimentar.

1. Quita el punto y coma al final de `printf`.
2. Intenta compilar y conserva el primer diagnóstico.
3. Explica qué parte del código lo causa.
4. Restaura el punto y coma, guarda y compila de nuevo.

Después cambia `Hola` por `Hloa`. El programa compila, pero el texto no cumple el objetivo. Eso demuestra que **compilar sin errores no equivale a resolver correctamente el problema**.

Puedes consultar [dos casos de diagnóstico](diagnostico/README.md). Se conservan como archivos `.c.txt` para que no se confundan con ejemplos correctos.

## Práctica independiente

Resuelve los [ejercicios de esta unidad](EJERCICIOS.md). Incluyen predicción de salida, una tarjeta personal y una tabla de texto. Las [soluciones razonadas](SOLUCIONES.md) sirven para comparar después de intentarlo.

## Criterios para terminar

- [ ] Puedo explicar qué hace el encabezado y dónde empieza el programa.
- [ ] Distingo archivo fuente y ejecutable.
- [ ] Puedo compilar y ejecutar sin depender de un botón automático.
- [ ] Predigo el efecto de agregar o quitar `\n`.
- [ ] Sé por qué debo recompilar después de cambiar el fuente.
- [ ] Corregí al menos un error de compilación leyendo su diagnóstico.
- [ ] Resolví la tarjeta personal y comparé su salida con el objetivo.

Conserva tus fuentes, tu resultado esperado y una nota breve sobre un error que resolviste. Una captura de salida no reemplaza al código necesario para reproducirla.

Cuando puedas explicar estos ejemplos sin consultar el texto, continúa con [Unidad 02 — Variables](../unidad02-variables/README.md).
