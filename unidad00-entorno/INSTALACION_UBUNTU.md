# Instalar las herramientas en Ubuntu

[Volver a la Unidad 00](README.md)

## Paso 1. Abrir la terminal

Abre la aplicación Terminal, o presiona Ctrl+Alt+T. Los comandos de esta página se escriben allí. No copies los indicadores `$` de otros ejemplos.

## Paso 2. Comprobar si GCC ya está disponible

```bash
gcc --version
```

Si aparece información de GCC, conserva la instalación y pasa al paso 5. No necesitas que el número de versión coincida exactamente con un tutorial. El curso utiliza C17 de manera explícita.

Si aparece que el comando no se encuentra, continúa con el paso 3.

## Paso 3. Actualizar la lista de paquetes

```bash
sudo apt update
```

`sudo` solicita permisos de administración. `apt` administra paquetes. `update` actualiza la lista de software disponible; no equivale a actualizar todos los programas instalados.

Si pide contraseña, escríbela y presiona Enter. Es habitual que no aparezcan caracteres mientras la introduces. No la compartas en capturas.

Si hay errores de conexión o repositorios, resuélvelos antes de instalar. No asumas que el paso terminó correctamente solo porque regresó el indicador de la terminal.

## Paso 4. Instalar el conjunto básico de compilación

```bash
sudo apt install build-essential
```

Este paquete incorpora las herramientas básicas necesarias para compilar, incluido GCC. Lee el resumen de paquetes y confirma si estás de acuerdo con la instalación. Espera a que termine.

Comprueba nuevamente:

```bash
gcc --version
```

Debes obtener información de GCC. Más adelante compilaremos un archivo; esta comprobación solo verifica que la herramienta se puede invocar.

## Paso 5. Preparar el editor

Si ya usas VS Code, no necesitas reinstalarlo. De lo contrario, sigue el [procedimiento oficial para Linux](https://code.visualstudio.com/docs/setup/linux).

Abre Extensiones con Ctrl+Shift+X. Busca **C/C++**, del publicador **Microsoft**, e instálala. Aporta ayuda de edición y diagnóstico; la compilación seguirá utilizando GCC.

Para comenzar no necesitas Code Runner ni configurar botones automáticos. Usaremos un comando visible para comprender el proceso.

## Paso 6. Comprobar la terminal del editor

En VS Code selecciona **Terminal → Nueva terminal** y ejecuta `gcc --version`. Si funciona en la terminal del sistema pero no en VS Code, cierra y vuelve a abrir el editor, y comprueba qué terminal estás utilizando.

## Si algo falla

| Mensaje o síntoma | Qué comprobar |
|---|---|
| `gcc: command not found` | Que terminó la instalación y estás en Ubuntu |
| No tienes permiso para usar `sudo` | Solicita instalación al administrador del equipo |
| Error de conexión durante `apt update` | Conexión y mensaje concreto del repositorio |
| GCC responde pero no encuentra tu archivo | Ubicación actual y nombre del archivo; la instalación puede estar bien |

No compiles ni ejecutes tus prácticas con `sudo`: escribir código en tu carpeta personal no lo requiere.

[Regresa al paso 4 de la Unidad 00](README.md#4-crear-la-carpeta-de-práctica).
