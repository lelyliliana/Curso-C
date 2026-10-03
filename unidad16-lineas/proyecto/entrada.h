#ifndef CURSO_C_LINEAS_ENTRADA_H
#define CURSO_C_LINEAS_ENTRADA_H
#include <stdbool.h>
#include <stddef.h>

enum EstadoLinea {
    LINEA_OK, LINEA_FIN, LINEA_LARGA, LINEA_INVALIDA, LINEA_ERROR, LINEA_ARGUMENTO
};
/* destino tiene capacidad char modificables; capacidad >= 1.
   Consume una linea hasta '\n' o fin/error. No almacena el salto.
   Rechaza NUL recibido y bytes > CHAR_MAX. Ante fallo de lectura/contenido,
   deja destino vacio. LINEA_OK admite una linea vacia. */
enum EstadoLinea leer_linea(char destino[], size_t capacidad);
/* texto es cadena terminada y separada de resultado, que es escribible.
   Espacios/tabulaciones solo alrededor; signo opcional; base decimal.
   false no cambia *resultado. minimo <= maximo. */
bool convertir_entero(const char texto[], int minimo, int maximo, int *resultado);
/* Decimal: digitos, punto opcional seguido de digitos, exponente opcional.
   Requiere locale numerico C; limites finitos. Rechaza ERANGE e infinitos/NaN.
   Mismas reglas de espacio y conservacion de resultado. */
bool convertir_decimal(const char texto[], double minimo, double maximo, double *resultado);
#endif
