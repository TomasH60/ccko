#include <stdio.h>
int main()
{
    char c;
    int med;
    FILE *file;
    if (fopen("./text.txt", "r") == NULL)
    {
        printf("Neexistuje subor: text.txt");
        return 0;
    }
    file = fopen("./text.txt", "r");
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '*')
        {
            printf("Koniec\n");
            break;
        }
        if (c == 'x' || c == 'X') {
            printf("Precital som X\n");
        }
        if (c == 'y' || c == 'Y') {
            printf("Precital som Y\n");
        }
        if (c == '#' || c == '$' || c == '&') {
            printf("Precital som riadiaci znak\n");
        }
        if (c == ' ') {
            med += 1;
        }
    }
    printf("Pocet precitanych medzier: %d", med);
    fclose(file);
    return 0;
}