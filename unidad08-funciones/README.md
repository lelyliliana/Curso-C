# Unidad 08 — Funciones: dar nombre a una tarea y reutilizarla

[Inicio](../README.md) · [Anterior: entrada](../unidad07-entrada/README.md) · [Siguiente: contratos](../unidad09-contratos/README.md)

## Punto de partida

Ya has llamado funciones de biblioteca, como `printf` y `getchar`. Ahora escribirás las tuyas. Una función reúne instrucciones bajo un nombre, puede recibir datos y puede devolver un resultado. Su utilidad no depende de que sea larga: una fórmula corta también merece un nombre si expresa una responsabilidad clara.

Comenzaremos con datos pequeños conocidos. En la siguiente unidad escribiremos contratos explícitos y separaremos lectura, cálculo y presentación. No necesitas punteros ni variables globales para estos primeros ejemplos.

## 1. Definir no es ejecutar

Archivo: [ejemplos/01-saludo.c](ejemplos/01-saludo.c).

```c
#include <stdio.h>

void mostrar_inicio(void)
{
    printf("Aprendemos C paso a paso.\n");
}

int main(void)
{
    mostrar_inicio();
    mostrar_inicio();
    return 0;
}
```

La definición de `mostrar_inicio` describe qué hacer. La llamada `mostrar_inicio();` solicita hacerlo. El programa empieza en `main`, llama la función, ejecuta su cuerpo y vuelve a la instrucción siguiente del llamador. Como hay dos llamadas, aparecen dos mensajes.

El primer `void` indica que esta función **no devuelve un valor**. El `void` entre paréntesis indica que **no recibe argumentos**. Cumplen papeles diferentes. Conserva la lista explícita `(void)` para funciones sin parámetros en la base C17 del curso.

La función está fuera de las llaves de `main`. C estándar no permite definir una función dentro de otra. Algunas herramientas admiten extensiones, pero no dependemos de ellas.

### Compilar y ejecutar

Entra con la terminal de tu sistema a `unidad08-funciones`, comprueba la carpeta con `ls` y crea `build` con `mkdir -p build`. En Windows usa UCRT64.

| Sistema | Compilar | Ejecutar tras una compilación correcta |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-saludo.c -o build/saludo` | `./build/saludo` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-saludo.c -o build/saludo.exe` | `./build/saludo.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-saludo.c -o build/saludo` | `./build/saludo` |

Salida:

```text
Aprendemos C paso a paso.
Aprendemos C paso a paso.
```

Para los otros archivos cambia fuente y ejecutable; conserva las opciones y `.exe` en Windows. Los ejemplos son programas independientes: compila uno por vez, sin reunir todos sus `main` en un mismo ejecutable.

## 2. Recibir datos y devolver un resultado

Archivo: [ejemplos/02-resultado.c](ejemplos/02-resultado.c).

```c
int sumar(int a, int b)
{
    return a + b;
}
```

| Parte | Significado |
|---|---|
| `int` antes del nombre | Tipo del resultado devuelto |
| `sumar` | Nombre de la función |
| `int a, int b` | Parámetros: datos con nombre dentro de la función |
| Cuerpo entre llaves | Instrucciones que ejecuta una llamada |
| `return a + b;` | Obtiene el resultado y lo devuelve al llamador |

Dentro de `main`:

```c
int libros = 3;
int revistas = 4;
int total = sumar(libros, revistas);
```

`libros` y `revistas` son los **argumentos** de esta llamada: sus valores se entregan a los parámetros `a` y `b`, respectivamente. Los nombres no tienen que coincidir. El resultado 7 se usa para inicializar `total`.

Salida completa:

```text
Total: 7
Otro total: 7
```

La segunda línea utiliza otra llamada, `sumar(2, 5)`. La misma definición resuelve ambos casos. El resultado es un valor, por lo que también puede formar parte de otra expresión o pasarse a `printf`, usando un formato apropiado.

El contrato inicial de esta función, para nuestros ejercicios, limita ambos operandos a enteros de 0 a 100. Así la suma no supera 200. La función no comprueba todavía ese contrato; que una operación esté dentro de una función no elimina el desbordamiento ni valida automáticamente los argumentos.

## 3. Devolver no significa imprimir

`sumar` calcula y devuelve; no muestra mensajes. El llamador decide cómo utilizar el resultado. Esto permite usar la suma en una impresión, una condición o una prueba sin producir texto inesperado.

`mostrar_inicio` imprime y no devuelve un valor. Ambas responsabilidades tienen sentido, pero son distintas:

| Función | Recibe datos | Devuelve valor | Imprime |
|---|---|---|---|
| `mostrar_inicio` | No | No | Sí |
| `sumar` | Dos enteros | Un entero | No |

