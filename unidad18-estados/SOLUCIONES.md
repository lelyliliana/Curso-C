# Unidad 18 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Representación

La salida muestra LISTO, código 20 y DESCONOCIDO para 99. Solo se admiten 10, 20, 30 y 40; un intervalo numérico no expresa ese conjunto. El código 20 queda fuera de los índices 0–3 de un arreglo de cuatro elementos. `switch` asocia nombres sin depender de índices contiguos.

## 2. Transiciones

INICIAR desde APAGADO se rechaza; ENCENDER permite llegar a LISTO y después INICIAR a ACTIVO. DETENER vuelve a LISTO. RESTABLECER solo se permite desde FALLO. ERROR_DETECTADO se admite desde cualquier estado reconocido, incluso desde FALLO; repetirlo conserva FALLO y devuelve éxito.

## 3. Valores desconocidos

La implementación compartida [proyecto/estado.c](proyecto/estado.c) rechaza un estado 99 antes de decidir evento alguno. No lo convierte en APAGADO como reparación silenciosa. Un evento 99 desde APAGADO también se rechaza y un puntero nulo no se desreferencia.

## 4. Conteo

Fuente completo: [soluciones/04-contar.c](soluciones/04-contar.c). Construye desde la unidad:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic soluciones/04-contar.c proyecto/estado.c -o build/conteo
```

En macOS usa `clang`; en UCRT64 agrega `.exe` al destino. Ejecuta después de construir correctamente. Salida:

```text
Aceptados: 3
Rechazados: 2
Final: LISTO
```

El segundo INICIAR se rechaza porque ya está ACTIVO. DETENER se admite. RESTABLECER desde LISTO se rechaza. El conteo consulta el resultado de la implementación real y no mantiene otra tabla divergente.
