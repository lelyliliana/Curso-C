# Soluciones — Unidad 25

[Guía](README.md) · [Ejercicios](EJERCICIOS.md) · [Entrega](ENTREGA.md)

## 1. Cambios incrementales

La segunda construcción sin cambios no ejecuta el compilador ni el enlazador. Un cambio de comentario modifica el archivo y su fecha: make reconstruye `agenda.o` y el ejecutable de aplicación que depende de él. Si ya construiste la prueba, `make test` vuelve a enlazarla al necesitar el objeto actualizado. El contenido del comentario no se interpreta para decidir que «no importa».

## 2. Encabezados

`agenda.o`, `catalogo.o`, `sensor.o`, `archivo.o`, `persistencia.o`, `main.o` y el objeto de pruebas dependen directa o indirectamente de `sensor.h`; el módulo de entrada numérica no lo incluye. Los `.d` generados registran esas inclusiones. Los nombres y rutas exactos aparecen al inspeccionar el archivo correspondiente.

Cambiar `CFLAGS` no actualiza por sí solo la fecha de un fuente o encabezado. Limpia y reconstruye para no mezclar objetos construidos con configuraciones distintas. La automatización incluida no pretende capturar todas las versiones de compilador y bibliotecas del entorno.

## 3. Datos preservados

`clean` retira `.o`, `.d`, aplicación y prueba de agenda del directorio de construcción elegido. No elimina `conservar.txt`, otras copias de datos ni toda la carpeta. En Windows necesitas conservar el sufijo `.exe` al ejecutar la regla para identificar esos ejecutables. Si elegiste nombres ajenos a los objetivos publicados, no esperes que la regla los adivine.

## 4. Evidencia y alcance

Un duplicado que cambiara el valor original incumpliría el dominio y puede detectarse llamando directamente a `insertar_sensor`. Un error que aceptara archivos truncados requiere probar el parser y la conservación del destino. Un menú que asociara actualizar con quitar necesitaría una sesión que compruebe la acción conectada. Ejecutar solo `make test` no demuestra las tres cosas.

El proyecto completo está en [agenda_app](../unidad24-aplicacion/proyecto/main.c), con [agenda.c](../unidad23-diseno/proyecto/agenda.c) y [persistencia.c](../unidad24-aplicacion/proyecto/persistencia.c). El [Makefile](Makefile) construye esos mismos fuentes. La [rúbrica](ENTREGA.md) permite valorar evidencias reales; no se entrega una puntuación automática de cien sin revisar el trabajo.
