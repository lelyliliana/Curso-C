# Unidad 10 — Ejercicios del proyecto

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

## 1. Seguir una responsabilidad

Localiza dónde se declara y dónde se define `leer_cantidad`. Haz lo mismo con `total_centavos`. ¿Por qué `mostrar_recibo` no está en `recibo.h`? ¿Qué archivo modificarías para cambiar solo una etiqueta de salida?

## 2. Dos formas de construir

Construye el recibo con tres fuentes en un comando. Después construye los tres objetos y enlázalos, siguiendo los pasos de la guía. Comprueba con ambas versiones 0, 10, 100 y 101. Deben corresponder mensajes y estados de salida.

¿Se puede ejecutar `main.o` como el recibo? ¿Qué pasos repetirías después de editar `recibo.c`? ¿Y tras editar `recibo.h`?

## 3. Encontrar una implementación ausente

En un comando de prueba, omite `entrada.c` al construir desde fuentes. Conserva el diagnóstico y no ejecutes el resultado si falla. El encabezado y su prototipo siguen disponibles: ¿por qué falta todavía una implementación?

Después intenta reunir `main.c`, `entrada.c`, `recibo.c` y `pruebas_recibo.c` en un solo ejecutable. Explica el diagnóstico de dos `main`. Restaura los comandos correctos: son prácticas de diagnóstico, no arreglos que deban permanecer en el proyecto.

## 4. Pruebas con la implementación compartida

Construye `pruebas_recibo.c` con `recibo.c`. Identifica una aserción para la ausencia de compra, otra para envío cobrado y otra para gratuidad. ¿Qué pruebas detectan una frontera equivocada, por ejemplo aplicar gratuidad desde 11 en vez de 10?

Explica por qué pasar estas pruebas no basta para afirmar que `10abc` se rechaza como línea completa.

## 5. Una nueva regla de envío

Ahora sí cambia el contrato: envío gratuito desde **20** artículos; cantidad cero sigue sin envío; el precio sigue en 125 centavos y el rango en 0–100. Conserva el lector y la interfaz de funciones.

Haz una variante de `recibo.c` y pruebas que utilicen esa misma variante. Comprueba:

| Cantidad | Envío en centavos | Total |
|---:|---:|---|
| 0 | 0 | `0.00` |
| 9 | 500 | `16.25` |
| 10 | 500 | `17.50` |
| 19 | 500 | `28.75` |
| 20 | 0 | `25.00` |
| 100 | 0 | `125.00` |

No cambies el encabezado para ocultar un desacuerdo ni edites una copia de la regla dentro del archivo de pruebas. ¿Qué aserciones antiguas deben cambiar y qué fronteras nuevas debes agregar?
