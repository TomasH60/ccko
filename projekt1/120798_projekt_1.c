#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void v(FILE **subor, char ***ID, char ***MerModul, char ***TypMerVeliciny, char ***Hodnota, char ***Cas, char ***Datum)
{
    if (*subor == NULL)
    {
        *subor = fopen("./dataloger.txt", "r+");
        if (*subor == NULL)
        {
            printf("Neotvoreny subor.\n");
            return;
        }
    }

    if (*ID != NULL)
    {
        int eoaID = 0;
        int eoaMerModul = 0;
        int eoaTypMerVeliciny = 0;
        int eoaHodnota = 0;
        int eoaCas = 0;
        int eoaDatum = 0;
        for (int i = 0;; i++)
        {
            if ((*ID)[i] == NULL)
            {
                eoaID = 1;
            }
            else
            {
                printf("ID cislo mer. osoby: %s\n", (*ID)[i]);
            }
            if ((*MerModul)[i] == NULL)
            {
                eoaMerModul = 1;
            }
            else
            {
                printf("Mer. modul: %s\n", (*MerModul)[i]);
            }
            if ((*TypMerVeliciny)[i] == NULL)
            {
                eoaTypMerVeliciny = 1;
            }
            else
            {
                printf("Typ mer. veliciny: %s\n", (*TypMerVeliciny)[i]);
            }
            if ((*Hodnota)[i] == NULL)
            {
                eoaHodnota = 1;
            }
            else
            {
                printf("Hodnota: %s\n", (*Hodnota)[i]);
            }
            if ((*Cas)[i] == NULL)
            {
                eoaCas = 1;
            }
            else
            {
                printf("Cas merania: %s\n", (*Cas)[i]);
            }
            if ((*Datum)[i] == NULL)
            {
                eoaDatum = 1;
            }
            else
            {
                printf("Datum: %s\n", (*Datum)[i]);
            }
            printf("\n");
            if (eoaID && eoaMerModul && eoaTypMerVeliciny && eoaHodnota && eoaCas && eoaDatum)
                break;
        }
    }
    else
    {
        int riadokBezMedzier = 0;
        char readLine[2048];
        for (; fgets(readLine, sizeof(readLine), *subor) != NULL;)
        {
            if (readLine[0] == 13)
            {
                continue;
            }
            switch (riadokBezMedzier % 6)
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
        fseek(*subor, 0, SEEK_SET);
    }
}
void o(FILE **subor)
{
    if (*subor == NULL)
    {
        printf("Neotvoreny subor.\n");
        return;
    }
    char merModul[2048];
    char typMerVeliciny[2048];
    scanf("%s %s", merModul, typMerVeliciny);

}
void h (char *** TypMerVeliciny, char *** Hodnota) {
    if (*TypMerVeliciny == NULL) {
        printf("Polia nie su vytvorene.\n");
        return;
    }
    char typMerVel[2048];
    scanf("%s", typMerVel);

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
        free(*ID);
        free(*MerModul);
        free(*TypMerVeliciny);
        free(*Hodnota);
        free(*Cas);
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
        dlzka = strlen(readline);
        readline[dlzka - 1] = '\0';
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
    /*printf("ID: %d\n", pocetID);
     printf("MerModul: %d\n", pocetMerModul);
     printf("TypMer: %d\n", pocetTypMerVeliciny);
     printf("Hodnota: %d\n", pocetHodnota);
     printf("Cas: %d\n", pocetCas);
     printf("Datum: %d\n", pocetDatum);*/

    fseek(*subor, 0, SEEK_SET);
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
    printf("caspocet: %d\n", pocet);
    int CasIntArr[pocet];
    int mocnina = 3;
    int cas = 0;
    for (int i = 0; (*Cas)[i] != NULL; i++)
    {
        mocnina = 3;
        for (int j = 0; (*Cas)[i][j] != '\0'; j++)
        {
            int cislo = (int)(*Cas)[i][j] - 48;
            cas += cislo * (int)pow(10, mocnina);
            mocnina--;
        }
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
    int cislo = 0;
    int check = 0;
    int pocitadlo = 0;
    int c = 0;
    for (int i = 0; i < pocet; i++)
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
void z (char ***ID, char ***MerModul, char ***TypMerVeliciny, char ***Hodnota, char ***Cas, char ***Datum) {
    if (*ID == NULL)
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }
    int pocetID = 0;
    for (; (*ID)[pocetID] != NULL; pocetID++)
        ;
    printf("IDpocet: %d\n", pocetID);
    char strID[2048];
    
    scanf("%s", strID);
    printf("strlen: %d\n", strlen(strID));
    strID[strlen(strID)] = '\r';
    int pocetcas = pocetID - 1;
    for (int i = 0; i < pocetID; i++)
    {
        if(!strcmp((*ID)[i], strID)) {
            printf("%d i\n", i);
            memmove(&(*Cas)[pocetcas], &(*Cas)[pocetcas+1], pocetcas * sizeof(char*));
            printf("POCEt CAS: %d\n", pocetcas);
            pocetcas--;
        }
    }
    printf("%d", pocetcas);
  
    for (int i = 0; (*Cas)[i] != NULL; i++) {
        printf("%s\n", (*Cas)[i]);
        
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
        switch (prikaz)
        {
        case 'v':
            v(&subor, &ID, &MerModul, &TypMerVeliciny, &Hodnota, &Cas, &Datum);
            break;
        case 'o':
            o(&subor);
            break;
        case 'n':
            n(&subor, &ID, &MerModul, &TypMerVeliciny, &Hodnota, &Cas, &Datum);
            break;
        case 'c':
            c(&subor);
            break;
        case 's':
            /* code */
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
            // free()
            if (subor != NULL)
            {
                fclose(subor);
            }
            if (ID != NULL)
            {
                free(ID);
                free(MerModul);
                free(TypMerVeliciny);
                free(Hodnota);
                free(Cas);
                free(Datum);
            }
            return 0;
        default:
            printf("Nespravny prikaz\n");
        }
    }
    return 0;
}