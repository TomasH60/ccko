#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define BUFFER 2048 // dlzka bufferu pre string

void v(FILE **subor, char ***ID, char ***MerModul, char ***TypMerVeliciny, char ***Hodnota, char ***Cas, char ***Datum)
{
    if (*subor == NULL) // skontoluje ci uz je otvoreny subor
    {
        *subor = fopen("./dataloger.txt", "r"); // otvori sa subor na citanie
        if (*subor == NULL)                     // ak subor nepodari otvorit
        {
            printf("Neotvoreny subor.\n");
            return;
        }
    }
    if (*ID != NULL) // ak uz su dynamicke polia vytvorene
    {
        int i = 0; // pocitadlo indexu
        while ((*ID)[i] != NULL && (*MerModul)[i] != NULL && (*TypMerVeliciny)[i] != NULL && (*Hodnota)[i] != NULL && (*Cas)[i] != NULL && (*Datum)[i] != NULL)
        {
            printf("ID cislo mer. osoby: %s\n", (*ID)[i]); // udaje sa printuju z dynamickych poli pokial sa element na kazdom indexe nerovna null cize koniec arrayu
            printf("Mer. modul: %s\n", (*MerModul)[i]);
            printf("Typ mer. veliciny: %s\n", (*TypMerVeliciny)[i]);
            printf("Hodnota: %s\n", (*Hodnota)[i]);
            printf("Cas merania: %s\n", (*Cas)[i]);
            printf("Datum: %s\n", (*Datum)[i]);
            printf("\n");
            i++;
        }
    }
    else // ak dynamicke polia niesu vytvorene udaje sa nacitavaju zo suboru
    {
        int riadokBezMedzier = 0;                                  // pocitadlo aktualneho riadku (bez medzier)
        char readLine[BUFFER];                                     // string do ktoreho sa uklada riadok
        for (; fgets(readLine, sizeof(readLine), *subor) != NULL;) // nacitava riadok po riadku pokial nieje na konci suboru (NULL)
        {
            if (readLine[0] == 13) // ak sa nacitany riadok == prazdnemu riadku tak tuto iteraciu preskoci
            {
                continue;
            }
            switch (riadokBezMedzier % 6) // zisti na akom type riadku sa nachadza (ID, MerModul, ...) a vypise jednotlivy riadok
            {
            case 0:
                printf("ID cislo mer. osoby: %s", readLine);
                break;
            case 1:
                printf("Mer. modul: %s", readLine);
                break;
            case 2:
                printf("Typ mer. veliciny: %s", readLine);
                break;
            case 3:
                printf("Hodnota: %s", readLine);
                break;
            case 4:
                printf("Cas merania: %s", readLine);
                break;
            case 5:
                printf("Datum: %s\n", readLine);
                break;
            default:
                break;
            }
            riadokBezMedzier++;
        }
        fseek(*subor, 0, SEEK_SET); // vrati pointer suboru na za zaciatok suboru
    }
}
void o(FILE **subor, char ***MerModul, char ***TypMerVeliciny, char ***Datum, char ***Cas, char ***Hodnota)
{
    if (*subor == NULL) // ak subor nieje otvoreny
    {
        printf("Neotvoreny subor.\n");
        return;
    }
    if (*MerModul == NULL) // ak niesu vytvorene dynamicke polia
    {
        char merModul[BUFFER]; // string do ktoreho sa nacita mer modul
        char typMerVeliciny[BUFFER];
        char merModulLine[BUFFER];                // string do ktoreho sa nacita mer modul
        char typMerVelicinyLine[BUFFER];          // string do ktoreho sa nacita typ mer veliciny
        scanf("%s %s", merModul, typMerVeliciny); // nacita mer modul a typ mer veliciny
        int dlzkaArr = 0;
        char readLine[BUFFER];
        int riadokBezMedzier = 0;
        int merModulSet = 0;
        int typMerVelSet = 0;
        for (; fgets(readLine, sizeof(readLine), *subor) != NULL;) // nacitava riadok po riadku pokial nieje na konci suboru (NULL)
        {
            if (readLine[0] == 13) // ak sa nacitany riadok == prazdnemu riadku tak tuto iteraciu preskoci
            {
                continue;
            }
            readLine[strlen(readLine) - 1] = '\0';
            readLine[strlen(readLine) - 1] = '\0';
            switch (riadokBezMedzier % 6) // zisti na akom type riadku sa nachadza (ID, MerModul, ...) a vypise jednotlivy riadok
            {
            case 1:
                strcpy(merModulLine, readLine);
                merModulSet = 1;
                break;
            case 2:
                strcpy(typMerVelicinyLine, readLine);
                typMerVelSet = 1;
                break;
            default:
                break;
            }
            if (merModulSet && typMerVelSet)
            {
                if (!strcmp(typMerVeliciny, typMerVelicinyLine) && !strcmp(merModul, merModulLine)) // porovna stringy a zisti ci sa na danych indexoch a zisti na kolkych indexoch sa kombinacia mer modul a typ mer veliciny nachadza
                {
                    dlzkaArr++; // zvacsi dlzku arrayov += 1
                }
                typMerVelSet = 0;
                merModulSet = 0;
            }
            riadokBezMedzier++;
        }
        riadokBezMedzier = 0;
        fseek(*subor, 0, SEEK_SET);
        if (dlzkaArr == 0)
        { // ak sa nenachadza kombinacia mer modulu a typu mer veliciny (nenasla sa ani jedna zhoda)
            printf("Dana kombinacia sa nenachadza v subore.\n");
            return;
        }
        double DatumCasArr[dlzkaArr];        // array pre kombinacie datumu a casu
        double DatumCasArrNotSort[dlzkaArr]; // array pre kombinacie datumu a casu nezoradenych
        double HodnotaArr[dlzkaArr];         // array pre hodnoty
        char hodnotaLine[BUFFER];            // string pre nacitanie hodnoty zo suboru
        char casLine[BUFFER];                // string pre nacitanie casu zo suboru
        char datumLine[BUFFER];              // string pre nacitanie datumu zo suboru
        dlzkaArr = 0;
        int hodnotaSet = 0;
        int casSet = 0;
        int datumSet = 0;
        double datumCasDouble = 0;
        for (; fgets(readLine, sizeof(readLine), *subor) != NULL;) // nacitava riadok po riadku pokial nieje na konci suboru (NULL)
        {
            if (readLine[0] == 13) // ak sa nacitany riadok == prazdnemu riadku tak tuto iteraciu preskoci
            {
                continue;
            }
            readLine[strlen(readLine) - 2] = '\0';
            switch (riadokBezMedzier % 6) // zisti na akom type riadku sa nachadza (ID, MerModul, ...) a prekopiruje jednotlive riadoky do danych stringov
            {
            case 1:
                strcpy(merModulLine, readLine);
                merModulSet = 1;
                break;
            case 2:
                strcpy(typMerVelicinyLine, readLine);
                typMerVelSet = 1;
                break;
            case 3:
                strcpy(hodnotaLine, readLine);
                hodnotaSet = 1;
                break;
            case 4:
                strcpy(casLine, readLine);
                casSet = 1;
                break;
            case 5:
                strcpy(datumLine, readLine);
                datumSet = 1;
                break;
            default:
                break;
            }
            if (merModulSet && typMerVelSet && hodnotaSet && casSet && datumSet) // ak su nacitane vsetky hodnoty
            {
                if (!strcmp(typMerVeliciny, typMerVelicinyLine) && !strcmp(merModul, merModulLine)) // porovna stringy a zisti ci sa na danych indexoch a zisti na kolkych indexoch sa kombinacia mer modul a typ mer veliciny nachadza
                {
                    datumCasDouble = (atof(casLine) / 10000) + atoi(datumLine); // premeni cas na double a vydeli ho 10 000 a scita ho z datumom premeneny na int
                    DatumCasArr[dlzkaArr] = datumCasDouble;                     // zapise hodnoty do jednotlivych arrayov
                    DatumCasArrNotSort[dlzkaArr] = datumCasDouble;
                    HodnotaArr[dlzkaArr] = atof(hodnotaLine);
                    dlzkaArr++; // posunie index arrayov
                    printf("dlzka Arr: %d\n", dlzkaArr);
                }
                typMerVelSet = 0; // resetuje hodnoty ci su nacitane stringy
                merModulSet = 0;
                hodnotaSet = 0;
                casSet = 0;
                datumSet = 0;
            }
            riadokBezMedzier++;
        }
        fseek(*subor, 0, SEEK_SET);        // pointer suboru sa vrati na zaciatok suboru
        for (int i = 0; i < dlzkaArr; i++) // bubble sort na usporiadanie DatumCasArr vzostupne
        {
            for (int j = 0; j < dlzkaArr - 1; j++)
            {
                if (DatumCasArr[j] > DatumCasArr[j + 1])
                {
                    double temp = DatumCasArr[j];
                    DatumCasArr[j] = DatumCasArr[j + 1];
                    DatumCasArr[j + 1] = temp;
                }
            }
        }
        for (int i = 0; i < dlzkaArr; i++) // iteruje cez jednotlive arraye
        {
           
            for (int j = 0; j < dlzkaArr; j++) // iteruje cez array DatumCasArrNotSort
            {
                if (DatumCasArr[i] == DatumCasArrNotSort[j]) // zisti na ktorom indexe sa nachadza dana hodnota daneho datumu a casu
                {
                    if (((int)((DatumCasArr[i] - (int)DatumCasArr[i]) * 10000) + 0.01) < 1000) // ak je cas mensi ako 1000 (aby sa pred napr. 905 napisala 0 (0905))
                    {
                        printf("%s %s     %d     0%d   %lf\n", merModul, typMerVeliciny, (int)DatumCasArr[i], (int)(((DatumCasArr[i] - (int)DatumCasArr[i]) * 10000) + 0.01), HodnotaArr[j]);
                        break;
                    }
                    else
                    {
                        printf("%s %s     %d     %d   %lf\n", merModul, typMerVeliciny, (int)DatumCasArr[i], (int)(((DatumCasArr[i] - (int)DatumCasArr[i]) * 10000) + 0.01), HodnotaArr[j]);
                        break;
                    }
                }
            }
        }
    }
    else
    {
        char merModul[BUFFER];                       // string do ktoreho sa nacita mer modul
        char typMerVeliciny[BUFFER];                 // string do ktoreho sa nacita typ mer veliciny
        scanf("%s %s", merModul, typMerVeliciny);    // nacita mer modul a typ mer veliciny
        int dlzkaArr = 0;                            // premenna pre dlzku arrayu jadnotlivych arrayov (DatumCasArr, HodnotaArr, DatumCasNotSort) pre dany mer modul a typ mer veliciny
        for (int i = 0; (*MerModul)[i] != NULL; i++) // prechadza cez array pokial nieje koniec arrayu
        {
            if (!strcmp(typMerVeliciny, (*TypMerVeliciny)[i]) && !strcmp(merModul, (*MerModul)[i])) // porovna stringy a zisti ci sa na danych indexoch a zisti na kolkych indexoch sa kombinacia mer modul a typ mer veliciny nachadza
            {
                dlzkaArr++; // zvacsi dlzku arrayov += 1
            }
        }
        if (dlzkaArr == 0)
        { // ak sa nenachadza kombinacia mer modulu a typu mer veliciny (nenasla sa ani jedna zhoda)
            printf("Dana kombinacia sa nenachadza v subore.\n");
            return;
        }
        double DatumCasArr[dlzkaArr];        // array pre kombinacie datumu a casu
        double DatumCasArrNotSort[dlzkaArr]; // array pre kombinacie datumu a casu nezoradenych
        double HodnotaArr[dlzkaArr];         // array pre hodnoty danych mer modul a typ mer veliciny
        dlzkaArr = 0;
        double datumCasDouble = 0;                   // premenna ktora docasne uklada hodnotu datumu a casu
        for (int i = 0; (*MerModul)[i] != NULL; i++) // ten isty proces ako v loope nad tymto
        {
            if (!strcmp(typMerVeliciny, (*TypMerVeliciny)[i]) && !strcmp(merModul, (*MerModul)[i])) // ten isty proces ako v loope nad tymto
            {
                datumCasDouble = (atof((*Cas)[i]) / 10000) + atoi((*Datum)[i]); // premeni cas na double a vydeli ho 10 000 a scita ho z datumom premeneny na int
                DatumCasArr[dlzkaArr] = datumCasDouble;                         // zapise hodnoty do jednotlivych arrayov
                DatumCasArrNotSort[dlzkaArr] = datumCasDouble;
                HodnotaArr[dlzkaArr] = atof((*Hodnota)[i]);
                dlzkaArr++; // posunie index arrayov
            }
        }
        for (int i = 0; i < dlzkaArr; i++) // bubble sort na usporiadanie DatumCasArr vzostupne
        {
            for (int j = 0; j < dlzkaArr - 1; j++)
            {
                if (DatumCasArr[j] > DatumCasArr[j + 1])
                {
                    double temp = DatumCasArr[j];
                    DatumCasArr[j] = DatumCasArr[j + 1];
                    DatumCasArr[j + 1] = temp;
                }
            }
        }
        for (int i = 0; i < dlzkaArr; i++) // iteruje cez jednotlive arraye
        {
            for (int j = 0; j < dlzkaArr; j++) // iteruje cez array DatumCasArrNotSort
            {
                if (DatumCasArr[i] == DatumCasArrNotSort[j]) // zisti na ktorom indexe sa nachadza dana hodnota daneho datumu a casu
                {
                    if (((int)((DatumCasArr[i] - (int)DatumCasArr[i]) * 10000) + 0.01) < 1000) // ak je cas mensi ako 1000 (aby sa pred napr. 905 napisala 0 (0905))
                    {
                        printf("%s %s     %d     0%d   %lf\n", merModul, typMerVeliciny, (int)DatumCasArr[i], (int)(((DatumCasArr[i] - (int)DatumCasArr[i]) * 10000) + 0.01), HodnotaArr[j]);
                        break;
                    }
                    else
                    {
                        printf("%s %s     %d     %d   %lf\n", merModul, typMerVeliciny, (int)DatumCasArr[i], (int)(((DatumCasArr[i] - (int)DatumCasArr[i]) * 10000) + 0.01), HodnotaArr[j]);
                        break;
                    }
                }
            }
        }
    }
}
void h(char ***TypMerVeliciny, char ***Hodnota)
{
    if (*TypMerVeliciny == NULL) // ak niesu vytvorene dynamicke polia
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }
    char typMerVel[2048]; // string pre typ mer veliciny
    scanf("%s", typMerVel);
    double max = 0;
    double min = 0;
    int dlzkaArr = 0;
    double hodnotaTemp = 0;
    for (int i = 0; (*TypMerVeliciny)[i] != NULL; i++)
    {
        if (!strcmp(typMerVel, (*TypMerVeliciny)[i]))
        {
            hodnotaTemp = atof((*Hodnota)[i]);
            if (hodnotaTemp > max)
            {
                max = hodnotaTemp;
            }
            else
            {
                min = hodnotaTemp;
            }
            dlzkaArr++;
        }
    }
    double DoubleHodArr[dlzkaArr];
    dlzkaArr = 0;
    for (int i = 0; (*TypMerVeliciny)[i] != NULL; i++)
    {
        if (!strcmp(typMerVel, (*TypMerVeliciny)[i]))
        {
            hodnotaTemp = atof((*Hodnota)[i]);
            DoubleHodArr[dlzkaArr] = hodnotaTemp;
            dlzkaArr++;
        }
    }
    max = (int)max + (5 - ((int)max % 5));
    int pocetIntervalov = max / 5;
    double intervalIncrement = 0;
    int pocetnost = 0;
    printf("    %s\t\tpocetnost\n", typMerVel);
    while (intervalIncrement != max)
    {
        for (int i = 0; i < dlzkaArr; i++)
        {
            if (DoubleHodArr[i] > intervalIncrement && DoubleHodArr[i] <= intervalIncrement + 5)
            {
                pocetnost += 1;
            }
        }
        if (pocetnost != 0)
        {
            printf("(%0.1lf -", intervalIncrement);
            intervalIncrement += 5;
            printf(" %0.1lf>", intervalIncrement);
            printf("\t   %d", pocetnost);
            printf("\n");
        }
        else
        {
            intervalIncrement += 5;
        }
        pocetnost = 0;
    }
}
void n(FILE **subor, char ***ID, char ***MerModul, char ***TypMerVeliciny, char ***Hodnota, char ***Cas, char ***Datum)
{
    if (*subor == NULL)
    {
        printf("Neotvoreny subor.\n");
        return;
    }
    if (*ID != NULL)
    {
        for (int i = 0; (*ID)[i] != NULL; i++)
        {
            free((*ID)[i]);
        }
        free(*ID);
        for (int i = 0; (*MerModul)[i] != NULL; i++)
        {
            free((*MerModul)[i]);
        }
        free(*MerModul);
        for (int i = 0; (*TypMerVeliciny)[i] != NULL; i++)
        {
            free((*TypMerVeliciny)[i]);
        }
        free(*TypMerVeliciny);
        for (int i = 0; (*Hodnota)[i] != NULL; i++)
        {
            free((*Hodnota)[i]);
        }
        free(*Hodnota);
        for (int i = 0; (*Cas)[i] != NULL; i++)
        {
            free((*Cas)[i]);
        }
        free(*Cas);
        for (int i = 0; (*Datum)[i] != NULL; i++)
        {
            free((*Datum)[i]);
        }
        free(*Datum);
    }
    char readline[2048];
    int pocetID = 0;
    int pocetMerModul = 0;
    int pocetTypMerVeliciny = 0;
    int pocetHodnota = 0;
    int pocetCas = 0;
    int pocetDatum = 0;
    int riadokBezMedzier = 0;
    for (; fgets(readline, sizeof(readline), *subor) != NULL;)
    {
        if (readline[0] == 13)
        {
            continue;
        }
        switch (riadokBezMedzier % 6)
        {
        case 0:
            pocetID++;
            break;
        case 1:
            pocetMerModul++;
            break;
        case 2:
            pocetTypMerVeliciny++;
            break;
        case 3:
            pocetHodnota++;
            break;
        case 4:
            pocetCas++;
            break;
        case 5:
            pocetDatum++;
            break;
        }
        riadokBezMedzier++;
    }
    fseek(*subor, 0, SEEK_SET);
    riadokBezMedzier = 0;
    *ID = malloc(pocetID * sizeof(char *) + 1);
    *MerModul = malloc(pocetMerModul * sizeof(char *) + 1);
    *TypMerVeliciny = malloc(pocetTypMerVeliciny * sizeof(char *) + 1);
    *Hodnota = malloc(pocetHodnota * sizeof(char *) + 1);
    *Cas = malloc(pocetCas * sizeof(char *) + 1);
    *Datum = malloc(pocetDatum * sizeof(char *) + 1);
    int indexID = 0;
    int indexMerModul = 0;
    int indexTypMerVeliciny = 0;
    int indexHodnota = 0;
    int indexCas = 0;
    int indexDatum = 0;
    int dlzka = 0;
    for (; fgets(readline, sizeof(readline), *subor) != NULL;)
    {
        if (readline[0] == 13)
        {
            continue;
        }
        readline[strlen(readline) - 2] = '\0';
        
        switch (riadokBezMedzier % 6)
        {
        case 0:
            (*ID)[indexID] = malloc(dlzka * sizeof(char));
            strcpy((*ID)[indexID], readline);
            indexID++;
            break;
        case 1:
            (*MerModul)[indexMerModul] = malloc(dlzka * sizeof(char));
            strcpy((*MerModul)[indexMerModul], readline);
            indexMerModul++;
            break;
        case 2:
            (*TypMerVeliciny)[indexTypMerVeliciny] = malloc(dlzka * sizeof(char));
            strcpy((*TypMerVeliciny)[indexTypMerVeliciny], readline);
            indexTypMerVeliciny++;
            break;
        case 3:
            (*Hodnota)[indexHodnota] = malloc(dlzka * sizeof(char));
            strcpy((*Hodnota)[indexHodnota], readline);
            indexHodnota++;
            break;
        case 4:
            (*Cas)[indexCas] = malloc(dlzka * sizeof(char));
            strcpy((*Cas)[indexCas], readline);
            indexCas++;
            break;
        case 5:
            (*Datum)[indexDatum] = malloc(dlzka * sizeof(char));
            strcpy((*Datum)[indexDatum], readline);
            indexDatum++;
            break;
        }
        riadokBezMedzier++;
    }
    (*ID)[indexID + 1] = NULL;
    (*TypMerVeliciny)[indexTypMerVeliciny + 1] = NULL;
    (*MerModul)[indexMerModul + 1] = NULL;
    (*Hodnota)[indexHodnota + 1] = NULL;
    (*Cas)[indexCas + 1] = NULL;
    (*Datum)[indexDatum + 1] = NULL;
    fseek(*subor, 0, SEEK_SET);
}
void s(char ***MerModul, char ***TypMerVeliciny, char ***Datum, char ***Cas, char ***Hodnota)
{
    if (*MerModul == NULL)
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }
    FILE *vystupFile;
    vystupFile = fopen("./vystup_S.txt", "w+");
    if (vystupFile == NULL)
    {
        printf("err\n");
        return;
    }
    char merModul[2048];
    char typMerVeliciny[2048];
    double datum = 0;
    scanf("%s %s", merModul, typMerVeliciny);
    int dlzkaArr = 0;
    for (int i = 0; (*MerModul)[i] != NULL; i++)
    {
        if (!strcmp(typMerVeliciny, (*TypMerVeliciny)[i]) && !strcmp(merModul, (*MerModul)[i]))
        {
            dlzkaArr++;
        }
    }
    double DatumCasArr[dlzkaArr];
    double DatumCasArrNotSort[dlzkaArr];
    double HodnotaArr[dlzkaArr];
    dlzkaArr = 0;
    for (int i = 0; (*MerModul)[i] != NULL; i++)
    {
        if (!strcmp(typMerVeliciny, (*TypMerVeliciny)[i]) && !strcmp(merModul, (*MerModul)[i]))
        {
            datum = (atof((*Cas)[i]) / 10000) + atoi((*Datum)[i]);
            DatumCasArr[dlzkaArr] = datum;
            DatumCasArrNotSort[dlzkaArr] = datum;
            HodnotaArr[dlzkaArr] = atof((*Hodnota)[i]);
            dlzkaArr++;
        }
    }
    if (dlzkaArr == 0)
    {
        printf("Pre dany vstup neexistuju zaznamy.\n");
        return;
    }
    for (int i = 0; i < dlzkaArr; i++)
    {
        for (int j = 0; j < dlzkaArr - 1; j++)
        {
            if (DatumCasArr[j] > DatumCasArr[j + 1])
            {
                double temp = DatumCasArr[j];
                DatumCasArr[j] = DatumCasArr[j + 1];
                DatumCasArr[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < dlzkaArr; i++)
    {

        for (int j = 0; j < dlzkaArr; j++)
        {
            if (DatumCasArr[i] == DatumCasArrNotSort[j])
            {
                if ((int)((DatumCasArr[i] - (int)DatumCasArr[i]) * 10000) < 1000)
                {
                    fprintf(vystupFile, "%d0%d\t%0.6lf\n", (int)DatumCasArr[i], (int)(((DatumCasArr[i] - (int)DatumCasArr[i]) * 10000) + 0.01), HodnotaArr[j]);
                    break;
                }
                else
                {
                    fprintf(vystupFile, "%d%d\t%0.6lf\n", (int)DatumCasArr[i], (int)(((DatumCasArr[i] - (int)DatumCasArr[i]) * 10000) + 0.01), HodnotaArr[j]);
                    break;
                }
            }
        }
    }
    printf("Pre dany vstup je vytvoreny txt subor.\n");
    fclose(vystupFile);
}
void c(FILE **subor)
{
    if (*subor == NULL)
    {
        printf("Neotvoreny subor.\n");
        return;
    }
    int counter = 0;
    int riadokBezMedzier = 0;
    int riadok = 0;
    int errLocal = 0;
    int errGlobal = 0;
    int bodka = 0;
    int datumCounter = 0;
    char mnozina[10][3] = {"R1", "U1", "A1", "R2", "U2", "A2", "R4", "U4", "A4", "e"};
    char readLine[2048];
    for (; fgets(readLine, sizeof(readLine), *subor) != NULL;)
    {
        riadok++;
        if (readLine[0] == 13)
        {
            continue;
        }
        switch (riadokBezMedzier % 6)
        {
        case 0:

            for (int i = 0; readLine[i] != 13; i++)
            {
                if (readLine[i] < 48 || readLine[i] > 57)
                {
                    errLocal = 1;
                }
                counter++;
            }
            if (counter != 10)
            {
                errLocal = 1;
            }
            long long int ID_cislo = 0;
            int mocnina = 9;
            for (int i = 0; readLine[i] != 13 && mocnina >= 0; i++)
            {
                int cislo = (int)readLine[i] - 48;
                ID_cislo += cislo * pow(10, mocnina);
                mocnina--;
            }
            if (ID_cislo % 11 != 0)
            {
                errLocal = 1;
            }
            if (errLocal == 1)
            {
                printf("Nekorektne zadany vstup: ID cislo mer. osoby: %sna riadku: %d\n", readLine, riadok);
                errGlobal = 1;
            }
            errLocal = 0;
            counter = 0;
            break;
        case 1:

            for (int j = 0; readLine[j] != 13; j++)
            {
                counter++;
            }
            if (counter != 3)
            {
                errLocal = 1;
            }
            if (readLine[0] < 65 || readLine[0] > 90)
            {
                errLocal = 1;
            }
            if ((readLine[1] < 48 || readLine[1] > 57) || (readLine[2] < 48 || readLine[2] > 57))
            {
                errLocal = 1;
            }
            if (errLocal == 1)
            {
                printf("Nekorektne zadany vstup: Mer. modul: %sna riadku: %d\n", readLine, riadok);
                errGlobal = 1;
            }
            errLocal = 0;
            counter = 0;
            break;
        case 2:
            errLocal = 1;
            for (int i = 0; mnozina[i][0] != 'e'; i++)
            {
                if (readLine[0] == mnozina[i][0])
                {
                    if (readLine[1] == mnozina[i][1])
                    {
                        errLocal = 0;
                    }
                }
            }

            for (int j = 0; readLine[j] != 13; j++)
            {
                counter++;
            }
            if (counter != 2)
            {
                errLocal = 1;
            }
            if (errLocal == 1)
            {
                printf("Nekorektne zadany vstup: Typ mer. veliciny: %sna riadku: %d\n", readLine, riadok);
                errGlobal = 1;
            }
            errLocal = 0;
            counter = 0;
            break;
        case 3:
            if ((readLine[0] != 43 && readLine[0] != 45) || (readLine[0] < 48 || readLine[0] > 57))
            {

                for (int i = 0; readLine[i] != 13; i++)
                {
                    if (readLine[i] == 46)
                    {
                        bodka++;
                    }
                    if ((readLine[i] < 48 || readLine[i] > 57) && readLine[i] != 46)
                    {
                        errLocal = 1;
                    }
                }
                if (bodka > 1)
                {
                    errLocal = 1;
                }
            }
            if (errLocal == 1)
            {
                printf("Nekorektne zadany vstup: Hodnota: %sna riadku: %d\n", readLine, riadok);
                errGlobal = 1;
            }
            errLocal = 0;
            bodka = 0;
            break;
        case 4:
            errLocal = 1;
            if (readLine[0] > 47 && readLine[0] < 51)
            {
                if (readLine[0] == 50 && (readLine[1] > 47 && readLine[1] < 52))
                {
                    if ((readLine[2] > 47 && readLine[2] < 54) && (readLine[3] > 47 && readLine[3] < 58))
                    {
                        errLocal = 0;
                    }
                }
                else if (readLine[0] != 50)
                {
                    if ((readLine[1] > 47 && readLine[1] < 58) && (readLine[2] > 47 && readLine[2] < 54) && (readLine[3] > 47 && readLine[3] < 58))
                    {
                        errLocal = 0;
                    }
                }
            }
            for (int j = 0; readLine[j] != 13; j++)
            {
                counter++;
            }
            if (counter != 4)
            {
                errLocal = 1;
            }

            if (errLocal == 1)
            {
                printf("Nekorektne zadany vstup: Cas merania: %sna riadku: %d\n", readLine, riadok);
                errGlobal = 1;
            }
            errLocal = 0;
            counter = 0;
            break;
        case 5:
            for (int i = 0; readLine[i] != 13; i++)
            {
                if (readLine[i] < 48 || readLine[i] > 57)
                {
                    errLocal = 1;
                }
                counter++;
            }
            if (counter != 8)
            {
                errLocal = 1;
            }
            if (errLocal == 0)
            {
                int rok = 0;
                int mocninaRok = 3;
                int prestupny = 0;
                for (int i = 0; i < 4; i++)
                {
                    int cislo = (int)readLine[i] - 48;
                    rok += cislo * pow(10, mocninaRok);
                    mocninaRok--;
                }
                if (rok % 4 == 0)
                {
                    prestupny = 1;
                }
                int mocninaMesiac = 1;
                int mesiac = 0;
                for (int j = 4; j < 6; j++)
                {
                    int cislo = (int)readLine[j] - 48;
                    mesiac += cislo * pow(10, mocninaMesiac);
                    mocninaMesiac--;
                }
                int mocninaDatum = 1;
                int datum = 0;
                for (int k = 6; k < 8; k++)
                {
                    int cislo = (int)readLine[k] - 48;
                    datum += cislo * pow(10, mocninaDatum);
                    mocninaDatum--;
                }
                if (mesiac > 12 || datum > 31)
                {
                    errLocal = 1;
                }
                if (errLocal == 0)
                {
                    if (mesiac == 4 || mesiac == 6 || mesiac == 9 || mesiac == 11)
                    {
                        if (datum > 30)
                        {
                            errLocal = 1;
                        }
                    }
                    if (mesiac == 2)
                    {
                        if (prestupny == 0 && datum > 28)
                        {
                            errLocal = 1;
                        }
                        if (prestupny == 1 && datum > 29)
                        {
                            errLocal = 1;
                        }
                    }
                }
            }
            if (errLocal == 1)
            {
                printf("Nekorektne zadany vstup: Datum: %sna riadku: %d\n", readLine, riadok);
                errGlobal = 1;
            }
            errLocal = 0;
            counter = 0;
            break;
        }
        riadokBezMedzier++;
    }
    if (errGlobal == 0)
    {
        printf("Data su korektne.\n");
    }
    fseek(*subor, 0, SEEK_SET);
}
void r(char ***Cas)
{
    if (*Cas == NULL)
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }
    int pocet = 0;
    for (; (*Cas)[pocet] != NULL; pocet++)
        ;
    int CasIntArr[pocet];
    int cas = 0;

    for (int i = 0; (*Cas)[i] != NULL; i++)
    {
        cas = atoi((*Cas)[i]);
        CasIntArr[i] = cas;
        cas = 0;
    }
    for (int i = 0; i < pocet; i++)
    {
        for (int j = 0; j < pocet - 1; j++)
        {
            if (CasIntArr[j] > CasIntArr[j + 1])
            {
                int temp = CasIntArr[j];
                CasIntArr[j] = CasIntArr[j + 1];
                CasIntArr[j + 1] = temp;
            }
        }
    }
    int temp[pocet];
    int j = 0;
    for (int i = 0; i < pocet - 1; i++)
        if (CasIntArr[i] != CasIntArr[i + 1])
            temp[j++] = CasIntArr[i];
    temp[j++] = CasIntArr[pocet - 1];
    for (int i = 0; i < j; i++)
        CasIntArr[i] = temp[i];
    int cislo = 0;
    int check = 0;
    int pocitadlo = 0;
    int c = 0;
    for (int i = 0; i < j; i++)
    {
        if (i != 0 && (int)(CasIntArr[i] / 100) != cislo)
        {
            printf("\n");
        }

        if ((int)(CasIntArr[i] / 100) < 10)
        {
            if (i == 0 || (int)(CasIntArr[i] / 100) != cislo)
            {
                c = 0;
                pocitadlo = 0;
                check = i;
                while ((int)(CasIntArr[i] / 100) == (int)(CasIntArr[check] / 100))
                {
                    check++;
                    pocitadlo++;
                }
                printf("0%d:", (int)(CasIntArr[i] / 100));
            }
        }
        else
        {
            if (i == 0 || (int)(CasIntArr[i] / 100) != cislo)
            {
                c = 0;
                pocitadlo = 0;
                check = i;
                while ((int)(CasIntArr[i] / 100) == (int)(CasIntArr[check] / 100))
                {
                    check++;
                    pocitadlo++;
                }
                printf("%d:", (int)(CasIntArr[i] / 100));
            }
        }
        if (c == pocitadlo - 1)
        {
            if (CasIntArr[i] % 100 < 10)
            {
                printf("0%d", CasIntArr[i] % 100);
            }
            else
            {
                printf("%d", CasIntArr[i] % 100);
            }
            c++;
        }
        else
        {
            if (CasIntArr[i] % 100 < 10)
            {
                printf("0%d, ", CasIntArr[i] % 100);
            }
            else
            {
                printf("%d, ", CasIntArr[i] % 100);
            }
            c++;
        }
        cislo = (int)(CasIntArr[i] / 100);
    }
    printf("\n");
}
void z(char ***ID, char ***MerModul, char ***TypMerVeliciny, char ***Hodnota, char ***Cas, char ***Datum)
{
    if (*ID == NULL)
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }
    int pocetID = 0;
    for (; (*ID)[pocetID] != NULL; pocetID++)
        ;
    long long int IDIntArr[pocetID];
    int mocnina = 9;
    long long int IDc = 0;
    int cislo = 0;
    for (int i = 0; (*ID)[i] != NULL; i++)
    {
        mocnina = 9;
        for (int j = 0; (int)(*ID)[i][j] != '\0'; j++)
        {
            cislo = (int)(*ID)[i][j] - 48;
            IDc += cislo * pow(10, mocnina);
            mocnina--;
        }
        IDIntArr[i] = IDc;
        IDc = 0;
        cislo = 0;
    }
    long long int IDs = 0;
    scanf("%lld", &IDs);
    int pocet = 0;
    for (int i = 0; i < pocetID; i++)
    {
        if (IDIntArr[i] == IDs)
        {
            memmove(&(*ID)[i - pocet], &(*ID)[i + 1 - pocet], (pocetID - i + 1) * sizeof(char *));
            memmove(&(*MerModul)[i - pocet], &(*MerModul)[i + 1 - pocet], (pocetID - i + 1) * sizeof(char *));
            memmove(&(*TypMerVeliciny)[i - pocet], &(*TypMerVeliciny)[i + 1 - pocet], (pocetID - i + 1) * sizeof(char *));
            memmove(&(*Hodnota)[i - pocet], &(*Hodnota)[i + 1 - pocet], (pocetID - i + 1) * sizeof(char *));
            memmove(&(*Cas)[i - pocet], &(*Cas)[i + 1 - pocet], (pocetID - i + 1) * sizeof(char *));
            memmove(&(*Datum)[i - pocet], &(*Datum)[i + 1 - pocet], (pocetID - i + 1) * sizeof(char *));
            pocet++;
        }
    }
    if (pocet == 0)
    {
        printf("ID Neexistuje.\n");
    }
    else
    {
        printf("Vymazalo sa: %d zaznamov!\n", pocet);
    }
}
int main()
{
    FILE *subor = NULL;
    char **ID = NULL;
    char **MerModul = NULL;
    char **TypMerVeliciny = NULL;
    char **Hodnota = NULL;
    char **Cas = NULL;
    char **Datum = NULL;
    while (1)
    {
        char prikaz;
        scanf(" %c", &prikaz);
        while ((getchar()) != '\n')
            ;
        switch (prikaz)
        {
        case 'v':
            v(&subor, &ID, &MerModul, &TypMerVeliciny, &Hodnota, &Cas, &Datum);
            break;
        case 'o':
            o(&subor, &MerModul, &TypMerVeliciny, &Datum, &Cas, &Hodnota);
            break;
        case 'n':
            n(&subor, &ID, &MerModul, &TypMerVeliciny, &Hodnota, &Cas, &Datum);
            break;
        case 'c':
            c(&subor);
            break;
        case 's':
            s(&MerModul, &TypMerVeliciny, &Datum, &Cas, &Hodnota);
            break;
        case 'h':
            h(&TypMerVeliciny, &Hodnota);
            break;
        case 'r':
            r(&Cas);
            break;
        case 'z':
            z(&ID, &MerModul, &TypMerVeliciny, &Hodnota, &Cas, &Datum);
            break;
        case 'k':
            if (subor != NULL)
            {
                fclose(subor);
            }
            if (ID != NULL)
            {
                for (int i = 0; (ID)[i] != NULL; i++)
                {
                    free((ID)[i]);
                }
                free(ID);
                for (int i = 0; (MerModul)[i] != NULL; i++)
                {
                    free((MerModul)[i]);
                }
                free(MerModul);
                for (int i = 0; (TypMerVeliciny)[i] != NULL; i++)
                {
                    free((TypMerVeliciny)[i]);
                }
                free(TypMerVeliciny);
                for (int i = 0; (Hodnota)[i] != NULL; i++)
                {
                    free((Hodnota)[i]);
                }
                free(Hodnota);
                for (int i = 0; (Cas)[i] != NULL; i++)
                {
                    free((Cas)[i]);
                }
                free(Cas);
                for (int i = 0; (Datum)[i] != NULL; i++)
                {
                    free((Datum)[i]);
                }
                free(Datum);
            }
            return 0;
        default:
            printf("Nespravny prikaz\n");
        }
    }
    return 0;
}