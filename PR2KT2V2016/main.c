#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char name[15];
    char car[15];
    int time1;
    int time2;
    int time3;
}   Drivers;

void topV6itlejad(const Drivers * myDriver, const int elements);
void printAllData(const Drivers * myDriver, const int elements);

int main()
{
    int input, n = 0;
    int condition = 1;
    Drivers * myDriver = malloc(sizeof(Drivers));

    FILE *Autod;
    Autod = fopen("autod.txt", "r");
        if(Autod == NULL){
        printf("File does not exist\n");
        exit(1);
    }

    while(!feof(Autod))
    {
        fscanf(Autod,"%s %s %d %d %d",
               (myDriver+n)->name, (myDriver+n)->car,
               &myDriver[n].time1, &myDriver[n].time2, &myDriver[n].time3);
        n++;
        myDriver = realloc(myDriver, sizeof(*myDriver)*(n+1));
    }
    while (condition == 1)
    {
        printf("\n=================================================================");
        printf("\nSelect an action from the list\n\n");
        printf("   1 - Top 3 v6itlejat\n");
        printf("   2 - Rally table\n");
        //printf("   3 - Add the data by the random number generator\n");
        //printf("   4 - Read the data from \n");
        printf("   3 - Exit\n\n");
        printf("Choose an action -> ");
        scanf("%d", &input);
        /*do
        {
            printf("Choose an action -> ");
            scanf("%d", &input);

        } while (input < 1 && input > 5);*/

        switch (input)
        {
            case 1:
                topV6itlejad(myDriver, n);
                break;
            case 2:
                printAllData(myDriver, n);
                break;
            /*case 3:
                break;
            case 4:
                break;*/
            case 3:
                condition = 0;
                break;
            default:
                printf("\nError, bad input, try again\n");
                break;
        }
    }

    fclose(Autod);
    free(myDriver);

    return 0;
}

void topV6itlejad(const Drivers * myDriver, const int elements)
{
    const int bigValue = 9999; //Additional time if time has NULL
    int i, totalTime;
    int bestTime = bigValue;
    int bufNr[3] = {0, 0, 0};

    //first rider
    for(i = 0; i != elements; i++) {
        totalTime = (myDriver+i)->time1 + (myDriver+i)->time2 + (myDriver+i)->time1;
        if ((myDriver+i)->time1 == 0 || (myDriver+i)->time2 == 0 || (myDriver+i)->time3 == 0)
            totalTime = totalTime + bigValue;
        if (totalTime < bestTime) {
            bestTime = totalTime;
            bufNr[0] = i;
        }
    }
    i = 0;
    bestTime = bigValue;
    //second rider
    do{
        totalTime = (myDriver+i)->time1 + (myDriver+i)->time2 + (myDriver+i)->time1;
        if ((myDriver+i)->time1 == 0 || (myDriver+i)->time2 == 0 || (myDriver+i)->time3 == 0)
            totalTime = totalTime + bigValue;
        if (totalTime < bestTime) {
            bestTime = totalTime;
            bufNr[1] = i;
        }
        i++;
        if (i == bufNr[0])
            i++;
    } while (i != elements);

    i = 0;
    bestTime = bigValue;
    //thirt rider
    do{
        totalTime = (myDriver+i)->time1 + (myDriver+i)->time2 + (myDriver+i)->time1;
        if ((myDriver+i)->time1 == 0 || (myDriver+i)->time2 == 0 || (myDriver+i)->time3 == 0)
            totalTime = totalTime + bigValue;
        if (totalTime < bestTime) {
            bestTime = totalTime;
            bufNr[2] = i;
        }
        i++;
        if (i == bufNr[0])
            i++;
        if (i == bufNr[1])
            i++;
    } while (i != elements);

    //best riders
    printf("\n\nTot 3 racers are\n");
    printf("%s\n", (myDriver + bufNr[0])->name);
    printf("%s\n", (myDriver + bufNr[1])->name);
    printf("%s\n", (myDriver + bufNr[2])->name);

}

void printAllData(const Drivers * myDriver, const int elements)
{
    int i;

    printf("\n\nName    Auto    etap1    etap2   etap3\n");
    for (i = 0; i != elements; i++) {
    printf("%s  %s  %d  %d  %d\n", (myDriver+i)->name,
           (myDriver+i)->car, (myDriver+i)->time1, (myDriver+i)->time2, (myDriver+i)->time3);
    }
}
