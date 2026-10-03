# Unidad 05 — Decisiones: actuar según los datos

[Inicio](../README.md) · [Anterior: expresiones](../unidad04-expresiones/README.md) · [Siguiente: ciclos](../unidad06-ciclos/README.md)

## Punto de partida

Ya puedes calcular plazas o promedios, pero un cálculo no responde por sí solo «¿puede entrar otra persona?» ni impide dividir por cero. Una decisión selecciona qué instrucciones ejecutar según una condición.

Los datos de esta unidad siguen escritos en el fuente. Aprenderás `if`, `else`, comparaciones, operadores lógicos y una selección con `switch`. Después podrás repetir decisiones con ciclos y, finalmente, aplicarlas a datos recibidos por teclado. Sigue ese orden: no necesitas copiar todavía un programa de entrada.

## 1. Dos caminos con `if` y `else`

Archivo: [ejemplos/01-aforo.c](ejemplos/01-aforo.c).

```c
const int capacidad = 20;
int ocupados = 12;

if (ocupados < capacidad) {
    printf("Hay plazas disponibles.\n");
    printf("Plazas: %d\n", capacidad - ocupados);
} else {
    printf("Sala completa.\n");
}
```

Este fragmento pertenece a `main`; el archivo enlazado contiene el programa completo. La condición se escribe entre paréntesis. Las llaves agrupan las instrucciones de cada camino. Si `ocupados < capacidad` es verdadera, se ejecuta el primer bloque; si es falsa, el bloque de `else`. No se ejecutan ambos caminos de esa misma decisión.

### Compilar este ejemplo

Entra con tu terminal a `unidad05-decisiones` y comprueba con `ls` que ves `ejemplos`. En Windows usa MSYS2 UCRT64. Crea la carpeta de ejecutables con `mkdir -p build`.

| Sistema | Compilar | Ejecutar tras una compilación correcta |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-aforo.c -o build/aforo` | `./build/aforo` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-aforo.c -o build/aforo.exe` | `./build/aforo.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-aforo.c -o build/aforo` | `./build/aforo` |

Salida:

```text
Hay plazas disponibles.
Plazas: 8
```

Cambia `ocupados` a 20, guarda y recompila. Ahora debe aparecer solo `Sala completa.`. Para los siguientes programas cambia la ruta y el nombre del ejecutable; conserva las opciones y `.exe` en Windows.

**Contrato de este primer ejemplo:** capacidad fija 20 y ocupados entre 0 y 20. Un valor de -3 sería un dato inválido del problema, aunque sea un `int` válido. Esta primera decisión no lo comprueba; en los próximos ejemplos añadimos ese control explícito.

## 2. Comparar sin cambiar

| Operador | Pregunta | Ejemplo verdadero |
|---|---|---|
| `<` | ¿Menor que? | `3 < 5` |
| `<=` | ¿Menor o igual? | `5 <= 5` |
| `>` | ¿Mayor que? | `7 > 5` |
| `>=` | ¿Mayor o igual? | `5 >= 5` |
| `==` | ¿Igual? | `5 == 5` |
| `!=` | ¿Diferente? | `3 != 5` |

Estas comparaciones producen un `int`: 1 cuando son verdaderas, 0 cuando son falsas. En una condición, cero se interpreta como falso y un valor distinto de cero como verdadero.

`ocupados = 20;` cambia el dato. `ocupados == 20` pregunta por él sin modificarlo. Escribir una asignación dentro de una condición puede compilar y cambiar la variable: no lo uses como sustituto de `==`. Lee las advertencias del compilador.

No escribas `0 <= nota <= 10` para comprobar un rango. C lo agrupa como `(0 <= nota) <= 10`: la primera comparación produce 0 o 1, y ambos son menores o iguales a 10. El rango correcto necesita dos preguntas unidas.

## 3. Unir condiciones

| Operador | Lectura | Cuándo es verdadero |
|---|---|---|
| `&&` | Y | Las dos condiciones son verdaderas |
| `||` | O inclusivo | Al menos una condición es verdadera |
| `!` | No | Su operando se interpreta como falso |

Para un rango válido: `nota >= 0 && nota <= 10`. Para detectar un valor fuera del rango: `nota < 0 || nota > 10`. Usa los operadores dobles `&&` y `||`; `&` y `|` son otros operadores y no los intercambiaremos aquí.

`&&` y `||` evalúan de izquierda a derecha con **cortocircuito**: si ya se conoce el resultado, no evalúan el operando derecho. Por ejemplo:

```c
int personas = 0;
if (personas != 0 && 5 / personas >= 1) {
    printf("Reparto entero positivo.\n");
}
```

Como `personas != 0` es falso, no se realiza `5 / personas`. No aparecerá el mensaje ni se dividirá por cero. El orden protege este cálculo concreto; no resuelve cualquier riesgo de una fórmula arbitraria. Para una división real del problema también debes validar rangos y significado, como en los ejercicios.

### Datos lógicos con `bool`

Incluye `<stdbool.h>` para utilizar `bool`, `true` y `false` en C17:

