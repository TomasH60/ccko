#include <stdio.h>

int cifernySucet(int x, int sum)
{
    if (x <= 9)
    {
        return sum += x;
    }
    sum += x % 10;
    x /= 10;
    return (cifernySucet((int)x, sum));
}
int main()
{
    int N, sum = 0;
    scanf("%d", &N);
    printf("%d", cifernySucet(N, sum));
    return 0;
}