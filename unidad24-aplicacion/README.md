# Unidad 24 — Aplicación completa y persistencia

[Inicio](../README.md) · [Anterior: diseño](../unidad23-diseno/README.md) · [Siguiente: construcción](../unidad25-construccion/README.md)

## Del módulo probado a una sesión de usuario

Aquí construirás la agenda de sensores con menú y archivos. El código utiliza las operaciones de la Unidad 23: no vuelve a escribir sus reglas dentro de cada opción. Los mensajes permiten saber qué cambió y qué se rechazó.

Los registros siguen siendo datos de ejemplo, no mediciones tomadas de un dispositivo. La agenda vive en memoria durante la sesión; para conservarla debes guardar explícitamente y comprobar el éxito. Cargar reemplaza la agenda completa, no mezcla colecciones ni crea un respaldo automático.

## 1. Definir la interacción

| Opción | Acción | Entrada adicional |
|---|---|---|
| 0 | Salir | Ninguna |
| 1 | Agregar | Nombre y valor |
| 2 | Listar | Ninguna |
| 3 | Buscar | Nombre |
| 4 | Actualizar | Nombre y valor |
| 5 | Quitar | Nombre |
| 6 | Resumen | Ninguna |
| 7 | Guardar | Ruta de archivo nuevo |
| 8 | Cargar | Ruta de archivo existente |

Cada solicitud atiende una línea completa. Las opciones y valores utilizan el lector y conversor de la Unidad 16: pueden tener espacios alrededor y signo, pero deben convertirse completamente y estar en rango. El nombre admite 1–12 símbolos de su lista explícita; no se recortan espacios para convertir un nombre inválido en otro.

Una línea inválida cancela esa operación y devuelve al menú sin cambiar la agenda. **No se piden los campos restantes de una operación cancelada**: si el nombre es inválido, el siguiente texto será una nueva opción, no su valor. Esto importa al preparar entradas redirigidas de prueba.

Fin o error de entrada termina con fracaso y libera la memoria. Un `0` explícito termina normalmente. Ambos pueden perder cambios que nunca se guardaron; no hay guardado automático. Un fallo de memoria al agregar termina con fracaso, después de conservar la agenda hasta la limpieza. Un fallo al cargar devuelve al menú con la agenda anterior intacta.

## 2. Compilar y abrir la sesión

