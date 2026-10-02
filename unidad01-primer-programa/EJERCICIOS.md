# Ejercicios — Primer programa

[Volver a la unidad](README.md) · [Consultar soluciones después de intentarlo](SOLUCIONES.md)

Trabaja con archivos independientes y conserva los ejemplos originales. Para cada ejercicio anota tu salida esperada antes de ejecutar, compila con las advertencias activadas y compara el resultado.

## Ejercicio 1. Predecir sin ejecutar

Dentro de un `main` correcto aparecen estas instrucciones:

```c
printf("A\n");
printf("B");
printf("C\n");
```

1. Escribe exactamente cómo quedaría la salida.
2. Explica cuántas líneas contienen texto.
3. Comprueba tu respuesta en una copia del primer ejemplo.

**Pista:** una llamada a `printf` no agrega un salto por sí sola.

## Ejercicio 2. Tarjeta de presentación

Crea `tarjeta.c` y muestra cuatro líneas:

```text
====================
Nombre: Ana
Meta: aprender C
====================
```

Utiliza tu nombre si lo deseas; no publiques información personal que no quieras compartir. Solo necesitas texto fijo: todavía no pidas datos al usuario.

**Condiciones:** cada mensaje ocupa la línea indicada, todas las líneas terminan con `\n` y no hay diagnósticos al compilar con las opciones de la unidad.

**Pista:** empieza copiando la estructura básica, y luego modifica el cuerpo de `main`. Escribe una llamada por línea para facilitar la lectura.

**Comprueba:** ¿puedes señalar qué parte es tu fuente, dónde está el ejecutable y qué comando lo generó?

## Ejercicio 3. Tabla pequeña de texto

Crea `tabla.c` y reproduce:

```text
Paso | Accion
1    | Escribir
2    | Guardar
3    | Compilar
4    | Ejecutar
```

Utiliza espacios para alinear; no necesitas cálculos, variables ni tabuladores. Aquí la barra `|` es un carácter de texto dentro de la cadena.

**Pista:** primero consigue el contenido correcto. Después revisa los espacios y saltos. Si se deforma la alineación, comprueba que la terminal utiliza una fuente de ancho fijo.

**Extensión opcional:** agrega `5    | Comprobar` sin cambiar las líneas anteriores.

## Ejercicio 4. Dos clases de error

En una copia de tu tarjeta:

1. Omite el punto y coma de una llamada. Compila y registra el primer mensaje.
2. Repara el error y comprueba que compila otra vez.
3. Cambia `Meta: aprender C` por `Meta: aprnder C`. Compila y ejecuta.
4. Explica por qué el segundo cambio puede compilar y aun así estar mal.

No ejecutes un archivo antiguo para concluir que el código con el primer error funciona. Revisa el resultado de la compilación antes de ejecutar.

## Ejercicio 5. Explicar a otra persona

En cinco o seis frases, responde:

- ¿Qué función cumplen VS Code, GCC o Clang y la terminal?
- ¿Por qué editar el `.c` no actualiza automáticamente el ejecutable?
- ¿Qué hace `\n`?
- ¿Qué comunica `return 0;` y qué no demuestra?

No necesitas memorizar una definición. Utiliza tu propia práctica como ejemplo.

## Cómo evaluar tu trabajo

| Criterio | Logrado cuando… |
|---|---|
| Construcción | Compila con las opciones indicadas y sin diagnósticos |
| Resultado | La salida coincide con el contenido y los saltos solicitados |
| Proceso | Puedes repetir guardar, compilar y ejecutar en la carpeta correcta |
| Diagnóstico | Explicas la diferencia entre error de compilación y resultado incorrecto |
| Comprensión | Describes las líneas del programa sin limitarte a leerlas |

Si un criterio no está logrado, identifica el paso concreto y repítelo. No avances solamente porque apareció texto en pantalla.
