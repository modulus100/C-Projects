#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int data_processing(double eps, double X, double A[]);
void print(double A[], int L);

int main()
{
    double eps, X;
    int L;

    do{
        printf("\nVvedite epsilon 0<e<1 -> ");
        scanf("%lf", &eps);
    }while(0>eps || eps>1);

    printf("\nVvedite X -> ");
    scanf("%lf", &X);

    double A[15];

    A[0] = 1;

    L = data_processing(eps,X,A);
    print(A, L);

    return 0;
}

int data_processing(double eps, double X, double A[])
{
    int i=1, k=1, k2=2;

    for(i=1; i!=16; i++){
        A[i] = (-1)*(double)k/k2 * X * A[i-1];
        if(fabs(A[i] - A[i-1]) <= eps){
            return i+1;
        }
        k = k + 2; k2 = k2 + 2;
    }
    return i-1;
}
void print(double A[], int L)
{
    int i=0;

    printf("\n\nL= %d",L);
    do{
        printf("\nA[%d] = %lf",i+1, A[i]);
        i++;
    }while(i != L);
}
