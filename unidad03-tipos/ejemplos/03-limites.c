#include <limits.h>
#include <stdio.h>

int main(void)
{
    printf("Bytes de int: %zu\n", sizeof(int));
    printf("Bytes de double: %zu\n", sizeof(double));
    printf("Bytes de char: %zu\n", sizeof(char));
    printf("Bits por byte: %d\n", CHAR_BIT);
    printf("INT_MIN: %d\n", INT_MIN);
    printf("INT_MAX: %d\n", INT_MAX);
    return 0;
}
