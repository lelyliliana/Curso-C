# Verificación del contenido publicado

Fecha: 2 de octubre de 2026.

## Alcance publicado

- Unidad 00: preparación del entorno, organización de archivos y guías de instalación por sistema.
- Unidad 01: primer programa, secuencia de salida, saltos de línea, diagnóstico y práctica.
- Unidad 02: variables enteras, copias, asignaciones, nombres y `const`.
- Unidad 03: tipos, formatos, precisión, tamaños, límites y conversiones.
- Unidad 04: operaciones, precedencia, división, resto, unidades y recibo en centavos.
- Unidad 05: comparaciones, lógica, decisiones, validación, selección y salidas tempranas.
- Unidad 06: ciclos, contador, acumulador, saltos y fronteras.
- Unidad 07: lectura por bytes, opciones completas, cantidad de 0–100, fin/error y reintentos; recibo interactivo.
- Unidad 08: funciones, resultados, parámetros por valor, alcance y prototipos.
- Unidad 09: contratos, estados nombrados, extracción del lector, recibo por funciones y dos lecturas independientes.
- Unidad 10: encabezados, guardas, objetos, enlace y pruebas con implementación compartida; variante de política de envío.
- 59 programas o variantes ejecutables: los 43 de las unidades 01–07 y 16 objetivos de ejecución de las unidades 08–10. El material contiene 61 fuentes `.c` y dos encabezados `.h`; en la Unidad 10 algunos fuentes se reutilizan entre ejecutables. Se conservan dos fuentes con errores intencionales de la Unidad 01 identificadas como `.c.txt`.

No hay unidades futuras vacías ni enlaces que presenten contenido previsto como si ya estuviera disponible.

## Comprobaciones de código

Entorno utilizado: Ubuntu 24.04, GCC 13.3.0.

Los fuentes de los programas correctos se compilaron con:

```text
-std=c17 -Wall -Wextra -Wpedantic -Werror
```

`-Werror` se utilizó para esta verificación: exige que las advertencias también provoquen un fallo. En los comandos de aprendizaje mantenemos las advertencias visibles sin introducir esa opción adicional.

### Unidad 01

| Archivo | Comprobación |
|---|---|
| `01-hola.c` | Salida `Hola, mundo!`, seguida de salto de línea |
| `02-presentacion.c` | Tres mensajes en el orden documentado |
| `03-saltos.c` | `UnoDos`, `Tres`, línea vacía y `Fin` |
| `02-tarjeta.c` | Cuatro líneas, separadores y contenido esperado |
| `03-tabla.c` | Cabecera, cuatro filas y espacios exactos |

### Unidades 02–04

| Unidad | Ejemplos y soluciones comprobados | Programas |
|---|---|---:|
| 02 | Valor entero, copia antes y después de actualizar, capacidad fija, ficha e inventario | 5 |
| 03 | Datos de distintos tipos, precisión visible, tamaños y límites, conversiones, medición y conversión independiente | 6 |
| 04 | Operaciones y precedencia, división según operandos, cajas, tiempo, rectángulo, promedio y recibo | 7 |

En los programas de las unidades 01–04: compilación sin diagnósticos, salida estándar igual a la prevista, salida de errores vacía y retorno cero. Las salidas de precisión y límites se contrastaron con los valores documentados **para este entorno**; no se exige que sus cifras sean universales.

Se ejecutaron además 21 casos correctos adicionales: cambios de ficha y precisión mostrada, conversión negativa, rectángulo de lados unitarios, promedio uniforme, cajas con cero/pocos objetos, minutos en fronteras de hora y hasta 500, tres variantes del recibo, seguimiento de copias, fragmentos reparados, actualización, resto negativo y dos alternativas de conversión antes de dividir. Los resultados se compararon con salidas previstas independientes del programa probado.

