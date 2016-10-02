#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//===========================
// Structures
struct Raamatud
{
    char kood[10];
    char pealkiri[27];
    char author[21];
    char aasta[5];
    char omahind[4];
    char muugihind[4];
};

struct Inventar
{
    char id[3];
    char raamatuKood[10];
    int riiuliKood;
    int kogus;
};

//==========================================================================
// Functions
int readFromFile(struct Raamatud **myRaamatud, const char MyFile1[],
                 struct Inventar **myInventar, const char MyFile2[]);
void printMenu();
void printMenu2();

void printData(struct Raamatud **myRaamatud, struct Inventar **myInventar,
               const int elements);
void searchByYear(struct Raamatud **myRaamatud, struct Inventar **myInventar,
                  const int elements);
void sortData(struct Raamatud **myRaamatud, struct Inventar **myInventar,
              int elements, int startPoint);
//===========================================================================

int main()
{
    //=======================================
    // Variables
    int quantity;
    int choice;
    char local;
    bool condition = true;
    //=======================================
    // Pointers
    struct Raamatud *myRaamatud;
    struct Inventar *myInventar;
    //=======================================
    // Allocate memory
    myRaamatud = malloc(sizeof(*myRaamatud));
    myInventar = malloc(sizeof(*myInventar));
    //===================================================
    // Reads books from files
    quantity = readFromFile(&myRaamatud, "Raamatud.txt",
                            &myInventar, "Inventar.txt");
    //=================================================================
    // Menu
    while (condition)
    {
        printMenu();
        printf("Valige tegevus -> ");
        //=============================================================
        // Check an input
        do {
            local = getchar ();
            if ((isdigit (local) == false) && (local != '\n')) {
                printMenu();
                printf("\nOli vale sisend\nValige tegevus uuesti -> ");
            }
        } while (isdigit ((unsigned char) local) == false);
        choice = (int)local - '0';
        //==============================================================
        // Choice
        switch (choice)
        {
            case 1:
                printData(&myRaamatud, &myInventar, quantity);
                break;
            case 2:
                searchByYear(&myRaamatud, &myInventar, quantity);
                break;
            case 3:
                //===============================================
                // 0, 1, 2, 3 Parameters
                sortData(&myRaamatud, &myInventar, quantity, 0);
                sortData(&myRaamatud, &myInventar, quantity, 1);
                sortData(&myRaamatud, &myInventar, quantity, 2);
                sortData(&myRaamatud, &myInventar, quantity, 3);
                break;
            case 4:
                condition = false;
                printf("\nThank you for attention!\n");
                break;
            default:
                printf("\nOli vale sisend\n");
                break;
        }
    }
    //=========================
    // Free memory (Destructor)
    free(myRaamatud);
    free(myInventar);

    return 0;
}

//===================================================================
int readFromFile(struct Raamatud **myRaamatud, const char MyFile1[],
                 struct Inventar **myInventar, const char MyFile2[])
{
    int n = 0;
    FILE *MyFilePtr1, *MyFilePtr2;
    //====================================
    //First file
    MyFilePtr1 = fopen(MyFile1, "r");

    if (MyFilePtr1 == NULL)
    {
        printf("File does not exist\n");
        exit(1);
    }
    while (!feof(MyFilePtr1))
    {
        *myRaamatud = realloc(*myRaamatud, sizeof(**myRaamatud)*(n+1));
        //==================================================================================
        fscanf(MyFilePtr1,"%s %s %s %s %s %s",
               (*myRaamatud)[n].kood, (*myRaamatud)[n].pealkiri, (*myRaamatud)[n].author,
               (*myRaamatud)[n].aasta, (*myRaamatud)[n].omahind, (*myRaamatud)[n].muugihind);
        n++;
    }
    fclose(MyFilePtr1);
    n = 0;
    //===================================
    //Second file
    MyFilePtr2 = fopen(MyFile2, "r");

    if (MyFilePtr2 == NULL)
    {
        printf("File does not exist\n");
        exit(1);
    }

    while (!feof(MyFilePtr2))
    {
        *myInventar = realloc(*myInventar, sizeof(**myInventar)*(n+1));
        //==================================================================================
        fscanf(MyFilePtr2,"%s %s %d %d",
               (*myInventar)[n].id, (*myInventar)[n].raamatuKood,
               &(*myInventar)[n].riiuliKood, &(*myInventar)[n].kogus);
        n++;
    }
    fclose(MyFilePtr2);

