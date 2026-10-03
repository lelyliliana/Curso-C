# Unidad 16 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Prefijo

`strtol` devuelve un `long` con valor 12 y escribe en `fin` la dirección de la `a`. `&fin` permite modificar la variable puntero del llamador; `*fin` consulta el byte sin convertir. En `"0"`, resultado cero, avance del final y ausencia de `ERANGE` permiten distinguir éxito de falta de conversión. Aun así, el contrato completo debe comprobar sintaxis y dominio.

## 2. Entero

Las fronteras -1000 y 1000, cero y `+12` son válidos; espacios y tabulaciones alrededor se admiten. Un espacio entre dígitos, un punto decimal, un sufijo o ausencia de dígitos se rechazan con `Numero invalido.`. Fin inmediato produce `Fin sin numero.` y cierre normal.

Treinta y dos ceros caben y se convierten a cero; treinta y tres producen `Linea demasiado larga.`. La diferencia pertenece al contrato de almacenamiento, no al valor aritmético. Un byte nulo produce `Linea con byte no admitido.` antes de convertir.

## 3. Decimal

| Caso | Resultado |
|---|---|
| -50, 150, 125 mediante `1.25e2`, `0.5`, `-0.25` | Aceptados dentro del dominio |
| `1e-3` | Válido; con dos decimales se presenta `0.00` |
| `nan`, `inf`, `0x1p2`, `.5`, `1.`, `1,5`, `1e` | Sintaxis rechazada por el contrato |
| `1e999` | Rechazado al no obtener un valor admitido representable |
| `1e-999` | Rechazado por error de rango en el entorno probado |

La biblioteca puede reconocer algunos formatos que nuestra gramática no admite. Un resultado mostrado con dos decimales es una presentación redondeada, no el valor exacto interno. No utilizamos esa presentación para decidir si pertenece al rango.

## 4. Reintentos

Fuente completo: [soluciones/04-reintentos.c](soluciones/04-reintentos.c). Desde `unidad16-lineas`, con `build` creado, construye:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Iproyecto soluciones/04-reintentos.c proyecto/entrada.c -o build/reintentos
```

`-Iproyecto` agrega la carpeta del encabezado a la búsqueda: el controlador está en `soluciones` y la implementación en `proyecto`. En macOS usa `clang`; en UCRT64 usa salida `build/reintentos.exe`. Después ejecuta.

Con las líneas `12abc`, `1001` y `-25`:

```text
Intento 1 de 3: entero de -1000 a 1000.
Numero invalido.
Intento 2 de 3: entero de -1000 a 1000.
Numero invalido.
Intento 3 de 3: entero de -1000 a 1000.
Entero aceptado: -25
```

Tres líneas vacías agotan intentos. La línea larga se consume completa antes del segundo intento: la siguiente línea 7 produce éxito. La función lectora no añade un presupuesto temporal, por lo que consumir una entrada sin final podría seguir esperando.

## 5. Colección

Fuente: [soluciones/05-coleccion.c](soluciones/05-coleccion.c). Primero construye:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Iproyecto soluciones/05-coleccion.c proyecto/entrada.c -o build/lecturas
```

Aplica las mismas variantes de sistema. Después ejecuta y proporciona 0, 10 y 100 en líneas separadas. La última línea es:

```text
Coleccion completa: 3 datos; suma 110.
```

El `while` comprueba capacidad antes de formar `&datos[usados]`. Si la conversión falla, no escribe en esa salida ni aumenta usados. Fin antes de completar indica `Coleccion incompleta.` y devuelve fallo; no presenta suma parcial. El tercer número sin salto final sí completa la colección, porque fin después del contenido termina una línea válida.

## 6. Comprobaciones

Fuente compartido de pruebas: [proyecto/pruebas_entrada.c](proyecto/pruebas_entrada.c). Los rechazos conservan una salida inicial 77. La sintaxis completa se comprueba antes de convertir; después se controla `ERANGE`, el final y el dominio. El reinicio de `errno` ocurre dentro de cada conversión, por lo que un intento previo con desbordamiento no invalida un número posterior correcto.

Leer una línea larga, consumir el resto, distinguir fin y recibir un byte nulo son pruebas del lector o de integración. Convertir una cadena local ya terminada permite probar directamente sintaxis, rango y conservación de salida. Ambas clases se complementan.

## Evidencia de cierre

Conserva comandos, salidas y una clasificación de rechazos por capa: lectura, sintaxis, representabilidad o dominio. Incluye una secuencia de reintentos y una colección que se cierra antes de completarse.
