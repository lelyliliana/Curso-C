# Unidad 25 — Construcción reproducible y entrega final

[Inicio](../README.md) · [Anterior: aplicación](../unidad24-aplicacion/README.md)

## El problema que resolverás

La aplicación ya funciona, pero compilar requiere recordar varios fuentes y dependencias. Aquí automatizarás la construcción con GNU make y prepararás una entrega que otra persona pueda verificar. Automatizar no cambia las reglas del programa: organiza cómo generar sus objetos, enlazar y ejecutar pruebas.

Esta unidad cierra el recorrido introductorio mediante el proyecto integrador de las unidades 23–24. No incluye hardware, concurrencia, bases de datos, Unicode general ni estructuras como árboles o tablas hash. Esas son posibles ampliaciones; no se presentan como contenido ya desarrollado.

## 1. Comprender una regla pequeña

El [Makefile](Makefile) tiene objetivos, prerrequisitos y recetas. Un objetivo puede ser un archivo generado o una acción. Sus prerrequisitos describen de qué depende. La receta indica el comando para producirlo o realizar la acción. Make compara existencia y fechas para decidir qué necesita reconstruirse.

Las líneas de receta de este archivo comienzan con una tabulación real. Espacios visualmente parecidos pueden producir `missing separator`. El Makefile incluido ya contiene las tabulaciones; configura el editor para conservarlas al modificarlo.

No confundas `make` con el compilador: make invoca GCC mediante sus recetas. Un archivo C válido puede fallar por una receta incorrecta, y una receta correcta puede fallar porque el fuente no compila.

## 2. Preparar la herramienta sin cambiar de entorno

1. En Ubuntu, comprueba `make --version`. Si falta, consulta el procedimiento de herramientas de compilación de la [Unidad 00](../unidad00-entorno/README.md) y la documentación de paquetes del sistema.
2. En Windows, usa la terminal **MSYS2 UCRT64** para este Makefile: necesita comandos de shell como `mkdir` y `rm`. No se afirma que funcione directamente desde PowerShell con cualquier herramienta llamada make. Comprueba `make --version`; si no existe, consulta los paquetes de tu instalación de MSYS2.
3. En macOS, comprueba `make --version` y que sea GNU make. No todas las herramientas predeterminadas cumplen lo mismo; si la instalación proporciona el comando `gmake`, úsalo donde esta guía diga `make`. La compilación C se realiza con `CC=clang`.
4. Si la herramienta no está disponible, puedes seguir usando el comando completo de la Unidad 24. No necesitas instalar otro sistema operativo para terminar el proyecto.

La construcción se verificó con GNU make y GCC en Ubuntu. No se ejecutó esta receta en Windows ni macOS. La disponibilidad y nombres de paquetes se consultan en fuentes oficiales; aquí no fijamos un instalador fechado.

## 3. Primera construcción

1. Desde la carpeta del curso entra con `cd unidad25-construccion`.
2. En Ubuntu ejecuta `make`. En MSYS2 UCRT64 utiliza `make EXE=.exe`. En macOS, con GNU make disponible, usa `make CC=clang`.
3. Lee los comandos generados. Primero compila cada fuente a `.o`; después enlaza el ejecutable.
4. Ejecuta `./build/agenda_app` o `./build/agenda_app.exe` en Windows.
5. Prueba la primera sesión de la [Unidad 24](../unidad24-aplicacion/README.md), recordando que ahora las rutas relativas se interpretan desde `unidad25-construccion`.
6. Termina con `0` y vuelve a ejecutar el mismo comando make sin modificar fuentes. No debería recompilar objetos que siguen actualizados.

El ejecutable utiliza exactamente los fuentes del proyecto anterior; no guardamos otra copia de su lógica en esta carpeta. El objetivo predeterminado `all` construye la aplicación. La carpeta `build` se crea antes de los objetos.

## 4. Leer las variables y dependencias

| Elemento | Función |
|---|---|
| `CC` | Compilador, GCC por defecto; se puede elegir con `CC=clang` |
| `CFLAGS` | Estándar, advertencias y opciones de compilación |
| `CPPFLAGS` | Opciones del preprocesador, por ejemplo rutas de inclusión |
| `LDFLAGS` / `LDLIBS` | Opciones de enlace y bibliotecas al final |
| `EXE` | Sufijo vacío o `.exe` |
| `$<` | Primer prerrequisito, el fuente de una regla de objeto |
| `$@` | Nombre del objetivo que se genera |
| `$^` | Lista de prerrequisitos para enlazar |

`-MMD -MP` genera archivos `.d` con dependencias de encabezados; `-include` los incorpora cuando existen. Así cambiar una interfaz recompila los objetos que la incluyen. El prerrequisito de orden `| build` exige la carpeta sin provocar reconstrucción solo porque su fecha cambie.

