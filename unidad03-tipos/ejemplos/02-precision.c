#include <stdio.h>

int main(void)
{
    float medida_corta = 0.1f;
    double medida = 0.1;

    printf("float, 17 decimales: %.17f\n", medida_corta);
    printf("double, 17 decimales: %.17f\n", medida);
    printf("double, 2 decimales: %.2f\n", medida);
    return 0;
}
