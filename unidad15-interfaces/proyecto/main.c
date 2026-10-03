#include "coleccion.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const int datos[] = {8, 2, 0, 10, 5};
    const size_t cantidad = sizeof datos / sizeof datos[0];
    int suma = 0;
    int minimo = 0;
    char nombre[8] = {0};
    if (!sumar_lecturas(datos, cantidad, &suma)
        || !minimo_lecturas(datos, cantidad, &minimo)
        || !copiar_texto("sensor", nombre, sizeof nombre)) {
        puts("No se pudo construir el informe.");
        return EXIT_FAILURE;
    }
    printf("Nombre: %s\nSuma: %d\nMinimo: %d\n", nombre, suma, minimo);
    return EXIT_SUCCESS;
}