    return n-1;
}

//=============================================================================
void printMenu()
{
        printf("\n========================================================\n");
        printf("   1 - Kuva ekranil raamatute nimekiri ja inventari info\n");
        printf("   2 - Otsi raamatut aasta jargi\n");
        printf("   3 - Sorteeri riiulid\n");
        printf("   4 - Exit\n\n");
}

//=============================================================================
void printMenu2()
{
        printf("\n========================================================\n");
        printf("Valida raamat aastaarvu jargi\n\n");
        printf("   1 - Varasem\n");
        printf("   2 - Hilisem\n");
        printf("   3 - Ajavahemikus\n");
        printf("   4 - Kuva pealkiri/aasta (K6oik raamatud)\n");
        printf("   5 - Exit\n\n");
}

//=========================================================================
void printData(struct Raamatud **myRaamatud, struct Inventar **myInventar,
               const int elements)
{
    int n, i;
    unsigned int maxLength = 0;
    const unsigned int SHIFT = 5;
    //==============================================================================
    // Searches maxLength of the string
    for (n = 0; n != elements; n++) {
        if (strlen((*myRaamatud)[n].pealkiri) > maxLength)
            maxLength = strlen((*myRaamatud)[n].pealkiri);
    }
    //==============================================================================
    // Prints the data
    printf("\n===================================================================");
    printf("\nPealkiri\t\t      ID     Kood\t     Riiul    Kogus\n\n");

    for (n = 0; n != elements; n++) {
        printf("%s", (*myRaamatud)[n].pealkiri);
        //============================================================================
        // Aligns the string
        for (i = 0; i != (maxLength - strlen((*myRaamatud)[n].pealkiri)) + SHIFT; i++)
            printf(" ");
        printf("%s     %s       %d        %d\n",
            (*myInventar)[n].id, (*myInventar)[n].raamatuKood,
            (*myInventar)[n].riiuliKood, (*myInventar)[n].kogus);
    }
    printf("\n===================================================================");
}

