# Unidad 11 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Posiciones

La salida inicial es 12, 0 y 10 con los mensajes de la guía. El cuarto elemento tiene índice 3. Asignarle 15 cambia ese elemento, aunque el programa original no lo imprime: agrega una impresión con índice 3 para observarlo. `[4]` intenta seleccionar un quinto elemento que no existe.

## 2. Recorrido

| `i` al comprobar | `i < 4` | Acción |
|---:|---|---|
| 0 | Verdadero | Imprimir 12 |
| 1 | Verdadero | Imprimir 7 |
| 2 | Verdadero | Imprimir 0 |
| 3 | Verdadero | Imprimir 9 |
| 4 | Falso | Salir sin acceder |

Con `<=` la comprobación de 4 sería verdadera y el acceso quedaría fuera del arreglo. El defecto se identifica por los límites; no necesitamos ejecutarlo para justificar la corrección.

## 3. Capacidad

Están cargados los índices 0 y 1, porque `usados` vale 2. La posición 1 contiene cero como dato válido. Los índices 2–4 están reservados e inicializados, pero no forman parte de los registros usados. Omitir la segunda inserción y su incremento deja `usados = 1`: solo se presenta 18.

## 4. Semana

Fuente completo: [soluciones/04-semana.c](soluciones/04-semana.c). Compílalo cambiando el fuente y el ejecutable en el comando de la guía. Salida:

```text
Dia 1: 3
Dia 2: 0
Dia 3: 5
Dia 4: 2
Dia 5: 0
Dia 6: 4
Dia 7: 1
```

`i + 1` solo cambia la presentación. El acceso sigue siendo `visitas[i]`. Hay siete elementos y el contador no se aproxima al máximo de `size_t` en este contrato.

## 5. Copia

Fuente: [soluciones/05-copia.c](soluciones/05-copia.c). Salida:

```text
Indice 0: original 4, copia 4
Indice 1: original 0, copia 9
Indice 2: original 7, copia 7
Indice 3: original 2, copia 2
```

Ambos arreglos tienen cuatro elementos. El ciclo lee y escribe posiciones 0–3. La modificación ocurre después de copiar y afecta al objeto `copia`. `copia = original;` no es una asignación válida de arreglos en C.

## 6. Inserción

Fuente: [soluciones/06-insercion.c](soluciones/06-insercion.c). Salida:

```text
Sin espacio para 9.
Usados: 3
Dato 0: 4
Dato 1: 7
Dato 2: 0
```

La primera propuesta se escribe en 1 y deja dos usados; la segunda se escribe en 2 y deja tres. La tercera encuentra la colección llena: no escribe en 3 ni incrementa. El programa termina correctamente porque rechazar propuestas que no caben forma parte de su tarea, no representa un fallo de construcción o de lectura.

Con `usados = 0` caben 7, 0 y 9 en posiciones 0–2; el 4 inicial deja de pertenecer al estado lógico y se sobrescribe. Con `usados = 3` se rechazan las tres propuestas y se muestran los datos originales 4, 0 y 0. En ambas variantes la cantidad inicial está dentro de 0–3.

## Evidencia de cierre

Entrega tu tabla de índices, comandos de construcción y salida de cada ejercicio. Explica una inserción rechazada sin usar la presencia de un cero como criterio de espacio disponible.
