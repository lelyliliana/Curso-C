# Unidad 18 — Ejercicios

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

## 1. Nombres y códigos

Predice el primer ejemplo. ¿Por qué 11 no es un estado aunque esté entre 10 y 40? ¿Por qué no se debe usar LISTO, cuyo código es 20, como índice de un arreglo de cuatro textos?

## 2. Tabla de transiciones

Traza la secuencia del controlador. Añade DETENER cuando está ACTIVO y comprueba que vuelve a LISTO. Prueba RESTABLECER desde LISTO: debe rechazarse sin cambiarlo. Incluye ERROR_DETECTADO dos veces y explica su aceptación según la tabla.

## 3. Estado desconocido

Agrega a las pruebas estado `(enum Estado)99`, evento ENCENDER y una salida de estado previamente guardada. Debe rechazar y conservar 99. Prueba también evento 99 desde APAGADO y puntero nulo. No confíes en que declarar el tipo `enum` haga esas comprobaciones por ti.

## 4. Contar una secuencia

Procesa ENCENDER, INICIAR, INICIAR, DETENER y RESTABLECER desde APAGADO. Cuenta aceptados y rechazados y presenta el estado final. Reutiliza `transicionar`, sin copiar sus reglas al controlador. Espera tres aceptados, dos rechazados y LISTO.
