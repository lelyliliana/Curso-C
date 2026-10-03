# Unidad 07 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Primera lectura

Con 5 o 56 el primer ejemplo informa `Primer digito: 5`; con A o línea vacía, `El primer byte no es un digito.`. Solo examinó un byte: no revisó que el resto de la línea estuviera vacío. `int` conserva el resultado de la lectura y el indicador `EOF`; no lo estrechamos a `char` antes de compararlo.

## 2. Opción

0, 1 y 2 producen `Salir.`, `Ver cursos.` y `Ver practica.`. Las demás líneas del ejercicio se rechazan con `Entrada invalida.`. Un espacio también es un byte adicional. Verificar solo el primer carácter permitiría una opción aparente en una línea que no cumple el contrato.

La línea vacía se detecta sin leer otra línea para completarla. Fin antes de cualquier byte cierra normalmente; fin justo después de una opción válida también la completa bajo el contrato.

## 3. Cantidad y reintentos

| Entrada | Resultado |
|---|---|
| `0` | Cantidad 0 |
| `42` | Cantidad 42 |
| `100` | Cantidad 100 |
| `00042` | Cantidad 42 |
| `00000000` | Cantidad 0: ocho dígitos admitidos |
| `000000000` | Rechazada: nueve bytes |
| `101` | Rechazada: fuera de rango |
| `12abc`, `-1`, `+1`, `2.5`, espacios iniciales/finales | Rechazadas: sintaxis |
| Línea vacía | Rechazada: falta el dato |
| Fin de entrada sin bytes | Cierre con `Sin datos.`; sin cantidad |

Para 101: el primer dígito forma 1; el segundo forma 10; el tercero, 1, cumple `valor == 10 && digito > 0`, por lo que activa la bandera **antes** de multiplicar y sumar. No se acepta el prefijo 10 como sustituto del dato completo.

En reintentos, `12` consume toda su línea y falla; la vacía cuenta como segundo intento inválido; 2 se acepta en el tercero. Tres líneas inválidas producen `Limite de intentos alcanzado.` con fallo. Fin antes de otra línea produce `Fin de entrada.` y termina normalmente; no se trata como un nuevo intento para repetir eternamente.

## 4. Grupo

Fuente: [soluciones/04-grupo.c](soluciones/04-grupo.c). Cambia las opciones aceptadas a A, B y C, pero conserva lectura en `int`, revisión de fin/error, línea vacía y consumo del resto. Para rechazar cualquier otro valor usa `grupo != 'A' && grupo != 'B' && grupo != 'C'`; además rechaza `extra`.

Solo A, B y C se aceptan. D, b, AB y vacío fallan. No se intenta corregir automáticamente una minúscula: el contrato exige mayúscula. Si quisiéramos otra política tendríamos que escribirla y comprobarla.

## 5. Recibo

Fuente: [soluciones/05-recibo.c](soluciones/05-recibo.c). Conserva el lector completo y agrega el cálculo **después** de sus comprobaciones. El envío empieza en 500 y cambia a cero con `valor == 0 || valor >= 10`.

Las salidas de subtotal, envío y total son las de la tabla del ejercicio. Con 9 el envío se cobra y el total es 16.25; con 10 se elimina y queda 12.50. Es consecuencia de esta política hipotética, no un error de resta ni una regla comercial universal.

Todos los valores aceptados están entre 0 y 100. El subtotal no supera 12500 y, aun suponiendo 500 de envío, el total no superaría 13000: ambos caben en el rango mínimo de `int`. La multiplicación se realiza después de validar el dato. La entrada 101 o `10abc` no produce subtotal, envío ni total, y un cierre sin datos no se convierte en una compra de cantidad cero.

La lectura aparece repetida para que puedas estudiar este programa completo con lo que ya sabes. Cuando aprendamos funciones, separaremos lectura, validación y cálculo para reutilizar el lector con una sola implementación.
