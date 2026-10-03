#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    int edad = 17;
    bool tiene_autorizacion = true;
    bool tiene_documento = true;

    if ((edad >= 18 || tiene_autorizacion) && tiene_documento) {
        printf("Puede participar.\n");
    } else {
        printf("Falta cumplir un requisito.\n");
    }

    if (!tiene_documento) {
        printf("Debe presentar documento.\n");
    }
    return 0;
}
