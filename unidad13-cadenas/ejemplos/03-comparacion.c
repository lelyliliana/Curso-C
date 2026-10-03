#include <stdio.h>
#include <string.h>

int main(void)
{
    const char primera[] = "sensor";
    const char segunda[] = "sensor";
    const char distinta[] = "Sensor";
    if (strcmp(primera, segunda) == 0) {
        puts("Las dos primeras son iguales.");
    }
    if (strcmp(primera, distinta) != 0) {
        puts("Mayuscula y minuscula son diferentes.");
    }
    return 0;
}
