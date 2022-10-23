#include <stdio.h>
int main()
{
    char ca, c;
    int x;
    ca = getc(stdin);
    FILE *file;
    if (fopen("./znak.txt", "r") == NULL)
    {
        printf("Neexistuje subor: znak.txt");
        return 0;
    }
    file = fopen("./znak.txt", "r");
    if (ca == 's')
    {
        FILE *fileNovy;
        fileNovy = fopen("novy.txt", "w");
        while ((c = fgetc(file)) != EOF)
        {
            fprintf(fileNovy, "%c", c);
        }
    }
    else
    {
        while ((c = fgetc(file)) != EOF)
        {
            putchar(c);
        }
        fclose(file);
    }
    return 0;
}