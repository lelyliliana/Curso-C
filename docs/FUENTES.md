# Fuentes técnicas

Las explicaciones y actividades de este curso están redactadas para el recorrido de aprendizaje. Estas fuentes permiten consultar las herramientas y comprobar sus instrucciones originales.

## Compilación y estándar

- [GCC: estándares de C admitidos](https://gcc.gnu.org/onlinedocs/gcc/Standards.html).
- [GCC: opciones de advertencias](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html).
- [GCC: opciones de salida y etapas de construcción](https://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html).

Utilizamos `-std=c17` para seleccionar una base de lenguaje explícita. Las advertencias son ayuda de diagnóstico; no constituyen una prueba de que el programa carezca de errores.

## Datos, conversiones y operaciones

- [WG14: borrador público N1570 de C11 (PDF)](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf), como referencia de las reglas fundamentales también utilizadas en este bloque de C17. [Transcripción HTML del mismo documento](https://oifans.cn/docs/c11/n1570.html), consultada para revisar sus apartados. Es una copia alojada fuera del sitio de WG14, no una nueva edición del estándar.
- [GNU: tipos de punto flotante](https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Floating_002dPoint-Data-Types.html).
- [GNU: división y resto](https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Division-and-Remainder.html).
- [GNU: desbordamiento entero](https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Integer-Overflow.html).
- [Linux man-pages: `printf`](https://man7.org/linux/man-pages/man3/printf.3.html), documentación de biblioteca para comprobar formatos de salida. Incluye también extensiones que no utilizamos en el curso.

Apartados de N1570 útiles para consultar: 6.2.5 (tipos), 6.3.1.4 (conversión entre enteros y punto flotante), 6.5.3.4 (`sizeof`), 6.5.5 (división y resto), 6.7.3 (`const`) y 7.21.6.1 (`printf`). No es una lectura obligatoria para comenzar.

El manual de GNU describe su implementación y extensiones. No convertimos sus tamaños habituales en garantías universales: los ejemplos consultan `sizeof`, `CHAR_BIT` y los límites de la plataforma. Se muestran solo formatos compatibles con la base C17 seleccionada.

## Control y entrada

- [GNU: operadores lógicos](https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Logical-Operators.html).
- [GNU: ciclo `while`](https://www.gnu.org/software/c-intro-and-ref/manual/html_node/while-Statement.html).
- [Linux man-pages: lectura con `getchar` y `fgetc`](https://man7.org/linux/man-pages/man3/fgetc.3.html).
- [Linux man-pages: indicadores de fin y error](https://man7.org/linux/man-pages/man3/ferror.3.html).

Para el lenguaje, N1570 incluye 6.5.13–6.5.14 (operadores lógicos), 6.8.4 (selección), 6.8.5 (iteración), 6.8.6 (saltos) y 7.18 (tipos lógicos). En entrada, los apartados 7.21.7 y 7.21.10 describen lectura e indicadores. La Unidad 07 utiliza un lector decimal propio con rango y sintaxis acotados, no una conversión general del estándar.

## Funciones y organización

- [GNU: declaración de funciones y prototipos](https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Function-Declarations.html).
- [GNU: semántica de llamadas y paso por valor](https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Function-Call-Semantics.html).
- [GCC: etapas, objetos y enlace](https://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html).
- [GCC: guardas de inclusión](https://gcc.gnu.org/onlinedocs/cpp/Once-Only-Headers.html).
- [Linux man-pages: `assert` y `NDEBUG`](https://man7.org/linux/man-pages/man3/assert.3.html).

En N1570, 6.5.2.2 describe llamadas; 6.7.6.3, declaradores de funciones; 6.9.1, definiciones; 6.7.2.2, enumeraciones; 6.10, preprocesamiento; y 7.2, aserciones. Los estados nombrados de la Unidad 09 pertenecen al contrato de ese lector acotado; no son códigos universales de la biblioteca de C.

## Arreglos y cadenas

- [WG14: borrador público N1570 (PDF)](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf): 6.2.5 (tipos de arreglos), 6.5.2.1 (índices), 6.5.3.4 (`sizeof`), 6.7.6.2 (declaraciones), 6.7.9 (inicialización), 7.1.1 (cadenas), 7.24.4.2 (`strcmp`) y 7.24.6.3 (`strlen`). Las garantías del conjunto básico de caracteres se describen en 5.2.1.
- [Linux man-pages: `strlen`](https://man7.org/linux/man-pages/man3/strlen.3.html).
- [Linux man-pages: `strcmp`](https://man7.org/linux/man-pages/man3/strcmp.3.html).

Las unidades 11–13 utilizan arreglos de capacidad fija y cadenas terminadas en objetos locales. El lector propio acepta una lista de símbolos y rechaza entradas completas fuera del contrato; no implementa Unicode ni sustituye un lector general por líneas. La longitud en bytes, el espacio reservado y la cantidad de registros utilizados se tratan por separado.

## Punteros, interfaces y conversión completa

- [WG14: borrador N1570 (PDF)](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf): 6.2.4 (duración), 6.3.2.1 (conversión de arreglos), 6.5.2.2 (llamadas), 6.5.3.2 (dirección e indirección), 6.5.6 (aritmética de punteros), 6.7.3 (calificación), 6.7.6.3 (ajuste de parámetros), 7.5 (`errno`), 7.12.3.2 (`isfinite`), 7.22.1.3 (`strtod`) y 7.22.1.4 (`strtol`). La configuración numérica inicial se describe en 7.11.1.1.
- [Linux man-pages: `strtol`](https://man7.org/linux/man-pages/man3/strtol.3.html).
- [Linux man-pages: `strtod`](https://man7.org/linux/man-pages/man3/strtod.3.html).

La documentación de biblioteca actual incluye formatos y versiones más amplios que el contrato del curso. En las unidades 14–16 se mantiene C17, base diez explícita para enteros y una gramática decimal propia, con punto y configuración numérica C. El estado, el contenido restante y el dominio se verifican antes de escribir salidas. La capacidad declarada no certifica automáticamente la extensión real ni la duración de memoria proporcionada por el llamador.

## Estructuras, estados y archivos

- [WG14: borrador N1570 (PDF)](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf): estructuras y enumeraciones (6.7.2), inicialización (6.7.9), flujos y archivos (7.21), apertura y cierre (7.21.5), salida formateada (7.21.6), lectura por caracteres (7.21.7) e indicadores de error (7.21.10).
- [Linux man-pages: modos de apertura de `fopen`](https://man7.org/linux/man-pages/man3/fopen.3.html).
- [Linux man-pages: comprobación de `fclose`](https://man7.org/linux/man-pages/man3/fclose.3.html).

El modo `wx` crea un archivo nuevo con apertura exclusiva; no sustituye un archivo existente. Las unidades 17–19 distinguen copia de registros, códigos enumerados y validación de datos externos. El guardado comprueba escritura y cierre, pero no promete reemplazo atómico ni persistencia física frente a una pérdida de energía. La carga valida todo y comprueba el cierre antes de modificar las salidas.

## Memoria dinámica y depuración

- [WG14: borrador N1570 (PDF)](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf): duración de objetos (6.2.4), tamaños máximos (7.20.3), gestión de memoria y asignaciones de tamaño cero (7.22.3). Se consultan las reglas de `malloc`, `calloc`, `realloc` y `free` con la base C17 explícita del curso.
- [Linux man-pages: asignación y liberación](https://man7.org/linux/man-pages/man3/malloc.3.html). La página también documenta POSIX, extensiones y versiones posteriores de C: no se trasladan al curso las garantías específicas de `errno` ni se utiliza `reallocarray` como función de C17.
- [GDB: sesión de ejemplo oficial](https://sourceware.org/gdb/current/onlinedocs/gdb.html/Sample-Session.html), como referencia de puntos de parada, avance, observación y pila de llamadas.
- [GCC: instrumentación y sanitizadores](https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html), con disponibilidad y límites dependientes del entorno.

Las unidades 20–22 evitan asignaciones de tamaño cero, validan tamaños antes de multiplicar y distinguen propiedad de préstamo. Las herramientas de depuración complementan los contratos y las pruebas de resultados; no demuestran por sí solas corrección ni cubren todas las rutas. El recorrido de GDB se ofrece como práctica opcional, sin presentarlo como una sesión ejecutada en el entorno de verificación.

## Proyecto integrador y construcción

- [GNU make: reglas y recetas](https://www.gnu.org/software/make/manual/html_node/Rule-Introduction.html).
- [GNU make: objetivos de acciones](https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html).
- [GNU make: dependencias automáticas](https://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html).
- [GCC: opciones del preprocesador y dependencias](https://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html).

Las unidades 23–25 reutilizan los módulos del curso y agregan requisitos explícitos de unicidad y persistencia para hasta cien registros. El formato nuevo no modifica el contrato de `C-REG-1`. El Makefile requiere GNU make y comandos del shell indicado; la verificación ejecutada corresponde a Ubuntu. La aplicación utiliza los mismos fuentes de las unidades 23–24, sin una segunda implementación para la etapa de construcción.

## Editor e instalación

- [Microsoft: C/C++ en Visual Studio Code](https://code.visualstudio.com/docs/languages/cpp).
- [Ubuntu: instalación de compiladores](https://help.ubuntu.com/community/InstallingCompilers).
- [MSYS2: instalación](https://www.msys2.org/).
- [MSYS2: entornos](https://www.msys2.org/docs/environments/).
- [MSYS2: actualización](https://www.msys2.org/docs/updating/).
- [Apple: instalar herramientas de línea de comandos](https://developer.apple.com/documentation/xcode/installing-the-command-line-tools).

Consulta la documentación de tu sistema si cambian los nombres de menús o los instaladores. Las guías se revisaron el 2 de octubre de 2026; los ejemplos de instalación no fijan una versión de GCC ni un nombre de instalador fechado.
