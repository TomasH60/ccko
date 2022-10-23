#include <stdio.h>

int main() {
    FILE * file;
    if (fopen("./cisla.txt", "r") == NULL) {
        printf("Neexistuje subor: cisla.txt");
        return 0;
    }
    file = fopen("./cisla.txt", "r");
    double sum, x;
    int c;
    while ((c = fgetc(file)) != EOF) {
        ungetc(c, file);
        fscanf(file,"%lf", &x);
        printf("%g\n", x);
        sum += x;
    }
    printf("Sucet cisel je: %g", sum);
    
    return 0;
}