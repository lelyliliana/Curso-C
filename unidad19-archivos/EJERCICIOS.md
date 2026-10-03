# Unidad 19 — Ejercicios

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

## 1. Contar y cerrar

Prueba el contador con archivo vacío, dos saltos finales, última línea sin salto y ruta inexistente. Explica por qué contar saltos no equivale siempre a contar líneas. ¿Qué cambiaría al utilizar `while (!feof(...))`?

## 2. Guardar y proteger un archivo existente

Crea el archivo del proyecto en una ruta nueva y examina su texto. Intenta guardar otra vez en la misma ruta: debe fallar sin alterar el contenido. Compara los modos `w` y `wx`. Explica por qué un error durante el cierre no permite anunciar guardado correcto.

## 3. Carga rechazada y salida anterior

Prepara variantes de prueba: versión ajena, cantidad 4, un registro menos que los declarados, nombre vacío, lectura 101, sufijo `12abc`, segundo separador y contenido adicional. Inicializa el destino con previo 77 y cantidad 99; cualquier rechazo debe conservarlos. La capacidad insuficiente también conserva las salidas. No modifiques el archivo válido para perder tu referencia.

## 4. Informe de una colección cargada

Crea un controlador que reutilice `cargar_registros`, reciba una ruta y sume solo después de una carga completa válida. Con los tres registros del proyecto espera cantidad 3 y suma 125. Con formato válido y cantidad cero espera suma cero. Si la carga falla, no presentes un informe parcial.

## 5. Recursos y representación

Explica quién abre/cierra el flujo en las funciones y auxiliares, por qué no se reintenta `fclose` sobre el mismo puntero y por qué no guardamos los bytes completos de `struct Sensor` como formato portable. Distingue «salidas de memoria intactas ante rechazo» de «archivo nuevo conservado íntegro ante cualquier fallo».
