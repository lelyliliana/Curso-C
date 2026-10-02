# Instalar las herramientas en Windows con MSYS2 UCRT64

[Volver a la Unidad 00](README.md)

Este recorrido utiliza Windows de 64 bits en un equipo x86-64 y GCC mediante **MSYS2 UCRT64**. Si tu equipo es ARM64, no copies la selección de paquete de esta guía: consulta los entornos compatibles en la documentación oficial.

## Paso 1. Instalar MSYS2

Visita [msys2.org](https://www.msys2.org/), descarga el instalador oficial para x86-64 y sigue el asistente. Conserva la carpeta sugerida `C:\msys64` si no tienes una razón para cambiarla.

MSYS2 proporciona herramientas y un administrador de paquetes. UCRT64 es el entorno que utilizaremos para construir programas nativos de Windows.

## Paso 2. Abrir la terminal adecuada

Busca **MSYS2 UCRT64** en el menú Inicio. Ábrela y verifica que el indicador de la terminal contiene `UCRT64`.

No utilices una ventana titulada únicamente MSYS, ni PowerShell, para los comandos `pacman` de esta guía. Instalar MSYS2 no hace que todos sus comandos estén disponibles automáticamente en cualquier terminal.

## Paso 3. Actualizar MSYS2

```bash
pacman -Syu
```

El comando sincroniza la información de paquetes y actualiza el sistema MSYS2. Lee las preguntas antes de confirmar.

Si solicita cerrar la terminal para completar una actualización, sigue esa indicación. Vuelve a abrir **MSYS2 UCRT64** y ejecuta de nuevo `pacman -Syu` hasta que finalice sin actualizaciones pendientes. No cierres una instalación que está trabajando salvo que el propio procedimiento te lo indique.

## Paso 4. Instalar GCC para UCRT64

En esa misma terminal:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc
```

`-S` solicita la instalación del paquete y `--needed` evita reinstalar paquetes que ya están actualizados. El nombre identifica GCC para este entorno concreto.

Comprueba:

```bash
gcc --version
```

Debes obtener información de GCC. Si dice que no encuentra el comando, verifica que la ventana es UCRT64 y que la instalación terminó sin errores.

## Paso 5. Preparar VS Code

Si no lo tienes, instala VS Code siguiendo su [guía oficial para Windows](https://code.visualstudio.com/docs/setup/windows). En Extensiones, instala **C/C++**, del publicador **Microsoft**.

Usa VS Code para escribir y guardar el archivo; utiliza MSYS2 UCRT64 para compilarlo en las primeras prácticas. No necesitas modificar el PATH global de Windows para seguir este recorrido.

La terminal integrada de VS Code puede abrir PowerShell de forma predeterminada. Que `gcc` no aparezca allí no demuestra que la instalación falló: verifica primero en UCRT64.

## Paso 6. Llegar a la carpeta de práctica

Crea `practicas-c` dentro de tu carpeta personal de Windows, y dentro crea `unidad01`.

En MSYS2, una ubicación Windows como `C:\Users\Leli\practicas-c\unidad01` se escribe como `/c/Users/Leli/practicas-c/unidad01`.

Introduce tu ruta real entre comillas, por ejemplo:

```bash
cd "/c/Users/Leli/practicas-c/unidad01"
```

Sustituye `Leli` si tu usuario tiene otro nombre. Si guardaste en OneDrive o en otra unidad, la ruta también será distinta. Busca la ubicación desde el Explorador; no pruebes nombres al azar.

Ahora escribe `pwd` y después `ls`. Al guardar `hola.c` en esa carpeta desde VS Code, `ls` debe mostrarlo.

## Paso 7. Recordar cómo ejecutar

En la Unidad 01 producirás `hola.exe`. Desde **MSYS2 UCRT64** se ejecuta así:

```bash
./hola.exe
```

En PowerShell la sintaxis sería `./hola.exe` o `.\hola.exe`, pero los comandos de instalación y navegación de esta guía están pensados para UCRT64. No cambies de terminal a mitad de la práctica sin identificar sus diferencias.

## Diagnóstico

| Situación | Acción |
|---|---|
| `pacman` no se reconoce | Abre MSYS2 UCRT64; no ejecutes su instalación en PowerShell |
| `gcc` no se encuentra | Comprueba UCRT64, el paquete instalado y los mensajes de instalación |
| `cd` dice que la ruta no existe | Revisa tu usuario, unidad y posible carpeta OneDrive |
| El archivo resulta ser `hola.c.txt` | Activa la visualización de extensiones y corrige el nombre |
| Un programa se cierra al hacer doble clic | Ejecútalo desde la terminal para conservar visible su salida |

[Regresa a la Unidad 00](README.md#4-crear-la-carpeta-de-práctica).
