#include <stdio.h>

int main() {
    double x;
    scanf("%lf", &x);
    FILE * file;
    file = fopen("./nasobky.txt", "w");
    for (int i = 1; i != 11; i++) {
        fprintf(file, "%d * %.2lf = %.2lf\n", i, x, i*x);
    }
    fclose(file);
    return 0;
}