Si escribieras solo `sumar(3, 4);`, se calcularía el resultado y se descartaría. No aparecería 7 por sí solo. Para conservarlo, asígnalo; para mostrarlo, pásalo a la presentación.

Al ejecutar `return` dentro de una función auxiliar, termina **esa llamada** y regresa al llamador. No termina automáticamente `main`. En una función `void`, puedes escribir `return;` para salir antes sin devolver un valor; también regresa al alcanzar el final del cuerpo.

## 4. Paso por valor: el parámetro es una copia

Archivo: [ejemplos/03-copia.c](ejemplos/03-copia.c).

```c
void cambiar_copia(int numero)
{
    numero = 9;
    printf("Dentro: %d\n", numero);
}
```

`main` declara su propio `int numero = 12;`, llama `cambiar_copia(numero)` y después imprime su variable. Predice antes de ejecutar:

```text
Dentro: 9
En main: 12
```

El parámetro recibió una copia del valor 12. La asignación dentro de la función cambió esa copia, no el objeto de `main`. Las dos variables incluso tienen el mismo nombre, pero pertenecen a ámbitos diferentes.

Para obtener una modificación en estos ejercicios, devuelve un nuevo valor y úsalo en el llamador. Por ejemplo, una función `int descontar_uno(int cantidad)` puede devolver `cantidad - 1`, y el llamador puede hacer `cantidad = descontar_uno(cantidad);`, con cantidad inicial entre 1 y 100.

Cuando estudiemos punteros aprenderemos cómo dar acceso a un objeto externo. El paso por valor seguirá siendo la regla: no cambia porque una función tenga muchos parámetros.

## 5. Variables locales y llamadas independientes

Un parámetro y una variable declarada dentro de una función solo se usan en su ámbito. El acumulador de `sumar_hasta`, en los ejercicios, se inicializa de nuevo a cero cada vez que se llama. Una segunda llamada no conserva automáticamente el resultado de la primera.

Las variables locales ordinarias de una llamada tienen duración asociada a esa ejecución. No intentes acceder a ellas desde otra función por su nombre. Más adelante dibujaremos duración, direcciones y casos especiales de almacenamiento.

Evita agregar una variable global para que todas las funciones compartan el mismo dato sin que aparezca en sus parámetros. En este bloque el flujo se ve en argumentos y resultados: permite saber qué necesita cada tarea y probarla de forma independiente.

## 6. Declaración, prototipo y definición

Hasta ahora colocamos la definición antes de llamar. También puedes anunciar la función y definirla más abajo:

```c
int duplicar(int numero);
```

Es un **prototipo**: declara el nombre, el tipo de retorno y los tipos de los parámetros. Termina en punto y coma; no incluye el cuerpo. La definición proporciona después las instrucciones.

Archivo: [ejemplos/04-prototipo.c](ejemplos/04-prototipo.c). `main` ve el prototipo y llama `duplicar(4)`; la definición posterior devuelve `numero * 2`. La salida es `Doble: 8`.

El compilador debe conocer una declaración apropiada antes de la llamada. El prototipo no produce por sí solo una implementación: si falta la definición al construir el programa, el enlace no podrá resolver la función. En la Unidad 10 verás esa diferencia en varios archivos.

Haz corresponder declaración y definición. No cambies solo el tipo de resultado en una de ellas. No escribas dos versiones de `duplicar` con distinto número de parámetros esperando que C elija por sus argumentos: en C no utilizamos la sobrecarga de funciones de C++.

## 7. Errores frecuentes

- Una función que promete devolver un dato necesita un resultado válido en cada camino que pueda recorrer. No copies el caso especial de finalización de `main` como regla para las auxiliares.
- `return` termina la llamada: las instrucciones posteriores de ese camino no se ejecutan.
- No olvides los paréntesis de la llamada ni confundas una declaración con una ejecución.
- No ocultes una lectura de teclado dentro de una función cuyo nombre solo promete calcular un área.
- Si una llamada modifica datos o lee entrada, no dependas de un orden supuesto entre varios argumentos de otra llamada. Ejecuta esas tareas en instrucciones separadas.

## Práctica y cierre

Resuelve [EJERCICIOS.md](EJERCICIOS.md) y compara con [SOLUCIONES.md](SOLUCIONES.md).

- [ ] Distingo definición, prototipo y llamada.
- [ ] Distingo argumento, parámetro y resultado.
- [ ] Explico dónde regresa una función al ejecutar `return`.
- [ ] Predigo el efecto de modificar un parámetro recibido por valor.
- [ ] Mantengo cálculo y presentación como responsabilidades diferentes.
- [ ] Compruebo que las llamadas repetidas no dependen de estado oculto.

Continúa con [Unidad 09 — Contratos y responsabilidades](../unidad09-contratos/README.md).
