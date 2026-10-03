# Unidad 08 — Ejercicios

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

Para cada función escribe qué recibe, qué devuelve, qué efectos produce y qué valores admite. Después compila cada programa por separado y verifica su salida.

## 1. Seguir una llamada

En `ejemplos/02-resultado.c`, identifica parámetros y argumentos de ambas llamadas. ¿En qué momento vuelve la ejecución a `main`? ¿Qué pasa si eliminas las impresiones y solo llamas a `sumar`?

## 2. Copia y actualización

Predice el ejemplo de copia. Luego crea una función `int descontar_uno(int cantidad)` que devuelva `cantidad - 1` y úsala para actualizar una variable inicializada en 12. Usa argumentos entre 1 y 100. ¿Qué línea del llamador hace que su variable pase a 11?

## 3. Un prototipo no es un cuerpo

Explica las diferencias entre `int duplicar(int numero);`, la definición y la llamada `duplicar(4)`. En una copia de `ejemplos/04-prototipo.c`, deja el prototipo y quita la definición. Intenta construir el ejecutable, pero no ejecutes un binario anterior si falla. ¿Falló por desconocer la firma o por no encontrar la implementación?

## 4. Rectángulo con dos funciones

Crea `rectangulo.c` con `area_rectangulo` y `perimetro_rectangulo`. Reciben dos `double`, devuelven un `double` y no imprimen. `main` presenta los resultados con dos decimales.

Usa longitudes conocidas, finitas, de 0 a 10 metros. Con 3.5 y 2.0: área 7.00 m2 y perímetro 11.00 m. Con 1.0 y 1.0: 1.00 m2 y 4.00 m. Con 0.0 y 2.0: 0.00 m2 y 4.00 m; aquí admitimos ese caso degenerado como ejercicio de fórmula, no como un terreno con área positiva.

## 5. Acumulador local

Crea `int sumar_hasta(int limite)` para límites conocidos de 0 a 100. Su acumulador es local, comienza en cero y utiliza un ciclo. Llama la función con 0, 5 y 100 en un mismo `main`: espera 0, 15 y 5050, respectivamente. Repite la llamada con 5: debe seguir produciendo 15.

## 6. Cajas como cálculo

Crea `int cajas_necesarias(int objetos, int por_caja)` y llama con (0, 5), (5, 5) y (17, 5): espera 0, 1 y 4. No imprimas dentro de la función.

Contrato de este ejercicio: objetos entre 0 y 100 y capacidad entre 1 y 100, comprobados al preparar los casos. No llames con divisor cero. En la siguiente unidad separaremos el control del contrato del cálculo.
