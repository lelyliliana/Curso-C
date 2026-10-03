# Ejercicios — Unidad 25

[Guía](README.md) · [Soluciones](SOLUCIONES.md) · [Entrega](ENTREGA.md)

## 1. Construcción incremental

Después de una construcción completa, ejecuta make otra vez sin cambios. Luego modifica un comentario en `agenda.c`, reconstruye y anota qué objeto y ejecutables cambian. No atribuyas a make una comprensión semántica del comentario: utiliza dependencias y fechas.

## 2. Dependencias de encabezados

Explica qué objetos deberían reconstruirse si cambia `sensor.h`. Inspecciona un `.d` generado y verifica que contiene la dependencia. Distingue fuente C, encabezado, objeto, archivo de dependencias y ejecutable. Si cambias las opciones sin tocar archivos, ¿por qué conviene limpiar?

## 3. Limpieza y datos

Crea `build/conservar.txt`, construye, ejecuta pruebas y limpia. Comprueba qué queda. Explica por qué `clean` no borra toda la carpeta. Realiza este ensayo solo dentro del proyecto, sin cambiar `BUILD` a una carpeta personal.

## 4. Entrega y revisión

Completa los hitos de [ENTREGA.md](ENTREGA.md). Para cada criterio, enlaza evidencia concreta. Describe un defecto que una prueba de dominio detecta y otro que requiere probar persistencia o interacción. No afirmes pruebas de sistemas que no hayas utilizado.
