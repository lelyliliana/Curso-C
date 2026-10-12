# Unidad 19 — Archivos de texto: guardar y recuperar registros

[Inicio](../README.md) · [Anterior: estados](../unidad18-estados/README.md)

## Objetivo

Los registros locales desaparecen cuando termina el programa. Un archivo permite conservar campos para otra ejecución. Aprenderás a abrir, leer, escribir y cerrar un flujo, y a validar un formato completo antes de aceptar sus registros.

Necesitas estructuras, enumeraciones, cadenas y conversión numérica. Al terminar podrás reconocer fallos de apertura, formato, capacidad, lectura, escritura y cierre. Este bloque utiliza archivos de texto pequeños; no es una base de datos ni promete reemplazos atómicos o recuperación ante corte eléctrico.

## 1. Ruta, directorio de trabajo y argumentos

Los programas reciben una ruta al ejecutarlos. `int main(int argc, char *argv[])` usa la forma de `main` con argumentos:

- `argc`: cantidad de argumentos, incluido el nombre del programa.
- `argv[0]`: nombre con que se invocó el programa cuando está disponible.
- `argv[1]`: primer argumento de usuario, accesible aquí solo tras comprobar `argc == 2`.

`argv` es un arreglo de punteros a cadenas del entorno de ejecución. Estas cadenas son accesibles durante el programa. No necesitamos escribir ni recorrer argumentos inexistentes.

Una ruta relativa como `build/sensores.txt` se interpreta desde el **directorio de trabajo** de la ejecución, no desde el archivo `.c`. Si ejecutas el mismo binario desde otra carpeta, esa ruta puede designar otro archivo. Usa comillas en la terminal si una ruta contiene espacios.

## 2. Abrir y cerrar un flujo

`<stdio.h>` declara `FILE` y las funciones de archivo. Tratamos `FILE *` como acceso a un flujo administrado por la biblioteca, sin inspeccionar sus miembros internos.

| Modo | Efecto relevante |
|---|---|
| `r` | Leer texto existente; falla si no puede abrirlo |
| `w` | Crear o **truncar** un archivo para escribir |
| `a` | Añadir al final; no lo usamos para construir este formato completo |
| `wx` | Crear para escribir únicamente si el archivo no existe |

`x` está disponible en la base C17 del curso. Nuestro guardado usa `wx`: no destruye un archivo existente para resolver una repetición. Si la ruta ya existe, devuelve un fallo de apertura.

`fopen` devuelve `NULL` ante fallo. No llames a `fgetc`, `fprintf` o `fclose` con ese resultado. Si abre, cierra el flujo exactamente una vez con `fclose` y comprueba su resultado. Después del cierre no uses el puntero ni reintentes cerrarlo, incluso si el cierre informó fallo.

Un mensaje de guardado solo se presenta después de comprobar escrituras **y cierre**. Parte de la salida puede estar almacenada temporalmente en búferes; un error puede aparecer al cerrar. Que el cierre pase no demuestra que el soporte físico sobreviva a cualquier corte de energía.

## 3. Primer recorrido de un archivo

Trabaja un paso a la vez:

1. Desde la carpeta del curso entra con `cd unidad19-archivos`.
2. Comprueba `ejemplos`, `proyecto` y `soluciones` con `ls`.
3. Crea `build` con `mkdir -p build`.
4. Construye el contador según tu sistema.

| Sistema | Construir |
|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-contar.c -o build/contar` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-contar.c -o build/contar.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic ejemplos/01-contar.c -o build/contar` |

Crea con tu editor `build/muestra.txt`, escribe dos líneas y guarda con un salto final en ambas. Luego ejecuta `./build/contar build/muestra.txt` (o `.exe`). Espera `Saltos de linea: 2`.

`fgetc` devuelve `int`, como `getchar`, pero recibe el flujo. Al devolver `EOF` consultamos `ferror` para distinguir error de fin normal. No utilizamos `while (!feof(flujo))` como condición de lectura: el indicador de fin se activa después de una lectura que encuentra ese fin, no antes de intentar leer.

El contador mide saltos `\n` vistos por la biblioteca, no necesariamente «líneas humanas»: un texto final sin salto no agrega uno. Rechaza más de 1000 saltos para conservar un dominio pequeño y un contador representable. Un archivo vacío tiene cero saltos; no se confunde con fallo de apertura.

