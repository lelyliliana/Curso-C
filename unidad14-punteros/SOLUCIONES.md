# Unidad 14 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Dirección

Los valores impresos son 12, 12 y 9. La línea de dirección cambia según ejecución e implementación. `&cantidad` obtiene la dirección; `acceso` contiene esa dirección; `*acceso` accede al entero. `&acceso` apunta a la propia variable puntero, que es otro objeto. Imprimir una dirección no lee automáticamente el objeto señalado.

## 2. Parámetro

El entero `valor` es una copia local. El puntero parámetro es también una copia local, pero contiene una dirección que permite llegar al objeto del llamador. La escritura mediante `*` usa esa dirección; la asignación al parámetro solo cambia su copia. La salida completa está en la guía.

## 3. Descontar

| Valor inicial | Primer intento | Valor después | Segundo intento del ejemplo |
|---:|---|---:|---|
| 100 | Éxito | 99 | Éxito; queda 98 |
| 1 | Éxito | 0 | Rechazo; conserva 0 |
| 0 | Rechazo | 0 | Rechazo |
| -1 | Rechazo | -1 | Rechazo |
| 101 | Rechazo | 101 | Rechazo |

El programa original presenta algunas ramas únicamente cuando hay éxito o rechazo; no imprime una línea por cada intento en todas las variantes. Comprueba el estado y los valores, no inventes mensajes que el controlador no contiene. El caso `NULL` siempre se rechaza sin desreferenciar.

## 4. Permisos y vida

Se imprime 12 y después 7 porque el objeto original es modificable y se actualiza a través de `acceso_fijo`. Escribir mediante `lectura` viola su tipo de acceso; reasignar `acceso_fijo` viola la constancia de esa variable puntero; escribir el entero mediante `acceso_fijo` está permitido.

La dirección de un local ordinario no prolonga su duración. Después de volver de la función no queda un entero vivo al que acceder mediante esa dirección. Retornar el valor copia el dato; una salida por puntero escribe en un objeto que el llamador mantiene vivo.

## 5. Intercambio

Fuente completo: [soluciones/05-intercambio.c](soluciones/05-intercambio.c). Construye ese archivo por separado con el patrón de la guía. Salida:

```text
a: 9; b: 4
Mismo objeto: 9
Rechazo sin cambio: 9
```

El temporal conserva el primer valor antes de sobrescribir. Si los punteros son iguales, las asignaciones siguen dejando ese valor igual. La función comprueba ambas ausencias antes de escribir: no deja un intercambio a medias por un `NULL`.

## 6. Dos salidas

Fuente: [soluciones/06-division.c](soluciones/06-division.c). Salida:

```text
Cociente: 3; resto: 2
Divisor rechazado; conserva 3 y 2.
```

Con cero objetos ambas salidas son cero y el `bool` es verdadero. Con capacidad uno y cien objetos, el cociente es cien y el resto cero. Un rechazo se decide antes de realizar división o escritura, por lo que conserva ambos resultados anteriores.

No se aceptan dos punteros iguales para estas dos salidas: de otro modo una asignación sobrescribiría el resultado de la otra. El contrato de esta función difiere del intercambio, que sí admite el mismo objeto.

## Evidencia de cierre

Entrega una tabla de direcciones simbólicas —por ejemplo, «dirección de cantidad»—, las salidas y un caso rechazado con valores conservados. No es necesario divulgar ni memorizar direcciones numéricas del proceso.
