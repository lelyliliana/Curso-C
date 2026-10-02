# Unidad 03 — Ejercicios

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

## 1. Elegir y justificar

Elige un tipo para cada dato: cantidad de estudiantes, temperatura con fracción, letra de grupo. Explica por qué un `char` no es la opción para guardar el nombre completo de una persona. No basta con copiar una tabla: describe qué información necesitas conservar.

## 2. Ficha de medición

Crea `medicion.c` con `int muestras = 4;`, `double temperatura = 21.75;` y `char grupo = 'A';`. Imprime:

```text
Muestras: 4
Temperatura: 21.75 C
Grupo: A
```

Cambia el formato de la temperatura a `%.3f`, sin modificar su variable. Predice la nueva línea y comprueba que el fuente conserva la misma inicialización.

## 3. Corregir el formato

Este fragmento es incorrecto: **no lo ejecutes**. Identifica ambos errores y escribe las líneas corregidas:

```c
double temperatura = 21.75;
char grupo = "A";
printf("Temperatura: %d\n", temperatura);
```

¿Por qué cambiar el formato es diferente de convertir la temperatura a entero?

## 4. Convertir y conservar

Crea `conversion.c` con `double medida = 6.75;` y una variable `int parte_entera` que reciba una conversión explícita. Muestra ambas:

```text
Medida: 6.75
Parte entera: 6
```

Repite con `-6.75`. ¿La parte entera es -6 o -7? ¿Cambió `medida`? Conserva las dos salidas; no uses valores fuera del rango de `int`.

## 5. Describir tu plataforma

Compila y ejecuta `ejemplos/03-limites.c`. Anota compilador, tamaño de `int`, bits por byte, `INT_MIN` e `INT_MAX`. Explica por qué no puedes exigir que otra plataforma entregue la misma salida, y por qué no usarías `INT_MAX + 1` como prueba.

## 6. Exactitud y presentación

Ejecuta `ejemplos/02-precision.c`. ¿Mostrar `0.10` demuestra que `double` almacenó 0.1 exactamente? ¿Promocionar un `float` a `double` recupera los dígitos perdidos? ¿Qué unidad entera propondrías para representar exactamente una cantidad monetaria de 12.50, y qué cuidado seguiría siendo necesario?
