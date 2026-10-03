# Unidad 21 — Propiedad, préstamos y limpieza de recursos

[Inicio](../README.md) · [Anterior: memoria](../unidad20-memoria/README.md) · [Siguiente: depuración](../unidad22-depuracion/README.md)

## El problema que resolverás

Un catálogo guarda sensores en memoria dinámica. Queremos hacer un respaldo, importar datos de un archivo y terminar limpiamente aunque alguna operación falle. La pregunta principal ya no es solo «¿dónde está el dato?», sino «¿quién debe devolver este recurso y hasta cuándo puede usarlo otra función?».

Al terminar distinguirás préstamo, copia independiente y transferencia de propiedad. Construirás una operación que reemplaza el catálogo solo después de preparar el resultado completo. Necesitas las [estructuras](../unidad17-estructuras/README.md), los [archivos](../unidad19-archivos/README.md) y la [memoria dinámica](../unidad20-memoria/README.md).

## 1. Un préstamo no es propiedad

Abre [01-prestamo.c](ejemplos/01-prestamo.c). La función `mostrar` recibe la dirección de un sensor automático de `main`. Puede observarlo durante esa llamada; no lo libera ni conserva la dirección para después de su duración.

1. Entra en `unidad21-recursos` desde la carpeta del curso.
2. Crea `build`: `mkdir -p build` en Ubuntu/macOS o `New-Item -ItemType Directory -Force build` en PowerShell.
3. Compila para tu sistema.
4. Ejecuta solo tras compilación exitosa.

| Sistema | Compilar | Ejecutar |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-prestamo.c -o build/prestamo` | `./build/prestamo` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-prestamo.c -o build/prestamo.exe` | `./build/prestamo.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-prestamo.c -o build/prestamo` | `./build/prestamo` |

Espera `patio: 25` y `Sigue vivo: patio`. `const` impide modificar el registro a través de ese acceso; no prolonga su duración ni convierte un objeto automático en dinámico.

## 2. Registrar al propietario

La interfaz [catalogo.h](proyecto/catalogo.h) contiene una estructura con puntero, cantidad y capacidad. Cada objeto comienza con `{0}`. El catálogo es el propietario exclusivo de su bloque; las funciones del módulo administran los metadatos. Solo las primeras `usados` posiciones están inicializadas.

| Acción | Responsable | Fin de validez |
|---|---|---|
| Agregar | El catálogo conserva el bloque y copia el registro recibido | El puntero recibido solo se necesita durante la llamada |
| Observar un elemento | El llamador toma un préstamo | Liberación, reemplazo o crecimiento exitoso que afecta el bloque |
| Clonar | Cada catálogo obtiene su propio bloque | Cada propietario libera el suyo |
| Mover | La propiedad pasa del origen al destino | El origen queda vacío; el destino administra la duración |

El módulo no puede demostrar que un puntero arbitrario posee memoria ni que dos objetos no comparten el mismo bloque. Esas son precondiciones de la interfaz, no consecuencias de comprobar `NULL`. No fabriques un catálogo cambiando manualmente su dirección o sus cantidades.

## 3. Por qué la asignación común no hace un respaldo

En la Unidad 17, copiar un `struct Sensor` copia también su arreglo de nombre: no contiene punteros propietarios. En cambio, asignar un `struct Catalogo` copia la dirección almacenada. No reserva nuevos sensores.

Si ambos objetos se consideran propietarios, modificar un dato afecta al mismo bloque y liberar ambos causa una doble liberación. Tampoco basta poner a nulo uno después de liberar: el otro sigue conteniendo una dirección vencida. Por eso no uses una asignación ordinaria para duplicar un catálogo.

`clonar_catalogo` crea una copia independiente. Primero valida y reserva, después copia los registros inicializados y finalmente reemplaza el destino. Si falla, el destino anterior sigue disponible. Clonar una colección vacía no reserva; reemplaza el destino por el estado vacío. La autocopia se acepta sin operaciones. Los dos objetos distintos deben poseer bloques separados desde antes de la llamada.

La copia es independiente para esta representación porque cada `Sensor` guarda su nombre dentro del registro. Si más adelante el registro tuviera un `char *` propietario, copiar sus campos no copiaría el texto: habría que diseñar otra operación de copia y limpieza.

## 4. Mover cambia el responsable

`mover_catalogo` libera el contenido anterior del destino, le transfiere el bloque del origen y restablece el origen a vacío. No reserva memoria ni duplica los sensores. Rechaza origen y destino iguales para no destruir el objeto al intentar moverlo sobre sí mismo.

Dentro de esa función verás `*destino = *origen`. Es correcto como transferencia porque inmediatamente se retira la propiedad del origen. La asignación por sí sola no expresaría ese contrato.

Tras mover, las direcciones de los elementos transferidos siguen apuntando al mismo bloque vivo, ahora administrado por el destino. Los préstamos al contenido anterior del destino han vencido porque ese bloque se liberó. Para mantener claro el responsable, obtén de nuevo los accesos desde el destino y no operes sobre un origen que ahora está vacío.

## 5. Agregar con un argumento que está dentro

