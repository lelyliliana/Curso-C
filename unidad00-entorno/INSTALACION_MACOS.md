# Instalar las herramientas en macOS

[Volver a la Unidad 00](README.md)

## Paso 1. Abrir Terminal

Abre **Aplicaciones → Utilidades → Terminal**, o busca Terminal con Spotlight.

## Paso 2. Comprobar Clang

```bash
clang --version
```

Si responde con información de Apple Clang, pasa al paso 4. Si macOS presenta una solicitud de instalación de herramientas de desarrollo, sigue el procedimiento del paso 3.

## Paso 3. Instalar las herramientas de línea de comandos

```bash
xcode-select --install
```

El comando solicita la instalación de las herramientas de desarrollo de Apple. Sigue el diálogo del sistema y espera a que termine. No necesitas instalar el entorno completo de Xcode para estas primeras prácticas.

Si indica que las herramientas ya están instaladas, comprueba otra vez `clang --version`. Para errores de instalación o incompatibilidad, consulta la [documentación de Apple](https://developer.apple.com/documentation/xcode/installing-the-command-line-tools).

## Paso 4. Preparar el editor

Si ya utilizas VS Code, conserva tu instalación. De lo contrario, sigue la [guía oficial para macOS](https://code.visualstudio.com/docs/setup/mac).

Instala la extensión **C/C++** de Microsoft. La extensión ayuda a editar; utilizaremos Clang para compilar C.

## Paso 5. Comprobar la terminal integrada

Abre **Terminal → Nueva terminal** en VS Code y ejecuta `clang --version`. Debe responder también allí.

En este curso, donde una instrucción general usa `gcc`, cambia el primer nombre del comando por `clang`. Conserva las demás opciones. Por ejemplo:

```bash
clang -std=c17 -Wall -Wextra -Wpedantic hola.c -o hola
```

Este comando se utilizará después de escribir el programa en la Unidad 01; no compiles aún el archivo que contiene solo un comentario.

## Diagnóstico

- Si la instalación no termina, revisa el mensaje del sistema y la documentación de Apple.
- Si Clang responde pero no encuentra `hola.c`, revisa carpeta actual y nombre; no reinstales las herramientas.
- Si `gcc --version` muestra Apple Clang, no significa necesariamente que instalaste GCC. Para evitar confusiones utilizamos el nombre `clang` explícitamente.

[Regresa a la Unidad 00](README.md#4-crear-la-carpeta-de-práctica).
