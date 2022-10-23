#include <stdio.h>

int fib(int n, int c)
{
    if (n <= 1)
    {
        return n;
    }
    else
    {
        printf("[%d, %d]", n - 2, n - 1);
        

        printf("level: %d", c);
        
        return fib(n - 2, c + 1) + fib(n - 1, c + 1);
    }
}

int main()
{
    int fibNum = 3;
    int arr[fibNum][fibNum] = {{1, 2, -1}, {3, 1, 4, -1}};
    printf("\n%d konec\n", fib(fibNum, 1));
    int totlvl = 2;
    
    printf("%d\n", fibNum);
    for (int j = 0; j < totlvl; j++)
    {
        for (int k = 0; k != -1; k++)
        {
            if (arr[j][k] == -1)
                break;
            printf("%d ", arr[j][k]);
        }
        printf("\n");
    }

    return 0;
}