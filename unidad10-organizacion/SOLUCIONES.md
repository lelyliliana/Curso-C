# Unidad 10 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Responsabilidades

`leer_cantidad` se anuncia en `entrada.h` y se define en `entrada.c`. `total_centavos` se anuncia en `recibo.h` y se define en `recibo.c`. La presentación es un detalle privado de `main.c`; por eso su función está marcada `static` y no se publica en la interfaz del cálculo. Una etiqueta se cambia en la presentación.

## 2. Construcción

Ambas formas producen el mismo programa bajo los casos del enunciado. Los `.o` son productos intermedios y pueden contener referencias pendientes. Cambiar `recibo.c` requiere recompilar su objeto y enlazar de nuevo. Cambiar `recibo.h` requiere recompilar los fuentes que lo incluyen, como `main.c`, `recibo.c` y el programa de pruebas, cada uno para su ejecutable correspondiente.

## 3. Diagnósticos

Sin `entrada.c`, el compilador puede conocer la firma gracias al encabezado, pero el enlace no encuentra la definición de `leer_cantidad`. Reunir aplicación y pruebas incorpora dos definiciones de `main`. No se resuelve quitando un encabezado: debes construir cada ejecutable con sus fuentes apropiados.

Los textos exactos varían con herramienta y versión. Conserva el primero que describa la referencia no resuelta o la definición duplicada y relaciónalo con el comando utilizado.

## 4. Pruebas

Las aserciones de envío con 0, 9 y 10 ejercitan ausencia de compra, cobro y gratuidad. Las de total verifican que esa decisión llega al resultado final. Una frontera 11 haría fallar el caso 10.

No se llama al lector en este ejecutable. Validar que una cantidad entera sea 0–100 es diferente de comprobar que una línea de bytes represente únicamente esa cantidad. Para `10abc` necesitas una prueba del lector o de la aplicación completa.

## 5. Variante completa de la regla

Archivos de solución: [05-recibo.c](soluciones/05-recibo.c) y [05-pruebas.c](soluciones/05-pruebas.c). El primer archivo sustituye solo la implementación de cálculo; el segundo contiene las pruebas de esa variante. Reutilizan el encabezado del proyecto. No son dos proyectos vacíos ni requieren otra copia de `entrada.c`.

Desde `unidad10-organizacion`, con `build` creado, construye primero las pruebas de la variante. En Ubuntu/UCRT64:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Iproyecto soluciones/05-pruebas.c soluciones/05-recibo.c -o build/pruebas_nueva_regla
```

En Windows agrega `.exe` al nombre de salida; en macOS usa `clang`. `-Iproyecto` agrega esa carpeta a la búsqueda de encabezados: las soluciones están en otra carpeta y necesitan encontrar `recibo.h`.

Ejecuta el binario correspondiente. Espera:

```text
Pruebas de nueva regla: OK.
```

Solo después construye la variante interactiva:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Iproyecto proyecto/main.c proyecto/entrada.c soluciones/05-recibo.c -o build/recibo_nueva_regla
```

Aplica los mismos cambios de herramienta y `.exe` por sistema. Ejecuta y prueba los casos de la tabla. **No agregues también `proyecto/recibo.c`**: estarías definiendo dos veces las mismas funciones.

Los casos 10 ahora esperan envío 500 y total 1750 centavos. Se agregan 19/20 para comprobar la nueva frontera. Cero mantiene su regla específica y 100 sigue siendo válido. El contrato de entrada no cambió.

Las pruebas antiguas con la nueva implementación deben detectar un desacuerdo en el caso 10: eso indica una diferencia de comportamiento real. Actualizar las expectativas corresponde aquí al cambio autorizado de regla, no a ocultar un error del programa original.
