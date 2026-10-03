# Unidad 08 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Llamadas

Los parámetros son `a` y `b`. Los argumentos de la primera llamada son los valores de `libros` y `revistas`; los de la segunda, 2 y 5. `return a + b;` devuelve 7 y la ejecución continúa donde el llamador necesita ese resultado. Sin impresiones no aparece texto: calcular no implica mostrar.

## 2. Actualizar mediante un resultado

```c
int descontar_uno(int cantidad)
{
    return cantidad - 1;
}
```

Dentro de `main`:

```c
int cantidad = 12;
cantidad = descontar_uno(cantidad);
printf("Cantidad: %d\n", cantidad);
```

La asignación del llamador conserva el 11 devuelto. La función no cambia directamente su variable. Estos fragmentos se colocan en un archivo completo con `<stdio.h>`, definición antes de `main` y `return 0;` al final de `main`.

## 3. Firma e implementación

El prototipo anuncia cómo llamar; la definición implementa la tarea; la llamada la ejecuta. Al quitar la definición, el compilador todavía conoce la firma y puede compilar la llamada, pero el enlace no encuentra `duplicar`. Guarda el diagnóstico como evidencia, y restaura la definición para obtener nuevamente el ejecutable correcto.

## 4. Rectángulo

Fuente completo: [soluciones/04-rectangulo.c](soluciones/04-rectangulo.c). Las funciones devuelven fórmulas y `main` imprime. La separación permite probarlas sin introducir teclado ni texto dentro del cálculo. Los casos y unidades son los del enunciado.

## 5. Acumulador

Fuente: [soluciones/05-suma.c](soluciones/05-suma.c). `suma` se crea e inicializa dentro de cada llamada. Las llamadas producen 0, 15 y 5050. Repetir 5 devuelve otra vez 15, no 30 ni 5065. El contrato de 0–100 mantiene seguros tanto el acumulador como el contador.

## 6. Cajas

Fuente: [soluciones/06-cajas.c](soluciones/06-cajas.c). Devuelve el cociente y agrega una caja si hay resto. Los argumentos del programa cumplen el contrato: no confunde un resultado válido cero con un error y no prueba divisiones inválidas. Pasar un dato por valor no valida su significado; el siguiente bloque de contratos hace visible esa responsabilidad.
