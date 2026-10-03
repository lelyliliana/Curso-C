# Unidad 12 — Ejercicios

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

Predice primero, construye después y guarda el resultado. Los datos se cambian en el fuente; no necesitas añadir entrada de teclado. Respeta las capacidades y dominios indicados.

## 1. Resumen y colección vacía

Traza `ejemplos/01-resumen.c`. Predice los resultados con los cinco datos, con solo el primero y con cero datos. Luego cambia los cinco valores a 7: espera suma 35, mínimo y máximo 7, promedio 7.00. Explica por qué inicializar el mínimo en cero sería incorrecto para ese último caso. Prueba un 101 y verifica el rechazo antes del cálculo.

## 2. Primera coincidencia

En `ejemplos/02-busqueda.c` busca sucesivamente 8, 5, 0 y 9. Espera índices 0, 4, 3 y ausencia. Mantén los duplicados de 8. ¿Qué cambia si quitas `break`? Predice también con `usados = 0`. No accedas a `codigos[posicion]` cuando el resultado sea ausencia.

## 3. Filtro

Traza `ejemplos/03-filtro.c` con umbrales 5, 0 y 101. Espera, respectivamente, `{8, 10, 5}`, `{8, 2, 0, 10, 5}` y una colección de salida vacía. Explica por qué el origen avanza aunque no se seleccione un dato. ¿Qué tendría de incorrecto usar `i` para escribir el destino?

## 4. Contar todas las coincidencias

Arreglo de capacidad 6: `{2, 0, 2, 7, 2, 0}`, seis usados. Cuenta todas las apariciones de un valor `buscado` y muestra el resultado. Con 2 espera 3; con 0 espera 2; con 9 espera 0. Con `usados = 0` también espera 0. Comprueba la cantidad antes del recorrido.

## 5. Invertir la parte utilizada

Arreglo de capacidad 5: `{4, 0, 7, 2, 9}`. Invierte los primeros `usados` elementos mediante intercambios y una variable temporal. Con cinco usados espera `{9, 2, 7, 0, 4}`. Con cuatro espera `{2, 7, 0, 4}` al presentar solo esos cuatro; el quinto queda fuera del segmento usado. Con uno conserva 4; con cero no accede ni muestra elementos. No calcules `usados - 1` fuera de una operación cuya condición asegure datos suficientes.

## 6. Informe de visitas

Reutiliza la semana de la Unidad 11: `{3, 0, 5, 2, 0, 4, 1}`, capacidad 7, siete usados. Cada dato utilizado debe estar entre 0 y 100. Calcula:

- Total: 15.
- Días con cero: 2.
- Primer día con mayor cantidad: día 3, con 5 visitas.
- Promedio: 2.14.

Comprueba primero cantidad y valores. El día presentado comienza en 1. Si varios días empatan en el máximo, conserva el primero. Con cero usados muestra total 0 y cero días con cero, pero indica que no hay mejor día ni promedio. Esa colección vacía difiere de una semana completa con siete ceros, que sí tiene siete registros y promedio 0.00.

Prueba también `{5, 5, 0, 0, 0, 0, 0}` con dos usados y un único cero con un usado. Explica los resultados sin confundir la reserva de memoria con los datos del informe.
