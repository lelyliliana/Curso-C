#include <stdio.h>

int main(void)
{
    double duracion = 3.75;
    int horas_completas = (int)duracion;
    double negativa = -3.75;
    int negativo_convertido = (int)negativa;

    printf("Duracion: %.2f\n", duracion);
    printf("Horas completas: %d\n", horas_completas);
    printf("Original tras convertir: %.2f\n", duracion);
    printf("Negativo convertido: %d\n", negativo_convertido);
    return 0;
}
