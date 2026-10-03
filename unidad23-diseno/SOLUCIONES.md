# Soluciones — Unidad 23

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Criterios observables

| Caso | Resultado | Efecto |
|---|---|---|
| Agregar A=0 a vacío | `AGENDA_OK` | Un registro con valor cero |
| Agregar A=100 cuando A=0 existe | `AGENDA_DUPLICADO` | A sigue en cero; cantidad igual |
| Actualizar Z ausente | `AGENDA_AUSENTE` | Agenda intacta |
| Quitar B de A/B/C | `AGENDA_OK` | A/C en ese orden |
| Resumir vacío | `false` | Salida previa intacta |
| Agregar un nombre nuevo a cien registros | `AGENDA_LIMITE` | Los cien registros y metadatos se conservan |

El límite se prueba con nombres distintos y válidos; usar repetidamente A solo comprobaría duplicados. Las reservas pueden fallar antes de llegar al límite y ese estado debe distinguirse.

## 2. Una posición cambia

C pasa de índice dos a índice uno. Volver a buscar por nombre produce su nueva posición. Una salida previa 99 permanece igual si `buscar_sensor` devuelve `false`; no se utiliza ese 99 para indexar. La posición solo se interpreta cuando la búsqueda tuvo éxito y mientras ninguna operación altere la colección.

## 3. Reglas de la aplicación

El contenedor administra memoria; la agenda añade unicidad por coincidencia exacta. A y a pueden coexistir. Cambiar a comparación sin distinguir mayúsculas exigiría una política explícita de normalización y una comparación coherente en búsqueda, inserción, revisión de unicidad e importación. No basta modificar únicamente el menú. El curso no incluye una solución Unicode general bajo ese cambio.

## 4. Programa completo

Fuente: [04-filtrar.c](soluciones/04-filtrar.c).

1. Desde `unidad23-diseno`, crea `build` como indica la guía.
2. Compila:

```sh
gcc -std=c17 -Wall -Wextra -Wpedantic soluciones/04-filtrar.c proyecto/agenda.c ../unidad21-recursos/proyecto/catalogo.c ../unidad17-estructuras/proyecto/sensor.c ../unidad19-archivos/proyecto/archivo.c ../unidad16-lineas/proyecto/entrada.c -o build/filtrar
```

3. Ejecuta `./build/filtrar`; Windows añade `.exe`, macOS usa `clang`.
4. Compara `B: 50`, `C: 100` y `Encontrados: 2; agenda: 3`, cada uno en una línea.

El recorrido observa registros inicializados y cuenta coincidencias; no elimina elementos ni requiere reservar otra colección. La limpieza devuelve el bloque incluso si no se pudo completar alguno de los agregados.
