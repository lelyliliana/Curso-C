# Unidad 09 — Ejercicios

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

## 1. Revisar el contrato

En `ejemplos/01-contrato.c`, prueba cantidades -1, 0, 1, 9, 10, 100 y 101. Identifica cuáles pueden llegar al cálculo y por qué el máximo subtotal es 12500. ¿Cambiar el precio a un número mucho mayor exigiría revisar solo el mensaje o también el rango del contrato?

## 2. Retorno y estado

Explica qué significan los retornos 0, 100, `LECTURA_FIN`, `LECTURA_INVALIDA` y `LECTURA_ERROR` del lector. ¿Por qué `return EXIT_FAILURE;` dentro de una auxiliar no termina por sí solo la aplicación? ¿Por qué no debes tratar un estado negativo como cantidad cero?

## 3. Equivalencia observable

Compara el recibo de la Unidad 07 con `ejemplos/03-recibo.c` usando 0, 1, 9, 10, 100, 00010, 101, 10abc y una línea vacía. Comprueba fin de entrada cuando puedas enviarlo. Conserva mensajes completos y estados de finalización: deben corresponder al mismo contrato.

Localiza la función que calcula el envío. ¿Qué responsabilidad cambiarías si solo quisieras presentar el total con otra etiqueta?

## 4. Rango reutilizable y pruebas

Crea `bool en_rango(int valor, int minimo, int maximo)`. Debe devolver verdadero solo cuando `minimo <= maximo` y el valor esté dentro del intervalo inclusivo. Admite cualquier `int` sin operaciones aritméticas que puedan desbordar. Un intervalo invertido devuelve falso.

Usa `assert` para comprobar (-1, 0, 100), (0, 0, 100), (100, 0, 100), (101, 0, 100) y (5, 10, 0). Espera falso, verdadero, verdadero, falso y falso. Al pasar todas, muestra `Pruebas de rango: OK.`. No coloques efectos necesarios dentro de las aserciones.

## 5. Dos lecturas independientes

Crea un programa que reutilice una sola definición de `leer_cantidad`, sin duplicar su cuerpo. Pide dos cantidades de 0 a 100 y, solo al recibir ambas válidas, muestra su suma. Con 2 y 4 espera `Suma de cantidades: 6`; con 100 y 100, 200.

Si una línea es inválida, informa `Entrada invalida.` y termina con fallo. Si la entrada acaba antes de obtener las dos cantidades, informa `Fin antes de completar dos cantidades.` con fallo. Si hay error, informa `Error de lectura.` con fallo. El cierre es aquí incompleto, aunque en un programa de una solicitud el fin inicial pudiera ser un cierre normal.

Prueba primera cantidad cero, segunda línea vacía, primera línea inválida, fin después de la primera y segunda cantidad válida sin salto final. No muestres una suma parcial como resultado completo.
