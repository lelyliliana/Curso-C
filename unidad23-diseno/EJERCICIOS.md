# Ejercicios — Unidad 23

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

## 1. Requisitos y casos

Redacta seis casos de aceptación: agregado válido, duplicado, actualización ausente, borrado intermedio, resumen vacío y límite de cien sensores. Incluye estado esperado y efecto sobre datos; no escribas únicamente «debe funcionar».

## 2. Posición y nombre

Con A, B y C en ese orden, se busca C y se obtiene posición dos. Después se elimina B. ¿Dónde queda C? Explica por qué guardar la posición anterior como identificador permanente sería incorrecto. Comprueba que buscar un nombre ausente conserva una salida previa 99.

## 3. Dominios diferentes

Explica por qué `Catalogo` admite nombres repetidos y `Agenda` los rechaza. Comprueba que A y a son nombres distintos. ¿Dónde cambiarías la regla si se pidiera búsqueda sin distinguir mayúsculas? Señala qué otras operaciones y pruebas habría que ajustar para mantener unicidad consistente.

## 4. Informe filtrado

Construye una agenda con A=0, B=50 y C=100. Muestra solo registros con valor mayor o igual a 50, junto con cantidad encontrada. No cambies la agenda. Usa las funciones del proyecto para agregar y limpia la memoria ante cualquier fallo. Entrega fuente, comando y salida.
