#include <stdio.h>

void showMatrix(size_t m, size_t n, int matrix[m][n])
{
    for (int i = 0; i < m; i++)
    {
        printf("[");
        for (int j = 0; j < n; j++)
        {
            printf(" %d ", matrix[i][j]);
        }
        printf("]");
        printf("\n");
    };
}
int main()
{
    int m,n,matrix[100][100];
    m = 3;
    n = 4;
    int arr1[3],arr2[3],arr3[3];
    

   
    
    
    showMatrix(m,n,matrix);
    

    return 0;
}