# Unidad 18 — Enumeraciones y transiciones de estado

[Inicio](../README.md) · [Anterior: estructuras](../unidad17-estructuras/README.md) · [Siguiente: archivos](../unidad19-archivos/README.md)

## Objetivo

Ya usamos enumeraciones para nombrar estados de lectura. Ahora diseñarás un conjunto de estados de aplicación y las transiciones permitidas. Un número recibido no se convierte automáticamente en una opción válida porque pueda almacenarse en una variable `enum`.

Al terminar podrás utilizar nombres en lugar de números dispersos, validar valores desconocidos y distinguir un estado de un evento. El ejemplo simula un dispositivo: no acciona hardware ni afirma confirmar una acción física.

## 1. Nombres de estado y códigos

Consulta [proyecto/estado.h](proyecto/estado.h):

```c
enum Estado {APAGADO = 10, LISTO = 20, ACTIVO = 30, FALLO = 40};
enum Evento {ENCENDER = 1, INICIAR, DETENER, ERROR_DETECTADO, RESTABLECER};
```

Los identificadores son constantes de enumeración. Los eventos siguientes al primero reciben valores consecutivos, 2–5. Los estados tienen valores explícitos separados: 11 no es un estado reconocido aunque esté entre 10 y 40.

Los nombres no son cadenas. `nombre_estado` convierte un estado reconocido a un texto para presentación mediante `switch`; el caso `default` devuelve `DESCONOCIDO`. No usamos un código de enumeración como índice de un arreglo de cuatro nombres.

En C17 una enumeración no impone por sí sola la validación completa que necesita la aplicación. Una conversión `(enum Estado)99` sirve en el ejemplo para representar un código desconocido; no demuestra que ese código esté admitido. Tampoco hacemos depender el contrato del tamaño en bytes del enum.

## 2. Construir una enumeración

Trabaja un paso a la vez:

1. Entra desde la carpeta del curso con `cd unidad18-estados`.
2. Reconoce sus carpetas con `ls`.
3. Crea `build` con `mkdir -p build`.
4. Construye usando la fila de tu sistema y ejecuta después de comprobar el resultado.

| Sistema | Construir | Ejecutar |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-enumeracion.c proyecto/estado.c -o build/enumeracion` | `./build/enumeracion` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-enumeracion.c proyecto/estado.c -o build/enumeracion.exe` | `./build/enumeracion.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-enumeracion.c proyecto/estado.c -o build/enumeracion` | `./build/enumeracion` |

Windows utiliza UCRT64. Salida:

```text
Nombre: LISTO
Codigo: 20
Codigo ajeno: DESCONOCIDO
```

El código se convierte a `int` antes de imprimirse con `%d`; la presentación no establece el formato de un archivo ni convierte el código ajeno en un estado válido.

## 3. Estado y evento no cumplen la misma función

El **estado** describe la situación actual. El **evento** solicita o comunica algo que podría cambiarla. No calculamos el estado siguiente sumando uno al código: consultamos las reglas.

| Estado actual | Evento | Estado siguiente |
|---|---|---|
| APAGADO | ENCENDER | LISTO |
| LISTO | INICIAR | ACTIVO |
| ACTIVO | DETENER | LISTO |
| Cualquier estado reconocido | ERROR_DETECTADO | FALLO |
| FALLO | RESTABLECER | APAGADO |

Todas las demás parejas se rechazan. ERROR_DETECTADO en FALLO se admite y conserva FALLO: el contrato lo permite. RESTABLECER no vuelve automáticamente a ACTIVO; requiere iniciar el recorrido de nuevo.

Esta tabla es una **máquina de estados** pequeña: hace explícitos los cambios. Es una regla de software de este ejercicio, no un protocolo universal de encendido o seguridad industrial.

## 4. Validar antes de confirmar el cambio

[proyecto/estado.c](proyecto/estado.c) define `bool transicionar(enum Estado *estado, enum Evento evento)`. Primero rechaza puntero nulo y estado desconocido. Calcula `siguiente` en una variable local y solo escribe `*estado` cuando reconoce una transición.

Un evento desconocido o no permitido devuelve `false` sin modificar el estado. El llamador interpreta el resultado antes de anunciar aceptación. El objeto señalado debe seguir vivo y ser modificable; comprobar nulidad no demuestra por sí solo esa precondición.

No hay conexión con actuadores: «aceptado» significa que la transición de datos se aplicó. Si el programa futuro controlara un motor, necesitaría además confirmar su resultado físico y gestionar tiempos y fallos externos.

## 5. Ejecutar una secuencia

Desde esta unidad construye primero:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/main.c proyecto/estado.c -o build/estados
```

Aplica `clang` en macOS y `.exe` en UCRT64. Después ejecuta. Espera:

```text
Evento 2: rechazado; estado APAGADO
Evento 1: aceptado; estado LISTO
Evento 2: aceptado; estado ACTIVO
Evento 4: aceptado; estado FALLO
Evento 2: rechazado; estado FALLO
Evento 5: aceptado; estado APAGADO
```

La presentación usa `ok ? "aceptado" : "rechazado"`, el **operador condicional**. Si `ok` es verdadero elige la primera expresión; si es falso, la segunda. Solo se evalúa la rama elegida. Aquí abrevia una selección de texto, no ejecuta las transiciones ni sustituye su validación.

## 6. Probar reglas y valores desconocidos

Construye las pruebas como otro ejecutable:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/pruebas_estado.c proyecto/estado.c -o build/pruebas_estado
```

Después ejecuta; espera `Pruebas de estado: OK.`. Ambos controladores enlazan el mismo `estado.c`. No combines sus dos `main` ni desactives las aserciones.

Prueba las parejas de la tabla, las que no aparecen y códigos desconocidos. Un conjunto de nombres no basta: la evidencia debe demostrar las reglas. No realices aritmética con enums para «explorar estados siguientes».

## 7. Contar eventos y decidir identidad

El ejercicio de conteo conserva cantidades independientes de aceptados y rechazados. Un evento repetido puede aceptarse o rechazarse según el estado actual: repetir INICIAR cuando ya está ACTIVO no inicia otro estado.

En aplicaciones con solicitudes remotas debes decidir también si una repetición es una nueva orden o el reintento de una anterior. Este ejemplo no implementa identificadores, transporte ni procesamiento exactamente una vez; solo enseña a declarar la regla que sí ejecuta.

## Práctica y cierre

Resuelve [EJERCICIOS.md](EJERCICIOS.md) y consulta luego [SOLUCIONES.md](SOLUCIONES.md).

- [ ] Distingo nombres, códigos y textos de presentación.
- [ ] No acepto todos los números entre el mínimo y el máximo.
- [ ] Separo estado de evento.
- [ ] Conservo el estado cuando rechazo una transición.
- [ ] Pruebo valores desconocidos y secuencias completas.

Conserva una tabla que muestre estado anterior, evento, aceptación y estado posterior.
