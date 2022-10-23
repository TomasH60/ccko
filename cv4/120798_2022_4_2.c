#include <stdio.h>
double tyzdenna_mzda(double h_mzda, double hod) {
    return h_mzda * hod;
}
int main() {
    int pocetVstupov;
    double hodinovaMzda, pocetHodin, sum;
    sum = 0;
    scanf("%d", &pocetVstupov);
    for (int i = 0; i < pocetVstupov; i++) {
        scanf("%lf %lf", &hodinovaMzda, &pocetHodin);
        printf("Hod. mzda: %.2lf Euro/hod, hodin: %.2lf, spolu: %.2lf Euro\n", hodinovaMzda, pocetHodin, tyzdenna_mzda(hodinovaMzda, pocetHodin));
        sum += tyzdenna_mzda(hodinovaMzda, pocetHodin);
    }
    printf("Celkova mzda: %.2lf", sum);
    return 0;
}