## 4. Diseñar un formato antes de guardar

El proyecto conserva hasta tres registros mediante este formato:

```text
C-REG-1
3
patio;25
salon;0
taller;100
```

| Parte | Regla |
|---|---|
| Primera línea | Versión exacta `C-REG-1` |
| Segunda línea | Un dígito entre 0 y 3 |
| Registros | Exactamente la cantidad declarada, uno por línea |
| Nombre | Contrato de sensor: 1–12 símbolos permitidos |
| Separador | Un `;` entre nombre y número |
| Lectura | Uno o más dígitos, valor 0–100; sin signo ni blancos |
| Límite de contenido por línea | 32 bytes más espacio para terminador |
| Después del último registro | Fin de archivo, sin líneas o contenido adicional |

La carga admite ceros iniciales en el número, si su línea cabe. El guardado escribe su representación decimal sin ese relleno. Los nombres repetidos son registros permitidos; este formato no define identidad única por nombre.

Un último registro válido sin salto final se acepta. Un salto vacío adicional después de los registros no se acepta como «dato irrelevante». Tampoco se aceptan BOM, versión distinta, bytes nulos o formatos numéricos más amplios de la Unidad 16. Un `\r` que llegue sin traducción de modo texto incumple estas reglas.

No escribimos la estructura con `fwrite` como si su representación interna fuera un formato portable. Relleno, tamaños, orden de bytes y futuros punteros podrían cambiar. Serializar significa elegir una representación de los campos; aquí la versión y las reglas son parte del contrato.

## 5. Guardar sin reemplazar archivos anteriores

Interfaz: [proyecto/archivo.h](proyecto/archivo.h). Implementación: [proyecto/archivo.c](proyecto/archivo.c). Se reutilizan el validador de la Unidad 17 y el conversor entero de la Unidad 16.

Primero construye desde esta unidad:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/guardar.c proyecto/archivo.c ../unidad17-estructuras/proyecto/sensor.c ../unidad16-lineas/proyecto/entrada.c -o build/guardar
```

En macOS usa `clang`; en UCRT64 usa destino `build/guardar.exe`. Después ejecuta `./build/guardar build/sensores.txt`, agregando `.exe` si corresponde. Esa ruta debe ser nueva. Espera `Tres registros guardados en archivo nuevo.` y abre el archivo con tu editor para contrastar sus campos.

Una segunda ejecución con la misma ruta debe fallar, **sin sobrescribirla**. Para otra prueba utiliza una ruta nueva, por ejemplo `build/sensores-2.txt`. No borres archivos personales para hacer pasar el ejemplo.

La función valida cantidad y todos los registros antes de abrir. Si un registro es inválido no crea el archivo. Después de abrir, cualquier fallo de escritura o cierre puede dejar un archivo nuevo incompleto: no hay reemplazo transaccional ni eliminación automática de un archivo cuya situación deba investigarse.

## 6. Cargar todo antes de modificar las salidas

Construye en otro paso:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/cargar.c proyecto/archivo.c ../unidad17-estructuras/proyecto/sensor.c ../unidad16-lineas/proyecto/entrada.c -o build/cargar
```

Aplica las variantes de sistema. Ejecuta `./build/cargar build/sensores.txt`. Espera:

```text
Registros: 3
patio: 25
salon: 0
taller: 100
```

La carga abre para leer, prepara tres registros temporales, comprueba versión/cantidad, valida cada línea y exige fin después de los declarados. Cierra el flujo antes de copiar los temporales al destino y asignar su cantidad utilizada. Un rechazo conserva **ambas salidas**: registros anteriores y cantidad anterior.

El lector acotado consume una línea larga o inválida hasta salto o fin/error, sin ampliar el búfer. La memoria está limitada; el tiempo de consumo de un flujo que nunca termine no lo está. La carga no acciona hardware ni acepta rutas de fuentes remotas.

`strchr` busca el primer `;` dentro de la cadena ya terminada y devuelve su dirección o `NULL`. Se comprueba el resultado antes de usarlo. Al reemplazarlo por `\0`, quedan dos segmentos: nombre y número. Un segundo separador aparecería dentro del número y sería rechazado por la gramática de dígitos.

