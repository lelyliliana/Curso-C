# Unidad 23 — Diseñar una agenda de sensores

[Inicio](../README.md) · [Anterior: depuración](../unidad22-depuracion/README.md) · [Siguiente: aplicación](../unidad24-aplicacion/README.md)

## Un proyecto que reúne lo aprendido

Construiremos una aplicación de consola para administrar una agenda de sensores. Son registros de ejemplo: cada nombre identifica una ubicación y cada valor es un entero 0–100. No existe una conexión real con hardware ni una unidad física implícita. El objetivo es administrar información y demostrar que las operaciones respetan un contrato.

La construcción se divide en tres etapas: aquí definimos reglas y operaciones de datos; en la Unidad 24 añadimos interacción y persistencia; en la Unidad 25 automatizamos la construcción y revisamos la entrega. Cada etapa tiene código funcional. No necesitas escribir un menú antes de comprobar las operaciones que lo sostienen.

Necesitas los módulos de [registros](../unidad17-estructuras/README.md), [recursos](../unidad21-recursos/README.md) y [depuración](../unidad22-depuracion/README.md).

## 1. Definir lo que el programa debe hacer

| Acción | Regla observable |
|---|---|
| Agregar | Nombre 1–12, lista de símbolos de `Sensor`, valor 0–100 y nombre no repetido |
| Buscar | Coincidencia exacta del nombre; conserva la salida si no encuentra |
| Actualizar | Cambia el valor del registro existente, sin crear otro |
| Quitar | Retira el registro y conserva el orden de los restantes |
| Listar | Muestra solo las posiciones utilizadas |
| Resumir | Cantidad, suma, mínimo, máximo y media; vacío no tiene media |

La agenda admite cien sensores. Los nombres distinguen mayúsculas de minúsculas: `patio` y `Patio` son dos identificadores diferentes. No normalizamos tildes ni Unicode; mantenemos la lista de símbolos de la Unidad 17. Definir estas reglas antes de programar evita que dos partes de la aplicación interpreten el mismo dato de distinta manera.

Una búsqueda ausente no es una posición cero. No escondemos ese estado con un índice inventado. Actualizar y quitar un nombre ausente devuelven un estado nombrado, no éxito silencioso.

## 2. Separar responsabilidades

| Parte | Responsabilidad | No decide |
|---|---|---|
| `sensor.c`, Unidad 17 | Validez de un registro individual | Unicidad entre registros |
| `catalogo.c`, Unidad 21 | Reserva, copia, transferencia y liberación | Reglas del menú |
| `agenda.c`, esta unidad | Unicidad, operaciones y resumen | Cómo pedir texto o abrir archivos |
| Aplicación, Unidad 24 | Interacción y presentación | Cómo crece el bloque de memoria |
| Persistencia, Unidad 24 | Formato, lectura completa y cierre | Qué opción elige el usuario |

La [interfaz agenda.h](proyecto/agenda.h) expresa estados mediante `enum ResultadoAgenda`. Los números del enum son detalles locales; en la guía de uso se explican sus nombres. El módulo de datos no imprime mensajes ni llama al lector de teclado: puede probarse con llamadas directas.

## 3. Mantener invariantes

Una invariante es una condición que debe seguir siendo cierta después de cada operación válida. La agenda usa un catálogo inicializado con `{0}` y propiedad exclusiva. Se exige:

- `usados <= capacidad <= 100`.
- Capacidad cero con puntero nulo; capacidad positiva con bloque vivo suficiente.
- Cada registro utilizado cumple el contrato de `Sensor`.
- No hay dos nombres iguales por `strcmp`.

[agenda_valida](proyecto/agenda.c) comprueba metadatos, registros y unicidad. No puede certificar que una dirección arbitraria esté viva, tenga extensión suficiente o pertenezca al objeto. Esas condiciones de memoria las garantiza quien usa el módulo. No edites el puntero ni las cantidades para fabricar una agenda.

La unicidad es una regla nueva del proyecto: el catálogo general de la Unidad 21 admite registros repetidos. Reutilizar un contenedor no significa que todas las aplicaciones deban tener exactamente las mismas reglas.

## 4. Diseñar cada cambio antes de publicarlo

