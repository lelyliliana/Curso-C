# Unidad 16 — Ejercicios

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

Anota el contrato y el resultado esperado antes de ejecutar. Construye con `entrada.c` cuando el controlador utilice esa interfaz. No pruebes entradas haciendo que un destino declare más memoria de la que realmente tiene.

## 1. Prefijo y final

Sigue `ejemplos/01-prefijo.c`. Identifica qué devuelve `strtol` y qué dirección escribe en `fin`. Explica el papel de `&fin` y de `*fin`. ¿Por qué un resultado 12 no permite aceptar `12abc`? Contrasta con `"0"`, donde cero sí es una conversión válida.

## 2. Entero completo

Construye `proyecto/main_entero.c` junto con `proyecto/entrada.c`. Verifica -1000, 1000, cero, `+12`, tabulación o espacios alrededor, `1001`, `12abc`, `1 2`, `1.0`, signo solo y línea vacía. Distingue fin inmediato de línea vacía. Usa también texto válido sin salto final.

Prueba 32 ceros en una línea y luego 33: el primero representa cero y cabe; el segundo debe rechazarse por longitud aunque su valor matemático seguiría siendo cero. Con un byte nulo recibido tampoco puede aceptarse un prefijo.

## 3. Decimal y rango

Construye `proyecto/main_decimal.c` con el módulo compartido. Verifica -50, 150, `1.25e2`, `0.5`, `-0.25`, `1e-3`, `nan`, `inf`, `0x1p2`, `.5`, `1.`, `1,5`, `1e`, `1e999` y `1e-999`. Clasifica sintaxis, representabilidad y dominio. Explica por qué la impresión de `1e-3` con dos decimales no conserva todos sus dígitos.

## 4. Hasta tres intentos

Crea un controlador que reutilice `leer_linea` y `convertir_entero` para -1000 a 1000. Cada intento consume una línea. Acepta un valor correcto en el primero, segundo o tercero. Tras tres solicitudes rechazadas devuelve fallo. Fin sin número cierra normalmente; un error de lectura detiene con fallo inmediatamente.

Prueba estas secuencias de líneas: `12abc`, `1001`, `-25`; tres líneas vacías; y una línea de 33 letras seguida de `7`. En esta última, el segundo intento debe leer 7, sin residuos de la línea larga.

## 5. Tres lecturas para una colección

Crea un arreglo de capacidad 3 y recibe tres enteros 0–100, uno por línea. Usa `&datos[usados]` como salida de conversión solo mientras `usados < CAPACIDAD`. Incrementa la cantidad después del éxito. Cualquier solicitud inválida detiene con fallo, sin reintentar.

Solo al completar las tres presenta cantidad y suma. Con 0, 10 y 100 espera tres datos y suma 110. Fin tras solo dos válidos debe indicar colección incompleta y no presentar un resumen completo. Un tercer dato sin salto final sigue siendo válido si llega fin después de sus dígitos.

## 6. Salida intacta y pruebas compartidas

En `proyecto/pruebas_entrada.c`, inicializa una salida en 77 y comprueba que `12abc`, `1001` y un entero de 32 nueves no la cambien al rechazarse. Añade decimal `150.1`, exponente incompleto y límites invertidos. Luego prueba un valor válido para demostrar que una conversión anterior fallida no deja `errno` contaminando la siguiente llamada.

Ejecuta las llamadas fuera de `assert`. Explica cuáles son pruebas de conversión y cuáles requieren ejecutar un lector sobre una entrada completa. No escribas otra implementación de conversión en las pruebas.
