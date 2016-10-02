#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student{
    char name[20];
    int mt_nr;
    int grade[4];
    int stip;
}stud[20];

void sort(struct student stud[], int count);
void print(struct student stud[], int count);

void sort(struct student stud[],int count)
{
    int MAX = 5;
    int MAX2 = 20;  //the sum of 4 5s
    int LVL = 3;
    int i, j, sum;
    int mt, gr[4];
    char str[20];

    //sortirovka struktury
    for(i = 1; i != count; i++){
        for(j = 0; j != count - i; j++){
            if(strcmp(stud[j].name, stud[j+1].name) > 0){
                strcpy(str, stud[j].name);
                strcpy(stud[j].name, stud[j+1].name);
                strcpy(stud[j+1].name, str);

                mt = stud[j].mt_nr;
                stud[j].mt_nr = stud[j+1].mt_nr;
                stud[j+1].mt_nr = mt;

                gr[0] = stud[j].grade[0];
                gr[1] = stud[j].grade[1];
                gr[2] = stud[j].grade[2];
                gr[3] = stud[j].grade[3];

                stud[j].grade[0] = stud[j+1].grade[0];
                stud[j].grade[1] = stud[j+1].grade[1];
                stud[j].grade[2] = stud[j+1].grade[2];
                stud[j].grade[3] = stud[j+1].grade[3];

                stud[j+1].grade[0] = gr[0];
                stud[j+1].grade[1] = gr[1];
                stud[j+1].grade[2] = gr[2];
                stud[j+1].grade[3] = gr[3];

            }
        }
    }
    // prisvoenie stipendii
    for(i = 0; i != count; i++){
        sum = stud[i].grade[0] + stud[i].grade[1] + stud[i].grade[2] + stud[i].grade[3];
        if(stud[i].grade[0] == MAX && stud[i].grade[1] == MAX &&
            stud[i].grade[2] == MAX && stud[i].grade[3] == MAX)
            stud[i].stip = 100;
        else if(stud[i].grade[0] > LVL && stud[i].grade[1] > LVL &&
                stud[i].grade[2] > LVL && stud[i].grade[3] > LVL && sum < MAX2){
                stud[i].stip = 75;
        }
        else{
            stud[i].stip = 0;
        }
    }
}
void print(struct student stud[], int count)
{
    int i;

    printf("Studenty polu4ivwie 100 EURO\n");
    for(i = 0; i != count; i++){
        if(stud[i].stip == 100){
            printf("%s\n",stud[i].name);
        }
    }
    printf("\nStudenty polu4ivwie 75 EURO\n");
    for(i = 0; i != count; i++){
        if(stud[i].stip == 75){
            printf("%s\n",stud[i].name);
        }
    }
    printf("\nStudenty bez stipendii");
    for(i = 0; i != count; i++){
        if(stud[i].stip == 0){
            printf("%s\n",stud[i].name);
        }
    }
}

int main()
{
    int i, n = 0;

    FILE *MyFile;
    MyFile = fopen("F1.txt", "r");

    if(MyFile == NULL){
        printf("File does not exist\n");
        exit(1);
    }
    while(!feof(MyFile)){
        fscanf(MyFile,"%s %d %d %d %d %d",stud[n].name, &stud[n].mt_nr,
               &stud[n].grade[0], &stud[n].grade[1],
               &stud[n].grade[2], &stud[n].grade[3]);
        n++;
    }
    fclose(MyFile);

    sort(stud,n);
    print(stud,n);

    MyFile = fopen("F2.txt", "w");

    fprintf(MyFile,"Studenty polu4ivwie 100 EURO\n");
    for(i = 0; i != n; i++){
        if(stud[i].stip == 100){
            fprintf(MyFile,"%s\n",stud[i].name);
        }
    }
    fprintf(MyFile,"\nStudenty polu4ivwie 75 EURO\n");
    for(i = 0; i != n; i++){
        if(stud[i].stip == 75){
            fprintf(MyFile,"%s\n",stud[i].name);
        }
    }
    fprintf(MyFile,"\nStudenty bez stipendii");
    for(i = 0; i != n; i++){
        if(stud[i].stip == 0){
            fprintf(MyFile,"%s\n",stud[i].name);
        }
    }
    fclose(MyFile);

    return 0;
}
