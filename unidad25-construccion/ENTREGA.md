# Entrega final — Agenda de sensores

[Guía](README.md) · [Diseño](../unidad23-diseno/README.md) · [Aplicación](../unidad24-aplicacion/README.md)

Trabaja un hito a la vez. Antes de avanzar, conserva su evidencia y explica el comportamiento observado. Puedes realizarlo individualmente o acordar una distribución de responsabilidades con tu docente.

## Hito 1. Reglas y dominio

Define nombres, rango, límite, unicidad y operaciones. Ejecuta las pruebas de agenda y conserva un caso de rechazo con datos anteriores preservados. Explica la diferencia entre nombre e índice.

## Hito 2. Sesión de consola

Ejecuta agregado, búsqueda, actualización, borrado y resumen. Prueba opción y dato inválidos seguidos de una operación válida. Comprueba fin de entrada a mitad de una solicitud; no publiques un resultado parcial como operación completa.

## Hito 3. Persistencia

Guarda en una ruta nueva, inicia otra sesión y carga. Prueba versión ajena, nombre repetido y truncamiento. Comprueba que el destino anterior se conserva. Documenta el límite del guardado exclusivo y la posible permanencia de un archivo nuevo parcial ante fallos.

## Hito 4. Construcción y entrega

Construye desde fuentes mediante GNU make o el comando manual completo. Ejecuta pruebas y conserva evidencia de tu sistema real. Entrega repositorio o carpeta de fuentes con README propio, comandos, casos reproducibles, resultados y límites conocidos; excluye productos de compilación y datos personales.

## Rúbrica orientativa

| Criterio | Puntos | Evidencia suficiente |
|---|---:|---|
| Requisitos y diseño | 20 | Reglas explícitas, módulos justificados y casos esperados |
| Operaciones e interacción | 25 | Secuencia completa y rechazos sin cambios incorrectos |
| Memoria y recursos | 20 | Propiedad inequívoca, limpieza en éxito/fallo y préstamos válidos |
| Archivos y conservación | 20 | Carga completa, formatos rechazados y guardado sin sobrescribir |
| Verificación y documentación | 15 | Construcción repetible, pruebas interpretadas y límites reales |
| **Total** | **100** | |

Un funcionamiento parcial recibe valoración según evidencia, no por cantidad de archivos. Una aplicación que pierde datos ante una carga inválida no satisface el criterio de conservación. Un programa que parece funcionar, pero no puede explicar quién libera su memoria, todavía requiere revisión.

Como evidencia complementaria, puedes grabar una explicación breve de 3–5 minutos: propósito, una sesión, un rechazo y una decisión de diseño. El video ayuda a justificar tu trabajo, pero no reemplaza fuentes ni pruebas reproducibles.

## Ampliaciones opcionales

Después de completar los hitos, elige **una** ampliación y define sus pruebas: ordenar por nombre, filtrar por umbral, confirmar antes de reemplazar al cargar, registrar cambios pendientes o mejorar mensajes de rechazo. No cambies varias reglas al mismo tiempo ni anuncies como disponible una extensión que no implementaste.

Los siguientes temas requieren diseño adicional: guardado con reemplazo atómico y recuperación, Unicode, grandes volúmenes, concurrencia y estructuras de datos más avanzadas. Esta entrega no exige fingir que ya están resueltos.
