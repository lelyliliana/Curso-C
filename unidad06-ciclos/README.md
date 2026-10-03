# Unidad 06 — Ciclos: repetir con un propósito y un final

[Inicio](../README.md) · [Anterior: decisiones](../unidad05-decisiones/README.md) · [Siguiente: entrada](../unidad07-entrada/README.md)

## Objetivo

Una decisión elige un camino una vez. Un ciclo permite volver a ejecutar un bloque mientras corresponda: mostrar varios pasos, sumar números o pedir otra entrada. Aprenderás a identificar el estado inicial, la condición, el trabajo y el avance que permite terminar.

Los datos todavía son fijos. No mezcles aún un ciclo con lectura de teclado: primero explica y verifica cuántas veces se ejecuta.

## 1. `while`: preguntar antes de cada vuelta

Archivo: [ejemplos/01-while.c](ejemplos/01-while.c).

```c
int paso = 1;

while (paso <= 3) {
    printf("Paso: %d\n", paso);
    paso = paso + 1;
}
printf("Fin.\n");
```

Una **iteración** es una vuelta del ciclo. `while` comprueba su condición antes de cada una. Si es verdadera, ejecuta el bloque y vuelve a comprobar. Si es falsa, continúa después del ciclo.

| Momento | Valor de `paso` | Condición `paso <= 3` | Acción |
|---|---:|---|---|
| Primera comprobación | 1 | Verdadera | Mostrar 1 y cambiar a 2 |
| Segunda | 2 | Verdadera | Mostrar 2 y cambiar a 3 |
| Tercera | 3 | Verdadera | Mostrar 3 y cambiar a 4 |
| Cuarta | 4 | Falsa | Salir del ciclo |

Hay cuatro comprobaciones de condición y tres ejecuciones del cuerpo. La última comprobación no imprime otro paso.

### Compilar

Entra a `unidad06-ciclos` con la terminal de tu sistema; en Windows usa UCRT64. Comprueba la carpeta con `ls` y crea `build` con `mkdir -p build`.

| Sistema | Compilar | Ejecutar después de compilar correctamente |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-while.c -o build/pasos` | `./build/pasos` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-while.c -o build/pasos.exe` | `./build/pasos.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-while.c -o build/pasos` | `./build/pasos` |

Salida:

```text
Paso: 1
Paso: 2
Paso: 3
Fin.
```

Cambia la ruta y el nombre del ejecutable para los otros fuentes. Guarda y recompila cada variante; ejecuta solo tras una compilación correcta.

## 2. Qué hace avanzar un ciclo

Antes de ejecutar responde cuatro preguntas:

1. ¿Con qué estado empieza?
2. ¿Qué condición mantiene la repetición?
3. ¿Qué trabajo hace cada vuelta?
4. ¿Qué cambia para que pueda finalizar?

En el ejemplo, quitar `paso = paso + 1;` mantiene siempre el valor 1. La condición nunca cambia y el programa imprime sin terminar. No necesitas ejecutar esa variante para descubrir el problema. Si accidentalmente un programa de consola queda repitiendo, Ctrl+C suele interrumpirlo en las terminales usadas en el curso. Luego corrige el avance; no conviertas la interrupción manual en el funcionamiento normal.

Un ciclo puede ejecutar **cero vueltas** si su condición es falsa desde el comienzo. Con `paso = 4`, el ejemplo muestra solo `Fin.`. Eso es correcto, no un fallo.

## 3. `for`: reunir inicio, condición y actualización

Cuando hay un recorrido contado, `for` permite verlo en una cabecera:

```c
for (int numero = 1; numero <= 5; numero++) {
    printf("%d\n", numero);
}
```

La cabecera contiene tres partes separadas por punto y coma:

| Parte | Cuándo se ejecuta |
|---|---|
| `int numero = 1` | Una vez, al entrar al `for` |
| `numero <= 5` | Antes de cada vuelta |
| `numero++` | Después de cada ejecución normal del cuerpo |

`numero++` incrementa en uno. Lo usamos como instrucción separada en la actualización; no combinaremos incrementos con otros usos del mismo objeto dentro de una expresión. `numero--` decrementa en uno.

La variable declarada en esa cabecera pertenece al `for` y su cuerpo; no puedes imprimirla después como si siguiera disponible. Si necesitas un resultado final, guárdalo en otra variable declarada antes del ciclo.

`for` y `while` no son una competencia de rapidez. Elige la forma que haga más clara la condición y el avance: `for` para un recorrido contado; `while` cuando la repetición depende de un estado que cambiará en el cuerpo.

## 4. Acumular un resultado

Archivo: [ejemplos/02-for.c](ejemplos/02-for.c).

```c
const int limite = 5;
int suma = 0;
for (int numero = 1; numero <= limite; numero++) {
    suma += numero;
}
printf("Suma de 1 a %d: %d\n", limite, suma);
```

