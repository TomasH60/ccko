#include <stdio.h>
#include <stdbool.h>

int zisti_prvocislo(int cislo) {
    if (cislo == 1 || cislo == 2 || cislo == 3) {
        return 1;
    } else if (cislo % 2 == 0 || cislo % 3 == 0) {
        return -1;
    } else {
        return 1;
    }
} 
int main() {
    int cislo1, cislo2;
    _Bool existuje = false;
    scanf("%d %d", &cislo1, &cislo2);
    for (int i = cislo1 + 1; i != cislo2; i++) {
        if (zisti_prvocislo(i) == 1) {
            existuje = true;
            printf("%d\n", i);
        }
    }
    if (existuje == false)
        printf("Prvocislo neexistuje");
    return 0;
}