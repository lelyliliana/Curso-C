# Unidad 06 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Trazado

| Inicio | Vueltas | Comprobaciones | Valor final |
|---:|---:|---:|---:|
| 1 | 3 | 4 | 4 |
| 3 | 1 | 2 | 4 |
| 4 | 0 | 1 | 4 |

El mensaje `Fin.` aparece una sola vez, fuera del ciclo. Sin actualización y con inicio 1 o 3, la condición permanece verdadera y el recorrido no termina por sí mismo.

## 2. Acumulador

Frontera 1 produce suma 1; frontera 0 produce suma 0 y cero vueltas. Reinicializar a cero en cada vuelta perdería lo anterior: al terminar la última vuelta conservarías solo el último término. El acumulador se declara e inicializa antes del recorrido.

## 3. Controles y saltos

La condición inicial falsa da cero vueltas en `while` y una en `do-while`. Con las condiciones `< 3` y contadores iniciales cero, ambos hacen tres vueltas y terminan con contador 3.

En el `for` de saltos, 2 y 8 son pares: `continue` evita imprimir y pasa a incrementar. El 7 se imprime y luego se incrementa a 8. El 9 entra en `break`: no se imprime, no se hace la actualización de esa vuelta y el ciclo termina.

## 4. Tabla

Fuente: [soluciones/04-tabla.c](soluciones/04-tabla.c). Valida de 1 a 10 y recorre los factores del 1 al 10 inclusive. Cada tabla válida genera diez filas; 0 y 11 se rechazan sin imprimir una tabla parcial. El mayor producto del contrato es 100.

## 5. Suma

Fuente: [soluciones/05-suma.c](soluciones/05-suma.c). `numero` controla el recorrido y `suma` acumula. Para límite 0, la primera condición `1 <= 0` ya es falsa. Para 100 hay cien términos y el resultado es 5050; después del último incremento el contador valdría 101, dentro del rango. La variable de la cabecera deja de estar disponible al terminar el `for`.

Los resultados y rechazos son los de la tabla del enunciado. Los casos cero y uno detectan errores que una prueba solo con cinco términos podría esconder.

## 6. Cuenta

Fuente: [soluciones/06-cuenta.c](soluciones/06-cuenta.c). Usa `restante >= 0` y `restante--`. Tras imprimir cero el contador pasa a -1, un valor representable en `int`, y la siguiente condición es falsa. No se imprime -1.

Con inicio cero hay una fila numérica, `0`, y luego `Despegue.`; con inicio uno, dos filas numéricas. Con diez, once filas numéricas. El caso -1 se rechaza antes de ejecutar el ciclo. No reemplaces sin analizar el contador por un tipo sin signo: sus valores y su comportamiento al decrementar son diferentes.
