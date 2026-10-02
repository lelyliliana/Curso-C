# Verificación del primer bloque

Fecha: 2 de octubre de 2026.

## Alcance publicado

- Unidad 00: preparación del entorno, organización de archivos y guías de instalación por sistema.
- Unidad 01: primer programa, secuencia de salida, saltos de línea, diagnóstico y práctica.
- Tres ejemplos correctos, dos soluciones ejecutables y dos fuentes con errores intencionales identificadas como `.c.txt`.

No hay unidades futuras vacías ni enlaces que presenten contenido previsto como si ya estuviera disponible.

## Comprobaciones de código

Entorno utilizado: Ubuntu 24.04, GCC 13.3.0.

Los cinco programas correctos se compilaron con:

```text
-std=c17 -Wall -Wextra -Wpedantic -Werror
```

`-Werror` se utilizó para esta verificación: exige que las advertencias también provoquen un fallo. En los comandos de aprendizaje mantenemos las advertencias visibles sin introducir esa opción adicional.

| Archivo | Comprobación |
|---|---|
| `01-hola.c` | Salida `Hola, mundo!`, seguida de salto de línea |
| `02-presentacion.c` | Tres mensajes en el orden documentado |
| `03-saltos.c` | `UnoDos`, `Tres`, línea vacía y `Fin` |
| `02-tarjeta.c` | Cuatro líneas, separadores y contenido esperado |
| `03-tabla.c` | Cabecera, cuatro filas y espacios exactos |

En todos ellos: compilación sin diagnósticos, salida estándar igual a la prevista, salida de errores vacía y retorno cero.

Los dos casos de diagnóstico fallaron al compilar, como corresponde. Se comprobaron también sus reparaciones: agregar el punto y coma o la comilla faltante restaura una compilación sin diagnósticos y produce el saludo esperado.

## Comprobaciones de documentación

- Se verifican los destinos y anclas de los enlaces internos antes de publicar.
- Las guías explican el lugar de ejecución de cada comando y separan instalar, escribir, compilar y ejecutar.
- Las soluciones utilizan únicamente conceptos introducidos en el bloque.
- Se conserva la diferencia entre salida correcta, compilación exitosa y finalización exitosa.
- No se incluyen binarios, credenciales ni instrucciones editoriales dirigidas a asistentes de IA.

## Límites de esta verificación

La ejecución local se comprobó con GCC en Ubuntu. Los procedimientos de instalación en Windows y macOS se contrastaron con documentación oficial, pero **no se ejecutaron en equipos con esos sistemas**. No se presenta esa revisión documental como una prueba práctica de instalación ni de compilación con Apple Clang.

El bloque utiliza programas de consola de escritorio. No incluye aún compilación para microcontroladores, acceso a periféricos ni aplicaciones completas con entrada del usuario.

[Inicio del curso](../README.md) · [Fuentes](FUENTES.md).
