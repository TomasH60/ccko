#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int go = 1, lenpole = 0;
    char moznost, *pole = NULL, c, *pomenovania[7];
    pomenovania[0] = "ID cislo mer. osoby: ";
    pomenovania[1] = "Mer. modul: ";
    pomenovania[2] = "Typ mer. veliciny: ";
    pomenovania[3] = "Hodnota: ";
    pomenovania[4] = "Cas merania: ";
    pomenovania[5] = "Datum: ";
    pomenovania[6] = "";
    FILE *dataloger = NULL;
    while (go == 1)
    {
        scanf("%c", &moznost);
        switch (moznost)
        {
        case 'v':

            if (dataloger == NULL)
            {
                dataloger = fopen("./datalogertest.txt", "r");
                if (dataloger == NULL)
                {
                    printf("Neotvoreny subor\n");
                    break;
                }
            }
            if (pole == NULL)
            {
                int i = 1;
                printf("ID cislo mer. osoby: ");
                while (feof(dataloger) == 0)
                {
                    if (c == 10)
                    {
                        printf("%s", pomenovania[i % 7]);
                        i++;
                    }
                    c = fgetc(dataloger);
                    printf("%c", c);
                }
                rewind(dataloger);
            }
            else
            {
            }

            break;
        case 'o':
            if (dataloger != NULL)
            {
                char pozadovany_mer_modul[4], pozadovana_mer_velicina[3], nacitany_string_1[4], nacitany_string_2[3];
                scanf("%s %s", pozadovany_mer_modul, pozadovana_mer_velicina);
                while (feof(dataloger) == 0)
                {
                    fgets(nacitany_string_1, 4, dataloger);
                    fseek(dataloger, -2, SEEK_CUR);
                    printf("%s", nacitany_string_1);

                    if (strcmp(nacitany_string_1, pozadovany_mer_modul) == 0)
                    {

                        fgets(nacitany_string_2, 3, dataloger);
                        if (strcmp(nacitany_string_2, pozadovana_mer_velicina) == 0)
                        {
                            printf(" asd  ");
                        }
                    }
                }
            }
            else
            {
                printf("Neotvoreny subor.\n");
            }
            rewind(dataloger);
            break;
        case 'n':

            break;
        case 'c':
            if (dataloger != NULL)
            {
                int i = -1, correct = 1;
                char line[100];
                while (feof(dataloger) == 0)
                {
                    fgets(line, 100, dataloger);
                    i++;
                    i = i % 7;
                    switch (i)
                    {
                    case 0:
                        if (line[10] == 10)
                        {
                            long long int ID = 0, nasobok = 1;
                            for (int b = 9; b >= 0; b--)
                            {
                                if (line[b] - 48 <= 9 && line[b] - 48 >= 0)
                                {

                                    printf("%lld  ", (int)line[b] * nasobok);

                                    nasobok *= 10;
                                    printf("%lld ", nasobok);
                                }
                                else
                                {
                                    correct = 0;
                                    break;
                                }
                            }
                            if (ID % 11 != 0)
                                correct = 0;
                        }
                        else
                            correct = 0;
                        if (correct == 0)
                        {
                            printf("Nekorektne zadany vstup: %s %s", pomenovania[i], line);
                            correct = 1;
                        }
                        break;
                    case 1:
                        break;
                    }
                }
            }

            rewind(dataloger);
            break;
        case 's':
            break;
        case 'h':
            break;
        case 'r':
            break;
        case 'z':
            break;
        case 'k':
            break;

        default:
            break;
        }
    }
}