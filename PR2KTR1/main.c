#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct kauplus{
    float hind;
    int suurus[3];
    char kaup[10];
}kaup[10];

void sort(struct kauplus kaup[], int count);
void print(struct kauplus kaup[], int count);

void sort(struct kauplus kaup[], int count)
{
    int i = 0, j;
    int tmp, dim[3];
    char goods[10];
    float price, volume[count];

    //Volume for a each kaup
    for(i = 0; i != count; i++){
        volume[i] = (float)(kaup[i].suurus[0] * kaup[i].suurus[1] * kaup[i].suurus[2]) / kaup[i].hind;    //i tak mowno
        //volume[i] = kaup[i].suurus[0] * kaup[i].suurus[1] * kaup[i].suurus[2];
        //("volume = %f\n", volume[i]);
    }

    for(i = 0; i < count - 1; i++) {
       for(j = 0; j < count - i - 1; j++) {
           if(volume[j] > volume[j+1]) {
                tmp = volume[j];
                strcpy(goods, kaup[j].kaup);
                dim[0] = kaup[j].suurus[0];
                dim[1] = kaup[j].suurus[1];
                dim[2] = kaup[j].suurus[2];
                price = kaup[j].hind;

                volume[j] = volume[j+1];
                strcpy(kaup[j].kaup, kaup[j+1].kaup);
                kaup[j].suurus[0] = kaup[j+1].suurus[0];
                kaup[j].suurus[1] = kaup[j+1].suurus[1];
                kaup[j].suurus[2] = kaup[j+1].suurus[2];
                kaup[j].hind = kaup[j+1].hind;

                volume[j+1] = tmp;
                strcpy(kaup[j+1].kaup, goods);
                kaup[j+1].suurus[0] = dim[0];
                kaup[j+1].suurus[1] = dim[1];
                kaup[j+1].suurus[2] = dim[2];
                kaup[j+1].hind = price;
           }
        }
    }
}
void print(struct kauplus kaup[], int max)
{
    int i = 0;

    printf("Maksimalnaja cena objoma\n");
    printf("Kaup          Suurus          Hind\n");
    printf("%s         %d %d %d           %f",kaup[max-1].kaup,
           kaup[max-1].suurus[0], kaup[max-1].suurus[1], kaup[max-1].suurus[2],
           kaup[max-1].hind);
    printf("\n\nMinimalnaja cena objoma\n");
    printf("Kaup          Suurus          Hind\n");
    printf("%s         %d %d %d           %f",kaup[i].kaup,
           kaup[i].suurus[0], kaup[i].suurus[1], kaup[i].suurus[2],
           kaup[i].hind);
}

int main()
{
    int i = 0, N, n = 0;

    FILE *MyFile;
    MyFile = fopen("A13.txt", "r");

    if(MyFile == NULL){
        printf("File does not exist\n");
        exit(1);
    }
    fscanf(MyFile,"%d",&N);

    while(!feof(MyFile)){
        fscanf(MyFile,"%f %d %d %d %s",&kaup[n].hind, &kaup[n].suurus[0],
               &kaup[n].suurus[1], &kaup[n].suurus[2], kaup[n].kaup);
        n++;
    }
    fclose(MyFile);

    sort(kaup,N);
    print(kaup,N);

    MyFile = fopen("BB.txt", "w");

    fprintf(MyFile,"Maksimalnaja cena objoma\n");
    fprintf(MyFile,"Kaup          Suurus          Hind\n");
    fprintf(MyFile,"%s         %d %d %d           %f",kaup[N-1].kaup,
           kaup[N-1].suurus[0], kaup[N-1].suurus[1], kaup[N-1].suurus[2],kaup[N-1].hind);
    fprintf(MyFile,"\n\nMinimalnaja cena objoma\n");
    fprintf(MyFile,"Kaup          Suurus          Hind\n");
    fprintf(MyFile,"%s         %d %d %d           %f",kaup[i].kaup,
           kaup[i].suurus[0], kaup[i].suurus[1], kaup[i].suurus[2], kaup[i].hind);
    fclose(MyFile);

    return 0;
}
