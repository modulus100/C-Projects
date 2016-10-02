#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int data_processing(double eps, double X, double **ptr);

void print(int quant, double **ptr);

int main()
{
    double eps, X, *A;
    int ind;

    A=(double*)malloc(sizeof(double));
    if(A==NULL){
        printf("\nError! Memory not allocated");
        exit(0);
    }
    *A = 1;

    do{
        printf("\nVvedite epsilon 0<e<1 -> ");
        scanf("%lf", &eps);
    }while(0>eps || eps>1);

    printf("\nVvedite X -> ");
    scanf("%lf", &X);

    ind = data_processing(eps,X,&A);
    print(ind,&A);

    //free(A);                //osvobowdaem pamjat
    printf("\n\n");
    system("pause");

    return 0;
}

int data_processing(double eps, double X, double **ptr)
{
    int i=0, k=1, k2=2;

    for(i=1; i!=15; i++){
        *ptr = realloc(*ptr,i);
        *(*ptr+i) = (-1)*(double)k/k2 * X * (*(*ptr+i-1));
        k = k + 2; k2 = k2 + 2;
        if(fabs(*(*ptr+i) - *(*ptr+i-1)) <= eps){
            i=15;
        return i+1;
        }
    }
    return i+1;
}
void print(int quant, double **ptr)
{
    int i;
    printf("\n\nL = %d\n",quant);

    for(i = 0; i != quant; i++)
        printf("\nA[%d] = %lf",i+1,*(*ptr+i));
}