//===================================================================================
void searchByYear(struct Raamatud **myRaamatud, struct Inventar **myInventar,
               const int elements)
{
    bool condition = true;
    char local, year1[5], year2[5];
    int input, n, i;
    unsigned int maxLength = 0;
    const unsigned int SHIFT = 5;

    //==============================================================================
    // Searches maxLength of the string
    for (n = 0; n != elements; n++) {
        if (strlen((*myRaamatud)[n].pealkiri) > maxLength)
            maxLength = strlen((*myRaamatud)[n].pealkiri);
    }
    //=================================================================
    // Menu
    while (condition)
    {
        printMenu2();
        printf("Valige tegevus -> ");
        //=============================================================
        // Check an input
        do {
            local = getchar ();
            if ((isdigit (local) == false) && (local != '\n')) {
                printMenu2();
                printf("\nOli vale sisend\nValige tegevus uuesti -> ");
            }
        } while (isdigit ((unsigned char) local) == false);
        input = (int)local - '0';
        //==============================================================
        // Choice
        switch (input)
        {
            case 1:
                //==================================================
                printf("\nA year must contain 4 digits -> 2016\n");
                do {
                printf("\nSisestage aasta -> ");
                scanf("%s",year1);
                } while (strlen(year1) != 4);
                //=================================================
                // Prints the data
                printf("\n===============================================");
                printf("\nPealkiri\t\t      Aasta       Kogus\n\n");
                for (n = 0; n != elements; n++) {
                    if (atoi((*myRaamatud)[n].aasta) <= atoi(year1))
                    {
                        printf("%s", (*myRaamatud)[n].pealkiri);
                        //============================================================================
                        // Aligns the string
                        for (i = 0; i != (maxLength - strlen((*myRaamatud)[n].pealkiri)) + SHIFT; i++)
                            printf(" ");
                        printf("%s        %d\n", (*myRaamatud)[n].aasta, (*myInventar)[n].kogus);
                    }
                }
                printf("\n===============================================");
                break;

            case 2:
            //====================================================
                printf("\nA year must contain 4 digits -> 2016\n");
                do {
                printf("\nSisestage aasta -> ");
                scanf("%s",year1);
                } while (strlen(year1) != 4);
                //=================================================
                // Prints the data
                printf("\n===============================================");
                printf("\nPealkiri\t\t      Aasta       Kogus\n\n");
                for (n = 0; n != elements; n++) {
                    if (atoi((*myRaamatud)[n].aasta) >= atoi(year1))
                    {
                        printf("%s", (*myRaamatud)[n].pealkiri);
                        //============================================================================
                        // Aligns the string
                        for (i = 0; i != (maxLength - strlen((*myRaamatud)[n].pealkiri)) + SHIFT; i++)
                            printf(" ");
                        printf("%s        %d\n", (*myRaamatud)[n].aasta, (*myInventar)[n].kogus);
                    }
                }
                printf("\n===============================================");
                break;

            case 3:
            //====================================================
                // Esimene aasta
                printf("\nA year must contain 4 digits -> 2016\n");
                printf("\n===============================================");
                printf("\nINFO!!!\nEsimene ajavahemik peab olema suurem kui teine\n");
                printf("\nNaidis\nEsimene aasta -> 2016\nTeine aasta -> 1999\n");
                do {
                printf("\nSisestage esimene ajavahemik -> ");
                scanf("%s",year1);
                } while (strlen(year1) != 4);
                //=================================================
                // Teine aasta
                do {
                printf("\nSisestage teine ajavahemik -> ");
                scanf("%s",year2);
                } while (strlen(year2) != 4);
                //=================================================
                // Prints the data
                printf("\n===============================================");
                printf("\nPealkiri\t\t      Aasta       Kogus\n\n");
                for (n = 0; n != elements; n++) {
                    if (atoi((*myRaamatud)[n].aasta) <= atoi(year1) &&
                        atoi((*myRaamatud)[n].aasta) >= atoi(year2))
                    {
                        printf("%s", (*myRaamatud)[n].pealkiri);
                        //============================================================================
                        // Aligns the string
                        for (i = 0; i != (maxLength - strlen((*myRaamatud)[n].pealkiri)) + SHIFT; i++)
                            printf(" ");
                        printf("%s        %d\n", (*myRaamatud)[n].aasta, (*myInventar)[n].kogus);
                    }
                }
                printf("\n===============================================");
                break;

            case 4:
                //=================================================
                // Prints the data
                printf("\n===============================================");
                printf("\nPealkiri\t\t      Aasta       Kogus\n\n");
                for (n = 0; n != elements; n++)
                {
                    printf("%s", (*myRaamatud)[n].pealkiri);
                    //============================================================================
                    // Aligns the string
                    for (i = 0; i != (maxLength - strlen((*myRaamatud)[n].pealkiri)) + SHIFT; i++)
                        printf(" ");
                    printf("%s        %d\n", (*myRaamatud)[n].aasta, (*myInventar)[n].kogus);
                }
                printf("\n===============================================");

                break;
            case 5:
                condition = false;
                break;
            default:
                printf("\nOli vale sisend\n");
                break;
        }
    }
}

void sortData(struct Raamatud **myRaamatud, struct Inventar **myInventar,
              int elements, int startPoint)
{
    //====================================================
    //This book store has 4 riiulid, that is why 4 is used
    const unsigned int SHIFT = 4;
    int i, n, iTemp;
    char cTemp1[27], cTemp2[3], cTemp3[10];
    //====================================================
    //Explosion brain
    for (n = startPoint; n < elements; n = n + SHIFT) {
        for (i = startPoint; i < elements - SHIFT; i = i + SHIFT){
            if ((*myInventar)[i].kogus > (*myInventar)[i + SHIFT].kogus) {
                iTemp = (*myInventar)[i + SHIFT].kogus;
                strcpy(cTemp1, (*myRaamatud)[i + SHIFT].pealkiri);
                strcpy(cTemp2, (*myInventar)[i + SHIFT].id);
                strcpy(cTemp3, (*myInventar)[i + SHIFT].raamatuKood);

                (*myInventar)[i + SHIFT].kogus = (*myInventar)[i].kogus;
                strcpy((*myRaamatud)[i + SHIFT].pealkiri, (*myRaamatud)[i].pealkiri);
                strcpy((*myInventar)[i + SHIFT].id, (*myInventar)[i].id);
                strcpy((*myInventar)[i + SHIFT].raamatuKood, (*myInventar)[i].raamatuKood);

                (*myInventar)[i].kogus = iTemp;
                strcpy((*myRaamatud)[i].pealkiri, cTemp1);
                strcpy((*myInventar)[i].id, cTemp2);
                strcpy((*myInventar)[i].raamatuKood, cTemp3);
            }
        }
    }
}//printf("\n%s    debug", (*myInventar)[n].id);
