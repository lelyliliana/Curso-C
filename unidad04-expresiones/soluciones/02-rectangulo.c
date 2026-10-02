#include <stdio.h>

int main(void)
{
    double ancho = 3.5;
    double alto = 2.0;
    double area = ancho * alto;
    double perimetro = 2.0 * (ancho + alto);

    printf("Area: %.2f m2\n", area);
    printf("Perimetro: %.2f m\n", perimetro);
    return 0;
}
