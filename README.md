# C desde cero

Aprende a escribir, compilar, ejecutar y comprender programas en C, aunque nunca hayas programado.

**Autora:** Leli Liliana Díaz Izquierdo · Ingeniera de Sistemas.

C se utiliza en sistemas operativos, bibliotecas, herramientas y dispositivos. Aprenderlo permite comprender cómo un programa representa datos y utiliza memoria. Esa cercanía también exige cuidado: el compilador no detecta todos los errores y un programa que ejecuta puede producir un resultado incorrecto.

No necesitas conocer C++, Arduino ni otro lenguaje. Necesitas saber crear una carpeta, guardar un archivo y utilizar un navegador. Las primeras unidades explican la terminal y los comandos desde el principio.

## Empieza aquí

1. [Unidad 00 — Preparar el entorno](unidad00-entorno/README.md): identifica tus herramientas, instala el compilador y organiza tus archivos.
2. [Unidad 01 — Tu primer programa](unidad01-primer-programa/README.md): escribe un programa, compílalo, ejecútalo y aprende a corregir errores iniciales.
3. [Unidad 02 — Variables](unidad02-variables/README.md): almacena datos, muestra sus valores y sigue sus cambios.
4. [Unidad 03 — Tipos de datos](unidad03-tipos/README.md): elige representaciones, consulta límites y reconoce pérdidas de información.
5. [Unidad 04 — Expresiones](unidad04-expresiones/README.md): calcula, verifica unidades y construye un recibo en centavos.
6. [Unidad 05 — Decisiones](unidad05-decisiones/README.md): compara, combina condiciones y valida antes de calcular.
7. [Unidad 06 — Ciclos](unidad06-ciclos/README.md): repite con contador, acumulador y final definido.
8. [Unidad 07 — Entrada validada](unidad07-entrada/README.md): comprueba opciones y cantidades completas y gestiona reintentos.

**Contenido publicado:** unidades 00–07, con explicaciones, ejemplos, ejercicios, soluciones y comprobaciones. Puedes comenzar sin esperar al curso completo. El siguiente bloque desarrollará funciones y organización de programas pequeños; todavía no está publicado. El resto del recorrido se desarrollará por bloques completos.

El orden de las unidades 05–07 prepara primero decisiones y ciclos: así puedes comprender la validación y los reintentos antes de recibir datos. La primera entrada numérica tiene un contrato explícito y pequeño; el procesamiento general de líneas y números se ampliará al estudiar funciones, arreglos y cadenas.

## Cómo estudiar

En cada unidad sigue este ciclo:

1. Lee el problema y anticipa qué debería ocurrir.
2. Escribe el ejemplo o abre el archivo correspondiente.
3. Compila y lee los mensajes, incluso cuando parecen advertencias.
4. Ejecuta y compara el resultado con la salida esperada.
5. Modifica una cosa y explica qué cambió.
6. Resuelve el ejercicio antes de consultar su solución.

Si un comando falla, detente en ese paso. Ejecutar más comandos sin comprender el error suele esconder la causa. Guarda tu trabajo antes de experimentar.

Los ejercicios son oportunidades de práctica, no un examen de velocidad. Repetir un ejemplo comprendiendo cada línea vale más que copiar muchos programas sin poder explicarlos.

## Herramientas y criterio técnico

- Archivos de código con extensión `.c`.
- VS Code como editor recomendado; puedes utilizar otro editor de texto plano.
- GCC en Ubuntu y Windows con MSYS2 UCRT64; Clang en macOS.
- C17 como base explícita de los ejemplos. No dependemos del estándar predeterminado de cada compilador.
- Advertencias activadas desde el inicio: `-Wall -Wextra -Wpedantic`.

C y C++ son lenguajes diferentes. Aquí compilamos C con `gcc` o `clang`, no con `g++`. La extensión de VS Code llamada C/C++ sirve para ambos lenguajes; su nombre no convierte este curso en C++.

En los ejemplos iniciales el texto de salida usa caracteres ASCII para evitar que la codificación de una terminal distraiga del aprendizaje. Las explicaciones del curso están en español. Más adelante se estudiará el tratamiento de texto y sus límites.

## Recorrido previsto

Esta tabla orienta el diseño del curso. Solo las unidades del apartado **Empieza aquí** tienen material publicado.

| Etapa | Aprendizaje previsto | Evidencia de aprendizaje |
|---|---|---|
| 1. Primeros pasos | Entorno, compilación, salida, variables, tipos y expresiones | Explicar y modificar un programa pequeño |
| 2. Resolver problemas | Entrada validada, decisiones, ciclos y funciones | Construir una calculadora y un menú con controles |
| 3. Organizar datos | Arreglos, recorridos, cadenas y límites | Procesar una colección sin salir de sus límites |
| 4. Comprender memoria | Direcciones, punteros, duración de objetos y memoria dinámica | Dibujar y justificar el uso de memoria de un programa |
| 5. Construir programas | Estructuras, enumeraciones, módulos, encabezados y archivos | Separar responsabilidades y guardar información |
| 6. Trabajar con calidad | Depuración, pruebas, sanitizadores, Make y portabilidad | Detectar errores y demostrar que una corrección funciona |
| 7. Integrar | Estructuras de datos y proyecto final | Entregar una aplicación con pruebas, documentación y límites conocidos |

La entrada de datos se enseñará con validación. El curso no utilizará `gets`, `fflush(stdin)` ni trucos de pausa dependientes del sistema como solución general. Los punteros se introducirán con dibujos y ejemplos de duración de objetos antes de abordar estructuras dinámicas.

## Organización actual

- [Unidad 00](unidad00-entorno/README.md): guía y tres recorridos de instalación.
- [Unidad 01](unidad01-primer-programa/README.md): explicación, tres ejemplos y práctica gradual.
- [Unidad 02](unidad02-variables/README.md): variables, copias, asignación y datos que no deben cambiar.
- [Unidad 03](unidad03-tipos/README.md): tipos, formatos de salida, precisión, límites y conversiones.
- [Unidad 04](unidad04-expresiones/README.md): operaciones, división, resto, unidades y pequeño proyecto.
- [Unidad 05](unidad05-decisiones/README.md): decisiones, lógica, validación, `switch` y práctica con fronteras.
- [Unidad 06](unidad06-ciclos/README.md): `while`, `for`, `do-while`, acumulación y saltos.
- [Unidad 07](unidad07-entrada/README.md): lectura gradual, línea completa, fin/error, cantidades acotadas y recibo interactivo.
- [Fuentes técnicas](docs/FUENTES.md): referencias del lenguaje y documentación de las herramientas.
- [Verificación](docs/VERIFICACION.md): comprobaciones realizadas y plataformas pendientes.

GitHub permite leer el material en el navegador. Para trabajar con los archivos, la Unidad 00 explica cómo obtener una copia sin requerir conocimientos previos de Git.

**Primer objetivo:** poder decir «sé dónde está mi archivo, con qué comando lo compilo, qué archivo se genera y cómo verifico su resultado».
