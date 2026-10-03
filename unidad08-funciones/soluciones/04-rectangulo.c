#include <stdio.h>

double area_rectangulo(double ancho, double alto)
{
    return ancho * alto;
}

double perimetro_rectangulo(double ancho, double alto)
{
    return 2.0 * (ancho + alto);
}

int main(void)
{
    double ancho = 3.5;
    double alto = 2.0;

    printf("Area: %.2f m2\n", area_rectangulo(ancho, alto));
    printf("Perimetro: %.2f m\n", perimetro_rectangulo(ancho, alto));
    return 0;
}
