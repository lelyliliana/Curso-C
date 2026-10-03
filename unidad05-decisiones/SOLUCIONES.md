# Unidad 05 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Comparaciones

Los resultados son 1, 0, 0 y 1, respectivamente. Ninguna comparación cambia `plazas`; `plazas = 3;` sí lo hace. El rango encadenado compara primero 0 con plazas y después compara ese resultado 0/1 con 20, por lo que no expresa la intención. Usa `plazas >= 0 && plazas <= 20`.

## 2. Permiso

| Edad | Autorización | Documento | Puede participar | Mensaje de documento |
|---:|---|---|---|---|
| 17 | false | false | No | Sí |
| 17 | false | true | No | No |
| 17 | true | false | No | Sí |
| 17 | true | true | Sí | No |
| 18 | false | false | No | Sí |
| 18 | false | true | Sí | No |
| 18 | true | false | No | Sí |
| 18 | true | true | Sí | No |

El segundo `if` es independiente: además de negar la participación puede explicar que falta documento. La autorización no elimina el requisito de documento.

## 3. Nota y selección

| Nota | Mensaje | Finalización |
|---:|---|---|
| -1, 11 | `Nota invalida.` | Fallo |
| 0, 5 | `Necesita repasar.` | Correcta |
| 6, 8 | `Aprobado.` | Correcta |
| 9, 10 | `Nivel alto.` | Correcta |

Los umbrales son inclusivos: 6 entra en aprobado y 9 en nivel alto. El valor inválido no recibe una categoría. En `switch`, A muestra `Grupo A: manana.`, B muestra `Grupo B: tarde.` y Z muestra `Grupo desconocido.` con fallo. `break` evita continuar al siguiente caso después del A.

## 4. Cajas

Fuente: [soluciones/04-cajas.c](soluciones/04-cajas.c). El cociente cuenta cajas completas; un resto distinto de cero requiere una adicional. Con cero objetos, cociente y resto son cero y no se añade ninguna. El divisor se valida antes de `/` y `%`.

El resultado máximo es 100 cajas, dentro del rango de `int`. Las validaciones no solo impiden dividir por cero: también descartan negativos y valores fuera del contrato.

## 5. División

Fuente: [soluciones/05-division.c](soluciones/05-division.c). Rechaza fuera de rango mediante una salida temprana y convierte `total` antes de dividir. Un total cero representa ninguna unidad para repartir; un divisor cero no representa un grupo por el cual se pueda hacer esta división.

## 6. Envío

Fuente: [soluciones/06-envio.c](soluciones/06-envio.c). Tras validar, inicializa envío en 500 y lo cambia a cero si `cantidad == 0 || cantidad >= 3`. El total se calcula después de esa decisión.

Los casos del enunciado ejercitan ninguna compra, envío cobrado, frontera de gratuidad, máximo válido y rechazo. Solo el caso 3 no detectaría un cobro indebido cuando la cantidad es cero ni una aceptación incorrecta de 11. El máximo del subtotal es 12500; incluso sumando 500 sigue siendo representable en un `int` de rango mínimo estándar.