**Agregar:** validar un registro local, comprobar que su nombre no existe y llamar a `agregar_sensor`. La copia local permite que el nombre de entrada provenga incluso de un registro de la misma agenda: no se conserva una fuente interna después de crecer. Un fallo no cambia registros ni cantidad.

**Actualizar:** verificar valor y localizar el nombre antes de escribir el nuevo valor. Actualizar no reasigna memoria. Una solicitud inválida conserva el valor anterior.

**Quitar:** localizar, desplazar los registros posteriores una posición hacia el inicio y reducir `usados`. No se reduce la capacidad ni se libera el bloque por cada borrado. Las posiciones anteriores a la nueva cantidad siguen siendo la colección publicada; la posición que quedó fuera no se lee como registro activo.

Los índices no son identidades permanentes. Después de quitar, una posición puede contener otro sensor aunque el bloque siga en la misma dirección. Un préstamo a un registro tampoco autoriza su uso después de un crecimiento o liberación. Para identificarlo otra vez, busca por nombre.

**Resumir:** validar la agenda y rechazar el vacío antes de usar el primer registro. Preparar un resumen local y escribir la salida una sola vez cuando todo esté listo. La suma máxima es 10000 y se almacena en `unsigned long`; la media convierte antes de dividir, conservando la lección de la Unidad 22.

## 5. Ejecutar sin menú

1. Desde la carpeta del curso entra con `cd unidad23-diseno`.
2. Crea `build`: `mkdir -p build` en Ubuntu/macOS o `New-Item -ItemType Directory -Force build` en PowerShell.
3. Compila el controlador y sus módulos:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/main.c proyecto/agenda.c ../unidad21-recursos/proyecto/catalogo.c ../unidad17-estructuras/proyecto/sensor.c ../unidad19-archivos/proyecto/archivo.c ../unidad16-lineas/proyecto/entrada.c -o build/agenda
```

4. Ejecuta `./build/agenda`. Windows UCRT64: añade `.exe` a salida y ejecución; macOS: cambia `gcc` por `clang`.
5. Compara:

```text
Duplicado rechazado: si
Cantidad: 2; total: 125; media: 62.50
Queda: salon 100
```

La salida muestra una secuencia fija para poder anticipar resultados. No es todavía el menú final. Aunque no lea archivos, `catalogo.c` tiene una operación que utiliza el módulo de archivos anterior; ese módulo y el de entrada también deben estar enlazados.

## 6. Comprobar sin depender de lo que se imprime

1. Compila [pruebas_agenda.c](proyecto/pruebas_agenda.c) sustituyendo `proyecto/main.c` en el comando anterior y usando salida `build/pruebas_agenda` o `.exe`.
2. Ejecuta y espera `Pruebas de agenda: OK.`.
3. Revisa que el duplicado conserve el valor inicial y la cantidad, y que el resumen vacío no cambie su salida.
4. Añade casos de quitar el último, el primero y uno intermedio.

Las funciones se ejecutan fuera de `assert`; las pruebas rechazan `NDEBUG`. No añadimos llamadas de entrada interactiva a las pruebas del dominio. Así un fallo de teclado no se confunde con un fallo de búsqueda.

El recorrido lineal de búsqueda y la revisión por pares de unicidad son fáciles de seguir. Con cien registros son suficientes para este ejercicio; no prometemos rendimiento para millones de sensores. Si cambia ese requisito, habrá que revisar la estructura de datos y medir, no solo subir una constante.

## 7. Antes de conectar interacción y archivos

Resuelve [EJERCICIOS.md](EJERCICIOS.md) y consulta [SOLUCIONES.md](SOLUCIONES.md). Conserva una tabla de casos: entrada, estado esperado y datos que deben permanecer iguales ante rechazo.

- [ ] Tengo una regla inequívoca para nombres repetidos.
- [ ] Distingo ausencia, argumento inválido, límite y falta de memoria.
- [ ] Puedo probar el dominio sin escribir en la terminal.
- [ ] Explico por qué borrar cambia posiciones, pero no necesita otra reserva.
- [ ] No presento una media inventada para la agenda vacía.
- [ ] Libero el único propietario al terminar.

Continúa con la [Unidad 24](../unidad24-aplicacion/README.md), que añade una sesión de consola y un formato propio para guardar toda la agenda.
