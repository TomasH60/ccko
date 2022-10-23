#include <stdio.h>

int main()
{
    FILE *file1;
    FILE *file2;
    char c, c2;
    int i = 0;
    int rozdiel = 0;
    if (fopen("./prvy.txt", "r") == NULL) {
        printf("Neexistuje subor: prvy.txt");
        return 0;
    }
    if (fopen("./druhy.txt", "r") == NULL) {
        printf("Neexistuje subor: druhy.txt");
        return 0;
    } 
    file1 = fopen("./prvy.txt", "r");
    file2 = fopen("./druhy.txt", "r");
    while (((c = fgetc(file1)) != EOF) && ((c2 = fgetc(file2)) != EOF))
    {
        if (c != c2)
        {
            i++;
        }
    }

    if (c == EOF)
    {
        while ((c2 = fgetc(file2)) != EOF)
        {
            rozdiel++;
        }
    }
    if (c2 == EOF)
    {
        while ((c = fgetc(file1)) != EOF)
        {
            rozdiel++;
        }
    }

    if (i == 0)
    {
        printf("Subory su identicke");
    }
    else
    {
        printf("\nPocet roznych znakov: %d\n", i);
        printf("Jeden zo suborov je dlhsi o %d znaky", rozdiel - 1);
    }
    fclose(file1);
    fclose(file2);
    return 0;
}