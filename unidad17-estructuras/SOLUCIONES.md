# Unidad 17 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Copias

El primer ejemplo cambia la lectura de 25 a 30. El segundo conserva original patio 25 y copia Patio 40; la auxiliar imprime una copia local con 99. Un arreglo incorporado es parte del valor del registro. Un miembro puntero copiaría una dirección y podría seguir compartiendo el objeto señalado.

## 2. Validación

Fuente compartido: [proyecto/sensor.c](proyecto/sensor.c). Las doce letras caben con terminador en el índice 12; trece no caben. Nombre vacío o con espacios y valores -1/101 se rechazan. Lectura cero y nombre `-` son válidos según este contrato. No se impone una regla de «primera letra» que el contrato no contiene.

## 3. Informe

Fuente completo: [soluciones/03-coleccion.c](soluciones/03-coleccion.c). Desde esta unidad construye primero:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic soluciones/03-coleccion.c proyecto/sensor.c -o build/coleccion
```

En macOS usa `clang`; en Windows UCRT64 agrega `.exe` al destino. Después ejecuta. Salida:

```text
patio: 25
salon: 0
taller: 100
Total: 125
```

Con una lectura 101 imprime solo `Registro invalido.` y finaliza con fallo. El total se presenta únicamente después de validar los tres registros.

## 4. Límite del miembro

[proyecto/pruebas_sensor.c](proyecto/pruebas_sensor.c) llena las trece posiciones con `A`. El validador limita cada acceso y devuelve falso por ausencia de terminador. Una estructura puede contener relleno que no representa campos; la igualdad se decide comparando sus valores, no todo el almacenamiento bruto.

Conserva comandos y una tabla de valores anteriores/posteriores al rechazo.