`suma += numero;` suma el valor actual de `numero` al valor anterior de `suma` y almacena el resultado. En este caso sencillo equivale a `suma = suma + numero;`.

Un **contador** registra cuántas veces o en qué posición vamos. Un **acumulador** reúne los valores calculados. Aquí `numero` controla el recorrido y `suma` acumula.

| Número | Suma antes | Suma después |
|---:|---:|---:|
| 1 | 0 | 1 |
| 2 | 1 | 3 |
| 3 | 3 | 6 |
| 4 | 6 | 10 |
| 5 | 10 | 15 |

Salida: `Suma de 1 a 5: 15`. El límite también se muestra mediante su valor: al cambiarlo, el mensaje sigue describiendo el recorrido real. Inicializamos en cero porque es el inicio matemático de esta suma, no porque queramos esconder un dato desconocido. Si reinicializaras `suma` dentro del cuerpo, perderías lo acumulado entre vueltas.

Cada suma y cada incremento deben caber en el tipo. Un ciclo no elimina los límites de `int`. El ejercicio de suma admite un máximo de 100, que da 5050, para mantener tanto el acumulador como el contador dentro de un rango sencillo.

## 5. `do-while`: ejecutar antes de preguntar

```c
do {
    /* Trabajo de una vuelta. */
} while (condicion);
```

Esta forma comprueba la condición al final y ejecuta el cuerpo al menos una vez. El punto y coma tras `while (condicion);` pertenece a su sintaxis.

Archivo: [ejemplos/03-do-while.c](ejemplos/03-do-while.c). Compara dos ciclos cuyo contador comienza en cero y cuya condición pide que sea menor que cero:

```text
Vueltas while: 0
Vueltas do-while: 1
```

Es una demostración del lugar de la comprobación, no un algoritmo para hacer una cantidad negativa de trabajos. Si un problema permite cero repeticiones, no elijas `do-while` sin considerar su primera ejecución obligatoria. Puede ser apropiado cuando el primer intento forma parte necesaria del procedimiento; aun así, debes diseñar cómo terminar.

## 6. `break` y `continue`

Archivo: [ejemplos/04-saltos.c](ejemplos/04-saltos.c). Recorre del 1 al 10, omite pares y termina cuando encuentra un impar mayor que 7.

- `continue` omite lo que queda de la vuelta actual. En un `for`, pasa a su actualización y luego comprueba otra vez la condición.
- `break` sale del ciclo más cercano que lo contiene; después continúa fuera de ese ciclo.

Salida:

```text
Impar: 1
Impar: 3
Impar: 5
Impar: 7
Fin.
```

Con número 2, `continue` omite la impresión, pero el `for` incrementa después a 3. Con 9, `break` termina el recorrido antes de imprimir. No se llega a procesar 10.

En un `while`, `continue` regresa a comprobar la condición. Si tu avance estaba escrito al final del cuerpo y lo saltas, puedes dejar el ciclo sin progreso. En los primeros ejercicios utiliza un avance fácil de revisar y no agregues saltos si una condición clara basta.

`break` dentro de un `switch` sale de ese `switch`, no automáticamente de un ciclo que lo rodee. `return` desde `main` termina el programa; son efectos distintos.

## 7. Fronteras y recuento

De 1 a 5 inclusive hay cinco números: `numero <= 5`. Escribir `< 5` recorre solo 1, 2, 3 y 4. De 0 a 4 inclusive también hay cinco, pero produce otros valores. No cambies una frontera solo hasta que «parezca funcionar»: escribe el conjunto esperado.

Para revisar un ciclo comprueba un caso de cero vueltas, uno de una vuelta y uno de varias. Observa tanto el primer valor como el último, la cantidad de resultados y el estado final.

No uses `numero <= INT_MAX` con `numero++` como si siempre terminara de forma segura: el incremento posterior al máximo podría desbordar. Las fronteras de nuestros ejemplos son pequeñas y explícitas.

## Práctica y cierre

Resuelve [EJERCICIOS.md](EJERCICIOS.md); las [soluciones](SOLUCIONES.md) incluyen una tabla de multiplicar, una suma y una cuenta descendente.

- [ ] Trazo estado inicial, condición, trabajo y avance.
- [ ] Distingo número de comprobaciones y número de vueltas.
- [ ] Explico la diferencia entre `while` y `do-while`.
- [ ] Distingo contador y acumulador.
- [ ] Identifico qué ocurriría si omito o salto una actualización.
- [ ] Compruebo cero, una y varias vueltas sin desbordar.

Continúa con [Unidad 07 — Entrada validada](../unidad07-entrada/README.md). Allí un nuevo carácter leído será también una forma de hacer avanzar el ciclo.
