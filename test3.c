#include <stdio.h>

void obsahObvod (int a, int b, int * obvod, int * obsah) {
    *obvod = 2 * a + 2 * b;
    *obsah = a * b;
}

int main () {
    int a, b, obvod, obsah;
    a = 5;
    b = 7;
    obvod = 0;
    obsah = 0;
    obsahObvod(a, b, &obvod, &obsah);
    printf("obsah: %d, obvod: %d", obsah, obvod);
    return 0;
}