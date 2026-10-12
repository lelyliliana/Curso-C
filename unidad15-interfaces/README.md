# Unidad 15 — Arreglos y cadenas en funciones

[Inicio](../README.md) · [Anterior: punteros](../unidad14-punteros/README.md) · [Siguiente: líneas](../unidad16-lineas/README.md)

## Objetivo

En las unidades 11–13 mantuvimos los arreglos dentro de `main`. Ahora podrás extraer operaciones sin copiar sus implementaciones en cada controlador. Diseñarás funciones con cantidad o capacidad explícita y pruebas que enlazan exactamente el mismo código que usa la aplicación.

Necesitas direcciones, punteros, permisos y duración. Al terminar podrás explicar por qué un parámetro con corchetes no recibe el arreglo completo por valor, separar cantidad de capacidad, conservar salidas ante rechazo y reconocer las precondiciones que una función no puede verificar por sí sola.

## 1. Un parámetro con corchetes se ajusta a puntero

Abre [ejemplos/01-parametro.c](ejemplos/01-parametro.c):

```c
void mostrar(const int datos[], size_t cantidad);
```

Como parámetro, `const int datos[]` se ajusta a `const int *datos`. La función recibe una dirección y una cantidad, no una copia de todos los elementos. Puede usar `datos[i]` para leer el elemento correspondiente mientras el arreglo original siga vivo.

En `main` la expresión `sizeof datos / sizeof datos[0]` sí obtiene tres elementos porque `datos` es el arreglo local declarado allí. Dentro de `mostrar`, `sizeof datos` sería el tamaño del **puntero ajustado**, no el tamaño total del arreglo del llamador. No escribimos esa fórmula dentro de la auxiliar. Un compilador puede advertir sobre ella, pero el diseño debe ser correcto aun antes del diagnóstico.

Escribir un número dentro del parámetro, como `int datos[5]`, tampoco transporta automáticamente el tamaño ni comprueba que el llamador tenga cinco elementos. Una interfaz necesita expresar cuántos elementos puede utilizar y qué memoria debe proporcionar el llamador.

El contrato del ejemplo exige que `datos` permita leer `cantidad` enteros vivos. Admite `mostrar(NULL, 0)` porque el ciclo no entra y no accede ni calcula direcciones a partir del puntero nulo. No admite `NULL` con cantidad positiva.

## 2. Construir un primer recorrido

Sigue cada paso por separado:

1. Desde la carpeta del curso entra con `cd unidad15-interfaces`.
2. Ejecuta `ls` y reconoce `ejemplos`, `proyecto` y `soluciones`.
3. Crea `build` con `mkdir -p build`.
4. Construye el ejemplo con tu compilador y ejecuta solo si termina correctamente.

| Sistema | Construir | Ejecutar después |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-parametro.c -o build/parametro` | `./build/parametro` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-parametro.c -o build/parametro.exe` | `./build/parametro.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-parametro.c -o build/parametro` | `./build/parametro` |

Usa UCRT64 en Windows. Salida:

```text
Indice 0: 4
Indice 1: 0
Indice 2: 7
```

La segunda llamada, con `NULL` y cero, no imprime elementos. No convierte ausencia en un dato cero.

## 3. Avanzar por elementos y detenerse en el límite

Abre [ejemplos/02-limite.c](ejemplos/02-limite.c). El arreglo local tiene tres elementos. `datos + 1` señala el segundo: la suma avanza **un elemento del tipo**, no necesariamente un byte.

`datos + cantidad` forma un puntero al lugar inmediatamente posterior al último elemento. Ese puntero sirve como límite de comparación, pero **no puede desreferenciarse**. El ciclo compara antes de leer:

```c
for (int *actual = datos; actual != final; actual++) {
    printf("Valor: %d\n", *actual);
}
```

Visita 4, 0 y 7; después imprime `Sumar uno avanza un elemento.`. Todas esas direcciones pertenecen al mismo arreglo o a su límite inmediatamente posterior.

No calcules una posición anterior al comienzo ni posterior a ese límite. No restes ni ordenes direcciones de objetos independientes para deducir distancias. En las funciones de este bloque preferimos índices y cantidades, que hacen los límites más visibles. La aritmética de punteros se enseña aquí para comprender las reglas, no como obligación de reemplazar cada `datos[i]`.

## 4. Diseñar la interfaz de una colección

Consulta [proyecto/coleccion.h](proyecto/coleccion.h). Declara tres funciones:

| Función | Entrada | Salida y significado |
|---|---|---|
| `sumar_lecturas` | Segmento de 0–5 enteros, cada uno 0–100 | `bool` y suma en un `int` del llamador |
| `minimo_lecturas` | Segmento de 1–5 enteros, cada uno 0–100 | `bool` y mínimo en un `int` del llamador |
| `copiar_texto` | Cadena terminada, destino y capacidad en `char` | `bool`; con éxito deja una cadena completa en destino |

El segmento de lectura usa una **cantidad de elementos**, no bytes. La copia de texto usa una capacidad en `char`, cuyo tamaño es un byte de C. No intercambies esas unidades por el hecho de que ambas cantidades tengan tipo `size_t`.

En las funciones numéricas el resultado debe señalar un entero modificable separado de los datos leídos. El arreglo se recibe mediante `const int *`: la implementación no lo modifica. La suma máxima es 500. En vacío la suma válida es cero; el mínimo devuelve `false` porque no existe un dato del que obtenerlo.

Antes de escribir un resultado se comprueban todos los valores. Si un valor es 101, una cantidad supera cinco o un argumento requerido es nulo, devuelve `false` conservando la salida previa.

