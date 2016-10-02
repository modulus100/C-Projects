#include <stdio.h>
#include <stdlib.h>
#include <math.h>       //4toby najti modul 4isla

void matrix(int N, int M);

void print(int N, int M, int BUFF[][M], double avr[]);

int main()
{
    int N, M;

    do{
        printf("\nVvedite 4islo stolbcov 1<=X<=10 -> ");
        scanf("%d", &M);
    }while(1>M || M>10);

    do{
        printf("\nVvedite 4islo strok    1<=X<=10 -> ");
        scanf("%d", &N);
    }while(1>N || N>10);

    matrix(N,M);

    return 0;
}

void matrix(int N, int M)
{
    int A[N][M], BUFF[N][M];            //BUFF hravit elementy s minimalnym otkloneniem or srednego
    int i, j, index, sum = 0;
    double avr[N];
    double dmin, delta;

    for(i = 0; i != N; i++ ){
        for(j = 0; j != M; j++){
            printf("\nVvedite element matricy A[%d][%d] = ", i, j);
            scanf("%d", &A[i][j]);
            sum = sum + A[i][j];
        }
        avr[i] = (double)sum/M;            //perevodim iz int v double
        sum = 0;
        dmin = fabs(avr[i] - A[i][j-1]);
        index = M;
        do{
            delta = avr[i] - A[i][j-1];
            if(fabs(delta) < dmin){
                dmin = fabs(delta);
                BUFF[i][j-1] = A[i][j-1];
                if(index > j-1){
                    BUFF[i][index] = 0;
                }
                index = j-1;
            }
            else{
                BUFF[i][j-1] = 0;
            }
            j--;
        }while(j != -1);                //-1 4toby  wet4ik j wital ot M do 0, kogda j stanovica j = -1 cikl do while perestajot rabotat
    }
    print(N, M, BUFF, avr);
}

void print(int N, int M, int BUFF[][M], double avr[])
{
    int i, j;

    for (i = 0; i != N; i++){
        for (j = 0; j != M; j++){
            if(BUFF[i][j] != 0){
                printf("\nStroka nr %d, srednee zna4enie stroki = %.3f ", i, avr[i]);
                printf("\nMinimalno otli4aeca ot srednege A[%d][%d] = %d ", i, j, BUFF[i][j]);
                printf("\n\n");
            }
        }
    }
}
