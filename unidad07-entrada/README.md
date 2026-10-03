# Unidad 07 — Entrada: leer, comprobar y recién entonces usar

[Inicio](../README.md) · [Anterior: ciclos](../unidad06-ciclos/README.md)

## Objetivo y alcance

Hasta ahora cambiabas un dato editando el fuente y recompilando. Ahora el programa recibirá texto durante su ejecución. Escribir algo por teclado no garantiza que sea una opción válida ni una cantidad utilizable.

Aprenderás en cuatro pasos: leer un carácter, validar una opción completa, construir una cantidad acotada y gestionar reintentos. Usaremos decisiones y ciclos ya estudiados, sin pedirte que manejes arreglos, cadenas o punteros antes de aprenderlos.

Esta es una primera entrada numérica con **contrato pequeño**: enteros de 0 a 100 escritos con dígitos y un máximo de ocho bytes antes del salto de línea. No es todavía un lector general de números con signo, decimales o notación científica. Cuando estudiemos funciones, arreglos y cadenas, construiremos lectores por líneas con `fgets` y conversiones como `strtol`.

## 1. Leer no es validar

Archivo: [ejemplos/01-caracter.c](ejemplos/01-caracter.c).

```c
int c = getchar();
```

`getchar`, declarada mediante `<stdio.h>`, intenta obtener el siguiente byte de la entrada estándar. En una sesión normal esa entrada proviene del teclado, pero también puede provenir de un archivo o una redirección. Su resultado se guarda en un **`int`**, no en `char`, para poder distinguir el dato leído del indicador `EOF`.

`EOF` es un nombre de la biblioteca que señala que no se obtuvo otro dato: puede ser fin de entrada o un error de lectura. No es una letra que debas escribir ni debemos reemplazarlo por el número fijo -1. Tras recibirlo consultamos `ferror(stdin)` para distinguir un error. `stdin` nombra el flujo de entrada estándar; por ahora lo pasamos a esa función sin manipular su representación interna.

### Compilar y realizar la primera lectura

Entra a `unidad07-entrada` con la terminal de tu sistema (UCRT64 en Windows). Comprueba con `ls` que ves `ejemplos` y crea `build` con `mkdir -p build`.

| Sistema | Compilar | Iniciar el programa |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-caracter.c -o build/caracter` | `./build/caracter` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-caracter.c -o build/caracter.exe` | `./build/caracter.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-caracter.c -o build/caracter` | `./build/caracter` |

Ejecuta solo después de compilar correctamente. Aparece:

```text
Escribe un digito y pulsa Enter.
```

Escribe `5` y pulsa Enter. El programa responde `Primer digito: 5`. Lo escrito por ti puede verse también en la terminal porque esta lo muestra; no confundas ese eco con una impresión del programa.

En las terminales habituales, Enter entrega la línea al programa. Que `getchar` espere mientras todavía no envías datos es parte de la lectura interactiva, no necesariamente un ciclo atascado.

Este primer ejemplo **solo inspecciona el primer byte**. Si escribes `56`, informa 5; no demuestra que la entrada completa fuera un solo dígito. Termina sin consumir el resto. No lo reutilices como validador completo ni como lector repetido: el siguiente ejemplo corrige precisamente esa limitación.

### De carácter a valor

```c
if (c >= '0' && c <= '9') {
    printf("Primer digito: %d\n", c - '0');
}
```

El carácter `'5'` y el número 5 son distintos. Los dígitos básicos están ordenados consecutivamente en C; después de comprobar que `c` es uno de ellos, `c - '0'` obtiene su valor de 0 a 9. No hace falta memorizar sus códigos ni asumir un número concreto para `'0'`.

La comprobación de `EOF` se realiza primero. Cuando no hay datos, el programa informa `Sin datos.`; no inventa un cero. Ante error informa `Error de lectura.` y termina con `EXIT_FAILURE`.

## 2. Aceptar una opción completa

Archivo: [ejemplos/02-opcion.c](ejemplos/02-opcion.c).

Contrato: **una sola opción**, escrita como `0`, `1` o `2`, seguida de Enter. También se acepta que el flujo termine inmediatamente después de ese carácter. No se admiten espacios, otros caracteres ni más dígitos en la misma línea. Las líneas posteriores pertenecen a otras posibles solicitudes; este programa atiende solo la primera y termina.

Primero lee `opcion`. Si es `EOF`, atiende fin/error. Si es un salto de línea, la entrada estaba vacía: no intenta leer una segunda línea para completarla. Si era otro carácter, consume el resto hasta `\n` o `EOF`:

```c
bool extra = false;
if (opcion != '\n') {
    int c = getchar();
    while (c != '\n' && c != EOF) {
        extra = true;
        c = getchar();
    }
    /* El archivo completo comprueba tambien ferror(stdin). */
}
```

`extra` recuerda que apareció al menos un carácter adicional. No lo devuelve a falso al encontrar otro. El ciclo avanza leyendo un carácter nuevo en cada vuelta.

Después valida `extra` y el valor de `opcion`. **Solo entonces** decide qué mensaje mostrar. No ejecuta la opción 1 antes de descubrir que la línea realmente decía `1abc`.

Compila ese archivo usando el patrón anterior, con salida `build/opcion` o `build/opcion.exe`. Inicia el programa y escribe `1`:

```text
Opcion: 1 cursos, 2 practica, 0 salir.
Ver cursos.
```

Solo se muestran mensajes; no se abre ningún sitio ni se realiza una acción externa. Con `2`, responde `Ver practica.`; con `0`, `Salir.`; con `12`, `1abc`, `1 ` o una línea vacía, `Entrada invalida.` y finalización con fallo.

Consumir hasta el final de la línea permite que, cuando agreguemos otro intento, la parte inválida no se convierta accidentalmente en la siguiente opción. No usamos `fflush(stdin)` para intentar borrar la entrada.

## 3. Construir una cantidad de varios dígitos

Archivo: [ejemplos/03-cantidad.c](ejemplos/03-cantidad.c). Antes de leer, escribe el contrato:

| Propiedad | Regla de este ejemplo |
|---|---|
| Rango | De 0 a 100 inclusive |
| Sintaxis | Uno a ocho dígitos básicos; ceros iniciales admitidos |
| Espacios y signos | Rechazados, incluso al principio o al final |
| Fracción y exponentes | Rechazados |
| Final de la solicitud | `\n`, o fin de entrada después de los dígitos |
| Línea vacía | Entrada inválida |
| Fin antes del primer byte | Cierre normal sin dato; no se calcula |
| Error de lectura | Fallo; no se usa el valor parcial |

El límite cuenta bytes antes del salto de línea, no caracteres visibles Unicode. Una tecla Enter de la terminal entrega el salto que el programa interpreta como `\n`. Si rediriges archivos con otros finales de línea, un `\r` que llegue como dato se rechaza bajo este contrato; no prometemos normalizar cualquier archivo.

### Acumulación decimal

Para construir 42: primero llega el dígito 4 y `0 * 10 + 4` produce 4. Luego llega 2 y `4 * 10 + 2` produce 42. Necesitamos multiplicar lo anterior por diez para abrir lugar al siguiente dígito.

| Variable | Responsabilidad |
|---|---|
| `valor` | Prefijo numérico construido y todavía dentro de 0–100 |
| `longitud` | Bytes examinados, con contador limitado a 8 |
| `invalida` | Recuerda cualquier violación del contrato |
| `c` | Byte actual o `EOF` |

Lee el archivo completo y localiza dónde se actualiza cada una. Luego traza `42`, `100`, `101` y `12x` a mano.

### Comprobar antes de multiplicar

En este rango concreto, si `valor > 10`, otro dígito produciría más de 100. Si `valor == 10`, solo un dígito cero puede producir 100. El programa comprueba eso **antes** del cálculo:

```c
if (valor > 10 || (valor == 10 && digito > 0)) {
    invalida = true;
} else {
    valor = valor * 10 + digito;
}
```

Así `101` se rechaza antes de almacenar 101, y una entrada de miles de dígitos no provoca una acumulación entera que desborde. No multiplicamos indefinidamente para después comprobar si «salió un número demasiado grande».

Una vez inválida, la línea sigue siendo inválida. El programa continúa consumiéndola hasta su terminador, pero deja de construir el número. Si supera ocho bytes, la bandera se activa y el contador tampoco sigue creciendo sin límite. No almacena la línea completa: utiliza memoria constante para estas variables.

Al terminar revisa error de lectura, ausencia de datos, línea vacía y bandera de invalidez. El cero inicial de `valor` **no prueba** que se haya recibido un cero: hay que comprobar también longitud y estado.

### Prueba guiada

Compila `ejemplos/03-cantidad.c` como `build/cantidad` (o `.exe`). Ejecútalo y escribe `42` seguido de Enter:

