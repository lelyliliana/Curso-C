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

## Editor e instalación

- [Microsoft: C/C++ en Visual Studio Code](https://code.visualstudio.com/docs/languages/cpp).
- [Ubuntu: instalación de compiladores](https://help.ubuntu.com/community/InstallingCompilers).
- [MSYS2: instalación](https://www.msys2.org/).
- [MSYS2: entornos](https://www.msys2.org/docs/environments/).
- [MSYS2: actualización](https://www.msys2.org/docs/updating/).
- [Apple: instalar herramientas de línea de comandos](https://developer.apple.com/documentation/xcode/installing-the-command-line-tools).

Consulta la documentación de tu sistema si cambian los nombres de menús o los instaladores. Las guías se revisaron el 2 de octubre de 2026; los ejemplos de instalación no fijan una versión de GCC ni un nombre de instalador fechado.
