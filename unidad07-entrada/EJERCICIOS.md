# Unidad 07 — Ejercicios y recibo interactivo

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

Para cada prueba anota lo enviado, el mensaje del programa y si aceptó, rechazó o cerró sin datos. Reinicia los programas de una sola solicitud para probar otra entrada. No trates tu texto escrito en la terminal como salida producida por el programa.

## 1. Primer byte frente a línea completa

Prueba `ejemplos/01-caracter.c` con `5`, `56`, `A` y línea vacía. ¿Por qué ver `Primer digito: 5` con `56` no valida una entrada de un solo dígito? ¿Por qué almacenar la lectura en `char` sería una mala elección para distinguir `EOF`?

## 2. Una opción completa

Prueba `ejemplos/02-opcion.c` con `0`, `1`, `2`, `3`, `12`, `1abc`, un espacio antes de 1, un espacio después de 1 y línea vacía. Explica por qué consumir el resto debe ocurrir antes de ejecutar la opción.

## 3. Cantidad y reintento

Construye una tabla para `ejemplos/03-cantidad.c` con estas líneas:

```text
0
42
100
00042
00000000
000000000
101
12abc
-1
+1
2.5
 12
12 
```

La última contiene un espacio después de 12; agrega también una línea vacía. Predice resultado y justifica rango, sintaxis y longitud por separado. Traza el estado con `101`: ¿en qué byte se activa `invalida`?

En `ejemplos/04-reintentos.c`, prueba en una misma ejecución `12`, luego una línea vacía y después `2`. También prueba tres líneas inválidas y verifica que no pide una cuarta. Señala fin de entrada cuando tu terminal lo permita: ¿por qué no debe seguir pidiendo indefinidamente?

## 4. Seleccionar grupo

Crea `grupo.c`: admite una sola letra `A`, `B` o `C` como línea completa. Conserva el consumo y control de error del ejemplo de opción. Rechaza minúsculas, espacios, línea vacía y texto adicional. Con B muestra `Grupo aceptado: B`.

Prueba A, B, C, D, b, AB y una línea vacía. Trata fin de entrada antes del primer byte como cierre normal, sin inventar un grupo.

## 5. Recibo con cantidad recibida

Crea `recibo.c` a partir del lector de cantidad. Conserva **todo su contrato**: rango 0–100, uno a ocho dígitos, sin signos ni espacios, fin/error explícitos. No calcules si la entrada es inválida o no contiene datos.

En este nuevo problema el precio unitario es **125 centavos**. El envío cuesta 500, es gratuito desde 10 artículos y también es cero cuando no hay compra. Calcula subtotal y total en centavos, con presentación final de dos cifras para la parte de centavos.

| Cantidad escrita | Subtotal | Envío | Total |
|---|---:|---:|---|
| `0` | 0 | 0 | `0.00` |
| `1` | 125 | 500 | `6.25` |
| `9` | 1125 | 500 | `16.25` |
| `10` | 1250 | 0 | `12.50` |
| `100` | 12500 | 0 | `125.00` |
| `00010` | 1250 | 0 | `12.50` |

Comprueba también `101`, `10abc`, una línea vacía y fin de entrada antes de escribir. Ninguno debe producir un recibo. ¿Por qué el total baja al pasar de 9 a 10 en esta regla hipotética? ¿Por qué la cantidad máxima permite verificar el rango de todos los cálculos?
