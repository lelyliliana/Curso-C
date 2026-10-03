# Unidad 19 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Recorrido

Archivo vacío: cero saltos. Dos líneas terminadas: dos. Una última línea sin terminador no agrega otro salto. Ruta inexistente: fallo de apertura. `feof` no anticipa el resultado de una lectura; la condición correcta utiliza el retorno de `fgetc` y después consulta `ferror`.

## 2. Creación exclusiva

El módulo [proyecto/archivo.c](proyecto/archivo.c) valida los datos antes de abrir con `wx`. La segunda ejecución se rechaza y conserva el archivo anterior. `w` lo truncaría al abrir y tendría otro efecto. Incluso si las escrituras retornan éxito, el cierre puede detectar un fallo pendiente; solo se confirma después de ambos.

## 3. Validación completa

Cantidad 4 y versión ajena son errores de formato. Cantidad válida mayor que capacidad es error de capacidad. Datos truncados, nombres vacíos, lecturas fuera de dominio, sufijos y separadores adicionales son errores de formato. También se rechaza contenido después de los registros declarados.

Los temporales no se publican hasta que todas las comprobaciones y el cierre pasan. El destino anterior y su cantidad no cambian ante rechazo. Una colección de cero es válida si la cabecera declara cero y el archivo termina después de esa línea.

## 4. Informe

Fuente completo: [soluciones/04-informe.c](soluciones/04-informe.c). Desde la unidad, primero construye:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic soluciones/04-informe.c proyecto/archivo.c ../unidad17-estructuras/proyecto/sensor.c ../unidad16-lineas/proyecto/entrada.c -o build/informe
```

En macOS usa `clang`; en Windows UCRT64 agrega `.exe`. Luego ejecuta con la ruta del archivo válido. Salida:

```text
Registros: 3
Suma: 125
```

Para cero registros la suma es cero. Los errores muestran `Informe rechazado.` y finalizan con fallo sin presentar una suma parcial. Tres lecturas máximas de cien dan total trescientos, dentro del dominio elegido.

## 5. Límites de las garantías

Las funciones públicas abren y cierran; el auxiliar de lectura solo usa el flujo prestado durante la llamada. Después del cierre el puntero deja de servir para operaciones, aunque el cierre haya reportado fallo.

La representación interna puede contener relleno y depender de implementación. El archivo define campos textuales y una versión. Conservar salidas de carga es una garantía distinta de escritura atómica: el guardado de un archivo nuevo puede dejarlo incompleto si ocurre un fallo. Este bloque no implementa reemplazo durable, bloqueo entre procesos ni recuperación automática.
