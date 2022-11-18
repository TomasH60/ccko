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
void delete (DATA **listHead, int position)
{
    DATA *temp;
    DATA *prev;
    temp = *listHead;
    prev = *listHead;
    for (int i = 0; i <= position; i++)
    {
        if (i == 0 && position == 0)
        {
            *listHead = (*listHead)->next;
            free(temp);
        }
        else
        {
            if (i == position && temp)
            {
                prev->next = temp->next;
                free(temp);
            }
            else
            {
                prev = temp;
                if (prev == NULL)
                    break;
                temp = temp->next;
            }
        }
    }
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
    return;
}
void v(DATA *listHead)
{
    int number = 1;

    if (listHead == NULL)
    {
        printf("kokotzzzz\n");
    }

    while (listHead != NULL)
    {
        printf("%d:\n", number);
        printf("ID_cislo_mer_osoby: %lld\n", listHead->ID_cislo_mer_osoby);
        printf("Meno_osoby: %s\n", listHead->Meno_osoby);
        printf("Mer_modul: %s\n", listHead->Mer_modul);
        printf("Typ_mer_veliciny: %s\n", listHead->Typ_mer_veliciny);
        printf("Hodnota: %lf\n", listHead->Hodnota);
        if (listHead->Cas_merania < 1000)
        {
            printf("Cas_merania: 0%d\n", listHead->Cas_merania);
        }
        else
        {
            printf("Cas_merania: %d\n", listHead->Cas_merania);
        }
        printf("Datum: %d\n", listHead->Datum);
        listHead = listHead->next;
        number++;
    }
    return;
}
void z(DATA **listHead)
{
    long long int ID_to_delete;
    scanf("%lld", &ID_to_delete);
    int position = 0;
    DATA *listHeads = *listHead;
    while (listHeads != NULL)
    {
        if (listHeads->ID_cislo_mer_osoby == ID_to_delete)
        {
            printf("Zaznam pre ID: %lld pre modul %s bol vymazany.\n", listHeads->ID_cislo_mer_osoby, listHeads->Mer_modul);
            delete (listHead, position);
            position--;
        }
        listHeads = listHeads->next;
        position++;
    }
    return;
}
void h(DATA *listHead)
{
    char MerModul[BUFFER];
    scanf("%s", MerModul);
    int number = 1;
    while (listHead != NULL)
    {
        if (!strcmp(MerModul, listHead->Mer_modul))
        {
            printf("%d:\n", number);
            printf("ID_cislo_mer_osoby: %lld\n", listHead->ID_cislo_mer_osoby);
            printf("Meno_osoby: %s\n", listHead->Meno_osoby);
            printf("Mer_modul: %s\n", listHead->Mer_modul);
            printf("Typ_mer_veliciny: %s\n", listHead->Typ_mer_veliciny);
            printf("Hodnota: %lf\n", listHead->Hodnota);
            printf("Cas_merania: %d\n", listHead->Cas_merania);
            printf("Datum: %d\n", listHead->Datum);
            number++;
        }
        listHead = listHead->next;
    }
    if (number == 1)
    {
        printf("Pre meraci modul %s niesu zaznamy.\n", MerModul);
    }
    return;
}
void p(DATA **listHead, int number)
{
    long long int ID_cislo_mer_osoby;
    char Meno_osoby[BUFFER];
    char Mer_modul[BUFFER];
    char Typ_mer_veliciny[BUFFER];
    double Hodnota;
    int Cas_merania;
    int Datum;
    scanf("%lld", &ID_cislo_mer_osoby);
    scanf("%s", Meno_osoby);
    scanf("%s", Mer_modul);
    scanf("%s", Typ_mer_veliciny);
    scanf("%lf", &Hodnota);
    scanf("%d", &Cas_merania);
    scanf("%d", &Datum);
    DATA *newNode;
    DATA *temp = *listHead;
    DATA **previous;
    newNode = (DATA *)malloc(sizeof(DATA));
    newNode->ID_cislo_mer_osoby = ID_cislo_mer_osoby;
    strcpy(newNode->Meno_osoby, Meno_osoby);
    strcpy(newNode->Mer_modul, Mer_modul);
    strcpy(newNode->Typ_mer_veliciny, Typ_mer_veliciny);
    newNode->Hodnota = Hodnota;
    newNode->Cas_merania = Cas_merania;
    newNode->Datum = Datum;
    int counter = 1;
    int numberOfRecords = 0;
    while (*listHead != NULL)
    {
        numberOfRecords++;
        *listHead = (*listHead)->next;
    }
    *listHead = temp;
    if (number > numberOfRecords)
    {
        number = numberOfRecords;
    }
    while (*listHead != NULL)
    {
        if (counter == number - 1)
        {
            *previous = *listHead;
            printf("KOKOTOKKTOKOTKOT\n");
        }
        if (counter == number)
        {
            if (counter == 1)
            {
                newNode->next = *listHead;
                *listHead = newNode;
                break;
            }
            if ((*listHead)->next == NULL)
            {
                (*listHead)->next = newNode;
                break;
            }
            (*previous)->next = newNode;
            DATA *temp2 = *listHead;
            newNode->next = *listHead;
            temp2 = newNode;
            break;
        }
        counter++;
        *listHead = (*listHead)->next;
    }
    *listHead = temp;
    return;
}
void r(DATA **listHead)
{
    int c1, c2;
    scanf("%d %d", &c1, &c2);
    DATA *temp = *listHead;
    DATA *nodeC1 = NULL;
    DATA *nodeC2 = NULL;
    DATA *prevC1 = NULL;
    DATA *prevC2 = NULL;
    int counter = 1;
    int numberOfRecords = 0;
    while (*listHead != NULL)
    {
        numberOfRecords++;
        *listHead = (*listHead)->next;
    }
    *listHead = temp;
	if (c1 == c2 || c1 > numberOfRecords || c2 > numberOfRecords)
		return;
    while (*listHead != NULL)
    {
        if (counter == c1)
        {
            nodeC1 = *listHead;
        }
        if (counter == c1 - 1)
        {
            prevC1 = *listHead;
        }
        if (counter == c2)
        {
            nodeC2 = *listHead;
        }
        if (counter == c2 -1)
        {
            prevC2 = *listHead;
        }
        counter++;
        *listHead = (*listHead)->next;
    }
    *listHead = temp;
    if (prevC1 != NULL) {
        prevC1->next = nodeC2;
    } else {
        *listHead = nodeC2;
    }
    if (prevC2 != NULL) {
        prevC2->next = nodeC1;
    } else {
        *listHead = nodeC1;
    }
    DATA * temp1 = nodeC1->next;
    nodeC1->next = nodeC2->next;
    nodeC2->next = temp1;
}
int main()
{
    FILE *file = NULL;
    DATA *listHead = NULL;
    char command[BUFFER];
    char *number;
    while (1)
    {
        gets(command);
        switch (command[0])
        {
        case 'n':
            n(&listHead, &file);
            break;
        case 'v':
            v(listHead);
            break;
        case 'z':
            z(&listHead);
            break;
        case 'u':
            break;
        case 'p':
            number = strtok(command, " ");
            number = strtok(NULL, " ");
            p(&listHead, atoi(number));
            break;
        case 'h':
            h(listHead);
            break;
        case 'r':
            r(&listHead);
            break;
        case 'k':
            if (file != NULL)
            {
                fclose(file);
            }
            if (listHead != NULL)
            {
                DATA *temp;
                while (listHead != NULL)
                {
                    temp = listHead;
                    listHead = listHead->next;
                    free(temp);
                }
            }
            return 0;
            break;
        }
    }
    return 0;
}
