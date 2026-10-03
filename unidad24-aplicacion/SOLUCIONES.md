# Soluciones — Unidad 24

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Datos finales

El archivo final contiene encabezado `C-AGENDA-1`, cantidad uno y registro `A;25`. Buscar A inicialmente muestra cero; actualizar no agrega un segundo A. Quitar B deja solo A y el resumen da cantidad uno, total 25, mínimo/máximo 25 y media 25.00. Otra sesión empieza vacía hasta cargar explícitamente el archivo.

Si el guardado se rechazó porque la ruta existía, ese archivo no es la evidencia de tu sesión actual. Utiliza una ruta nueva y comprueba `Guardado completo.` antes de afirmar que los datos quedaron conservados.

## 2. Cancelación

`1x` se rechaza como opción. Un nombre de trece caracteres excede el destino de trece bytes porque falta espacio para su terminador; el lector consume toda esa línea y la operación vuelve al menú. No pide valor. Si el nombre era válido, `101` o `25x` cancelan al recibir el valor; después vuelve al menú. No se agrega un prefijo numérico ni un nombre recortado.

## 3. Resultado de archivos

Cero válido produce una agenda vacía. Cien nombres distintos y valores en rango se admiten. Ciento uno, duplicados, byte nulo, truncamiento y datos extra se rechazan con `PERSISTE_FORMATO`. En todos esos rechazos el catálogo anterior continúa igual; la construcción temporal se libera. La versión anterior `C-REG-1` se rechaza por su encabezado: conserva un significado distinto y su propio lector sigue disponible en la Unidad 19.

Cantidad y valores permiten ceros iniciales, pero no signo ni espacios. Un archivo con esos elementos excluidos no es equivalente al formato válido, aunque el conversor interactivo acepte otras gramáticas.

## 4. Programa completo

Fuente: [04-validar.c](soluciones/04-validar.c).

1. Desde `unidad24-aplicacion`, crea `build` según la guía.
2. Compila:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic soluciones/04-validar.c proyecto/persistencia.c ../unidad23-diseno/proyecto/agenda.c ../unidad21-recursos/proyecto/catalogo.c ../unidad17-estructuras/proyecto/sensor.c ../unidad19-archivos/proyecto/archivo.c ../unidad16-lineas/proyecto/entrada.c -o build/validar
```

3. Ejecuta `./build/validar build/sesion-01.txt` con un archivo válido creado por la aplicación. En Windows añade `.exe`; en macOS usa `clang`.
4. Espera `Archivo valido: N registros.`, donde N es la cantidad realmente cargada.
5. Repite con un archivo truncado: informa el rechazo por `stderr` y termina con fracaso.

La salida de fracaso puede consultarse inmediatamente con `echo $?` en Bash o con `$LASTEXITCODE` en PowerShell, antes de ejecutar otro programa. Sin argumento se informa la forma de uso. El validador comparte el parser publicado y solo observa; no reescribe el archivo.
