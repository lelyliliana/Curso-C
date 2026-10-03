# Unidad 22 — Depurar con hipótesis y pruebas

[Inicio](../README.md) · [Anterior: recursos](../unidad21-recursos/README.md)

## El problema que resolverás

Un programa muestra la media de 1 y 2 como `1.00`. Compila sin advertencias, termina con éxito y no accede fuera de sus límites. Aun así, el resultado es incorrecto. Aprenderás a reproducir el fallo, localizar el paso que pierde información, corregirlo y conservar una prueba que lo detecte.

Necesitas tipos, división, funciones y colecciones. La solución final también conecta el módulo de memoria de la [Unidad 20](../unidad20-memoria/README.md). No debes modificar varias cosas al azar: cada prueba responde a una hipótesis concreta.

## 1. Reproducir antes de corregir

El fuente [media_defectuosa.c](ejemplos/media_defectuosa.c) tiene un **defecto lógico intencional**. Está separado de la [implementación correcta](proyecto/media.c); ambos definen la misma función. Enlaza una sola implementación en cada ejecutable.

1. Desde la carpeta del curso entra con `cd unidad22-depuracion`.
2. Crea `build`: `mkdir -p build` en Ubuntu/macOS o `New-Item -ItemType Directory -Force build` en PowerShell.
3. Compila la variante defectuosa según tu sistema.
4. Ejecuta el resultado y registra lo observado antes de leer la corrección.

| Sistema | Compilar | Ejecutar |
|---|---|---|
| Ubuntu | `gcc -std=c17 -Wall -Wextra -Wpedantic -g -O0 proyecto/main.c ejemplos/media_defectuosa.c -o build/defecto` | `./build/defecto` |
| Windows UCRT64 | `gcc -std=c17 -Wall -Wextra -Wpedantic -g -O0 proyecto/main.c ejemplos/media_defectuosa.c -o build/defecto.exe` | `./build/defecto.exe` |
| macOS | `clang -std=c17 -Wall -Wextra -Wpedantic -g -O0 proyecto/main.c ejemplos/media_defectuosa.c -o build/defecto` | `./build/defecto` |

Obtendrás `Media: 1.00`, pero la media esperada es 1.5. El formato `%.2f` explica los dos decimales mostrados, no la pérdida de la fracción. El código de salida cero significa que el programa siguió su ruta de éxito, no que alguien comprobó la fórmula.

`-g` añade información para depuración y `-O0` reduce la optimización para facilitar relacionar instrucciones y fuente. Son opciones del compilador, no del lenguaje. La versión de publicación puede tener otra configuración; aquí buscamos observar la ejecución con claridad.

## 2. Formar una hipótesis comprobable

| Pregunta | Observación necesaria |
|---|---|
| ¿Se sumaron los dos datos? | Total antes de dividir: 3 |
| ¿La cantidad es correcta? | Cantidad: 2 |
| ¿Se perdió la fracción antes de guardar? | Comparar división entera y división en `double` |
| ¿El formato elimina la fracción? | Observar `media` antes de imprimir |

Puedes comenzar siguiendo el código a mano. Las primeras iteraciones llevan total de cero a uno y después a tres. La expresión defectuosa convierte a `double` **después** de `total / cantidad`. Los dos operandos son enteros: la división ya produjo uno. Convertir ese uno obtiene 1.0, no recupera el 0.5 que se descartó.

La corrección convierte antes de dividir: `(double)total / (double)cantidad`. No sirve cambiar únicamente `%.2f`, añadir otro decimal ni convertir la variable destino. Cambia el lugar en que la operación pasa al dominio de punto flotante.

## 3. Observar con GDB, paso a paso

Este recorrido es opcional si tienes GDB disponible. El razonamiento y las pruebas se pueden realizar sin instalarlo. La compilación y ejecución de los programas se verificaron con GCC en Ubuntu; esta sesión interactiva **no se ejecutó en el entorno de verificación**, donde GDB no estaba instalado. No afirmamos haber validado sesiones de GDB en Windows ni de LLDB en macOS.

1. En Ubuntu, escribe `gdb --version`. Si el comando no está disponible, continúa con la sección de pruebas. Si decides instalarlo, consulta primero la documentación de paquetes de tu sistema; no copies un nombre de paquete para otro entorno.
2. Con el ejecutable defectuoso compilado, abre `gdb ./build/defecto`.
3. Dentro de GDB escribe `break calcular_media` y después `run`. El programa debería detenerse al entrar en la función.
4. Escribe `print cantidad` y `print datos[0]`. Deberían mostrar 2 y 1.
5. Escribe `list` para ver el código. Usa `next`, una instrucción cada vez, hasta terminar el ciclo y **antes** de asignar `media`. El depurador suele mostrar la próxima línea por ejecutar: que una línea aparezca no significa que ya se ejecutó. No leas `media` antes de su inicialización.
6. Escribe `print total`, `print total / cantidad` y `print (double)total / (double)cantidad`. Deberías observar 3, 1 y 1.5.
7. Escribe `next` para ejecutar la asignación defectuosa; luego `print media`. Observa 1. Usa `bt` para ver la pila de llamadas.
8. Escribe `continue` para terminar y `quit` para salir del depurador.

`next` avanza sin entrar en las funciones llamadas; `step` intenta entrar. `print` observa una expresión; `bt` muestra qué llamadas condujeron al punto actual. Las direcciones, números de línea y mensajes exactos cambian con el entorno. No necesitas que coincidan con una captura para comprender el dato observado.

