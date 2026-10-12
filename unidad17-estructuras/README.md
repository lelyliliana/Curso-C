# Unidad 17 — Estructuras: datos que pertenecen al mismo registro

[Inicio](../README.md) · [Anterior: líneas](../unidad16-lineas/README.md) · [Siguiente: estados](../unidad18-estados/README.md)

## Objetivo

Un sensor tiene nombre y lectura. Guardarlos en variables o arreglos independientes facilita confundir qué lectura pertenece a cada nombre. Una **estructura** reúne esos campos en un registro con una identidad de tipo.

Necesitas arreglos, cadenas y punteros. Al terminar podrás declarar registros, inicializar miembros, copiar estructuras por valor, utilizar un puntero a estructura y validar antes de publicar cambios. No usamos memoria dinámica todavía.

## 1. Definir el tipo y crear un objeto

Abre [proyecto/sensor.h](proyecto/sensor.h):

```c
struct Sensor {
    char nombre[13];
    int valor;
};
```

La definición describe el tipo; no crea por sí sola un sensor con esos datos. `struct Sensor sensor` declara un objeto de ese tipo. El punto selecciona un miembro: `sensor.valor` y `sensor.nombre`.

En [ejemplos/01-registro.c](ejemplos/01-registro.c):

```c
struct Sensor sensor = {.nombre = "patio", .valor = 25};
```

`.nombre` y `.valor` son **designadores del inicializador**: hacen visible a qué miembro pertenece cada valor. El arreglo del nombre incluye su terminador y ocupa espacio dentro del propio registro. No es un puntero a un nombre almacenado en otra parte.

`struct Sensor sensor = {0};` inicializa los miembros en cero, pero no crea automáticamente un registro válido para la aplicación: el nombre queda vacío y nuestro contrato exige un nombre no vacío. Inicializado y válido no significan lo mismo.

## 2. Construir el primer registro

Realiza un paso y comprueba el resultado antes del siguiente:

1. Desde la carpeta del curso entra con `cd unidad17-estructuras`.
2. Comprueba `ejemplos`, `proyecto` y `soluciones` con `ls`.
3. Crea `build` con `mkdir -p build`.
4. Construye el ejemplo usando el compilador correspondiente.

| Sistema | Construir | Ejecutar después |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-registro.c -o build/registro` | `./build/registro` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-registro.c -o build/registro.exe` | `./build/registro.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-registro.c -o build/registro` | `./build/registro` |

En Windows usa UCRT64. Ejecuta solo tras construir correctamente. Espera:

```text
Nombre: patio
Valor: 25
Actualizado: 30
```

El nombre no cambia cuando modificamos `sensor.valor`. Conserva una tabla de miembros antes y después de esa asignación.

## 3. Copiar un registro por valor

[ejemplos/02-copia.c](ejemplos/02-copia.c) utiliza `struct Sensor copia = original;`. La estructura sí se puede copiar por inicialización o asignación entre objetos compatibles. Se copian los valores de sus miembros, incluido el arreglo incorporado del nombre.

Esto difiere de asignar dos arreglos aislados con `a = b`, que no era válido. El arreglo está aquí dentro del valor de una estructura copiable.

Modificar `copia.nombre[0]` o `copia.valor` no cambia esos miembros del original. Además, `cambiar_copia(struct Sensor sensor)` recibe otro valor local, como las funciones con enteros de la Unidad 08. Salida:

```text
Copia en funcion: 99
Original: patio 25
Copia: Patio 40
```

Si una estructura futura contiene **punteros**, copiarla copia sus direcciones; no duplica automáticamente los objetos señalados. Esta estructura contiene un arreglo de `char`, por lo que su nombre sí forma parte del objeto copiado. No generalices «copiar una estructura» a «duplicar toda memoria relacionada».

## 4. Puntero a registro: punto y flecha

La función `sensor_valido(const struct Sensor *sensor)` recibe una dirección para leer sin copiar el registro completo. Después de comprobar que no sea nula, `sensor->valor` accede al mismo miembro que `(*sensor).valor`. Los paréntesis de la segunda forma son necesarios.

| Situación | Expresión |
|---|---|
| Objeto local `sensor` | `sensor.valor` |
| Puntero `acceso` a ese objeto | `acceso->valor` |
| Dirección para una función | `&sensor` |
| Registro dentro de arreglo | `sensores[i].valor` |
| Dirección de ese registro | `&sensores[i]` |

