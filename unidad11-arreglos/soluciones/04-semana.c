#include <stddef.h>
#include <stdio.h>

int main(void)
{
    const int visitas[] = {3, 0, 5, 2, 0, 4, 1};
    const size_t dias = sizeof visitas / sizeof visitas[0];
    for (size_t i = 0; i < dias; i++) {
        printf("Dia %zu: %d\n", i + 1, visitas[i]);
    }
    return 0;
}