Los dos casos de diagnóstico fallaron al compilar, como corresponde. Se comprobaron también sus reparaciones: agregar el punto y coma o la comilla faltante restaura una compilación sin diagnósticos y produce el saludo esperado.

Se comprobaron seis diagnósticos adicionales mediante compilación, **sin ejecutar los fragmentos incorrectos**: modificación de `const`, redeclaración, argumento de formato ausente, cadena asignada a `char`, formato incompatible y lectura local sin inicialización. Para esta comprobación se usó también `-O1`, que facilita algunos diagnósticos de flujo de datos; las advertencias se trataron como errores. Los mensajes y la capacidad de detectar cada problema pueden variar con compilador y opciones.

### Unidades 05–07

Los 20 programas nuevos compilaron sin advertencias con las mismas opciones estrictas. Se realizaron 985 ejecuciones, comparando salida completa, ausencia de mensajes inesperados en la salida de errores y estado de finalización esperado:

| Grupo | Ejecuciones | Comprobación |
|---|---:|---|
| Ejemplos y soluciones con datos fijos | 14 | Resultados iniciales documentados de decisiones y ciclos |
| Variantes con datos fijos | 60 | Fronteras, ocho combinaciones de permiso, categorías, selección, divisor inválido, cajas, envío, cero/una/varias vueltas y máximos admitidos |
| Casos de entrada | 905 | Bytes, líneas, cantidad completa, grupo, recibo y reintentos |
| Error de lectura inicial | 6 | Cada lector reconoce una entrada estándar no disponible y finaliza con fallo |

Los lectores de cantidad y recibo se comprobaron con 428 entradas distintas cada uno. Incluyen todos los valores de 0 a 100, con salto de línea, sin salto final y rellenados con ceros hasta ocho dígitos; además, casos inválidos y una muestra reproducible de secuencias de bytes. La aceptación se contrastó con un criterio independiente de sintaxis, longitud y rango.

Se comprobaron también `101`, signos, fracciones, espacios, tabulaciones, bytes nulos y no ASCII, línea vacía, fin inmediato y líneas de 100000 bytes. El texto posterior en la misma línea invalida la solicitud. Una línea posterior no cambia una solicitud ya completa: los programas de una sola solicitud atienden la primera línea.

Los reintentos consumen la línea inválida antes de leer la siguiente, aceptan una opción válida en el tercer intento, detienen tres intentos inválidos y terminan ante fin de entrada. Cada ejecución de prueba tenía un límite externo de tres segundos para detectar bloqueos con entradas finitas; eso no añade un tiempo de espera al programa interactivo.

Los casos válidos y cierres normales finalizaron correctamente; los rechazos de datos y errores de lectura devolvieron fallo intencional. En este entorno `EXIT_FAILURE` corresponde a 1; no se fija ese número como garantía universal. Los mensajes didácticos se imprimen por la salida estándar.

### Unidades 08–10

Se construyeron y ejecutaron 16 programas o variantes a partir de los 18 nuevos fuentes `.c` y dos encabezados. Todos los fuentes correctos compilaron sin diagnósticos con las mismas opciones estrictas. Los módulos se construyeron tanto desde fuentes en un comando como mediante compilación separada a objetos y enlace.

| Comprobación | Alcance |
|---|---|
| Salidas iniciales y casos adicionales con datos fijos | 23 ejecuciones: funciones, copia de parámetros, prototipo, fórmulas, contratos, pruebas de rango, cambio de límites y guardas |
| Equivalencia con la Unidad 07 | 1284 comparaciones de salida completa y estado: 428 entradas para el lector extraído, 428 para el recibo por funciones y 428 para el recibo en módulos |
| Política alternativa de envío desde 20 | 428 entradas, con resultados previstos independientes y casos de frontera |
| Contrato de retorno del lector modular | 428 entradas contrastadas con cantidades 0–100 o los estados de invalidez/fin |
| Dos lecturas del mismo lector | 12 casos: valores válidos, ceros, segunda cantidad sin salto final, invalidez, exceso de longitud y cierre incompleto |
| Error de lectura inicial | Cinco controladores terminan con fallo; una prueba directa comprueba el estado `LECTURA_ERROR` devuelto por la función |
| Construcción por objetos | Cuatro casos de entrada equivalentes a la construcción directa: 0, 10, 100 y 101 |

