#include <stdio.h>
#include <stdlib.h>

int main()
{
    int sum = 0, i = 0, j = 0, sw = 0;
    int min;
    int B[6];
    int A[6][8]={   {-1,2,3,4,5,6},
                    {-1,2,3,4,5,6},
                    {1,2,-3,4,5,6},
                    {1,-2,3,4,5,6},
                    {-1,-2,3,4,5,6},
                    {-1,2,3,4,-5,6},
                    {1,2,-3,4,5,6},
                    {1,-2,3,4,5,6}
                };

    do{
        if(A[i][j] >= 0 && A[i+1][j+1] >= 0){
            if(sw == 0){
                sum = (A[i][j] * A[i+1][j+1]);
                sw = 1;
            }
            else{
                sum = sum * A[i+1][j+1];
            }
        }
        i++;
        j++;
    }while(i != 5);

    printf("Proizvedenie diagonali = %d ",sum);

    i = 0;
    j = 0;

    do{
        min = A[i][j];
        do{
            if(A[i+1][j] < A[i][j]){
                min = A[i+1][j];
            }
            i++;

        }while(i != 6);
        i=0;
        B[j] = min;
    j++;
    printf("\nB[%d] = %d ",j,B[j]);
    }while(j != 5 );

    return 0;
}
