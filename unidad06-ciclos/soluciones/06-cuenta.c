#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int inicio = 3;

    if (inicio < 0 || inicio > 10) {
        printf("Inicio invalido.\n");
        return EXIT_FAILURE;
    }
    for (int restante = inicio; restante >= 0; restante--) {
        printf("%d\n", restante);
    }
    printf("Despegue.\n");
    return EXIT_SUCCESS;
}
