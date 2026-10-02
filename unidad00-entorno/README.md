# Unidad 00 — Preparar el entorno

[Inicio del curso](../README.md) · [Siguiente: tu primer programa](../unidad01-primer-programa/README.md)

## Lo que vas a lograr

Al terminar podrás distinguir el editor, la terminal y el compilador; comprobar que tu compilador responde; crear una carpeta de trabajo y guardar un archivo `.c` en el lugar correcto.

**Antes de empezar:** reserva tiempo para la instalación y trabaja con una conexión a Internet. Instalar herramientas puede requerir permisos de administración. Si utilizas un equipo institucional sin esos permisos, pide apoyo al responsable; no cambies su configuración por ensayo y error.

## 1. Comprender las herramientas

Imagina que escribes las instrucciones para preparar una receta. Necesitas un lugar para escribirlas, alguien que interprete esas instrucciones y un lugar para ponerlas en práctica. La analogía ayuda a separar responsabilidades, aunque un compilador no cocina ni entiende intenciones.

| Elemento | Qué hace | Ejemplo |
|---|---|---|
| Editor | Permite escribir y guardar código como texto | VS Code |
| Código fuente | Contiene las instrucciones escritas por ti | `hola.c` |
| Compilador | Traduce el programa y participa en la construcción del ejecutable | GCC o Clang |
| Ejecutable | Es el archivo que el sistema puede iniciar | `hola` o `hola.exe` |
| Terminal | Permite escribir comandos y leer sus respuestas | Terminal de Ubuntu o MSYS2 UCRT64 |

La terminal no es el compilador. Desde la terminal le pides al compilador que trabaje. VS Code tampoco incluye por sí solo el compilador: instalar una extensión añade ayuda al editor, pero aún necesitas la herramienta que construye tu programa.

Un archivo Word no sirve como código fuente: puede contener formato y datos ajenos al texto de C. Usa un editor de texto plano.

## 2. Elegir un solo recorrido de instalación

Abre únicamente la guía de tu sistema:

- [Ubuntu](INSTALACION_UBUNTU.md).
- [Windows con MSYS2 UCRT64](INSTALACION_WINDOWS.md).
- [macOS con Clang](INSTALACION_MACOS.md).

En Windows utilizaremos la terminal **MSYS2 UCRT64** para los comandos iniciales. Los comandos de instalación de Ubuntu no sirven en PowerShell, y `pacman` no es un comando de Ubuntu. Cada guía indica dónde escribir.

Estas guías te llevan hasta una comprobación del compilador. No sigas a la Unidad 01 hasta que `gcc --version` o `clang --version` respondan en la terminal que utilizarás para compilar.

## 3. Leer un comando sin copiar el indicador de la terminal

Un tutorial puede mostrar algo así:

```text
usuario@equipo:~$ gcc --version
```

El texto anterior al comando es el **indicador de la terminal**: informa dónde estás y que puedes escribir. Lo único que debes introducir es:

```bash
gcc --version
```

Presiona Enter para ejecutarlo. `--version` pide información de la herramienta; no compila ni modifica tu programa. En macOS utiliza `clang --version`.

Si ves una versión, el comando existe en esa terminal. No significa todavía que hayas compilado un programa: esa comprobación ocurre en la siguiente unidad.

Si no responde, vuelve a la sección de diagnóstico de tu guía. No descargues otro compilador antes de saber qué falta.

## 4. Crear la carpeta de práctica

Usa el administrador de archivos de tu sistema para crear una carpeta llamada `practicas-c` dentro de tu carpeta personal. Dentro crea otra llamada `unidad01`.

La carpeta personal suele ser `/home/tu_usuario` en Ubuntu, `C:\Users\tu_usuario` en Windows y `/Users/tu_usuario` en macOS. **Son ejemplos de ubicación:** `tu_usuario` representa tu nombre real, no una carpeta que debas crear.

Utiliza nombres sencillos al comenzar. Los espacios son válidos, pero exigen comillas en muchos comandos y pueden distraerte durante la primera práctica.

Abre VS Code y utiliza **Archivo → Abrir carpeta**. Selecciona `practicas-c`. El explorador del editor debe mostrar `unidad01` dentro de ella.

