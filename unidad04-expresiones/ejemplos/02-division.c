#include <stdio.h>

int main(void)
{
    int piezas = 5;
    int personas = 2;
    int reparto_entero = piezas / personas;
    double resultado_tardio = piezas / personas;
    double reparto_decimal = (double)piezas / personas;
    double conversion_tardia = (double)(piezas / personas);

    printf("Division entera: %d\n", reparto_entero);
    printf("Destino double: %.2f\n", resultado_tardio);
    printf("Conversion antes: %.2f\n", reparto_decimal);
    printf("Conversion despues: %.2f\n", conversion_tardia);
    return 0;
}
