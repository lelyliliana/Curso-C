# Diagnóstico guiado

[Volver a la unidad](../README.md#10-aprender-de-los-errores)

Estos archivos contienen **errores intencionales**. Terminan en `.c.txt` para separarlos de los ejemplos correctos. Trabaja con una copia en tu carpeta de práctica; no sustituyas tu programa que ya funciona.

## Caso 1. Falta un punto y coma

Abre [01-sin-punto-y-coma.c.txt](01-sin-punto-y-coma.c.txt), copia su contenido y guárdalo como `error.c`.

Compila desde esa carpeta:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic error.c -o error
```

En macOS usa `clang`; en Windows UCRT64 utiliza `-o error.exe`.

La compilación debe fallar. Un diagnóstico habitual menciona que se esperaba `;` antes de `return`. Observa que el problema está al final de la línea de `printf`, aunque el compilador pueda señalar la siguiente.

**Reparación:** agrega `;` después del paréntesis de cierre de `printf`. Guarda, compila sin errores y ejecuta. Debe mostrar `Hola, mundo!`.

## Caso 2. Falta cerrar la cadena

Utiliza una nueva copia de [02-sin-comilla.c.txt](02-sin-comilla.c.txt). Guárdala como `error.c` y repite la compilación.

El primer diagnóstico suele mencionar una comilla de cierre ausente. Puede aparecer una cadena de errores posteriores porque el compilador dejó de interpretar correctamente el resto del archivo.

**Reparación:** cierra la cadena con `"` inmediatamente después de `\n`, antes del paréntesis. La llamada completa debe quedar `printf("Hola, mundo!\n");`.

Corrige el primer problema y compila otra vez antes de intentar arreglar todos los mensajes secundarios.

## Registro breve

Para cada caso escribe:

- comando utilizado;
- primer mensaje del compilador;
- parte del código que lo causó;
- cambio realizado;
- resultado de la nueva compilación y ejecución.

No necesitas que tu mensaje sea idéntico al del curso. Debes reconocer la causa. Los ejemplos de esta carpeta no deben compilar como programas correctos hasta ser reparados.
