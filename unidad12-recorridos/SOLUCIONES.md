# Unidad 12 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Resumen

Con los cinco datos: cantidad 5, suma 25, mínimo 0, máximo 10 y promedio 5.00. Con un dato: cantidad 1, suma 8, ambos extremos 8 y promedio 8.00. Con cero: mensaje de ausencia, sin cálculo de extremos ni división.

Con cinco sietes, el mínimo debe ser 7: un cero inicial ajeno a los datos nunca sería reemplazado por un valor mayor al calcular el mínimo. Inicializar desde el primer dato real evita ese error. Un 101 utilizado produce `Lectura fuera de rango.` y finalización con fallo. Si el 101 estuviera fuera del segmento usado, no participaría en el resumen.

## 2. Búsqueda

Con 8 se devuelve índice 0; con 5, 4; con 0, 3; con 9, ausencia. Quitar `break` conserva la última coincidencia: para 8 sería índice 2. Ese resultado podría ser válido para otra tarea, pero incumple la que exige la primera.

Con cero usados el ciclo no entra y `posicion == usados` sigue indicando ausencia. La rama de ausencia evita leer `codigos[0]` como si fuera un registro cargado.

## 3. Filtro

Los tres umbrales producen tres, cinco y cero seleccionadas. Escribir en el índice de origen dejaría huecos: por ejemplo, 10 acabaría en 3 aunque fuera el segundo seleccionado. Recorrer después solo tres usados no mostraría la colección esperada. Escribir en `seleccionados` mantiene un segmento continuo de registros.

## 4. Conteo

Fuente completo: [soluciones/04-conteo.c](soluciones/04-conteo.c). Salida inicial:

```text
Coincidencias de 2: 3
```

El contador comienza en cero y aumenta solo ante igualdad. A diferencia de la búsqueda de la primera coincidencia, no utiliza `break`. Cambiar el buscado a 0 produce 2; a 9 produce 0. Con cero usados conserva cero sin acceder. La cantidad mayor que seis se rechaza.

## 5. Inversión

Fuente: [soluciones/05-invertir.c](soluciones/05-invertir.c). Salida inicial:

```text
Usados: 5
Valor: 9
Valor: 2
Valor: 7
Valor: 0
Valor: 4
```

Con cuatro usados intercambia 0/3 y 1/2. Con uno o cero, `usados / 2` vale cero y no se ejecuta la resta del índice opuesto. La copia temporal conserva el primer valor de cada pareja. Solo se modifica la parte utilizada del arreglo.

## 6. Informe

Fuente: [soluciones/06-informe.c](soluciones/06-informe.c). Salida:

```text
Dias: 7
Total: 15
Dias con cero: 2
Mejor dia: 3 (5 visitas)
Promedio: 2.14
```

Antes de sumar se validan todos los registros utilizados: el total máximo es 700 y cabe en `int`. El índice `mejor` comienza en 0, pero no se usa para leer hasta que un recorrido tiene datos. La comparación estricta `>` conserva el primer máximo en un empate. La impresión añade uno para presentar el día.

| Variante | Total | Días con cero | Mejor día | Promedio |
|---|---:|---:|---|---|
| Dos usados, valores 5 y 5 | 10 | 0 | Día 1, cinco visitas | 5.00 |
| Un usado con valor cero | 0 | 1 | Día 1, cero visitas | 0.00 |
| Siete usados, todos cero | 0 | 7 | Día 1, cero visitas | 0.00 |
| Cero usados | 0 | 0 | No hay | No hay |

Con cero usados imprime `Sin mejor dia ni promedio.` después de las tres primeras líneas. No usa un valor artificial para fingir un máximo existente. Un dato inválido produce `Visitas fuera de rango.` y finalización con fallo, sin presentar un informe parcial.

## Evidencia de cierre

Conserva el código, comandos, salidas y una tabla de seguimiento. Compara explícitamente una colección vacía con una colección que contiene un cero y justifica el acceso al máximo en cada caso.