Las 428 entradas conservan la cobertura del bloque anterior: todos los valores aceptados, distintas terminaciones y ceros iniciales, sintaxis inválida, exceso de rango/longitud, bytes nulos y no ASCII, fin sin datos y líneas largas. Se conserva la diferencia entre fin sin cantidad y cantidad válida cero. Las pruebas de dos lecturas verifican que las variables locales del lector comienzan de nuevo en cada llamada y que no se muestra una suma parcial como completa.

Se realizaron además 16 aserciones externas sobre las funciones publicadas para comprobar llamadas repetidas, cajas en fronteras y rangos con `INT_MIN`, `INT_MAX`, intervalo invertido y límites iguales. No se ejecutaron cálculos con argumentos que violaran sus precondiciones.

Los programas de pruebas del proyecto enlazan la misma implementación de cálculo que el programa interactivo. Se verificaron ocho fallos intencionales de construcción: definición ausente de `duplicar`, lector ausente, dos `main`, cálculos duplicados, firma de encabezado incompatible y tres intentos de construir pruebas con `NDEBUG`. Las guardas admitieron incluir ambos encabezados dos veces en una misma unidad de traducción.

También se comprobó que las pruebas de la política original detectan la implementación alternativa: fallan en la aserción de envío para cantidad 10. Se ejecutó como una prueba negativa controlada, sin producir volcado de memoria. Las pruebas específicas de la nueva regla pasan con su implementación correspondiente.

## Comprobaciones de documentación

- Se comprobaron 205 enlaces internos, incluidos sus destinos y anclas, antes de publicar este bloque.
- Las guías explican el lugar de ejecución de cada comando y separan instalar, escribir, compilar y ejecutar.
- Las soluciones utilizan únicamente conceptos introducidos en el bloque.
- Se conserva la diferencia entre salida correcta, compilación exitosa y finalización exitosa.
- Se publican fuentes y documentación para estudiantes; se excluyen binarios y credenciales.

## Límites de esta verificación

La ejecución local se comprobó con GCC en Ubuntu. Los procedimientos de instalación en Windows y macOS se contrastaron con documentación oficial, pero **no se ejecutaron en equipos con esos sistemas**. No se presenta esa revisión documental como una prueba práctica de instalación ni de compilación con Apple Clang.

El contenido utiliza programas de consola de escritorio, ahora con una primera entrada validada de alcance acotado. No incluye compilación para microcontroladores ni acceso a periféricos. Las restricciones de rango, sintaxis, longitud y divisor se explican en cada problema.

El primer ejemplo de lectura inspecciona solo un byte y se identifica como introducción, no como validador de línea. Los demás lectores consumen hasta salto de línea o fin/error, pero no imponen un tiempo de espera ni un presupuesto total de bytes: una entrada abierta puede mantenerlos esperando. No son protocolos de red ni conversores numéricos generales.

La inyección de error se comprobó al comenzar la lectura en procesos de prueba de Ubuntu. No se afirma haber probado todas las posibles fallas de dispositivos, ni una terminal interactiva de Windows/macOS. La entrada numérica con signo, decimales y conversión general por líneas se desarrollará después de funciones, arreglos y cadenas.

Las funciones de cálculo admiten las precondiciones documentadas, no cualquier entero arbitrario. La interfaz de estados negativos del lector depende de que las cantidades válidas sean no negativas; no se presenta como una solución general para todas las lecturas. Las aserciones de cálculo no sustituyen las pruebas de lectura ni validan datos externos.

[Inicio del curso](../README.md) · [Fuentes](FUENTES.md).
