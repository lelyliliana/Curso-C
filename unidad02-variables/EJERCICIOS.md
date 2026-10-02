# Unidad 02 — Ejercicios

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

Intenta cada actividad antes de abrir las soluciones. Para los programas entrega el fuente, la salida esperada y una frase que explique lo aprendido. Compila con las advertencias indicadas en la guía.

## 1. Seguir una copia

Sin ejecutar, anota el estado después de cada línea y predice la salida:

```c
int original = 4;
int copia = original;
original = 7;
printf("%d %d\n", original, copia);
copia = 2;
printf("%d %d\n", original, copia);
```

¿Qué instrucción faltaría para que `copia` reciba el valor actual de `original`?

## 2. Elegir nombres

Clasifica `total_libros`, `3mesas`, `return`, `edad` y `mi edad` como válidos o inválidos. Luego explica por qué `edad` y `Edad` no designan necesariamente el mismo objeto.

## 3. Una ficha con datos

Crea `ficha.c` con las variables `edad` y `lecciones`, inicializadas en 19 y 2. Muestra sus valores con `%d`; no escribas los números directamente dentro del mensaje.

```text
Edad: 19
Lecciones completadas: 2
```

Cambia **solo la inicialización** de `lecciones` a 3, guarda y recompila. La segunda línea debe cambiar a `Lecciones completadas: 3`.

## 4. Inventario y registro anterior

Crea `inventario.c`: `existencias` comienza en 15 y `registro_anterior` recibe una copia. Actualiza `existencias` a 11. Imprime el estado anterior y el actual. Después actualiza el registro y muéstralo.

```text
Registro anterior: 15
Existencias actuales: 11
Registro actualizado: 11
```

No necesitas restar ni leer teclado. Explica qué cambiaría si copiaras el registro **después** de actualizar las existencias.

## 5. Reparar sin adivinar

Estos son fragmentos incorrectos, no programas para ejecutar. Corrige cada uno por separado y explica la causa:

```c
int mesas = 3;
int mesas = 5;
```

```c
int libros;
printf("%d\n", libros);
```

```c
int sillas = 12;
printf("Sillas: %d\n");
```

En el segundo caso sabemos que hay 8 libros. No justifiques una corrección diciendo «cualquier número sirve».

## 6. Decidir qué puede cambiar

Una sala tiene capacidad fija de 20 personas y hoy hay 12 asistentes. Escribe las dos declaraciones y justifica dónde usarías `const`. ¿Qué harías si mañana el número de asistentes fuera diferente? ¿Y si el dato inicial de capacidad estaba mal escrito en el fuente?
