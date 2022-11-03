#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define BUFFER 2048 // dlzka bufferu pre string
// v, o, n, c, s, h, r, z  done
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
            if (readLine[0] == 13 || readLine[0] == 10) // ak sa nacitany riadok == prazdnemu riadku tak tuto iteraciu preskoci
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
        if (readLine[0] == 13 || readLine[0] == 10) // ak sa nacitany riadok == prazdnemu riadku tak tuto iteraciu preskoci
        {
            continue;
        }
        if (readLine[strlen(readLine) - 2] == '\r')
        {
            readLine[strlen(readLine) - 2] = '\0'; // odstrani \r zo stringu
        }
        else
        {
            readLine[strlen(readLine) - 1] = '\0'; // odstrani \r zo stringu
        }
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
        if (readLine[0] == 13 || readLine[0] == 10) // ak sa nacitany riadok == prazdnemu riadku tak tuto iteraciu preskoci
        {
            continue;
        }
        if (readLine[strlen(readLine) - 2] == '\r')
        {
            readLine[strlen(readLine) - 2] = '\0'; // odstrani \r zo stringu
        }
        else
        {
            readLine[strlen(readLine) - 1] = '\0'; // odstrani \r zo stringu
        }
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
            }
            typMerVelSet = 0; // resetuje hodnoty ktore udavaju ci su nacitane jednotlive stringy
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
void n(FILE **subor, char ***ID, char ***MerModul, char ***TypMerVeliciny, char ***Hodnota, char ***Cas, char ***Datum)
{
    if (*subor == NULL) // ak nieje otvoreny subor
    {
        printf("Neotvoreny subor.\n");
        return;
    }
    if (*ID != NULL) // ak uz su vytvorene dynamicke polia najprv sa dealokuju a potom vytvoria nove
    {
        for (int i = 0; (*ID)[i] != NULL; i++) // dealokacia jednotlivych stringov
        {
            free((*ID)[i]);
        }
        free(*ID); // dealokacia arrayu v ktorom stringy su
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
    char readline[BUFFER]; // string riadku
    int pocetID = 0;
    int pocetMerModul = 0;
    int pocetTypMerVeliciny = 0;
    int pocetHodnota = 0;
    int pocetCas = 0;
    int pocetDatum = 0;
    int riadokBezMedzier = 0;
    for (; fgets(readline, sizeof(readline), *subor) != NULL;) // zisti pocet jednotlivych zaznamov
    {
        if (readline[0] == 13 || readline[0] == 10)
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
    fseek(*subor, 0, SEEK_SET); // vrati pointer suboru na zaciatok suboru
    riadokBezMedzier = 0;
    *ID = malloc(pocetID * sizeof(char *) + 1); // dynamicke alokovanie pamate pre jednotlive arraye
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
        if (readline[0] == 13 || readline[0] == 10)
        {
            continue;
        }
        if (readline[strlen(readline) - 2] == '\r')
        {
            readline[strlen(readline) - 2] = '\0'; // odstrani \r zo stringu
        }
        else
        {
            readline[strlen(readline) - 1] = '\0'; // odstrani \r zo stringu
        }
        switch (riadokBezMedzier % 6)
        {
        case 0:
            (*ID)[indexID] = malloc(dlzka * sizeof(char)); // dynamicke alokovanie pamate pre jednotlive stringy
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
    (*ID)[indexID + 1] = NULL; // pridanie NULL na koniec arrayu
    (*TypMerVeliciny)[indexTypMerVeliciny + 1] = NULL;
    (*MerModul)[indexMerModul + 1] = NULL;
    (*Hodnota)[indexHodnota + 1] = NULL;
    (*Cas)[indexCas + 1] = NULL;
    (*Datum)[indexDatum + 1] = NULL;
    fseek(*subor, 0, SEEK_SET); // vrati pointer suboru
}
void c(FILE **subor)
{
    if (*subor == NULL) // ak nieje otvoreny subor
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
    char mnozina[10][3] = {"R1", "U1", "A1", "R2", "U2", "A2", "R4", "U4", "A4", "e"}; // na konci string e aby sme vedeli kedy je koniec arrayu
    char readLine[BUFFER];                                                             // string riadku
    for (; fgets(readLine, sizeof(readLine), *subor) != NULL;)
    {
        riadok++;
        if (readLine[0] == 13 || readLine[0] == 10) // ak je prazdny riadok
        {
            continue;
        }
        switch (riadokBezMedzier % 6)
        {
        case 0:                                                          // riadok ID
            for (int i = 0; readLine[i] != 13 && readLine[i] != 10; i++) // prejde cez cely riadok a ak nie su vsteky char cisla hodi error
            {
                if (readLine[i] < 48 || readLine[i] > 57)
                {
                    errLocal = 1;
                }
                counter++;
            }
            if (counter != 10) // ak nie je dlzka riadku 10
            {
                errLocal = 1;
            }
            long long int ID_cislo = 0;

            int mocnina = 9;
            if (readLine[strlen(readLine) - 2] == '\r')
            {
                readLine[strlen(readLine) - 2] = '\0'; // odstrani \r zo stringu
            }
            else
            {
                readLine[strlen(readLine) - 1] = '\0'; // odstrani \r zo stringu
            }
            ID_cislo = atoll(readLine);
            if (ID_cislo % 11 != 0) // ak riadok nieje delitelny 11 hodi error
            {
                errLocal = 1;
            }
            if (errLocal == 1) // ak je error
            {
                printf("Nekorektne zadany vstup: ID cislo mer. osoby: %s\n", readLine);
                errGlobal = 1;
            }
            errLocal = 0;
            counter = 0;
            break;
        case 1:                                                          // riadok Mer Modul
            for (int j = 0; readLine[j] != 13 && readLine[j] != 10; j++) // pocet char riadku
            {
                counter++;
            }
            if (counter != 3) // ak dlzka riadku nieje 3
            {
                errLocal = 1;
            }
            if (readLine[0] < 65 || readLine[0] > 90) // ak prve pismeno nie je od A po Z
            {
                errLocal = 1;
            }
            if ((readLine[1] < 48 || readLine[1] > 57) || (readLine[2] < 48 || readLine[2] > 57)) // ak druhy a treti char nieje cislo
            {
                errLocal = 1;
            }
            if (errLocal == 1) // ak je error
            {
                printf("Nekorektne zadany vstup: Mer. modul: %s\n", readLine);
                errGlobal = 1;
            }
            errLocal = 0;
            counter = 0;
            break;
        case 2:                                        // riadok Typ mer veliciny
            errLocal = 1;                              // err == 1 treba ho vynulovat
            for (int i = 0; mnozina[i][0] != 'e'; i++) // iteruje cez array pokial nieje na "e"
            {
                if (readLine[0] == mnozina[i][0]) // ak je prvy char riadku v array
                {
                    if (readLine[1] == mnozina[i][1]) // ak aj druhy char riadku je v array (na tom istom indexe ako ten prvy)
                    {
                        errLocal = 0; // format je spravny
                    }
                }
            }
            for (int j = 0; readLine[j] != 13 && readLine[j] != 10; j++) // pocet char v riadku
            {
                counter++;
            }
            if (counter != 2) // ak riadok nema dlzku 2
            {
                errLocal = 1;
            }
            if (errLocal == 1) // ak je error
            {
                printf("Nekorektne zadany vstup: Typ mer. veliciny: %s\n", readLine);
                errGlobal = 1;
            }
            errLocal = 0;
            counter = 0;
            break;
        case 3:                                                                // riadok Hodnota
            if ((readLine[0] != 45) || (readLine[0] < 48 || readLine[0] > 57)) // ak nieje prvy char - alebo nieje cislo
            {
                for (int i = 0; readLine[i] != 13 && readLine[i] != 10; i++) // prejde cez cely riadok char po char
                {
                    if (readLine[i] == 46) // ak sa char == .
                    {
                        bodka++;
                    }
                    if ((readLine[i] < 48 || readLine[i] > 57) && readLine[i] != 46) // ak char nieje cislo
                    {
                        errLocal = 1;
                    }
                }
                if (bodka > 1) // ak je v cisle viac bodiek ako 1
                {
                    errLocal = 1;
                }
            }
            if (errLocal == 1) // ak je error
            {
                printf("Nekorektne zadany vstup: Hodnota: %s\n", readLine);
                errGlobal = 1;
            }
            errLocal = 0;
            bodka = 0;
            break;
        case 4:                                       // riadok Cas
            errLocal = 1;                             // err == 1 treba ho vynulovat
            if (readLine[0] > 47 && readLine[0] < 51) // zisti ci je prve cislo bud 0, 1, 2
            {
                if (readLine[0] == 50 && (readLine[1] > 47 && readLine[1] < 52)) // ak sa prve cislo rovna 2 a a druhe cislo je z intervalu <0,3>
                {
                    if ((readLine[2] > 47 && readLine[2] < 54) && (readLine[3] > 47 && readLine[3] < 58)) // ak tretie cislo je z intervalu <0,5> a stvrte <0,9> vynuluje sa error
                    {
                        errLocal = 0;
                    }
                }
                else if (readLine[0] != 50) // ak prve cislo nieje 2jka
                {
                    if ((readLine[1] > 47 && readLine[1] < 58) && (readLine[2] > 47 && readLine[2] < 54) && (readLine[3] > 47 && readLine[3] < 58)) // ak je druhe cislo z intervalu <0,9>, tretie z intervalu <0,5> a stvrte z <0,9> vynuluje sa error
                    {
                        errLocal = 0;
                    }
                }
            }
            for (int j = 0; readLine[j] != 13 && readLine[j] != 10; j++) // spocita pocet char casu
            {
                counter++;
            }
            if (counter != 4) // ak sa dlzka casu nerovna 4
            {
                errLocal = 1;
            }
            if (errLocal == 1) // ak je na riadku error
            {
                printf("Nekorektne zadany vstup: Cas merania: %s\n", readLine);
                errGlobal = 1;
            }
            errLocal = 0;
            counter = 0;
            break;
        case 5:                                                          // riadok Datum
            for (int i = 0; readLine[i] != 13 && readLine[i] != 10; i++) // zisti ci su vsetky su vsetky char cisla a ak nie hodi error
            {
                if (readLine[i] < 48 || readLine[i] > 57)
                {
                    errLocal = 1;
                }
                counter++;
            }
            if (counter != 8) // ak je datum kratsi alebo dlhsi ako 8 char hodi error
            {
                errLocal = 1;
            }
            if (errLocal == 0)
            {
                int rok = 0;
                int mocninaRok = 3;
                int prestupny = 0;
                for (int i = 0; i < 4; i++) // vycisli rok
                {
                    int cislo = (int)readLine[i] - 48;
                    rok += cislo * pow(10, mocninaRok);
                    mocninaRok--;
                }
                if (rok % 4 == 0) // zisti ci je rok prestupny
                {
                    prestupny = 1;
                }
                int mocninaMesiac = 1;
                int mesiac = 0;
                for (int j = 4; j < 6; j++) // vycisli mesiac
                {
                    int cislo = (int)readLine[j] - 48;
                    mesiac += cislo * pow(10, mocninaMesiac);
                    mocninaMesiac--;
                }
                int mocninaDatum = 1;
                int datum = 0;
                for (int k = 6; k < 8; k++) // vycisli datum
                {
                    int cislo = (int)readLine[k] - 48;
                    datum += cislo * pow(10, mocninaDatum);
                    mocninaDatum--;
                }
                if (mesiac > 12 || datum > 31) // ak je mesiac alebo datum mimo interval
                {
                    errLocal = 1;
                }
                if (errLocal == 0)
                {
                    if (mesiac == 4 || mesiac == 6 || mesiac == 9 || mesiac == 11) // ak ma mesiac 30 dni a mal by nahodou 31 hodi error
                    {
                        if (datum > 30)
                        {
                            errLocal = 1;
                        }
                    }
                    if (mesiac == 2) // ak je februar zisti ci ma mat maximalne 28 alebo 29 dni
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
            if (errLocal == 1) // ak sa bol error niekde na riadku
            {
                printf("Nekorektne zadany vstup: Datum: %s\n", readLine);
                errGlobal = 1;
            }
            errLocal = 0;
            counter = 0;
            break;
        }
        riadokBezMedzier++;
    }
    if (errGlobal == 0) // ak su vsetky data korektne
    {
        printf("Data su korektne.\n");
    }
    fseek(*subor, 0, SEEK_SET); // vrati pointer suboru na zaciatok suboru
}
void s(char ***MerModul, char ***TypMerVeliciny, char ***Datum, char ***Cas, char ***Hodnota)
{
    if (*MerModul == NULL) // ak polia niesu vytvorene
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }
    FILE *vystupFile;                           // deklaracia vystupneho suboru
    vystupFile = fopen("./vystup_S.txt", "w+"); // vytvory vystupny subor
    if (vystupFile == NULL)                     // ak sa ho nepodarilo vytvorit
    {
        printf("err\n");
        return;
    }
    char merModul[BUFFER];
    char typMerVeliciny[BUFFER];
    double datum = 0;
    scanf("%s %s", merModul, typMerVeliciny); // nacita mer modul a typ mer veliciny
    int dlzkaArr = 0;
    for (int i = 0; (*MerModul)[i] != NULL; i++) // iteruje cez mer modul pokial nieje NULL
    {
        if (!strcmp(typMerVeliciny, (*TypMerVeliciny)[i]) && !strcmp(merModul, (*MerModul)[i])) // ak su kombinacie mer modul a typ mer veliciny spravne na danych indexoch
        {
            dlzkaArr++; // zvacsi dlzku arr
        }
    }
    double DatumCasArr[dlzkaArr];        // array datumu a casu danych kombinacii mer modul a typ mer veliciny
    double DatumCasArrNotSort[dlzkaArr]; // ten isty arr ale nebude usporiadany
    double HodnotaArr[dlzkaArr];         // array hodnot danych kombinacii mer modul a typ mer veliciny
    dlzkaArr = 0;
    for (int i = 0; (*MerModul)[i] != NULL; i++) // iteruje cez mer modul pokial nieje NULL
    {
        if (!strcmp(typMerVeliciny, (*TypMerVeliciny)[i]) && !strcmp(merModul, (*MerModul)[i])) // ak su kombinacie mer modul a typ mer veliciny spravne na danych indexoch
        {
            datum = (atof((*Cas)[i]) / 10000) + atoi((*Datum)[i]); // konvertuje cas na float a datum na int a scita ich do formatu (napr. 20221230.0905)
            DatumCasArr[dlzkaArr] = datum;                         // zapise sa do arr
            DatumCasArrNotSort[dlzkaArr] = datum;
            HodnotaArr[dlzkaArr] = atof((*Hodnota)[i]); // hodnotu konvertuje na float a ulozi dod arrayu
            dlzkaArr++;
        }
    }
    if (dlzkaArr == 0) // ak neexistuje kombinacia mer modul a typ mer veliciny
    {
        printf("Pre dany vstup neexistuju zaznamy.\n");
        return;
    }
    for (int i = 0; i < dlzkaArr; i++) // bubble sort na DatumCasArr
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
    fclose(vystupFile); // uzavre subor
}
void h(char ***TypMerVeliciny, char ***Hodnota)
{
    if (*TypMerVeliciny == NULL) // ak niesu vytvorene dynamicke polia
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }
    char typMerVel[BUFFER]; // string pre typ mer veliciny
    scanf("%s", typMerVel); // nacita typ mer veliciny
    double max = 0;
    double min = 0;
    int dlzkaArr = 0;
    double hodnotaTemp = 0;
    for (int i = 0; (*TypMerVeliciny)[i] != NULL; i++) // zisti pocet zaznamov ktore maju dany typ mer veliciny
    {
        if (!strcmp(typMerVel, (*TypMerVeliciny)[i]))
        {
            hodnotaTemp = atof((*Hodnota)[i]); // zisti maximalnu hodnotu
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
    double DoubleHodArr[dlzkaArr]; // array pre hodnoty danej typ mer veliciny
    dlzkaArr = 0;
    for (int i = 0; (*TypMerVeliciny)[i] != NULL; i++) // prepise dane hodnoty do arrayu v tvare floatu
    {
        if (!strcmp(typMerVel, (*TypMerVeliciny)[i]))
        {
            hodnotaTemp = atof((*Hodnota)[i]);
            DoubleHodArr[dlzkaArr] = hodnotaTemp;
            dlzkaArr++;
        }
    }
    max = (int)max + (5 - ((int)max % 5)); // max sa zaokruhli hore podla 5ky ak max = 4 tak max = 5 ak napr max = 126 tak max = 130 atd
    int pocetIntervalov = max / 5;         // zisti pocet intervalov
    double intervalIncrement = 0;          // zvacsovanie intervalu
    int pocetnost = 0;
    printf("    %s\t\tpocetnost\n", typMerVel);
    while (intervalIncrement != max) // pokial sa interval nerovna max
    {
        for (int i = 0; i < dlzkaArr; i++) // iteruje cez DoubleHodArr
        {
            if (DoubleHodArr[i] > intervalIncrement && DoubleHodArr[i] <= intervalIncrement + 5) // ak je hodnota z toho daneho pod intervalu zvacsi pocetnost
            {
                pocetnost += 1;
            }
        }
        if (pocetnost != 0) // ak je pocetnost podintervalu nenulova printuje dany riadok
        {
            printf("(%0.1lf -", intervalIncrement);
            intervalIncrement += 5;
            printf(" %0.1lf>", intervalIncrement);
            printf("\t   %d", pocetnost);
            printf("\n");
        }
        else // inak zvacsi increment intervalu o 5
        {
            intervalIncrement += 5;
        }
        pocetnost = 0;
    }
}
void r(char ***Cas)
{
    if (*Cas == NULL) // ak dynamicke polia niesu vytvorene
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }
    int pocet = 0;
    for (; (*Cas)[pocet] != NULL; pocet++) // spocita pocet casov v array
        ;
    int CasIntArr[pocet];
    int cas = 0;
    for (int i = 0; (*Cas)[i] != NULL; i++) // iteruje cez *Cas a konvertuje stringy do int a pridava ich do CasIntArr
    {
        cas = atoi((*Cas)[i]);
        CasIntArr[i] = cas;
        cas = 0;
    }
    for (int i = 0; i < pocet; i++) // bubble sort na CasIntArr
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
    int j = 0;                          // nova dlzka arrayu bez duplikatov
    for (int i = 0; i < pocet - 1; i++) // iteruje cez CasIntArr a vymaze duplikaty
    {
        if (CasIntArr[i] != CasIntArr[i + 1])
        {
            temp[j++] = CasIntArr[i];
        }
    }
    temp[j++] = CasIntArr[pocet - 1];
    for (int i = 0; i < j; i++)
    {
        CasIntArr[i] = temp[i];
    }
    int cislo = 0;
    int check = 0;
    int pocitadlo = 0;
    int c = 0;
    for (int i = 0; i < j; i++) // iteruje cez CasIntArr
    {
        if (i != 0 && (int)(CasIntArr[i] / 100) != cislo) // ak sa hodina nerovna predoslej hodine tak preskoci na novy riadok
        {
            printf("\n");
        }

        if ((int)(CasIntArr[i] / 100) < 10) // ak je hodina mensia ako 10 napise pred hodinu 0
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
        else // ak je hodina > 10
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
        if (c == pocitadlo - 1) // ak je to posledny udaj v riadku nenapise ,
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
        else // ak nie je poslendny udaj v riadku napise ,
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
        cislo = (int)(CasIntArr[i] / 100); // ulozi cislo a pouzije ho v dalsej iteracii ako predosle cislo
    }
    printf("\n");
}
void z(char ***ID, char ***MerModul, char ***TypMerVeliciny, char ***Hodnota, char ***Cas, char ***Datum)
{
    if (*ID == NULL) // ak dynamicke polia niesu vytvorene
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }
    int pocetID = 0;
    for (; (*ID)[pocetID] != NULL; pocetID++) // zisti kolko ID je v array
        ;
    long long int IDIntArr[pocetID]; // vytvory array na ID v formate long long int
    long long int IDc = 0;
    for (int i = 0; (*ID)[i] != NULL; i++)
    {
        IDc = atoll((*ID)[i]);
        IDIntArr[i] = IDc; // prida ho do arrayu
        IDc = 0;
    }
    long long int IDinput = 0;
    scanf("%lld", &IDinput); // nacita dane ID
    int pocet = 0;
    for (int i = 0; i < pocetID; i++) // iteruje cez IDIntArr
    {
        if (IDIntArr[i] == IDinput) // ak je zhoda danych ID
        {
            free((*ID)[i - pocet]); // najprv uvolni string ktory sa pojde vymazat
            memmove(&(*ID)[i - pocet], &(*ID)[i + 1 - pocet], (pocetID - i + 1) * sizeof(char *)); // od indexu [i + 1 - pocet] posunie cely array na index [i - pocet] cim nahradi dany string ktory chceme vymazat (posuva pamat)
            free((*MerModul)[i - pocet]);
            memmove(&(*MerModul)[i - pocet], &(*MerModul)[i + 1 - pocet], (pocetID - i + 1) * sizeof(char *));
            free((*TypMerVeliciny)[i - pocet]);
            memmove(&(*TypMerVeliciny)[i - pocet], &(*TypMerVeliciny)[i + 1 - pocet], (pocetID - i + 1) * sizeof(char *));
            free((*Hodnota)[i - pocet]);
            memmove(&(*Hodnota)[i - pocet], &(*Hodnota)[i + 1 - pocet], (pocetID - i + 1) * sizeof(char *));
            free((*Cas)[i - pocet]);
            memmove(&(*Cas)[i - pocet], &(*Cas)[i + 1 - pocet], (pocetID - i + 1) * sizeof(char *));
            free((*Datum)[i - pocet]);
            memmove(&(*Datum)[i - pocet], &(*Datum)[i + 1 - pocet], (pocetID - i + 1) * sizeof(char *));
            pocet++; // uchovava pocet vymazanych indexov aby sme sa vedeli posuvat relativne od vymazanych stringov
        }
    }
    if (pocet == 0) // ak dane id neexistuje
    {
        printf("ID Neexistuje.\n");
    }
    else // ak sa vymazali zaznamy
    {
        printf("Vymazalo sa: %d zaznamov!\n", pocet);
    }
}
int main()
{
    FILE *subor = NULL;
    char **ID = NULL; // deklaracia jednotlivych retazcov stringov
    char **MerModul = NULL;
    char **TypMerVeliciny = NULL;
    char **Hodnota = NULL;
    char **Cas = NULL;
    char **Datum = NULL;
    char prikaz;
    while (1) // loop bezi pokial sa neukonci program
    {
        scanf(" %c", &prikaz); // nacita prikaz
        while ((getchar()) != '\n') // vycisti sa input
            ;
        switch (prikaz) // volanie jednotlivych funkcii podla zadaneho prikazu
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
            if (subor != NULL) // ak je subor otvoreny tak sa zavre
            {
                fclose(subor);
            }
            if (ID != NULL) // ak su vytvorene dynamicke polia tak sa uvolni pamat tych poli, aj stringov v nich
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
            printf("Nespravny prikaz\n"); // nespravny prikaz
        }
    }
    return 0;
}