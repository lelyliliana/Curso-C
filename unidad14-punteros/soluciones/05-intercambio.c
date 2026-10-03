#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool intercambiar(int *a, int *b)
{
    if (a == NULL || b == NULL) {
        return false;
    }
    const int temporal = *a;
    *a = *b;
    *b = temporal;
    return true;
}

int main(void)
{
    int a = 4;
    int b = 9;
    if (intercambiar(&a, &b)) {
        printf("a: %d; b: %d\n", a, b);
    }
    if (intercambiar(&a, &a)) {
        printf("Mismo objeto: %d\n", a);
    }
    if (!intercambiar(&a, NULL)) {
        printf("Rechazo sin cambio: %d\n", a);
    }
    return 0;
}
