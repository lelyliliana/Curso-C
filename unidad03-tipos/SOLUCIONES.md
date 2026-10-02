# Unidad 03 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Tipo y significado

Para una cantidad pequeña de estudiantes usamos `int`; para temperatura con fracción, `double`; para una letra básica, `char`. Un nombre completo es una secuencia de caracteres, y no cabe en un solo `char`. También deberemos considerar codificación y longitud al estudiar cadenas.

## 2. Ficha de medición

Fuente completo: [soluciones/02-medicion.c](soluciones/02-medicion.c). Los formatos son `%d`, `%.2f` y `%c`, respectivamente. Con `%.3f`, la segunda línea pasa a ser `Temperatura: 21.750 C`. Cambió la presentación, no el objeto almacenado.

## 3. Reparar el fragmento

```c
double temperatura = 21.75;
char grupo = 'A';
printf("Temperatura: %.2f\n", temperatura);
```

Usamos comillas simples para la letra y un formato apropiado para el `double`. Cambiar a `%.2f` conserva la fracción al mostrar. Convertir con `(int)temperatura` produciría 21 para este valor y perdería la fracción en el resultado convertido. No usaríamos `%d` con el `double` original.

Si introduces este fragmento en `main`, muestra también `grupo` con `%c`: así verificas su contenido y evitas una variable que no se usa.

## 4. Conversión

Fuente completo: [soluciones/04-conversion.c](soluciones/04-conversion.c). Para 6.75 obtenemos 6; para -6.75 obtenemos -6. Se elimina la fracción hacia cero. `medida` sigue mostrando 6.75 o -6.75 según su inicialización: el cast obtiene un nuevo valor sin modificar el original.

## 5. Plataforma

El ejemplo de la guía informa 4 bytes de `int`, 8 bits por byte y rango de -2147483648 a 2147483647 en el entorno probado. Tu informe debe contener los valores de **tu ejecución**, no copiar esos números si son diferentes. `sizeof(char)` sí debe ser 1; eso no fija universalmente ocho bits por byte. `INT_MAX + 1` desborda el tipo entero con signo de esa operación, por lo que no es una prueba con resultado definido.

## 6. Aproximación

Dos cifras visibles no demuestran exactitud. La promoción a `double` conserva el valor aproximado del `float`; no lo reconstruye a partir del decimal original. Para 12.50 podrías guardar 1250 centavos como entero. Aun así, debes elegir un rango suficiente y evitar desbordamientos en los cálculos. En un sistema real también hay reglas explícitas de redondeo al aplicar porcentajes o convertir monedas.