Si utilizas Windows UCRT64, la disponibilidad de GDB depende de las herramientas instaladas. En macOS puede estar disponible LLDB, cuya interfaz es distinta: este recorrido no cambia automáticamente los comandos de GDB por comandos válidos de LLDB. La ruta común del curso sigue siendo compilación, casos reproducibles y comprobación de resultados.

## 4. Corregir y comparar

1. Lee [media.c](proyecto/media.c) y localiza la diferencia en la expresión.
2. Compila con el mismo controlador y la implementación correcta:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic -g -O0 proyecto/main.c proyecto/media.c -o build/correcto
```

3. Ejecuta `./build/correcto`. En Windows agrega `.exe`; en macOS usa `clang`.
4. Comprueba `Media: 1.50`.
5. No enlaces simultáneamente `media.c` y `media_defectuosa.c`: ambos definen `calcular_media` y producirían un conflicto de enlace.

La función valida datos 0–100, cantidad hasta 1000, nulidad y salida. Utiliza `unsigned long` para un total máximo de 100000, representable incluso con el mínimo garantizado para ese tipo. Cantidad cero devuelve `MEDIA_VACIO`, sin dividir ni inventar una media cero. Todos los rechazos conservan el valor anterior de la salida.

El `-1.0` del controlador es solo un valor inicial para observar si se escribió; no representa una lectura válida ni se publica como media de una colección vacía. El estado de la función decide si existe un resultado.

## 5. Conservar una prueba de regresión

1. Abre [pruebas_media.c](proyecto/pruebas_media.c).
2. Compílalo con `proyecto/media.c`, salida `build/pruebas_media` o `.exe`, usando las opciones anteriores.
3. Ejecuta. Espera `Pruebas de media: OK.`.
4. Observa la comprobación de `{1, 2}`: exige un resultado próximo a 1.5.
5. Revisa además iguales, extremos, vacío, dato inválido y argumentos.

Una prueba de regresión conserva el caso que detectó el defecto. Probar únicamente `{2, 4}` no habría descubierto la división entera porque su media es entera. Elegir casos discriminantes importa más que acumular ejecuciones iguales.

La tolerancia 0.000000001 corresponde al dominio pequeño de este ejercicio; no es una tolerancia universal para cualquier magnitud o algoritmo numérico. La igualdad exacta no sirve en general para resultados aproximados. Las aserciones permanecen activas; estos fuentes rechazan `NDEBUG`. La validación pública no depende de ellas.

Para comprobar que una prueba detecta el defecto, se puede construir temporalmente el mismo fuente de pruebas con la implementación defectuosa. Esa ejecución debe fallar: no se interpreta como éxito ni se presenta como una solución. En algunos sistemas un fallo de aserción puede producir un archivo de diagnóstico; no hace falta ese ensayo para ejecutar la versión correcta.

## 6. Instrumentar memoria no comprueba la fórmula

GCC puede añadir comprobaciones en tiempo de ejecución. En un entorno que disponga de los sanitizadores:

1. Compila la versión correcta:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic -g -O0 -fsanitize=address,undefined -fno-sanitize-recover=all proyecto/pruebas_media.c proyecto/media.c -o build/pruebas_instrumentadas
```

2. Ejecuta `./build/pruebas_instrumentadas`.
3. Lee los diagnósticos completos si aparecen y vuelve al caso mínimo que los produce.
4. Si el compilador o el sistema no ofrece ese soporte, utiliza las pruebas normales; no interpretes la ausencia de la herramienta como una aprobación del código.

AddressSanitizer ayuda a detectar ciertos accesos de memoria inválidos y UndefinedBehaviorSanitizer ciertas operaciones de comportamiento indefinido. No detectan todos los errores ni demuestran que la media sea correcta. La variante defectuosa realiza una división entera válida: la prueba del resultado es la que revela ese defecto.

La disponibilidad de detección de fugas depende de plataforma y configuración; no afirmamos que `-fsanitize=address` cubra todas las fugas en todos los sistemas. En este bloque las pruebas externas también simulan fallos de asignación pequeños y comprueban qué propietario conserva cada bloque. No confundas una ejecución instrumentada sin diagnóstico con cobertura de todas las rutas.

## 7. Un informe con memoria administrada

Resuelve [EJERCICIOS.md](EJERCICIOS.md). [SOLUCIONES.md](SOLUCIONES.md) incluye un informe completo que construye una colección dinámica, calcula la media y limpia sus recursos tanto al tener éxito como ante fallo.

Al depurar, conserva siempre estos datos: caso mínimo, resultado esperado, resultado observado, hipótesis, evidencia y prueba final. Si una modificación no responde a la hipótesis, sepárala para no confundir el resultado.

- [ ] Distingo errores de compilación, enlace, ejecución y lógica.
- [ ] Puedo reproducir el fallo con dos datos.
- [ ] Observo un valor solo después de inicializarlo.
- [ ] Explico qué prueba distingue el algoritmo correcto del defectuoso.
- [ ] Compruebo rechazos y conservación de salidas.
- [ ] Distingo los límites de las pruebas y las herramientas.

Con este bloque puedes construir colecciones dinámicas, administrar recursos y verificar resultados. El siguiente bloque desarrollará un proyecto integrador y sus decisiones de diseño; aún no se presenta como material publicado.