Queremos permitir `agregar_sensor(&catalogo, &catalogo.datos[0])` cuando existe ese elemento. Si el agregado necesita `realloc`, el puntero recibido podría quedar invalidado antes de copiarlo.

[La implementación](proyecto/catalogo.c) valida y copia el registro a una variable local **antes** del crecimiento. Después reserva y escribe desde la copia local. Así admite ese caso sin leer un puntero vencido. No autoriza que el llamador vuelva a utilizar el puntero antiguo después del retorno exitoso.

La capacidad crece desde dos hasta un máximo de 100 sensores. Este límite de memoria es distinto del formato de archivos de la Unidad 19, que continúa admitiendo como máximo tres registros. Introducir memoria dinámica no modifica silenciosamente un contrato de archivo publicado.

## 6. Limpiar todas las rutas de salida

Abre [main.c](proyecto/main.c). Tiene tres propietarios inicialmente vacíos. Cualquier fallo salta a la etiqueta `limpieza`; allí se libera cada uno y se devuelve el resultado adecuado.

`goto limpieza` es un salto dentro de la misma función, no una llamada. Se utiliza aquí para compartir una secuencia corta de liberación que todas las rutas necesitan. Los recursos se inicializan antes de posibles saltos; no accedemos a variables cuya inicialización fue omitida. En programas pequeños, liberar antes de cada `return` también puede ser claro. El objetivo es comprobar todas las rutas, no añadir saltos por costumbre.

1. Desde `unidad21-recursos`, compila el proyecto con los módulos compartidos:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/main.c proyecto/catalogo.c ../unidad17-estructuras/proyecto/sensor.c ../unidad19-archivos/proyecto/archivo.c ../unidad16-lineas/proyecto/entrada.c -o build/catalogo
```

2. Ejecuta `./build/catalogo`. En Windows usa `.exe` en salida y ejecución; en macOS cambia `gcc` por `clang`.
3. Compara:

```text
Original: 25; copia: 40
Origen movido: 0; destino: 1 40
```

Aunque `main` no importe archivos, enlazamos las dependencias de todo `catalogo.c`, que también define la función de carga. Omitir el módulo de archivos puede producir referencias sin resolver.

## 7. Importar sin destruir lo anterior

`cargar_catalogo` sigue esta secuencia:

1. Lee y valida hasta tres registros con el módulo de archivos, incluyendo el cierre.
2. Construye un catálogo temporal en memoria.
3. Si falla alguna reserva, libera el temporal y conserva el destino.
4. Cuando todo está listo, mueve el temporal al destino.

El temporal es la frontera de publicación: no confundimos un prefijo válido con una importación completa. No significa que el guardado de la Unidad 19 sea atómico frente a cortes eléctricos. Aquí protegemos el estado de memoria durante una carga.

Para practicar:

1. Crea manualmente `build/sensores.txt` con este contenido y guarda el archivo:

```text
C-REG-1
2
patio;25
salon;0
```

2. Compila sustituyendo `proyecto/main.c` por `proyecto/importar.c` en el comando anterior y cambiando la salida a `build/importar` o `.exe`.
3. Ejecuta `./build/importar build/sensores.txt` o su variante Windows.
4. Espera `Cargados: 2`, `patio: 25` y `salon: 0`.
5. En otro archivo elimina la última línea para dejarlo truncado; ejecuta con su ruta. El programa termina con fracaso e informa `Carga rechazada (4); conserva anterior 77`.

El código 4 es `CAT_ARCHIVO`, que agrupa los rechazos del módulo de archivos para esta interfaz. No es un código de error universal ni identifica por sí solo si falló apertura, contenido o cierre. Para herramientas de diagnóstico más completas se podría devolver además el detalle original.

## 8. Verificar propiedad y duración

1. Compila `proyecto/pruebas_catalogo.c` con los mismos módulos y salida `build/pruebas_catalogo` o `.exe`.
2. Ejecuta y espera `Pruebas de catalogo: OK.`.
3. Observa la prueba que agrega un registro interno justo al crecer, la independencia de la copia, la autocopia y la transferencia que reemplaza un destino no vacío.
4. Resuelve [EJERCICIOS.md](EJERCICIOS.md) y consulta [SOLUCIONES.md](SOLUCIONES.md).

Repetir la función de liberación de un catálogo que ya quedó vacío es válido. Liberar copias independientes también. Repetir `free` sobre una dirección liberada o liberar una dirección prestada no lo es. Un puntero no nulo puede estar vencido: nulidad y validez son propiedades diferentes.

- [ ] Identifico un propietario por cada bloque vivo.
- [ ] Distingo una copia de dirección de una copia independiente.
- [ ] Explico qué conserva una operación rechazada.
- [ ] Reviso éxito y fallo de cada paso que adquiere recursos.
- [ ] Mantengo los préstamos dentro de la duración del bloque.
- [ ] Libero temporales sin destruir un destino todavía válido.

La [Unidad 22](../unidad22-depuracion/README.md) comprobará hipótesis con pruebas, seguimiento de variables y herramientas de depuración.
