# Unidad 09 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Dominio del cálculo

- -1 y 101 se rechazan; no se llaman las funciones de cálculo.
- 0, 1, 9, 10 y 100 se admiten.
- El subtotal máximo es `100 * 125 = 12500`. Incluso con 500 adicionales, el límite superior sería 13000, representable en el rango mínimo de `int`.

Cambiar el precio exige revisar productos, suma y tipos, además de la regla y sus pruebas. La función no aumenta automáticamente su rango porque el precio se edite.

## 2. Estados

0 y 100 son cantidades válidas. Los tres estados nombrados indican ausencia de dato, invalidez o error según la tabla de la guía. `return` finaliza la llamada auxiliar y entrega un resultado al controlador. Solo el controlador en `main` decide el estado final del programa.

Convertir un estado en cero escondería la diferencia entre ninguna entrada, una entrada incorrecta y una compra real de cero artículos. La separación tiene que conservarse hasta la decisión del controlador.

## 3. Refactor

Los dos programas producen los mismos recibos y rechazos bajo el contrato. El envío se calcula en `envio_centavos`. Cambiar la etiqueta visible corresponde a `mostrar_recibo`; no exige tocar el lector ni la regla de envío.

Compara también las salidas de cierre: `Sin datos.` no es una cantidad aceptada. Una línea que empieza con 10 y continúa con abc no genera un recibo en ninguna versión.

## 4. Rango

Fuente: [soluciones/04-rango.c](soluciones/04-rango.c). Utiliza `minimo <= maximo && valor >= minimo && valor <= maximo`. No resta límites ni realiza cálculos con valores extremos; solamente compara.

Las cinco aserciones comprueban fronteras y un intervalo invertido. Se compilan activas; el programa muestra su mensaje solo después de atravesarlas. Eso no demuestra que toda función del curso esté probada: esta ejecución verifica su propia función `en_rango`.

## 5. Dos cantidades

Fuente: [soluciones/05-dos-cantidades.c](soluciones/05-dos-cantidades.c). Un ciclo de dos vueltas llama al mismo lector, interpreta cada resultado y acumula solo cantidades válidas. Cada llamada crea su `valor`, `longitud` e `invalida` desde el inicio. La suma máxima es 200.

Con 2 y 4 imprime 6; con 100 y 100, 200; con 0 y 4, 4. Si la segunda línea es vacía, rechaza esa línea sin imprimir suma. Si termina después de la primera, informa que faltó completar las dos cantidades. Con `2` seguido de salto y `4` seguido de fin, ambas se aceptan: el contrato permite terminar una cantidad mediante fin de entrada después de sus dígitos.
