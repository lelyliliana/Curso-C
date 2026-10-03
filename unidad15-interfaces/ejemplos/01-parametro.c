#include <stddef.h>
#include <stdio.h>

void mostrar(const int datos[], size_t cantidad)
{
    for (size_t i = 0; i < cantidad; i++) {
        printf("Indice %zu: %d\n", i, datos[i]);
    }
}

int main(void)
{
    const int datos[] = {4, 0, 7};
    const size_t cantidad = sizeof datos / sizeof datos[0];
    mostrar(datos, cantidad);
    mostrar(NULL, 0);
    return 0;
}
