# Unidad 12 — Recorrer colecciones para resolver problemas

[Inicio](../README.md) · [Anterior: arreglos](../unidad11-arreglos/README.md) · [Siguiente: cadenas](../unidad13-cadenas/README.md)

## Objetivo

Un arreglo ya permite guardar varios datos. Ahora aprenderás a obtener un resumen, buscar la primera coincidencia, filtrar valores y modificar el orden. Cada algoritmo tendrá una pregunta concreta y un límite que puedas explicar.

Necesitas distinguir capacidad, cantidad utilizada e índice. Al terminar podrás procesar colecciones vacías y pequeñas sin inventar mínimos ni confundir un cero con ausencia. Los datos iniciales están en el código: este bloque todavía no introduce un lector numérico para llenar arreglos desde teclado.

## 1. Definir datos y contrato antes de calcular

Abre [ejemplos/01-resumen.c](ejemplos/01-resumen.c):

```c
enum { CAPACIDAD = 5 };
const int lecturas[CAPACIDAD] = {8, 2, 0, 10, 5};
const size_t usados = 5;
```

El arreglo reserva cinco elementos. Solo los primeros `usados` pertenecen a la colección. El contrato exige `usados <= CAPACIDAD` y cada lectura utilizada entre 0 y 100. Esas cantidades son pequeñas: cinco valores máximos suman 500, dentro incluso del rango mínimo exigido para `int`.

El programa comprueba la cantidad antes de usarla como límite. Después comprueba los valores antes de calcular el resumen. Un arreglo válido en memoria puede contener un dato que no cumple el problema. Un número usado correcto no valida automáticamente todos los elementos.

Si modificas el dominio o la capacidad, revisa también la capacidad del acumulador. Que cada elemento quepa en `int` no garantiza que su suma completa quepa. En este curso no dependemos del desbordamiento entero con signo.

## 2. Construir y ejecutar el resumen

Sigue cada paso por separado:

1. Desde la carpeta del curso entra con `cd unidad12-recorridos`.
2. Comprueba `ejemplos` y `soluciones` con `ls`.
3. Crea la carpeta de ejecutables: `mkdir -p build`.
4. Compila usando tu sistema y comprueba el resultado antes de ejecutar.

| Sistema | Construir | Ejecutar después |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-resumen.c -o build/resumen` | `./build/resumen` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-resumen.c -o build/resumen.exe` | `./build/resumen.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-resumen.c -o build/resumen` | `./build/resumen` |

Usa UCRT64 en Windows. Los demás archivos se construyen de forma independiente cambiando fuente y nombre del ejecutable. Cada uno tiene un `main`: no combines todos sus fuentes en un programa.

Salida inicial:

```text
Cantidad: 5
Suma: 25
Minimo: 0
Maximo: 10
Promedio: 5.00
```

## 3. Un resumen necesita distinguir una colección vacía

Antes de leer `lecturas[0]`, el ejemplo comprueba `usados == 0`. Para cero datos imprime:

```text
Sin lecturas: no hay minimo, maximo ni promedio.
```

No establece mínimo o máximo en 0 como sustituto de un resultado inexistente. Tampoco divide por cero. En el caso vacío finaliza correctamente: no hubo lecturas que resumir, y eso es un resultado reconocido por el contrato.

Con al menos un dato, inicializa:

```c
int suma = 0;
int minimo = lecturas[0];
int maximo = lecturas[0];
```

La suma comienza en cero porque ese es el valor inicial de una acumulación. Los extremos comienzan en **un dato real**. Un mínimo inicial cero daría un resultado falso si todas las lecturas fueran positivas.

Durante el ciclo mantiene esta propiedad: tras procesar los primeros elementos, `suma` es su suma, `minimo` es su menor valor y `maximo` su mayor valor. Una propiedad que sigue siendo verdadera al avanzar se llama **invariante**; no necesitas una notación matemática compleja para comenzar a usarla.

| Índice recién procesado | Lectura | Suma | Mínimo | Máximo |
|---:|---:|---:|---:|---:|
| 0 | 8 | 8 | 8 | 8 |
| 1 | 2 | 10 | 2 | 8 |
| 2 | 0 | 10 | 0 | 8 |
| 3 | 10 | 20 | 0 | 10 |
| 4 | 5 | 25 | 0 | 10 |

El promedio usa `(double)suma / (double)usados`. La conversión ocurre **antes** de dividir y solo con cantidad positiva. Si usaras división entera y después convirtieras el resultado, habrías perdido la fracción.

Prueba ahora `usados = 1`: solo participa 8. Luego `usados = 0`. Guarda y recompila cada cambio. Conserva el tamaño fijo y no uses una cantidad mayor que cinco para acceder; el programa rechaza esa cantidad antes del recorrido.

## 4. Buscar la primera coincidencia

Abre [ejemplos/02-busqueda.c](ejemplos/02-busqueda.c). Busca 8 en `{8, 2, 8, 0, 5}`. La tarea exige la **primera** coincidencia, por eso termina el recorrido con `break` al encontrarla.

```c
size_t posicion = usados;
```

`usados` representa «no encontrado» en esta variable: no es un índice de dato válido dentro del intervalo 0–`usados - 1`. Es un resultado auxiliar del algoritmo, **no** una posición que debamos leer. No utilizamos -1 en un tipo sin signo.

Después de buscar se comprueba el resultado:

```c
if (posicion == usados) {
    puts("No encontrado.");
} else {
    printf("Primera coincidencia: indice %zu, valor %d\n", posicion, codigos[posicion]);
}
```