El código comprueba esos casos, pero no puede medir la extensión real de cualquier memoria que reciba. Si el llamador pasa un arreglo de dos elementos y declara que tiene cinco, la comprobación `cantidad <= 5` no descubre esa mentira. La precondición de memoria válida sigue siendo responsabilidad del llamador. Prueba rechazos que la interfaz maneja; no ejecutes lecturas fuera del objeto para «probar» el contrato.

## 5. Copiar una cadena requiere un origen válido

[proyecto/coleccion.c](proyecto/coleccion.c) comprueba argumentos y capacidad antes de copiar. `strlen(origen)` se utiliza solo bajo la precondición de que el origen ya es una cadena terminada accesible. Una capacidad de destino no limita la búsqueda del terminador del origen.

La copia acepta cuando `longitud < capacidad`; copia cada byte y escribe `destino[longitud] = '\0'`. Si no cabe, conserva el destino anterior. El origen y el destino deben ser regiones separadas, **sin solapamiento**. La función no promete manejar copias dentro de una misma región; otras herramientas y contratos se estudiarán más adelante.

`NULL` no es una cadena vacía. La cadena vacía tiene un terminador accesible y necesita capacidad de destino de al menos uno. La copia rechaza punteros nulos y capacidad cero.

## 6. Construir aplicación y pruebas compartidas

El proyecto utiliza el patrón de la Unidad 10:

| Fuente | Responsabilidad |
|---|---|
| [coleccion.h](proyecto/coleccion.h) | Declaraciones y contratos |
| [coleccion.c](proyecto/coleccion.c) | Cálculos y copia |
| [main.c](proyecto/main.c) | Preparar datos y presentar un informe |
| [pruebas_coleccion.c](proyecto/pruebas_coleccion.c) | Comprobar esas mismas funciones |

Desde `unidad15-interfaces`, con `build` creado, construye la aplicación:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/main.c proyecto/coleccion.c -o build/coleccion
```

En macOS sustituye `gcc` por `clang`; en UCRT64 usa `build/coleccion.exe`. Después ejecuta `./build/coleccion` o su variante `.exe`. Espera:

```text
Nombre: sensor
Suma: 25
Minimo: 0
```

Luego, en un paso separado, construye las pruebas:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/pruebas_coleccion.c proyecto/coleccion.c -o build/pruebas_coleccion
```

Aplica las mismas variantes de compilador y extensión. Ejecuta ese segundo programa: debe imprimir `Pruebas de coleccion: OK.`. No combines ambos `main`, no incluyas archivos `.c` dentro de otros y no uses un comodín para reunir todos los fuentes.

Cada llamada de prueba se ejecuta fuera de `assert`; la aserción solo comprueba su resultado. Además, `#ifdef NDEBUG` impide construir las pruebas con aserciones desactivadas. Eso conserva su significado como pruebas, no como validación de una entrada de usuario.

## 7. Filtrar con salida completa o sin cambios

El ejercicio de filtro recibe origen, cantidad, umbral, destino, capacidad de destino y una dirección donde entregar la cantidad escrita. Consulta después [soluciones/filtro.h](soluciones/filtro.h) y [soluciones/filtro.c](soluciones/filtro.c).

Si el destino tiene capacidad tres y hay cinco seleccionados, no queremos dejar un prefijo aceptado como resultado final. La implementación hace dos recorridos:

1. Valida valores y cuenta cuántos cumplen el umbral, sin escribir salidas.
2. Si caben todos, recorre otra vez y copia los seleccionados en orden.
3. Solo al completar escribe la cantidad en `*usados`.

Un rechazo conserva tanto los elementos del destino como su cantidad previa. Origen, destino y objeto de salida de cantidad deben permanecer separados y vivos. La función admite origen nulo solo con cantidad cero, y destino nulo solo con capacidad cero; esa ausencia de destino solo permite resultados vacíos.

Este algoritmo no es una transacción general frente a concurrencia o interrupciones: es una garantía de la función de un solo hilo sobre los rechazos que comprueba, bajo sus precondiciones. No asumimos que otro código cambie el origen entre los dos recorridos.

## Práctica y cierre

Resuelve [EJERCICIOS.md](EJERCICIOS.md) y después consulta [SOLUCIONES.md](SOLUCIONES.md), incluidos comandos de filtro y pruebas.

- [ ] Explico el ajuste de parámetros de arreglo a puntero.
- [ ] Paso cantidad y capacidad con sus unidades correctas.
- [ ] Calculo `sizeof` del arreglo donde todavía es un arreglo.
- [ ] Distingo precondiciones de memoria de comprobaciones de dominio.
- [ ] Respeto las reglas de nulidad, duración y separación de salidas.
- [ ] Pruebo la implementación enlazada por la aplicación.

Conserva una prueba de rechazo con salida intacta. En la [Unidad 16](../unidad16-lineas/README.md) crearás un lector compartido que llena un arreglo de texto del llamador y separa lectura de conversión numérica.

---

### ¿Necesitas apoyo con este tema?

Si te bloqueaste con la práctica, necesitas revisar tu entorno o adaptar lo aprendido a tu proyecto, podemos trabajarlo en una sesión personalizada.

[**Solicitar asesoría para este tema por WhatsApp**](https://wa.me/573103618296?text=Hola%2C%20Leli.%20Estoy%20estudiando%2015%20%C2%B7%20Interfaces%20de%20arreglos%20y%20cadenas%20del%20curso%20C%20desde%20cero%20%28https%3A%2F%2Fgithub.com%2Flelyliliana%2FCurso-C%2Ftree%2Fmain%2Funidad15-interfaces%29%20y%20necesito%20una%20asesor%C3%ADa%20personalizada.%20Mi%20duda%20es%E2%80%A6)