Un puntero no nulo sigue necesitando un registro vivo y legible. La flecha no incorpora comprobaciones automáticas de duración ni permisos.

## 5. Validación de miembros con límites reales

El contrato del sensor exige nombre de 1–12 símbolos A–Z, a–z, dígitos, `_` o `-`, y lectura entera de 0–100. El cero es una lectura válida; un registro vacío no lo es.

[sensor.c](proyecto/sensor.c) revisa el nombre del registro con un recorrido **limitado por el tamaño del miembro**. Comprueba un terminador dentro de las trece posiciones antes de aceptar. No llama a `strlen` sobre un miembro que podría carecer de terminador.

La condición `i < NOMBRE_SENSOR && sensor->nombre[i] != '\0'` comprueba primero el índice. El cortocircuito evita acceder al índice 13. Una secuencia de trece letras sin terminador queda rechazada; no se imprime con `%s` como si fuera una cadena válida.

La función `crear_sensor` tiene otro contrato: recibe una cadena de origen ya terminada y un destino separado, vivo y modificable. Prepara un registro temporal, valida longitud, símbolos y lectura, y solo al completar asigna `*destino = temporal`.

Si falla, conserva el registro anterior entero. No mezcla un nombre nuevo con un valor anterior por una validación a medias. La cadena de origen debe seguir siendo accesible durante la llamada; la comprobación de longitud no valida direcciones arbitrarias.

## 6. Compartir implementación y pruebas

Desde esta unidad, primero construye:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/main.c proyecto/sensor.c -o build/sensor
```

Aplica `clang` en macOS y `.exe` en UCRT64. Luego ejecuta. Espera:

```text
Creado: sensor_2 0
Rechazo; conserva sensor_2 0.
```

Después construye y ejecuta las pruebas, como paso separado:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/pruebas_sensor.c proyecto/sensor.c -o build/pruebas_sensor
```

Espera `Pruebas de sensor: OK.`. Las llamadas ocurren fuera de `assert`; un control de `NDEBUG` impide simular pruebas con aserciones desactivadas. Se prueba la misma implementación que utiliza el controlador.

## 7. Colecciones de registros y representación

[soluciones/03-coleccion.c](soluciones/03-coleccion.c) contiene tres sensores. Calcula la cantidad con `sizeof sensores / sizeof sensores[0]`, valida todos antes de presentar el informe y suma como máximo 300. No utiliza el nombre para deducir si una posición está cargada.

Una estructura puede tener relleno entre miembros o al final, por requisitos de alineación. `sizeof(struct Sensor)` no tiene que ser la suma exacta de los tamaños de los campos. Tampoco define un formato de intercambio entre computadoras.

Compara registros por sus campos significativos: nombre y valor. No uses `memcmp` como igualdad semántica general de estructuras. En la Unidad 19 guardaremos campos en texto, no los bytes internos del objeto.

## Práctica y cierre

Resuelve [EJERCICIOS.md](EJERCICIOS.md) y consulta luego [SOLUCIONES.md](SOLUCIONES.md).

- [ ] Distingo definición de tipo y creación de objeto.
- [ ] Utilizo punto o flecha según tenga objeto o puntero.
- [ ] Explico una copia con arreglo incorporado y el límite de esa idea ante punteros.
- [ ] Valido terminación y dominio antes de mostrar un registro.
- [ ] Conservo el destino ante rechazo.
- [ ] No confundo representación interna con formato de archivo.

Conserva un ejemplo válido con lectura cero y uno rechazado sin modificar el destino.

---

### ¿Necesitas apoyo con este tema?

Si te bloqueaste con la práctica, necesitas revisar tu entorno o adaptar lo aprendido a tu proyecto, podemos trabajarlo en una sesión personalizada.

[**Solicitar asesoría para este tema por WhatsApp**](https://wa.me/573103618296?text=Hola%2C%20Leli.%20Estoy%20estudiando%2017%20%C2%B7%20Estructuras%20y%20registros%20del%20curso%20C%20desde%20cero%20%28https%3A%2F%2Fgithub.com%2Flelyliliana%2FCurso-C%2Ftree%2Fmain%2Funidad17-estructuras%29%20y%20necesito%20una%20asesor%C3%ADa%20personalizada.%20Mi%20duda%20es%E2%80%A6)