1. Desde la carpeta del curso entra con `cd unidad24-aplicacion`.
2. Crea `build`: `mkdir -p build` en Ubuntu/macOS o `New-Item -ItemType Directory -Force build` en PowerShell.
3. Compila:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/main.c proyecto/persistencia.c ../unidad23-diseno/proyecto/agenda.c ../unidad21-recursos/proyecto/catalogo.c ../unidad17-estructuras/proyecto/sensor.c ../unidad19-archivos/proyecto/archivo.c ../unidad16-lineas/proyecto/entrada.c -o build/agenda_app
```

4. Ejecuta `./build/agenda_app`. En Windows UCRT64 añade `.exe` a salida y ejecución. En macOS usa `clang` en la compilación.
5. Lee el menú y escribe una opción por línea. No escribas toda una operación en una sola línea.

El módulo `archivo.c` anterior sigue enlazado como dependencia de `catalogo.c`; el formato final lo implementa `persistencia.c`. No confundas estar enlazado con que la opción del menú utilice la carga antigua.

## 3. Primera sesión, un paso cada vez

1. Escribe `1`, Enter; cuando pida nombre, escribe `patio`; cuando pida valor, escribe `25`. Espera `Operacion completa.`.
2. Escribe `1` y agrega `salon` con `0`.
3. Escribe `2`. Espera `Registros: 2`, `patio: 25` y `salon: 0`.
4. Escribe `1` y vuelve a intentar `patio` con `100`. Espera `Operacion rechazada (2).`; el valor original no cambia.
5. Escribe `4`, nombre `salon` y valor `100`. Después `6`: espera cantidad dos, total 125, mínimo 25, máximo 100 y media 62.50.
6. Escribe `7`; cuando pida ruta, escribe `build/sesion-01.txt`, usando un nombre que no exista. Espera `Guardado completo.`.
7. Escribe `0` para terminar. Abre el archivo guardado y contrástalo con el formato de la siguiente sección.
8. Inicia otra sesión, escribe `8` y la ruta anterior. Espera `Carga completa.`. Usa `2` para confirmar los datos y `0` para salir.

Si la ruta ya existe, el guardado se rechaza sin reemplazar su contenido. Elige otro nombre; no borres una copia importante para «hacer que funcione». En las rutas relativas, el punto de partida es el directorio desde el que ejecutas el programa. La aplicación no crea carpetas inexistentes.

## 4. Un contrato de archivo nuevo

La Unidad 19 utilizó `C-REG-1` y un máximo de tres registros. El proyecto final necesita guardar hasta cien y exige nombres únicos. Por eso presenta una versión independiente, **`C-AGENDA-1`**, sin modificar la interfaz ni los archivos antiguos.

Ejemplo:

```text
C-AGENDA-1
2
patio;25
salon;100
```

Reglas del formato:

- Primera línea exactamente `C-AGENDA-1`.
- Segunda línea: cantidad decimal 0–100, solo dígitos, sin signo ni espacios. Se admiten ceros iniciales.
- Exactamente esa cantidad de registros `nombre;valor`.
- Nombre válido, único por comparación exacta, y valor decimal 0–100 solo con dígitos. Ceros iniciales permitidos.
- Cada línea tiene máximo 32 bytes de contenido antes del salto; byte nulo y bytes superiores a `CHAR_MAX` se rechazan.
- Tras los registros debe encontrarse fin de archivo. No se admiten comentarios, líneas vacías adicionales ni registros sobrantes.
- La última línea puede terminar sin salto. Para cantidad cero, la segunda línea también puede acabar directamente en fin.

Es texto bajo las reglas de traducción de flujos de C. En Ubuntu, un byte CR explícito en el contenido se rechaza; Windows puede traducir CRLF al leer en modo texto. No se afirma haber verificado esa traducción en Windows. No es un formato CSV general: los nombres no contienen `;`, comillas ni saltos, por lo que no implementamos escape de campos.

La extensión `.txt` es una elección de la persona; el encabezado y las reglas determinan el contenido. Una ruta larga puede ser válida para el sistema y aun así quedar fuera de la interfaz del menú, que admite hasta 128 bytes. Una ruta con espacios se recibe como línea completa. No la envolvemos en comillas al responder al menú: esas comillas formarían parte de la ruta recibida.

## 5. Cargar todo o conservar lo anterior

[La implementación](proyecto/persistencia.c) abre el archivo, lee en un catálogo temporal y comprueba el final. Si un registro es inválido o repetido, falta información, sobra contenido o falla una reserva, libera lo temporal. Siempre comprueba el cierre. Solo después de lectura y cierre correctos transfiere el catálogo al destino.

Esto protege el estado de memoria. No significa que guardar sea una transacción de base de datos. El guardado utiliza `wx` para crear exclusivamente un archivo nuevo y comprueba escritura y cierre. Un fallo puede dejar **ese archivo nuevo** parcial; nunca anunciamos éxito en ese caso. No prometemos escritura atómica, sincronización física ni recuperación ante corte eléctrico.

No guardamos los bytes internos de `struct Catalogo`: contiene un puntero que no sirve como dato persistente. Serializamos nombres, valores y cantidad. La capacidad asignada es un detalle de memoria, no parte del archivo.

## 6. Interpretar los rechazos

| Mensaje de dominio | Significado |
|---|---|
| `Operacion rechazada (1).` | Argumento fuera del contrato |
| `Operacion rechazada (2).` | Nombre repetido |
| `Operacion rechazada (3).` | Nombre ausente |
| `Operacion rechazada (4).` | Límite de cien registros |

| Mensaje de archivo | Significado |
|---|---|
| `Archivo rechazado (1).` | Argumento o agenda fuera del contrato |
| `Archivo rechazado (2).` | No se pudo abrir; al guardar puede existir ya |
| `Archivo rechazado (3).` | Formato, versión, registros o unicidad inválidos |
| `Archivo rechazado (4).` | Reserva de memoria rechazada al cargar |
| `Archivo rechazado (5).` | Error de lectura, escritura o cierre |

Los códigos de dominio y archivo son enums diferentes. El contexto del mensaje identifica cuál se está mostrando. Estos mensajes permiten diagnosticar la práctica, pero una aplicación para público general podría presentar explicaciones más detalladas y conservar el código técnico para registro.

## 7. Verificar persistencia y sesión

1. Compila [pruebas_persistencia.c](proyecto/pruebas_persistencia.c) sustituyendo `proyecto/main.c` en el comando de la sección 2. Usa salida `build/pruebas_persistencia` o `.exe`.
2. Ejecuta `./build/pruebas_persistencia build/prueba-nueva.txt` o su variante Windows con una ruta que no exista.
3. Espera `Pruebas de persistencia: OK.`. Retira únicamente el archivo que creó con apertura exclusiva exitosa. Si la ruta existe, falla sin borrarla.
4. Prueba manualmente un archivo truncado, una versión antigua y dos registros con el mismo nombre. El destino anterior debe permanecer.
5. Comprueba entrada inválida seguida de una opción válida y fin de entrada a mitad de un agregado.

Las pruebas del dominio siguen en la Unidad 23. Las de persistencia ejercitan su módulo compartido; las de sesión contrastan entradas completas y mensajes. Tener una prueba de archivo exitosa no demuestra por sí solo que todas las opciones del menú estén bien conectadas.

Resuelve [EJERCICIOS.md](EJERCICIOS.md) y consulta [SOLUCIONES.md](SOLUCIONES.md). La siguiente unidad añadirá una construcción reproducible y una entrega revisable.

---

### ¿Necesitas apoyo con este tema?

Si te bloqueaste con la práctica, necesitas revisar tu entorno o adaptar lo aprendido a tu proyecto, podemos trabajarlo en una sesión personalizada.

[**Solicitar asesoría para este tema por WhatsApp**](https://wa.me/573103618296?text=Hola%2C%20Leli.%20Estoy%20estudiando%2024%20%C2%B7%20Aplicaci%C3%B3n%20y%20persistencia%20del%20curso%20C%20desde%20cero%20%28https%3A%2F%2Fgithub.com%2Flelyliliana%2FCurso-C%2Ftree%2Fmain%2Funidad24-aplicacion%29%20y%20necesito%20una%20asesor%C3%ADa%20personalizada.%20Mi%20duda%20es%E2%80%A6)