```c
bool tiene_autorizacion = true;
bool tiene_documento = true;
```

Son datos de sí/no. `!tiene_documento` significa que falta el documento. Archivo: [ejemplos/03-permiso.c](ejemplos/03-permiso.c).

Su regla hipotética es: tener documento **y**, además, ser mayor de edad **o** tener autorización. Se escribe `(edad >= 18 || tiene_autorizacion) && tiene_documento`. Los paréntesis hacen visible esa regla; no representa una política legal de una actividad real. La edad del ejemplo es un dato conocido no negativo.

Con edad 17 y ambas banderas verdaderas, la salida es:

```text
Puede participar.
```

No basta la autorización cuando falta el documento. Prueba ese caso y explica por separado cada condición.

## 4. Validar antes de clasificar

Archivo: [ejemplos/02-nota.c](ejemplos/02-nota.c).

Primero se rechaza una nota fuera de 0–10. Después se selecciona **una** categoría:

```c
if (nota >= 9) {
    printf("Nivel alto.\n");
} else if (nota >= 6) {
    printf("Aprobado.\n");
} else {
    printf("Necesita repasar.\n");
}
```

Para la nota inicial 7, la salida es `Aprobado.`. Una nota 9 también es mayor que 6, pero al entrar en el primer camino la cadena no continúa a los siguientes. Es diferente de escribir varios `if` independientes: con estos podrías producir más de una categoría.

Pon las condiciones de forma que reflejen la regla. Si probaras primero `nota >= 6`, también atraparías las notas 9 y 10 en ese primer camino.

La validación ocurre antes. No clasifiques -1 como «necesita repasar»: es un valor fuera del contrato, no una nota válida baja.

## 5. Salir cuando no podemos continuar

El ejemplo de la nota incluye `<stdlib.h>` y utiliza `EXIT_SUCCESS` y `EXIT_FAILURE`, nombres de la biblioteca estándar para comunicar finalización correcta o fallo. `return 0;` también expresa finalización correcta desde `main`.

```c
if (nota < 0 || nota > 10) {
    printf("Nota invalida.\n");
    return EXIT_FAILURE;
}
```

`return` termina `main` en ese momento: la clasificación de abajo no se ejecuta. Es una **salida temprana**. El mensaje explica el problema a la persona; el estado de salida permite detectarlo desde otras herramientas. El número concreto correspondiente a `EXIT_FAILURE` depende de la implementación.

Un programa que detecta y rechaza correctamente un dato inválido puede terminar con fallo de manera intencional. No es lo mismo que un fallo de compilación, una caída inesperada o un resultado de cálculo incorrecto. Para mantener el foco inicial, estos programas muestran también los mensajes de error con `printf`; la separación entre salida normal y salida de errores se estudiará después.

## 6. Elegir entre valores concretos con `switch`

Archivo: [ejemplos/04-seleccion.c](ejemplos/04-seleccion.c). El grupo inicial `'B'` produce `Grupo B: tarde.`.

```c
switch (grupo) {
    case 'A':
        printf("Grupo A: manana.\n");
        break;
    case 'B':
        printf("Grupo B: tarde.\n");
        break;
    default:
        printf("Grupo desconocido.\n");
        return EXIT_FAILURE;
}
```

`switch` selecciona por el valor de una expresión de tipo entero; aquí usamos un carácter. Cada `case` identifica un valor constante. `default` atiende los demás valores.

`break` sale del `switch`. Sin él, la ejecución puede continuar por las instrucciones del caso siguiente aunque su etiqueta no coincida. En estos ejemplos queremos un caso por selección y conservamos los `break`.

Usa `if` cuando la regla combina rangos o condiciones; `switch` resulta cómodo para valores discretos como una opción de menú. No recibe cadenas completas ni sirve para seleccionar directamente por un `double`.

## 7. Errores que conviene reconocer

- Un punto y coma inmediatamente después de `if (condicion)` crea una instrucción vacía; el bloque que sigue puede ejecutarse siempre. Conserva el patrón de la guía.
- Sin llaves, la decisión controla solo la instrucción inmediata. Usaremos llaves incluso para una sola instrucción.
- Una sangría bonita no cambia lo que controlan las llaves.
- Un dato dentro del tipo puede seguir siendo inválido para el problema.
- Revisar solo un caso favorable deja sin comprobar las fronteras y el camino de rechazo.

## Práctica y cierre

Resuelve [EJERCICIOS.md](EJERCICIOS.md) y después compara con [SOLUCIONES.md](SOLUCIONES.md). Retomaremos las cajas de la unidad anterior para calcular cuántas se necesitan en total.

- [ ] Distingo asignar, comparar y elegir un camino.
- [ ] Escribo un rango con dos comparaciones.
- [ ] Explico el cortocircuito y sus límites.
- [ ] Separo un dato inválido de un dato válido con resultado desfavorable.
- [ ] Compruebo fronteras, caminos alternativos y estado de salida.
- [ ] Distingo `break` dentro de `switch` y `return` desde `main`.

Continúa con [Unidad 06 — Ciclos](../unidad06-ciclos/README.md).
