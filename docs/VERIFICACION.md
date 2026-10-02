# Verificación del contenido publicado

Fecha: 2 de octubre de 2026.

## Alcance publicado

- Unidad 00: preparación del entorno, organización de archivos y guías de instalación por sistema.
- Unidad 01: primer programa, secuencia de salida, saltos de línea, diagnóstico y práctica.
- Unidad 02: variables enteras, copias, asignaciones, nombres y `const`.
- Unidad 03: tipos, formatos, precisión, tamaños, límites y conversiones.
- Unidad 04: operaciones, precedencia, división, resto, unidades y recibo en centavos.
- 23 programas correctos: 14 ejemplos y nueve soluciones ejecutables. Se conservan dos fuentes con errores intencionales de la Unidad 01 identificadas como `.c.txt`.

No hay unidades futuras vacías ni enlaces que presenten contenido previsto como si ya estuviera disponible.

## Comprobaciones de código

Entorno utilizado: Ubuntu 24.04, GCC 13.3.0.

Los 23 programas correctos se compilaron con:

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

En todos los programas: compilación sin diagnósticos, salida estándar igual a la prevista, salida de errores vacía y retorno cero. Las salidas de precisión y límites se contrastaron con los valores documentados **para este entorno**; no se exige que sus cifras sean universales.

Se ejecutaron además 21 casos correctos adicionales: cambios de ficha y precisión mostrada, conversión negativa, rectángulo de lados unitarios, promedio uniforme, cajas con cero/pocos objetos, minutos en fronteras de hora y hasta 500, tres variantes del recibo, seguimiento de copias, fragmentos reparados, actualización, resto negativo y dos alternativas de conversión antes de dividir. Los resultados se compararon con salidas previstas independientes del programa probado.

Los dos casos de diagnóstico fallaron al compilar, como corresponde. Se comprobaron también sus reparaciones: agregar el punto y coma o la comilla faltante restaura una compilación sin diagnósticos y produce el saludo esperado.

Se comprobaron seis diagnósticos adicionales mediante compilación, **sin ejecutar los fragmentos incorrectos**: modificación de `const`, redeclaración, argumento de formato ausente, cadena asignada a `char`, formato incompatible y lectura local sin inicialización. Para esta comprobación se usó también `-O1`, que facilita algunos diagnósticos de flujo de datos; las advertencias se trataron como errores. Los mensajes y la capacidad de detectar cada problema pueden variar con compilador y opciones.

## Comprobaciones de documentación

- Se comprobaron 93 enlaces internos, incluidos sus destinos y anclas, antes de publicar este bloque.
- Las guías explican el lugar de ejecución de cada comando y separan instalar, escribir, compilar y ejecutar.
- Las soluciones utilizan únicamente conceptos introducidos en el bloque.
- Se conserva la diferencia entre salida correcta, compilación exitosa y finalización exitosa.
- Se publican fuentes y documentación para estudiantes; se excluyen binarios y credenciales.

## Límites de esta verificación

La ejecución local se comprobó con GCC en Ubuntu. Los procedimientos de instalación en Windows y macOS se contrastaron con documentación oficial, pero **no se ejecutaron en equipos con esos sistemas**. No se presenta esa revisión documental como una prueba práctica de instalación ni de compilación con Apple Clang.

El contenido utiliza programas de consola de escritorio con datos fijos y pequeños. No incluye aún entrada del usuario, compilación para microcontroladores ni acceso a periféricos. Los ejemplos no deben presentarse como programas que validan valores arbitrarios: las restricciones de rango, signo y divisor se explican en cada problema.

[Inicio del curso](../README.md) · [Fuentes](FUENTES.md).
