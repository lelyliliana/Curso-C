# Ejercicios — Unidad 21

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

## 1. Identificar responsables

Dibuja o describe dos catálogos clonados con un sensor cada uno. Indica cuántos bloques existen y quién los libera. Compara con una asignación ordinaria de la estructura, sin ejecutar una doble liberación. ¿Por qué el préstamo de `mostrar` no se libera?

## 2. El argumento interno

Un catálogo tiene usados dos y capacidad dos. Se agrega una copia de su primer registro pasando la dirección de ese elemento. Explica el orden necesario para que un crecimiento no vuelva inválida la fuente antes de leerla. ¿Puede el llamador conservar ese puntero para usarlo después del agregado?

## 3. Importación y fallos

Prueba un archivo vacío válido (`C-REG-1` seguido de cantidad `0`), uno con dos registros, uno truncado y uno con una línea adicional. Anota código de salida y contenido final. Explica qué ocurre si el archivo es válido, pero falla la reserva del catálogo temporal. No intentes agotar la memoria del equipo.

## 4. Respaldo y restauración

Crea un catálogo con `patio` y valor cero. Clónalo en un respaldo, cambia el valor de trabajo a 100 y muestra ambos. Restaura transfiriendo el respaldo a trabajo. Debe quedar trabajo en cero y respaldo vacío. Todas las rutas de fallo deben limpiar los dos propietarios. Comprueba también que una transferencia sobre el mismo objeto se rechaza sin cambios.