La lectura ocurre únicamente en la rama con coincidencia. Salida inicial:

```text
Primera coincidencia: indice 0, valor 8
```

Con `buscado = 0` espera índice 3. Con 9 espera `No encontrado.`. Con `usados = 0` no se visita ninguna posición y también resulta «no encontrado». Un valor cero se busca igual que cualquier otro valor.

El recorrido es una **búsqueda lineal**: avanza por las posiciones en orden. No requiere datos ordenados. No apliques búsqueda binaria a estos datos; necesita otro contrato y otro algoritmo.

## 5. Filtrar sin confundir dos índices

Abre [ejemplos/03-filtro.c](ejemplos/03-filtro.c). Conserva las lecturas mayores o iguales que 5 en un segundo arreglo. Tiene dos cantidades:

- `usados`: cantidad de lecturas del origen.
- `seleccionados`: cantidad ya escrita en el destino.

`i` recorre el origen, incluso cuando un dato no se selecciona. El destino solo avanza al guardar una coincidencia. No uses `seleccionadas[i]` para insertar: dejarías huecos si el filtro descartó valores anteriores.

| Índice del origen | Valor | ¿Se conserva? | Índice escrito en destino | Seleccionados después |
|---:|---:|---|---|---:|
| 0 | 8 | Sí | 0 | 1 |
| 1 | 2 | No | Ninguno | 1 |
| 2 | 0 | No | Ninguno | 1 |
| 3 | 10 | Sí | 1 | 2 |
| 4 | 5 | Sí | 2 | 3 |

Salida:

```text
Seleccionadas: 3
Valor: 8
Valor: 10
Valor: 5
```

Ambos arreglos tienen capacidad cinco. Seleccionar como máximo una vez cada entrada no puede producir más datos que el origen. Aun así, el ejemplo comprueba espacio antes de escribir; si cambiaras la capacidad del destino, esa responsabilidad seguiría siendo visible.

Se conserva el orden original. Filtrar no significa ordenar ni eliminar duplicados. Con umbral 0 se conservan todos los datos válidos; con 101 no se conserva ninguno. El umbral es un entero de comparación, no una nueva lectura que deba cumplir 0–100.

Si un valor del origen está fuera de rango, se rechaza el informe. El programa no presenta una selección parcial como resultado completo. Puede haber escrito parte del destino antes de detectar el problema, pero ese estado interno no se publica como éxito.

## 6. Contar, invertir y conservar fronteras

Los ejercicios amplían los mismos recorridos:

- **Contar coincidencias:** visitar todos los elementos, sin detenerse en la primera.
- **Invertir:** intercambiar parejas desde los extremos hacia el centro.
- **Informar:** calcular total, días con cero y primer día con el máximo.

[soluciones/05-invertir.c](soluciones/05-invertir.c) utiliza:

```c
for (size_t i = 0; i < usados / 2; i++) {
    const size_t opuesto = usados - 1 - i;
    const int temporal = datos[i];
    datos[i] = datos[opuesto];
    datos[opuesto] = temporal;
}
```

Cada pareja se intercambia una vez. Con cinco elementos se intercambian 0/4 y 1/3; el índice 2 queda en su sitio. `temporal` conserva el primer valor antes de sobrescribirlo. Dos asignaciones sin ese temporal perderían uno de los valores.

Con cero o un elemento la condición del ciclo es falsa desde el principio. No se calcula `usados - 1 - i` en esos casos: colocar esa resta fuera del ciclo introduciría un problema cuando `usados` vale cero. Un contador sin signo no se recorre hacia atrás con una condición `i >= 0`, que siempre es verdadera.

## 7. Elegir casos que puedan revelar errores

No basta con repetir los valores iniciales. Antes de probar anota el resultado esperado:

| Caso | Qué comprueba |
|---|---|
| Colección vacía | No leer un primer dato inexistente en el contrato lógico |
| Un elemento | Extremos iguales y recorrido mínimo |
| Todos ceros | Cero como dato, no ausencia |
| Todos iguales | Repeticiones y primer máximo en caso de empate |
| Coincidencia al principio o al final | Límites de búsqueda |
| Ninguna coincidencia | No usar el indicador como índice |
| Filtro que conserva todo o nada | Cantidad de salida independiente de capacidad |
| Inversión con cantidad par e impar | Centro y número de intercambios |
| Cantidad mayor que capacidad | Rechazo antes de acceder |
| Valor fuera del dominio | No calcular un informe con datos inválidos |

En los arreglos inicializados puedes variar `usados` dentro del contrato sin borrar el resto de la memoria: las posiciones fuera del segmento usado simplemente no pertenecen al conjunto que procesas.

## Práctica y cierre

Resuelve [EJERCICIOS.md](EJERCICIOS.md); consulta después [SOLUCIONES.md](SOLUCIONES.md), con programas completos y resultados.

- [ ] Distingo suma, conteo, búsqueda y filtro.
- [ ] No calculo extremos ni promedio de una colección vacía.
- [ ] Uso un indicador de ausencia sin acceder con él.
- [ ] Mantengo separados los índices de origen y destino.
- [ ] Justifico las restas de índices sin signo.
- [ ] Compruebo dominio y capacidad antes de publicar un resultado.

Conserva una tabla de acumulación y al menos tres casos adicionales del informe. En la [Unidad 13](../unidad13-cadenas/README.md) estudiarás cómo un arreglo de `char` representa texto y por qué necesita espacio para un terminador.
