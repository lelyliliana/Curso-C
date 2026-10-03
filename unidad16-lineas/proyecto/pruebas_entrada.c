#include "entrada.h"
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#ifdef NDEBUG
#error "Las pruebas requieren assert activo."
#endif

int main(void)
{
    int entero = 77;
    bool ok = convertir_entero(" -1000\t", -1000, 1000, &entero);
    assert(ok && entero == -1000);
    ok = convertir_entero("+0", -1000, 1000, &entero);
    assert(ok && entero == 0);
    entero = 77;
    ok = convertir_entero("12abc", -1000, 1000, &entero);
    assert(!ok && entero == 77);
    ok = convertir_entero("1001", -1000, 1000, &entero);
    assert(!ok && entero == 77);
    ok = convertir_entero("99999999999999999999999999999999", INT_MIN, INT_MAX, &entero);
    assert(!ok && entero == 77);
    ok = convertir_entero("0", 1, 0, &entero);
    assert(!ok && entero == 77);
    ok = convertir_entero(NULL, -1000, 1000, &entero);
    assert(!ok && entero == 77);
    ok = convertir_entero("0", -1000, 1000, NULL);
    assert(!ok);
    double decimal = 77.0;
    ok = convertir_decimal(" 1.25e+2 ", -50.0, 150.0, &decimal);
    assert(ok && decimal == 125.0);
    decimal = 77.0;
    ok = convertir_decimal("nan", -50.0, 150.0, &decimal);
    assert(!ok && decimal == 77.0);
    ok = convertir_decimal("1e999", -50.0, 150.0, &decimal);
    assert(!ok && decimal == 77.0);
    ok = convertir_decimal("1e-999", -50.0, 150.0, &decimal);
    assert(!ok && decimal == 77.0);
    ok = convertir_decimal(".5", -50.0, 150.0, &decimal);
    assert(!ok && decimal == 77.0);
    ok = convertir_decimal("0", NAN, 150.0, &decimal);
    assert(!ok && decimal == 77.0);
    puts("Pruebas de conversion: OK.");
    return 0;
}
