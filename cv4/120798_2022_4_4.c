#include <stdio.h> 

int sucetCisel (int x, int sum) {
    if (x == 0) {
        return sum;
    }
    if ((x - 1) % 2 == 0) {
        sum += x;
    }
    return sucetCisel(x - 1, sum);
}

int main() {
    int N, sum = 0;
    scanf("%d", &N);
    printf("%d", sucetCisel(N, sum));
    return 0;
}