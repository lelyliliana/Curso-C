#include <stdio.h>

int main(void)
{
    int vueltas_while = 0;
    while (vueltas_while < 0) {
        vueltas_while++;
    }

    int vueltas_do = 0;
    do {
        vueltas_do++;
    } while (vueltas_do < 0);

    printf("Vueltas while: %d\n", vueltas_while);
    printf("Vueltas do-while: %d\n", vueltas_do);
    return 0;
}
