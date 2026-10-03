#include <stddef.h>
#include <stdio.h>

int main(void)
{
    int datos[] = {4, 0, 7};
    const size_t cantidad = sizeof datos / sizeof datos[0];
    int *final = datos + cantidad;
    for (int *actual = datos; actual != final; actual++) {
        printf("Valor: %d\n", *actual);
    }
    if (datos + 1 == &datos[1]) {
        puts("Sumar uno avanza un elemento.");
    }
    return 0;
}
