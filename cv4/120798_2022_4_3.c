#include <stdio.h>

long reverzne_cislo(long x)
{
    int zvysok, opak = 0;
    while (x != 0)
    {
        zvysok = x % 10;
        opak = opak * 10 + zvysok;
        x /= 10;
    }
    return opak;
}
int main()
{
    long cislo;
    scanf("%ld", &cislo);
    long int opakCisla = reverzne_cislo(cislo);
    printf("%ld\n", opakCisla);
    if (opakCisla == cislo) {
        printf("Cislo %ld je palindrom", cislo);
    } else {
        printf("Cislo %ld nie je palindrom", cislo);
    }

    return 0;
}