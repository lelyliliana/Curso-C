# Ejercicios — Unidad 22

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

## 1. Clasificar el fallo

La variante defectuosa compila, enlaza y termina con estado cero. ¿En qué categoría está el problema? Explica por qué cambiar `%.2f` por `%.4f` no lo corrige. Registra esperado y observado con `{1, 2}`.

## 2. Elegir casos que distinguen

Predice las medias de `{2, 4}`, `{0, 1}`, `{0, 100}` y `{1, 2, 2}` en la implementación correcta y en la defectuosa. Elige el menor conjunto que ya demuestra el defecto, y explica por qué conviene añadir después fronteras y rechazos.

## 3. Un contrato también se depura

Con salida previa 77, comprueba cantidad cero, un dato -1, un dato 101, puntero nulo con cantidad uno y cantidad 1001. No pases una cantidad válida superior a la extensión real del arreglo. Explica qué validaciones se realizan antes de leer datos y qué necesita garantizar el llamador.

## 4. Informe completo

Usa el módulo de números para agregar 0, 25 y 100. Calcula la media con la función corregida. Publica cantidad y media con dos decimales; si falla un agregado o el cálculo, libera y termina con fracaso, sin informe parcial. Entrega comando, salida y una prueba que haya detectado el defecto original.

Si tienes depurador, conserva una observación de total y división antes de la asignación. Si no lo tienes, entrega un seguimiento manual por iteraciones y los resultados de las pruebas: no inventes una sesión ejecutada.
