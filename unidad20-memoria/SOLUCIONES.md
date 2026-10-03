# Soluciones — Unidad 20

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Duración

La variable puntero es automática; su desaparición no devuelve el bloque dinámico. Si era la única referencia propietaria y se pierde sin liberar, se produce una fuga durante la ejecución. `cantidad` es un objeto automático, no un bloque devuelto por el asignador, por lo que `free(&cantidad)` no es válido. El sistema puede recuperar recursos al terminar el proceso, pero eso no resuelve fugas en un programa que sigue funcionando.

## 2. Tamaño y capacidad

Diez elementos requieren `10 * sizeof *datos` bytes, después de verificar que el producto es representable. `sizeof datos` mide la variable puntero. Para usados tres, se pueden leer índices 0, 1 y 2; los otros reservados aún no contienen datos publicados. Pedir capacidad dos conserva la reserva existente. Pedir `SIZE_MAX` se rechaza por los límites del módulo sin solicitar memoria ni modificar la lista.

## 3. Secuencia

Con la política actual: 0 deja usados 1/capacidad 2; 100 deja 2/2; 25 deja 3/4. -1 y 101 se rechazan antes de crecer. Reservar cero no asigna ni reduce. `liberar_numeros` pone el propietario a `NULL`; una segunda llamada termina en `free(NULL)`. Eso no permite liberar nuevamente una copia del puntero antiguo ni convierte los préstamos previos en válidos. Puedes ampliar [pruebas_numeros.c](proyecto/pruebas_numeros.c) con esos dos rechazos.

## 4. Programa completo

Fuente: [04-entrada.c](soluciones/04-entrada.c), con [numeros.c](proyecto/numeros.c) y [entrada.c](../unidad16-lineas/proyecto/entrada.c).

1. Desde `unidad20-memoria`, crea `build` como explica la guía.
2. Compila los tres fuentes:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic soluciones/04-entrada.c proyecto/numeros.c ../unidad16-lineas/proyecto/entrada.c -o build/entrada
```

3. Ejecuta `./build/entrada`. En Windows añade `.exe` en compilación y ejecución; en macOS usa `clang`.
4. Escribe `3`, pulsa Enter y escribe `0`, `25`, `100`, cada uno seguido de Enter. Al final obtendrás `Cantidad: 3; total: 125`.
5. Repite con `0`: no pide valores y muestra cantidad y total cero.
6. Repite con `3` y un valor; finaliza la entrada con Ctrl+D en una línea vacía en Ubuntu/macOS, o Ctrl+Z seguido de Enter en una consola Windows que lo admita. Se informa `Coleccion incompleta.` y termina con fracaso. También se puede probar redirigiendo un archivo de texto truncado.

Una cantidad como `11` o `3x` se rechaza antes de reservar. Un valor inválido, una línea excesiva, fin/error o fallo de crecimiento liberan la colección y no publican suma parcial. La suma utiliza `unsigned long`; incluso el límite de 1000 valores de 100 del módulo cabe en el mínimo garantizado para ese tipo. No se usa una suma `int` de 100000 que fallaría en plataformas con enteros pequeños.
