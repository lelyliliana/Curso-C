# Soluciones — Unidad 21

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Propiedad

Una clonación no vacía produce dos bloques independientes. Cada catálogo libera su propio bloque. Una asignación común produciría dos estructuras con la misma dirección; no establece un segundo bloque ni un segundo derecho a liberarlo. `mostrar` observa un objeto automático que pertenece a la duración de `main`, por lo que no llama `free`.

## 2. Orden

Se valida el registro y se copia completo a una variable local. Después se crece y, al conseguir la reserva, se escribe desde la copia. [agregar_sensor](proyecto/catalogo.c) hace exactamente eso. Tras un `realloc` exitoso el puntero anterior no se utiliza, incluso si la dirección parece idéntica. El llamador recupera un nuevo acceso desde el catálogo.

## 3. Carga

Con cantidad cero y fin correcto, la carga reemplaza el destino anterior por vacío sin reservar. Dos registros válidos reemplazan el catálogo por ambos. Un archivo truncado o con línea adicional produce `CAT_ARCHIVO` y conserva `anterior 77` en el controlador. Un fallo de reserva después de una lectura válida libera lo construido temporalmente y devuelve `CAT_MEMORIA`; el catálogo anterior permanece íntegro. La interfaz limita a tres los registros importados, aunque el catálogo admita cien en memoria.

Una ruta inexistente también se rechaza conservando el estado. No confundas que el mensaje conserve un valor con una prueba exhaustiva de todos los errores: hay que cubrir también cantidad, bloque, capacidad y propiedad. El [programa importar](proyecto/importar.c) y la guía contienen la compilación y ejecución completas.

## 4. Programa completo

Fuente: [04-respaldo.c](soluciones/04-respaldo.c).

1. Desde `unidad21-recursos`, crea `build` como indica la guía.
2. Compila:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic soluciones/04-respaldo.c proyecto/catalogo.c ../unidad17-estructuras/proyecto/sensor.c ../unidad19-archivos/proyecto/archivo.c ../unidad16-lineas/proyecto/entrada.c -o build/respaldo
```

3. Ejecuta `./build/respaldo`. Windows: `.exe` en salida y ejecución; macOS: `clang`.
4. Compara:

```text
Trabajo: 100; respaldo: 0
Restaurado: 0; respaldo vacio: 0
```

La copia mantiene el valor anterior independientemente. La restauración libera el bloque modificado y transfiere el del respaldo; ambos objetos terminan con un responsable inequívoco. La etiqueta `limpieza` cubre fallos al agregar, clonar y mover. [pruebas_catalogo.c](proyecto/pruebas_catalogo.c) comprueba el rechazo de una transferencia sobre el mismo objeto sin efectuar la liberación.