## 7. Estados y responsabilidad del flujo

| Resultado | Significado |
|---|---|
| `ARCHIVO_OK` | Operación completa y cierre comprobado |
| `ARCHIVO_ARGUMENTO` | Argumento comprobable inválido |
| `ARCHIVO_ABRIR` | No se pudo abrir o crear de forma exclusiva |
| `ARCHIVO_FORMATO` | Versión, sintaxis, registro o completitud inválida |
| `ARCHIVO_CAPACIDAD` | Registros declarados no caben en destino |
| `ARCHIVO_IO` | Fallo de lectura, escritura o cierre |

Los controladores muestran el código con su fallo. La tabla explica su significado; el número no pretende identificar una causa exacta del sistema operativo. Un fallo de apertura puede ser existencia previa, ruta inexistente o falta de acceso según la operación.

Quien abre el flujo en estas funciones también lo cierra. Los auxiliares que reciben `FILE *` no lo cierran por su cuenta. Esa responsabilidad evita cierres duplicados y accesos después de liberar el flujo.

Los punteros recibidos deben tener extensión, duración y permisos reales. La carga permite destino nulo únicamente con capacidad cero; puede cargar una colección declarada vacía en ese caso. La salida de cantidad sigue necesitando un objeto válido y separado.

## 8. Pruebas e informe

Primero construye las pruebas compartidas:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic proyecto/pruebas_archivo.c proyecto/archivo.c ../unidad17-estructuras/proyecto/sensor.c ../unidad16-lineas/proyecto/entrada.c -o build/pruebas_archivo
```

Aplica el sistema correspondiente. Luego ejecuta `./build/pruebas_archivo build/prueba-nueva.txt` o su variante `.exe`, con ruta nueva. Espera `Pruebas de archivo: OK.`. Las pruebas retiran únicamente el archivo que crearon tras una creación exclusiva exitosa. Si la ruta ya existe, fallan sin borrarla.

También utilizan `tmpfile`, que crea un flujo temporal eliminado al cerrarlo. Después de escribir, `fseek(..., 0, SEEK_SET)` reposiciona antes de leer y comprueba su retorno; no alternamos lectura/escritura de un flujo de actualización sin cumplir sus reglas.

Las pruebas cubren guardado/carga, negativa a reemplazar, capacidad insuficiente y argumentos. Compleméntalas con archivos malformados: datos truncados, versión ajena, sufijos, byte nulo y contenido adicional. No copies otra implementación del parser dentro de las pruebas.

Resuelve [EJERCICIOS.md](EJERCICIOS.md) y consulta luego [SOLUCIONES.md](SOLUCIONES.md), con un informe de suma sobre registros cargados.

## Práctica y cierre

- [ ] Identifico el directorio desde el que se interpreta una ruta.
- [ ] Compruebo apertura antes de operar y cierro una sola vez.
- [ ] Distingo fin normal de error de lectura.
- [ ] Compruebo escrituras y cierre antes de anunciar éxito.
- [ ] Defino versión, capacidad y gramática del archivo.
- [ ] Conservo salidas ante carga rechazada y no publico datos parciales.
- [ ] Distingo serialización de copia de almacenamiento interno.

Conserva el archivo válido y uno malformado de prueba dentro de `build`, con sus resultados. Continúa con la [Unidad 20 — Memoria dinámica](../unidad20-memoria/README.md); después administrarás propietarios y préstamos, y depurarás resultados.

---

### ¿Necesitas apoyo con este tema?

Si te bloqueaste con la práctica, necesitas revisar tu entorno o adaptar lo aprendido a tu proyecto, podemos trabajarlo en una sesión personalizada.

[**Solicitar asesoría para este tema por WhatsApp**](https://wa.me/573103618296?text=Hola%2C%20Leli.%20Estoy%20estudiando%2019%20%C2%B7%20Archivos%20de%20texto%20del%20curso%20C%20desde%20cero%20%28https%3A%2F%2Fgithub.com%2Flelyliliana%2FCurso-C%2Ftree%2Fmain%2Funidad19-archivos%29%20y%20necesito%20una%20asesor%C3%ADa%20personalizada.%20Mi%20duda%20es%E2%80%A6)
