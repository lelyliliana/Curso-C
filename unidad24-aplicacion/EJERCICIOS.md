# Ejercicios — Unidad 24

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

## 1. Sesión completa

Agrega A=0 y B=100, busca A, actualiza A a 25, quita B, resume y guarda en una ruta nueva. Inicia otra sesión y carga ese archivo. Conserva entrada utilizada, mensajes y archivo final. Comprueba que el rechazo de un duplicado no cambia el dato existente.

## 2. Rechazo sin prefijos

Prueba opción `1x`, nombre de trece caracteres, valor `101` y valor con sufijo `25x`. Tras cada operación cancelada, introduce una opción válida. Explica cuál será la siguiente solicitud; no envíes un valor cuando el nombre ya canceló el agregado.

## 3. Archivo como contrato

Prueba cantidad cero, cien nombres distintos, ciento uno, nombre duplicado, byte nulo, archivo truncado y una línea adicional. Documenta esperado y observado. Explica por qué cambiar solo la constante del formato antiguo no hubiera conservado su contrato. No uses nombres repetidos para preparar el archivo de cien.

## 4. Validador independiente de sesión

Escribe un programa de consola que reciba una ruta como argumento, cargue mediante `cargar_agenda` y muestre si el archivo es válido y cuántos registros tiene. Libera todo antes de terminar. Un archivo rechazado o una cantidad de argumentos incorrecta debe producir fracaso. No escribas otro parser en el validador.
