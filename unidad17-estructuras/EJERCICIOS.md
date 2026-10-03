# Unidad 17 — Ejercicios

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

## 1. Miembros y copias

Traza los dos ejemplos. Distingue la modificación de un miembro, la copia del registro y el parámetro por valor. Explica por qué cambiar la primera letra de la copia no cambia el original. ¿Qué sería distinto si el miembro del nombre fuera un puntero?

## 2. Crear sin cambios parciales

Construye el proyecto y sus pruebas. Añade nombre vacío, doce letras, trece letras, un espacio, un guion, lecturas -1, 0 y 101. Ante rechazo debe conservarse el nombre y el valor previos. No obtengas una cadena inválida leyendo más allá del miembro.

## 3. Colección de sensores

Prepara tres registros: patio 25, salon 0 y taller 100. Valida todos antes de mostrar y calcula total 125. Construye como programa independiente enlazando `sensor.c`. Luego cambia una lectura a 101 y verifica rechazo sin informe parcial.

## 4. Terminador y representación

En las pruebas crea un registro con trece letras permitidas y ningún terminador dentro del miembro. Espera rechazo del validador sin llamar a `strlen` ni `%s` sobre ese nombre. Explica por qué los bytes de relleno no deben decidir si dos sensores significan lo mismo.