`all`, `test` y `clean` se declaran `.PHONY`: representan acciones y no se consideran satisfechas por archivos que casualmente tengan esos nombres. La receta `test` ejecuta una prueba real; un fallo del programa produce un fallo de make, en lugar de imprimir un mensaje de éxito sin comprobarlo.

Make no detecta automáticamente que cambiaste compilador u opciones si los archivos fuente siguen iguales. Después de cambiar `CC`, `CFLAGS` o instrumentación, limpia y reconstruye. Los `.d` cubren dependencias de archivos, no todo el entorno ni todas las decisiones de configuración.

## 5. Pruebas y limpieza, paso a paso

1. Ejecuta `make test` en Ubuntu, `make test EXE=.exe` en MSYS2 UCRT64 o `make test CC=clang` con GNU make en macOS.
2. Espera `Pruebas de agenda: OK.`. Ese objetivo cubre el dominio de la Unidad 23; **no ejecuta todas las pruebas de persistencia ni sesiones completas**. Realiza esas comprobaciones siguiendo la Unidad 24.
3. Crea, si necesitas practicar, un archivo de datos `build/conservar.txt` distinto de los productos de compilación.
4. Ejecuta `make clean`, manteniendo `EXE=.exe` en Windows cuando corresponda.
5. Comprueba que desaparecieron objetos, dependencias y los dos ejecutables conocidos; el archivo de datos continúa.
6. Ejecuta make otra vez para reconstruir.

La limpieza no elimina toda la carpeta `build`: una carpeta de trabajo puede contener archivos de datos creados por la persona. Tampoco ejecutes reglas de limpieza de un proyecto desconocido sin leer qué rutas borran. En este archivo no cambies `BUILD` a una carpeta de datos ajena.

Para una revisión estricta:

1. Limpia los productos previos.
2. Ejecuta `make CFLAGS='-std=c17 -Wall -Wextra -Wpedantic -Werror -g -O0'` en el shell indicado.
3. Ejecuta `make test` con las mismas opciones y sufijo correspondiente.
4. Si agregas sanitizadores, utiliza sus opciones en compilación **y enlace**, limpia previamente y respeta los límites descritos en la [Unidad 22](../unidad22-depuracion/README.md).

`-Werror` convierte advertencias en errores para esta revisión; no demuestra ausencia de defectos lógicos. La variante de media defectuosa de la Unidad 22 muestra por qué también hay que contrastar resultados.

## 6. Evidencias de una entrega verificable

Incluye fuentes y un README propio que permita a otra persona repetir la construcción. No incluyas binarios, objetos, `.d`, archivos de prueba con información sensible ni una copia de credenciales. La carpeta `build` está excluida en el `.gitignore` del curso.

La entrega final debe contener:

- Propósito, requisitos y límites: cien nombres únicos, valores 0–100 y formato `C-AGENDA-1`.
- Mapa de módulos y comandos de compilación y ejecución, con sistema realmente utilizado.
- Una sesión reproducible de agregado, búsqueda, actualización, borrado, resumen, guardado y nueva carga.
- Al menos un rechazo de entrada, uno de duplicado y uno de archivo, comprobando que no se cambia el estado anterior.
- Resultados de pruebas, defectos corregidos y limitaciones todavía conocidas.
- Explicación de quién libera cada bloque y cuándo vencen los préstamos.

Si usas asistencia automatizada durante tu trabajo, explica las partes que revisaste y qué decisiones puedes justificar.

## 7. Evaluar y continuar

[ENTREGA.md](ENTREGA.md) contiene hitos y una rúbrica. Resuelve [EJERCICIOS.md](EJERCICIOS.md) y consulta [SOLUCIONES.md](SOLUCIONES.md) para analizar construcción incremental y alcance de las pruebas.

Conserva una limitación concreta junto con una propuesta: por ejemplo, «guardado exclusivo, sin reemplazo atómico; una ampliación deberá diseñar y verificar recuperación ante fallos». Decir «el programa es perfecto» no es una evaluación técnica.

El curso introductorio llega hasta una aplicación modular con entrada validada, datos dinámicos, archivos y pruebas. C++ es un recorrido diferente; haber aprendido C no exige mezclar clases, `new` o compilación con `g++` dentro de este proyecto.

---

### ¿Necesitas apoyo con este tema?

Si te bloqueaste con la práctica, necesitas revisar tu entorno o adaptar lo aprendido a tu proyecto, podemos trabajarlo en una sesión personalizada.

[**Solicitar asesoría para este tema por WhatsApp**](https://wa.me/573103618296?text=Hola%2C%20Leli.%20Estoy%20estudiando%2025%20%C2%B7%20GNU%20make%20y%20entrega%20final%20del%20curso%20C%20desde%20cero%20%28https%3A%2F%2Fgithub.com%2Flelyliliana%2FCurso-C%2Ftree%2Fmain%2Funidad25-construccion%29%20y%20necesito%20una%20asesor%C3%ADa%20personalizada.%20Mi%20duda%20es%E2%80%A6)
