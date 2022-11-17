#include <stdio.h>
#include <string.h>

int main () {
    char mena[100][2048];
    char meno[2047];
    int pocetnost[100];
    memset(pocetnost, 0, 100*sizeof(int));
    int c = 0;
    while (meno[0] != 48)
    {
        printf("meno:\n");
        scanf("%s", meno);
        strcpy(mena[c], meno);
        c++;
    }
    int temp[c - 1];
    int j = 0;
    for (int i = 0; i < c - 1; i++)
    {
        if (strcmp(mena[i], mena[i+1]))
        {
            temp[j++] = mena[i];
        }
    }
    temp[j++] = merModulTypMer[c - 1];
    for (int i = 0; i < j; i++)
    {
        merModulTypMer[i] = temp[i];
    }
    
    for (int i = 0; i < c - 1; i++)
    {
        printf("%s\n", mena[i]);
    }
    
    return 0;
}