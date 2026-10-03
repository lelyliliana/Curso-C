# Soluciones — Unidad 22

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Error lógico

El fallo está en la fórmula efectiva, no en compilación, enlace ni un acceso de memoria. Se divide entre enteros antes de convertir a `double`. Con `{1, 2}`, esperado 1.50 y observado 1.00. Cambiar los decimales mostraría 1.0000: conservaría el mismo cálculo incorrecto.

## 2. Casos discriminantes

| Datos | Correcta | Defectuosa |
|---|---|---|
| 2, 4 | 3 | 3 |
| 0, 1 | 0.5 | 0 |
| 0, 100 | 50 | 50 |
| 1, 2, 2 | aproximadamente 1.6666667 | 1 |

Un solo caso con media fraccionaria ya distingue las versiones. Eso no valida el contrato completo; añade vacíos, límites, datos inválidos y salidas preservadas. [pruebas_media.c](proyecto/pruebas_media.c) conserva `{1, 2}` como regresión junto con otras comprobaciones.

## 3. Rechazos

Cantidad cero devuelve `MEDIA_VACIO`; -1 y 101 devuelven `MEDIA_DATO`; puntero nulo con cantidad uno y cantidad 1001 devuelven `MEDIA_ARGUMENTO`. La salida sigue en 77. La cantidad fuera del límite se rechaza antes de recorrer el arreglo: una prueba puede pasar un arreglo corto con cantidad 1001 precisamente porque ese valor está excluido antes del acceso. Eso no autoriza pasar un arreglo corto con cantidad 999.

El llamador debe proporcionar memoria viva, legible, de extensión suficiente para una cantidad admitida, y una salida viva escribible que no invada los datos. Comprobar el puntero nulo no valida una dirección inventada, destruida o insuficiente. Las comparaciones sobre los valores ocurren después de acceder a posiciones cuya existencia es una precondición.

## 4. Programa completo

Fuente: [04-informe.c](soluciones/04-informe.c), [media.c](proyecto/media.c) y [numeros.c](../unidad20-memoria/proyecto/numeros.c).

1. Desde `unidad22-depuracion`, crea `build` como indica la guía.
2. Compila:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic soluciones/04-informe.c proyecto/media.c ../unidad20-memoria/proyecto/numeros.c -o build/informe
```

3. Ejecuta `./build/informe`; en Windows agrega `.exe` y en macOS usa `clang`.
4. Espera `Cantidad: 3; media: 41.67`.

El valor exacto racional es 125/3. El programa calcula una aproximación en `double` y presenta dos decimales; 41.67 es una salida redondeada, no la prueba de representación exacta. Con la fórmula defectuosa habría mostrado 41.00. La lista se libera en la etiqueta de limpieza tanto en éxito como ante rechazo. No se requiere que la función de media sea propietaria de los datos: toma un préstamo solo durante la llamada.