```text
Cantidad de 0 a 100, solo digitos (maximo 8).
Cantidad: 42
```

Vuelve a iniciar para cada variante: `0`, `100`, `101`, `12abc`, `-1`, `2.5` y línea vacía. Los valores 0, 42 y 100 se aceptan; 101 y las entradas de sintaxis incorrecta se rechazan. Los ejercicios amplían estas pruebas.

## 4. Reintentar sin repetir los mismos datos inválidos

Archivo: [ejemplos/04-reintentos.c](ejemplos/04-reintentos.c). Retoma las opciones 0–2, con un máximo de tres líneas de intento. Sale al aceptar una opción, al acabar los intentos o al terminar la entrada. Una línea vacía cuenta como intento inválido; `EOF` antes de otra línea termina la sesión y no consume un intento ficticio.

La condición del ciclo reúne los tres motivos para seguir:

```c
while (intentos < max_intentos && !aceptada && !terminado) {
    /* Lectura, consumo de linea, validacion y avance. */
}
```

Son comentarios ilustrativos: el archivo enlazado contiene el cuerpo completo. El contador aumenta una vez por línea recibida, incluyendo líneas inválidas. La bandera `aceptada` registra una opción válida; `terminado`, el cierre de entrada.

Inicia el programa. Escribe `12` y Enter; después `2` y Enter:

```text
Opcion: 1 cursos, 2 practica, 0 salir.
Entrada invalida.
Opcion: 1 cursos, 2 practica, 0 salir.
Opcion aceptada: 2
```

La segunda lectura no reutiliza el `2` de la primera línea. Es tu nueva línea la que se procesa. El ejemplo confirma una elección; no implementa aún un menú que regresa después de ejecutar cada operación.

En Ubuntu y macOS suele poderse señalar fin de entrada con Ctrl+D en una línea vacía. La forma de enviarlo desde una terminal Windows puede variar: no supongas que toda terminal reconoce el mismo atajo. El código también se verifica con entradas finitas redirigidas, sin depender de esas teclas.

## 5. Por qué todavía no utilizamos `scanf("%d", ...)`

Una conversión por formato no demuestra por sí sola que la línea completa tenga la sintaxis exigida. Puede dejar texto pendiente, requiere comprobar cuántas conversiones se realizaron y necesita una estrategia para valores fuera de rango. No basta con repetir una lectura sobre los mismos caracteres inválidos.

Aquí comprobamos explícitamente cada byte dentro de un problema acotado. Eso no significa que debas crear un conversor general a mano para cada aplicación. Más adelante, con arreglos, cadenas y funciones, leeremos líneas y utilizaremos las conversiones de biblioteca con sus comprobaciones de rango y texto sobrante.

La repetición del lector en la solución del recibo es temporal y visible: el siguiente bloque enseñará a extraer responsabilidades a funciones. No necesitas entender una función auxiliar oculta para poder estudiar estos primeros lectores.

## 6. Límites prácticos

Los ciclos de consumo terminan cuando llega salto de línea o fin/error. Con una entrada finita, incluso muy larga, no acumulan sin límite ni se atascan releyendo el mismo byte. En una consola abierta pueden esperar a que completes la línea: no hay un tiempo máximo de espera ni un presupuesto de lectura total. Estos ejemplos no se presentan como protocolos para una red o un servicio expuesto.

Los errores de entrada no deben activar el cálculo. Un prefijo válido seguido de basura, como `12abc`, invalida la solicitud completa. La ausencia de entrada tampoco debe convertirse en cantidad cero.

## Práctica y cierre

Resuelve [EJERCICIOS.md](EJERCICIOS.md). Las [soluciones](SOLUCIONES.md) incluyen una selección de grupo y un recibo calculado solo después de validar la cantidad.

- [ ] Distingo byte, dígito, número y línea completa.
- [ ] Conservo el resultado de `getchar` en `int` y compruebo `EOF`.
- [ ] Distingo fin de entrada, error y una línea inválida.
- [ ] Rechazo texto sobrante antes de utilizar el valor.
- [ ] Compruebo rango y longitud antes de operaciones peligrosas.
- [ ] Verifico que un reintento recibe una línea nueva.
- [ ] Puedo explicar las restricciones del lector y no lo llamo conversor general.

El siguiente bloque desarrollará funciones y la organización de programas pequeños. Aún no está publicado. Antes de avanzar, conserva al menos un caso válido, uno inválido y uno de fin de entrada con sus resultados.
