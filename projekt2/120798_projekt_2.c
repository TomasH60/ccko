#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 256
typedef struct dataLinkedList
{
    long long int ID_cislo_mer_osoby;
    char Meno_osoby[BUFFER];
    char Mer_modul[BUFFER];
    char Typ_mer_veliciny[BUFFER];
    double Hodnota;
    int Cas_merania;
    int Datum;
    struct dataLinkedList *next;
} DATA;
void append(DATA **listHead, long long int ID_cislo_mer_osoby, char *Meno_osoby, char *Mer_modul, char *Typ_mer_veliciny, double Hodnota, int Cas_merania, int Datum)
{
    DATA *new_node = (DATA *)malloc(sizeof(DATA));
    DATA *last = *listHead;
    new_node->ID_cislo_mer_osoby = ID_cislo_mer_osoby;
    strcpy(new_node->Meno_osoby, Meno_osoby);
    strcpy(new_node->Mer_modul, Mer_modul);
    strcpy(new_node->Typ_mer_veliciny, Typ_mer_veliciny);
    new_node->Hodnota = Hodnota;
    new_node->Cas_merania = Cas_merania;
    new_node->Datum = Datum;
    new_node->next = NULL;
    if (*listHead == NULL)
    {
        *listHead = new_node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return;
}

void n(DATA **listHead, FILE **file)
{
    if (*file == NULL)
    {
        *file = fopen("./dataloger_V2.txt", "r");
        if (*file == NULL)
        {
            printf("Zaznamy neboli nacitane!\n");
            return;
        }
    }
    if (*listHead != NULL)
    {
        DATA *tmp;
        while (*listHead != NULL)
        {
            tmp = *listHead;
            *listHead = (*listHead)->next;
            free(tmp);
        }
    }

    char line[BUFFER];
    int numberOfRecords = 0;
    int lineNumber = 0;
    long long int ID_cislo_mer_osoby;
    char Meno_osoby[BUFFER];
    char Mer_modul[BUFFER];
    char Typ_mer_veliciny[BUFFER];
    double Hodnota;
    int Cas_merania;
    int Datum;
    double cislo = 7;
    for (; fgets(line, sizeof(line), *file) != NULL;) 
    {
        line[strlen(line) - 1] = '\0';
        if (!strcmp(line, "$$$"))
        {
            ++numberOfRecords;
            if (lineNumber != 0)
            {
                append(listHead, ID_cislo_mer_osoby, Meno_osoby, Mer_modul, Typ_mer_veliciny, Hodnota, Cas_merania, Datum);
            }
            continue;
        }

        switch (lineNumber % 7)
        {
        case 0:
            ID_cislo_mer_osoby = atoll(line);
            break;
        case 1:
            strcpy(Meno_osoby, line);
            break;
        case 2:
            strcpy(Mer_modul, line);
            break;
        case 3:
            strcpy(Typ_mer_veliciny, line);
            break;
        case 4:
            Hodnota = atof(line);
            break;
        case 5:
            Cas_merania = atoi(line);
            break;
        case 6:
            Datum = atoi(line);
            break;
        default:
            break;
        }
        if (strcmp(line, "$$$"))
        {
            lineNumber++;
        }
    }
    append(listHead, ID_cislo_mer_osoby, Meno_osoby, Mer_modul, Typ_mer_veliciny, Hodnota, Cas_merania, Datum);
    printf("Nacitalo sa %d zaznamov\n", numberOfRecords);
    fseek(*file, 0, SEEK_SET);
}
void v(DATA *listHead)
{
    int number = 1;
    while (listHead != NULL)
    {
        printf("%d:\n", number);
        printf("ID_cislo_mer_osoby: %lld\n", listHead->ID_cislo_mer_osoby);
        printf("Meno_osoby: %s\n", listHead->Meno_osoby);
        printf("Mer_modul: %s\n", listHead->Mer_modul);
        printf("Typ_mer_veliciny: %s\n", listHead->Typ_mer_veliciny);
        printf("Hodnota: %lf\n", listHead->Hodnota);
        printf("Cas_merania: %d\n", listHead->Cas_merania);
        printf("Datum: %d\n", listHead->Datum);
        listHead = listHead->next;
        number++;
    }
}
int main()
{
    FILE *file = NULL;
    DATA *listHead = NULL;
    char command;
    while (1)
    {
        scanf(" %c", &command);
        while ((getchar()) != '\n')
            ;
        switch (command)
        {
        case 'n':
            n(&listHead, &file);
            break;
        case 'v':
            v(listHead);
            break;
        case 'z':
            break;
        case 'u':
            break;
        case 'p':
            break;
        case 'h':
            break;
        case 'r':
            break;
        case 'k':
            if (file != NULL)
            {
                fclose(file);
            }
            return 0;
            break;
        }
    }
    return 0;
}
