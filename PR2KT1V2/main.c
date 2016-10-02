#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nimi[21];
    char hobbi[10][21];         //do 10
    char linn[21];
    char tanav[21];
    int indeks;
    int H;
} person;

/*int * getIndex(person *myperson, char huvi[], int n);       //declaration

int * getIndex(person *myperson, char huvi[], int n)        //definition
{
    int j, i;
    int r[n];
    for(i = 0; i != n; i++){
        for(j = 0; j != myperson[i].H; j++){
            r[i] = 0;
            if(strcmp(myperson[i].hobbi[j], huvi) == 0){
                printf("  tut    %s\n",myperson->hobbi[1]);
                r[i] = 1;
            }
        }
    }
    return r;
    //printf("  tut    %s\n",myperson->hobbi[1]);
    //printf("  tut    %s\n",huvi);
}*/
int main()
{
    int i, j, n = 0;
    char huvi[21];
    int *p;

    person * myperson = malloc(sizeof(person));         //memory allocated using malloc
    p = (int*)malloc(sizeof(int));
    FILE *MyFile;

    MyFile = fopen("F1.txt", "r");

    printf("The program reads the data from a file F1 and writes it to a file F2\n");
    printf("Please check a F2 file after the finishing !\n\n");
    if(MyFile == NULL){
        printf("File does not exist\n");
        exit(1);
    }

    while(!feof(MyFile)){
    //4teniee failov iz F1
        fscanf(MyFile,"%s %d",myperson[n].nimi, &myperson[n].H);    // ili mowno tak (myperson+n)->nimi
        for(i = 0; i != myperson[n].H; i++ ){
            fscanf(MyFile,"%s",myperson[n].hobbi[i]);
        }
        fscanf(MyFile,"%s %s %d",myperson[n].linn, myperson[n].tanav, &myperson[n].indeks);
        n++;
        p = realloc(p, sizeof(*p)*(n+1));
        myperson = realloc(myperson, sizeof(*myperson)*(n+1));
    }
    fclose(MyFile);

    printf("Palun sisestake string Huvi -> ");
    scanf("%s",huvi);
    printf("\n");

    for(i = 0; i != n; i++){
        for(j = 0; j != myperson[i].H; j++){
            if(strcmp(myperson[i].hobbi[j], huvi) == 0){
                *(p+i) = 1;
                break;
            }
        }
    }
    //p = getIndex(myperson,huvi,n);
    //
    MyFile = fopen("F2.txt", "w");

    fprintf(MyFile,"Nimi:               Adress:               Huvialad:\n");
    for(i = 0; i != n; i++){
        if(p[i] == 1){
            fprintf(MyFile,"%s              %s, %s, %d",
            (myperson+i)->nimi, (myperson+i)->linn,
            (myperson+i)->tanav, (myperson+i)->indeks);
            for(j = 0; j != (myperson+i)->H; j++){
                if(j == 0)
                    fprintf(MyFile,"      %s\n",(myperson+i)->hobbi[j]);
                else
                    fprintf(MyFile,"                                          %s\n",(myperson+i)->hobbi[j]);
            }
            fprintf(MyFile,"\n");
        }
    }
    fclose(MyFile);
    free(myperson);           //Free memory

    return 0;
}
