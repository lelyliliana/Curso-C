# Unidad 05 — Ejercicios

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

No necesitas teclado todavía: cambia los valores iniciales, guarda y recompila cada variante. Para cada caso anota camino esperado, mensaje y si debe terminar correctamente o rechazar los datos.

## 1. Preguntas y cambios

Con `int plazas = 5;`, predice `plazas == 5`, `plazas != 5`, `plazas > 5` y `plazas >= 5`. ¿Cuál de esas expresiones cambia `plazas`? ¿Qué instrucción sí la cambiaría a 3?

Explica por qué `0 <= plazas <= 20` no valida correctamente el rango.

## 2. Permiso

Modifica `ejemplos/03-permiso.c` para edad 17 o 18 y autorización/documento verdaderos o falsos. Construye una tabla con las ocho combinaciones. Predice si puede participar y si aparece el mensaje de presentar documento.

## 3. Clasificación

Prueba `ejemplos/02-nota.c` con -1, 0, 5, 6, 8, 9, 10 y 11. Justifica las fronteras 5/6 y 8/9. No cambies las reglas hipotéticas por reglas de una institución real.

En `ejemplos/04-seleccion.c`, prueba `'A'`, `'B'` y `'Z'`. ¿Qué instrucción evita ejecutar también el caso B después del A?

## 4. Cajas necesarias

Crea `cajas.c`: objetos entre 0 y 100, capacidad por caja entre 1 y 100. Rechaza los datos fuera de esos rangos antes de dividir. Calcula cajas completas; si hay resto, agrega una caja.

| Objetos | Por caja | Resultado |
|---:|---:|---|
| 0 | 5 | `Cajas necesarias: 0` |
| 4 | 5 | `Cajas necesarias: 1` |
| 5 | 5 | `Cajas necesarias: 1` |
| 17 | 5 | `Cajas necesarias: 4` |
| 100 | 1 | `Cajas necesarias: 100` |
| 17 | 0 | `Datos invalidos.` y finalización con fallo |
| -1 | 5 | `Datos invalidos.` y finalización con fallo |

## 5. División protegida

Crea `division.c` con total entre 0 y 100 y personas entre 1 y 100. Valida antes de convertir y dividir. Con 5 y 2 muestra `Promedio: 2.50`; con 0 y 2, `Promedio: 0.00`; con 5 y 0 rechaza los datos. Explica por qué cero puede ser válido para el total y no para el divisor.

## 6. Política de envío

En este ejercicio el artículo cuesta 1250 centavos, se admiten de 0 a 10 artículos y el envío cuesta 500 centavos. Es gratuito desde 3 artículos. Si no se compran artículos, no se cobra envío. Rechaza cantidades fuera del rango.

Crea `envio.c`, calcula y muestra envío en centavos y total en unidades con dos cifras de centavos. Comprueba:

| Cantidad | Envío | Total |
|---:|---:|---|
| 0 | 0 | `0.00` |
| 1 | 500 | `17.50` |
| 2 | 500 | `30.00` |
| 3 | 0 | `37.50` |
| 10 | 0 | `125.00` |
| 11 | — | `Cantidad invalida.` |

Explica por qué no basta con comprobar solo cantidad 3.