## 5. Guardar un archivo real de C

Dentro de `unidad01`, crea un archivo llamado `hola.c`. Puedes escribir por ahora este comentario:

```c
/* Mi primer archivo de practica. */
```

Guárdalo con Ctrl+S; en macOS, Command+S. Esto prepara el archivo: el comentario solo no constituye el programa que construiremos en la Unidad 01.

Comprueba lo siguiente:

1. El nombre termina en `.c`, no en `.cpp` ni en `.txt`.
2. El archivo está dentro de `practicas-c/unidad01`.
3. VS Code identifica el lenguaje como C en su barra de estado.
4. Ya no aparece el indicador de cambios sin guardar en la pestaña.

En Windows activa **Ver → Mostrar → Extensiones de nombre de archivo** en el Explorador; el nombre exacto del menú puede variar. Así podrás detectar `hola.c.txt`, que aparenta ser `hola.c` si las extensiones están ocultas.

## 6. Entender dónde está trabajando la terminal

Una terminal tiene una **carpeta actual**. Cuando escribes `hola.c` sin una ubicación completa, la herramienta busca el archivo en esa carpeta.

En Ubuntu y macOS puedes abrir la terminal integrada de VS Code desde **Terminal → Nueva terminal**. En Windows, abre MSYS2 UCRT64 desde Inicio; la guía de Windows explica cómo llegar a la carpeta de práctica.

En estas terminales puedes escribir:

```bash
pwd
```

`pwd` muestra la carpeta actual. No la cambia.

Para listar su contenido:

```bash
ls
```

Si estás en `practicas-c`, entra a su subcarpeta:

```bash
cd unidad01
```

`cd` cambia la carpeta actual. Ahora ejecuta `pwd` y luego `ls`; deberías estar dentro de `unidad01` y ver `hola.c`.

Si ves `No such file or directory`, comprueba con `pwd` y `ls` dónde estás. No basta con abrir el archivo en el editor: la terminal puede estar en otra carpeta.

## 7. Obtener los ejemplos del curso sin usar Git

Puedes escribir los ejemplos siguiendo las explicaciones; esto es suficiente para iniciar. Si prefieres obtener todos los archivos:

1. Abre la página principal del repositorio en GitHub.
2. Pulsa **Code → Download ZIP**.
3. Extrae el ZIP con el administrador de archivos. No trabajes dentro del archivo comprimido.
4. Abre la carpeta extraída en VS Code.
5. Busca `unidad01-primer-programa/ejemplos`.

En una página de archivo individual, el botón **Raw** permite ver su texto sin la interfaz de GitHub. Evita guardar una página HTML con el nombre `hola.c`: contener un nombre correcto no convierte su contenido en código de C.

Descargar un ZIP crea una copia local; no sincroniza futuras actualizaciones. Para actualizaciones frecuentes podrás aprender Git más adelante.

## Práctica de comprobación

Sin consultar la tabla del inicio, responde:

1. ¿Qué herramienta permite escribir el archivo?
2. ¿Qué herramienta construirá el ejecutable?
3. ¿Dónde escribes `gcc --version`?
4. Si `ls` no muestra `hola.c`, ¿qué comprobarías antes de compilar?

Después realiza estas acciones: abre tu carpeta, guarda `hola.c`, verifica la versión del compilador y muestra con `ls` que la terminal está en el lugar correcto.

**Respuestas orientativas:** editor; compilador; terminal; ubicación actual y lugar donde guardaste el archivo. Instalar otra extensión no resuelve una ruta incorrecta.

## Antes de avanzar

- [ ] Puedo explicar editor, terminal, compilador y ejecutable con mis palabras.
- [ ] Mi compilador responde en la terminal elegida.
- [ ] Tengo `hola.c` guardado y conozco su ubicación.
- [ ] Puedo entrar a su carpeta y listar el archivo.
- [ ] Sé que aún debo escribir el programa y compilarlo.

Si algo falla, anota el sistema operativo, la terminal utilizada, el comando exacto y su respuesta. Esa información es más útil que «no funciona».

[Continúa con la Unidad 01](../unidad01-primer-programa/README.md).
