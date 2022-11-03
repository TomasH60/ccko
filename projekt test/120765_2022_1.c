#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void v(FILE **dataloger, char **pomenovania, long long int *ID, char **MM, char **TMV, double *H, int *CM, long long int *D, int howmany)
{
    if (howmany == 0)
    { // Skontrolujeme či boli allocované dynamické polia
        char line[100];
        if (*dataloger == NULL) // Skontrolujeme či bol súbor otvorený
        {
            *dataloger = fopen("./dataloger.txt", "r"); // skúsime otvoriť
            if (*dataloger == NULL)                     // Ak sa nepodarí vypíšeme: neotvoreny subor
            {
                printf("Neotvoreny subor\n");
                return;
            }
        }
        
        int i = 0;
        while (fgets(line, 100, *dataloger) != NULL) // Dokiaľ nie sme na konci súboru berieme celé riadky
        {
            printf("%s%s", pomenovania[i % 7], line); // Printujeme riadok a príslušné pomenovanie k nemu
            i++;
        }
        fseek(*dataloger, 0, SEEK_SET);
    }
    else
    { // Inak vypíšeme dáta z dynamických polí s príslušným pomenovaním
        for (int i = 0; i < (int)(howmany / 7); i++)
        {
            printf("%s%lld\n", pomenovania[0], ID[i]);
            printf("%s%s", pomenovania[1], MM[i]);
            printf("%s%s", pomenovania[2], TMV[i]);
            printf("%s%lf\n", pomenovania[3], H[i]);
            printf("%s%d\n", pomenovania[4], CM[i]);
            printf("%s%lld\n\n", pomenovania[5], D[i]);
        }
    }
}
void o(FILE **dataloger)
{
    if (*dataloger != NULL) // Skontrolujeme či bol súbor otvorený
    {
        char pozadovany_mer_modul[4], pozadovana_mer_velicina[3], nacitany_string_1[100];
        scanf("%s %s", pozadovany_mer_modul, pozadovana_mer_velicina); // Načítavame požadovaný Mer modul a Mer veličinu
        int i = 0, b = 16;
        double *hodnota = (double *)calloc(b, sizeof(double)); // Vytvárame dynamické polia pre dátum čas a hodnotu ↓
        long long int *datum = (long long int *)calloc(b, sizeof(long long int)), *cas = (long long int *)calloc(b, sizeof(long long int)), *celydatum = (long long int *)calloc(b, sizeof(long long int));
        while (feof(*dataloger) == 0) // Dokiaľ nie sme na konci súboru
        {
            fgets(nacitany_string_1, 100, *dataloger);                                                                                                                 // Načítávame celé riadky
            if (nacitany_string_1[0] == pozadovany_mer_modul[0] && nacitany_string_1[1] == pozadovany_mer_modul[1] && nacitany_string_1[2] == pozadovany_mer_modul[2]) // Ak sa prvé 3 písmená riadku rovnajú s načítaným Mer modulom
            {
                fgets(nacitany_string_1, 100, *dataloger);
                if (nacitany_string_1[0] == pozadovana_mer_velicina[0] && nacitany_string_1[1] == pozadovana_mer_velicina[1]) // Ak sa prvé 2 písmená riadku rovnajú s načítanou Mer veličinou
                {
                    fscanf(*dataloger, "%lf\n", &hodnota[i]); // Načítame ďaľšie 3 riadky do našich polí ↓
                    fscanf(*dataloger, "%lld\n", &cas[i]);
                    fscanf(*dataloger, "%lld\n", &datum[i]);
                    celydatum[i] = datum[i] * 10000 + cas[i]; // Spočítame 10000 násobok datumu s časom a vytvríme celkový čas ktorý môžeme neskôr porovnávať

                    if (i == b - 2) // Ak sa počet prvkov blíži k veľkosti polí reallocujeme na dvojnásobnú veľkosť
                    {

                        b *= 2;
                        hodnota = (double *)realloc(hodnota, b * sizeof(double));
                        cas = (long long int *)realloc(cas, b * sizeof(long long int));
                        datum = (long long int *)realloc(datum, b * sizeof(long long int));
                        celydatum = (long long int *)realloc(celydatum, b * sizeof(long long int));
                    }
                    i++;
                }
            }
        }
        for (int a = 0; a < i; a++) // Bubble sort ↓
        {
            for (int j = 0; j < i - a - 1; j++)
            {

                if (celydatum[j] > celydatum[j + 1]) // Podľa celého dátumu triedim všetky ↓
                {

                    long long int temp;
                    double atemp;
                    temp = celydatum[j];
                    celydatum[j] = celydatum[j + 1];
                    celydatum[j + 1] = temp;
                    temp = datum[j];
                    datum[j] = datum[j + 1];
                    datum[j + 1] = temp;

                    temp = cas[j];
                    cas[j] = cas[j + 1];
                    cas[j + 1] = temp;

                    atemp = hodnota[j];
                    hodnota[j] = hodnota[j + 1];
                    hodnota[j + 1] = atemp;
                }
            }
        }

        for (int k = 0; k < i; k++)
        {
            printf("%s %s %lld ", pozadovany_mer_modul, pozadovana_mer_velicina, datum[k]);
            if (cas[k] < 1000) // Ak má čas len 3 čísla printneme pred čas 0
            {
                printf("0");
            }
            printf("%lld %lf  %d\n", cas[k], hodnota[k], k);
        }
    }
    else
    {
        printf("Neotvoreny subor.\n");
    }
    fseek(*dataloger, 0, SEEK_SET);
}
void n(FILE **dataloger, long long int **ID, char ***MM, char ***TMV, double **H, int **CM, long long int **D, int *howmany)
{
   
    if (*dataloger != NULL) // Skontrolujeme či bol súbor otvorený
    {
        char placeholder[100];
        int i = 0, b = 0;
        while (fgets(placeholder, 100, *dataloger) != NULL) // Počítame riadky
        {
            i++;
        }
        for (int j = 0; j < (int)((*howmany) / 7); j++)
        {
            free((*MM)[j]);
            free((*TMV)[j]);
        }

        free(*ID);
        free(*MM);
        free(*TMV);
        free(*H);
        free(*CM);
        free(*D); // Dealokujeme Predchádzajúce záznamy↑

        *ID = (long long int *)calloc((int)((i + 1) / 7), sizeof(long long int)); // Alocujeme počet riadkov/7 prkov pre každé pole ↓
        *MM = (char **)calloc((int)((i + 1) / 7), sizeof(char *));
        *TMV = (char **)calloc((int)((i + 1) / 7), sizeof(char *));
        *H = (double *)calloc((int)((i + 1) / 7), sizeof(double));
        *CM = (int *)calloc((int)((i + 1) / 7), sizeof(int));
        *D = (long long int *)calloc((int)((i + 1) / 7), sizeof(long long int));
        *howmany = i + 1;
        fseek(*dataloger, 0, SEEK_SET);
        i = 0;

        long long int IDC = 0;
        int CMC = 0;

        while (feof(*dataloger) == 0) // Zapisujeme dáta do polí ↓
        {
            fscanf(*dataloger, "%lld\n", &((*ID)[b]));

            fgets(placeholder, 100, *dataloger);

            (*MM)[b] = (char *)calloc(4, sizeof(char));

            for (int a = 0; a < 4; a++)
            {
                (*MM)[b][a] = placeholder[a];
            }

            fgets(placeholder, 100, *dataloger);
            (*TMV)[b] = calloc(3, sizeof(char));
            for (int a = 0; a < 3; a++)
            {
                (*TMV)[b][a] = placeholder[a];
            }

            fscanf(*dataloger, "%lf\n", &((*H)[b]));

            CMC = 0;

            fgets(placeholder, 100, *dataloger);
            int nasobok = 1;
            for (int a = 3; a >= 0; a--)
            {

                CMC += ((int)placeholder[a] - 48) * nasobok;
                nasobok *= 10;
            }
            (*CM)[b] = CMC;

            fscanf(*dataloger, "%lld\n", &((*D)[b]));

            b++;
        }
    }
    else
    {
        printf("Neotvoreny subor.\n");
    }
    fseek(*dataloger, 0, SEEK_SET);
}
void c(FILE **dataloger, char **pomenovania)
{
    if (*dataloger != NULL)
    { // Skontrolujeme či bol súbor otvorený
        int i = -1, correct = 1, sukorektne = 1, riadok = 0;
        char line[100];
        while (fgets(line, 100, *dataloger) != NULL) // Pre každý riadok
        {
            riadok++;
            i++;
            i = i % 7;
            switch (i)
            {
            case 0:
                if (line[10] == 10 || line[10] == 13) //Či má 10 čísel
                {
                    long long int ID = 0, nasobok = 1;
                    for (int b = 9; b >= 0; b--)
                    {
                        if (line[b] - 48 <= 9 && line[b] - 48 >= 0) //Či každý ascii character je číslo
                        {
                            ID += (line[b] - 48) * nasobok; // Z ascii čísla odčítame 48 čím dostaneme číslo ktoré to ascii reprezentuje, vynasobíme ho b tou mocninou 10 a pripočítame
                            nasobok *= 10;
                        }
                        else
                        { // Inak je vstup nesprávny a correct = 0
                            correct = 0;
                            break;
                        }
                    }
                    if (ID % 11 != 0)
                        correct = 0; // Navyše ak nie je číslo deliteľné 11 bez zvyšku sa correct = 0
                }
                else
                    correct = 0;
                if (correct == 0)
                {
                    printf("Nekorektne zadany vstup na riadku %d: %s %s", riadok, pomenovania[i], line); // Vypíše v akom riadku chyba nastala, ktorý typ dát to bol a konktrétny string v ktorom bola chyba
                    sukorektne = 0;                                                                      // Finálny check či sú všetky údaje korektné
                    correct = 1;
                }
                break;
            case 1:
                if (line[3] == 10 || line[3] == 13) //Či má 3 čísla
                {
                    if ((int)line[0] >= 65 && (int)line[0] <= 90) // Ak prvý znak je z intervalu <A;Z>
                    {
                        if ((int)line[1] >= 48 && (int)line[1] <= 57 && (int)line[2] >= 48 && (int)line[2] <= 57) // Ak druhý a tretí znak je z intervalu <0;9>
                        {
                        }
                        else
                            correct = 0;
                    }
                    else
                        correct = 0;
                }
                else
                    correct = 0;
                if (correct == 0)
                {
                    printf("Nekorektne zadany vstup na riadku %d: %s %s ", riadok, pomenovania[i], line);
                    sukorektne = 0;
                    correct = 1;
                }
                break;
            case 2:
                if (line[2] == 10 || line[2] == 13) //Či má 2 čísla
                {
                    if ((line[0] == 82 || line[0] == 65 || line[0] == 85) && (line[1] == 49 || line[1] == 50 || line[1] == 52)) //Či prvý znak je z množiny [R, U, A] a druhý znak je z množiny [1, 2, 4]
                    {
                    }
                    else
                        correct = 0;
                }
                else
                    correct = 0;
                if (correct == 0)
                {
                    printf("Nekorektne zadany vstup na riadku %d: %s %s ", riadok, pomenovania[i], line);
                    sukorektne = 0;
                    correct = 1;
                }
                break;
            case 4:
                if (line[4] == 10 || line[4] == 13)
                {
                    if (((line[0] == 48 || line[0] == 49) && (line[1] >= 48 && line[1] <= 57) || (line[0] == 50 && line[1] <= 52 && line[1] >= 48)) && line[2] >= 48 && line[2] <= 53 && line[3] >= 48 && line[3] <= 57) // Ak je prvý znak 0 alebo 1 tak druhý znak môže byť z intervalu <0;9> inak ak je prvý 2 tak druhý musí byť z intervalu <0,3>, tretí znak musí byť z intervalu <0;5> a štvrtý z intervalu <0;9>
                    {
                    }
                    else
                        correct = 0;
                }
                else
                    correct = 0;
                if (correct == 0)
                {
                    printf("Nekorektne zadany vstup na riadku %d: %s %s ", riadok, pomenovania[i], line);
                    sukorektne = 0;
                    correct = 1;
                }
                break;
            case 5:
                if (line[8] == 10 || line[8] == 13) //Či má 8 čísel
                {
                    int rok = 0, mesiac = 0, den = 0, mocnina = 1;
                    for (int i = 3; i >= 0; i--) // Načíta rok
                    {
                        rok += (line[i] - 48) * mocnina;
                        mocnina *= 10;
                    }
                    mocnina = 1;
                    for (int i = 5; i >= 4; i--) // Načíta mesiac
                    {
                        mesiac += (line[i] - 48) * mocnina;
                        mocnina *= 10;
                    }
                    mocnina = 1;
                    for (int i = 7; i >= 6; i--) // Načíta deň
                    {
                        den += (line[i] - 48) * mocnina;
                        mocnina *= 10;
                    }

                    if (mesiac == 1 || mesiac == 3 || mesiac == 5 || mesiac == 7 || mesiac == 8 || mesiac == 10 || mesiac == 12) // Pre tieto mesiace musí mať <1;31> dní
                    {
                        if (den <= 31 && den >= 1)
                        {
                        }
                        else
                            correct = 0;
                    }
                    else if (mesiac == 4 || mesiac == 6 || mesiac == 9 || mesiac == 11) // Pre tieto mesiace musí mať <1;30> dní
                    {
                        if (den <= 30 && den >= 1)
                        {
                        }
                        else
                            correct = 0;
                    }
                    else if (mesiac == 2) // Pre tento mesiace musí mať <1;29> dní, a ak je prestupný rok 28
                    {
                        if (den <= 28 && den >= 1 || den <= 29 && den >= 1 && (rok % 4 != 0))
                        {
                        }
                        else
                            correct = 0;
                    }
                    else
                        correct = 0;
                }
                else
                    correct = 0;
                if (correct == 0)
                {
                    printf("Nekorektne zadany vstup na riadku %d: %s %s ", riadok, pomenovania[i], line);
                    sukorektne = 0;
                    correct = 1;
                }
                break;
            }
        }
        if (sukorektne == 1) //
        {
            printf("Data su korektne\n");
        }
    }
    fseek(*dataloger, 0, SEEK_SET);
}
void s(FILE **dataloger, char **MM, char **TMV, double *H, int *CM, long long int *D, int howmany)
{
    if (howmany != 0)
    {
        char pozadovany_mer_modul[4], pozadovana_mer_velicina[3], nacitany_string_1[100];
        int b = 10, j = 0;
        double *hodnoty = calloc(b, sizeof(double));
        long long int *date = calloc(b, sizeof(long long int));
        scanf("%s %s", pozadovany_mer_modul, pozadovana_mer_velicina);
        for (int i = 0; i < (int)(howmany / 7); i++)
        {
            if (TMV[i][0] == pozadovana_mer_velicina[0] && TMV[i][1] == pozadovana_mer_velicina[1] && MM[i][0] == pozadovany_mer_modul[0] && MM[i][1] == pozadovany_mer_modul[1] && MM[i][2] == pozadovany_mer_modul[2]) // Ak sa prvé 3 písmená riadku rovnajú s načítaným Mer modulom a ak sa prvé 2 písmená riadku rovnajú s načítanou Mer veličinou
            {
                if (j + 1 == b)
                {
                    b *= 2;
                    date = realloc(date, b * sizeof(long long int));
                    hodnoty = realloc(hodnoty, b * sizeof(double));
                }
                date[j] = D[i] * 10000 + CM[i];
                hodnoty[j] = H[i];
                j++;
            }
        }
        for (int a = 0; a < j; a++) // Buble sort ↓
        {
            for (int k = 0; k < j - a - 1; k++)
            {
                if (date[k] > date[k + 1])
                {
                    double temp;
                    long long int tempa;
                    tempa = date[k];
                    date[k] = date[k + 1];
                    date[k + 1] = tempa;

                    temp = hodnoty[k];
                    hodnoty[k] = hodnoty[k + 1];
                    hodnoty[k + 1] = temp;
                }
            }
        }
        for (int i = 0; i < j; i++)
        {
            printf("%lld    %lf\n", date[i], hodnoty[i]);
        }
    }
}
void h(FILE **dataloger, char **TMV, double *H, int howmany)
{
    if (howmany != 0)
    {
        int b = 10, j = 0;
        double **correcth = calloc(b, sizeof(double *)); // 2D pole, ktorého každý element bude pole, ktorého prvé číslo bude vrchné číslo intervalu a druhé bude počet hodnôt v danom intervale
        char chosen[3];
        scanf("%s", chosen); // Načíta typ mernej veličiny

        for (int i = 0; i < (int)(howmany / 7); i++) // Prejde všetky elemenry z TMV
        {
            if (TMV[i][0] == chosen[0] && TMV[i][1] == chosen[1]) // Ak nájde zhodu
            {

                if (j + 1 == b)
                {
                    b *= 2;
                    correcth = realloc(correcth, b);
                }
                int added = 0;

                for (int k = 0; k < j; k++) // Pre každý 2D element pola correcth prejde jeho prvú hodnotu
                {
                    if (correcth[k][0] == ((int)H[i] - (int)H[i] % 5 + 5)) // ak od hodnoty odčítame modulo 5 aktuálnej hodnoty a pričítame 5 dostaneme vrchnú hranicu intervalu v ktorom sa nachádza.
                    {
                        correcth[k][1] += 1; // ak tento interval už máme, pripočítame 1 k druhému elementu
                        added = 1;
                        break;
                    }
                }
                if (!added)
                {
                    correcth[j] = (double *)calloc(2, sizeof(double)); // ak sme interval nenašli
                    correcth[j][1] = 1;                                // vytvoríme nový

                    correcth[j][0] = (int)H[i] - (int)H[i] % 5 + 5;
                    j++;
                }
            }
        }

        for (int a = 0; a < j; a++) // bubble sort ↓
        {
            for (int k = 0; k < j - a - 1; k++)
            {
                if (correcth[k][0] > correcth[k + 1][0])
                {
                    double *temp;
                    temp = correcth[k];
                    correcth[k] = correcth[k + 1];
                    correcth[k + 1] = temp;
                }
            }
        }
        printf("      %s      pocetnost\n", chosen);
        for (int i = 0; i < j; i++)
        {
            printf("(%.1lf-%.1lf>  %.0lf\n", correcth[i][0] - 5, correcth[i][0], correcth[i][1]);
        }
    }
}
void r(FILE **dataloger, int *CM, int howmany)
{
    
    for (int i = 0; i < (howmany) / 7; i++) // bubble sort ↓
    {
        for (int j = 0; j < (howmany) / 7 - i - 1; j++)
        {
            if (CM[j] > CM[j + 1])
            {
                int temp;
                temp = CM[j];

                CM[j] = CM[j + 1];
                CM[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < (howmany / 7); i++)
    {
        int hour = (int)(CM[i] / 100);
        if ((int)(CM[i] / 100) != (int)(CM[i - 1] / 100)) // Ak asa hodiny nerovnaju vypíśe novú hodinu
        {
            if (hour < 10)
            {
                if (CM[i] % 100 < 10)
                {
                    printf("0%d:0%d", hour, CM[i] % 100);
                }
                else
                    printf("0%d:%d", hour, CM[i] % 100);
            }
            else if (CM[i] % 100 < 10)
            {
                printf("%d:0%d", hour, CM[i] % 100);
            }
            else
                printf("%d:%d", hour, CM[i] % 100);
        }
        else if (CM[i] % 100 != CM[i - 1] % 100)
        { // Ak sa hodiny rovnajú a predchádzajúca minúta sa nerovnaja s aktúalnou vypíše minútu
            if (CM[i] % 100 < 10)
            {
                printf(",0%d", CM[i] % 100);
            }
            else
                printf(",%d", CM[i] % 100);
        }
        if ((int)(CM[i] / 100) != (int)(CM[i + 1] / 100)) // Po každej hodine vypíše nový riadok
        {
            printf("\n");
        }
    }
}
void z(FILE **dataloger, long long int **ID, char ***MM, char ***TMV, double **H, int **CM, long long int **D, int *howmany)
{
    if (*howmany != 0)
    {
        long long int vybraneid;
        int pocetid = 0;
        scanf("%lld", &vybraneid);
        printf("%lld cislo\n", vybraneid);
        for (int i = 0; i < 57; i++)
        {
            if ((*ID)[i] == vybraneid) // Ak nájdeme ID ktoré sa rovná inputu vymažeme ho a všetky záznamy na jeho mieste
            {
               
                for (int j = i; j < ((*howmany) / 7) - 1; j++) // Posúvame všetky elementy po ID ktoré sme našli o jedno doľava
                {
                    (*ID)[j] = (*ID)[j + 1];
                    (*H)[j] = (*H)[j + 1];
                    (*CM)[j] = (*CM)[j + 1];
                    (*D)[j] = (*D)[j + 1];
                    (*MM)[j] = (*MM)[j + 1];
                    (*TMV)[j] = (*TMV)[j + 1];
                }
                (*ID)[((int)((*howmany) / 7)) - 1] = 0; // Vymazávame posledný záznam ↓
                (*H)[((int)((*howmany) / 7)) - 1] = 0;
                (*CM)[((int)((*howmany) / 7)) - 1] = 0;
                (*D)[((int)((*howmany) / 7)) - 1] = 0;
                (*MM)[((int)((*howmany) / 7)) - 1] = NULL;
                (*TMV)[((int)((*howmany) / 7)) - 1] = NULL;
                *howmany -= 7;
                i--;
                pocetid++;
            }
        }
        printf("Vymazalo sa: %d zaznamov !\n", pocetid);
    }
}
void k(FILE **dataloger, long long int **ID, char ***MM, char ***TMV, double **H, int **CM, long long int **D, int howmany)
{
    if (*dataloger != NULL)
    {
        if (howmany != 0)
        {
            free(*ID); // Uvoľníme všetky polia ↓
            for (int i = 0; i < (int)((howmany) / 7); i++)
            {
                free((*MM)[i]);
                free((*TMV)[i]);
            }
            free(*H);
            free(*CM);
            free(*D);
        }
        fclose(*dataloger);
    }
}

int main()
{
    double *H = NULL;
    long long int *ID = NULL;
    long long int *D = NULL;
    int go = 1, lenpole = 0, howmany = 0;
    int *CM = NULL;
    char moznost, **MM = NULL, **TMV = NULL, *pomenovania[7];
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
            v(&dataloger, pomenovania, ID, MM, TMV, H, CM, D, howmany);
            break;
        case 'o':
            o(&dataloger);
            break;
        case 'n':
            n(&dataloger, &ID, &MM, &TMV, &H, &CM, &D, &howmany);
            break;
        case 'c':
            c(&dataloger, pomenovania);
            break;
        case 's':
            s(&dataloger, MM, TMV, H, CM, D, howmany);
            break;
        case 'h':
            h(&dataloger, TMV, H, howmany);
            break;
        case 'r':
            r(&dataloger, CM, howmany);
            break;
        case 'z':
            z(&dataloger, &ID, &MM, &TMV, &H, &CM, &D, &howmany);
            break;
        case 'k':
            k(&dataloger, &ID, &MM, &TMV, &H, &CM, &D, howmany);
            return 0;
            break;

        default:
            break;
        }
    }
}
