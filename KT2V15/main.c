/*The stepen function was developed because of a function pow from  the math library
From a math function, I received incorrect results during a computing by unknown reasons
Example, what I received when cnt = 2   bit = pow(10,cnt) = 99. Through my function "stepen", I avoided this problem*/

#include <stdio.h>
#include <stdlib.h>

int converting(int N, int P);
int stepen(int n);
void print(int A[], int lim, int N, int P);

int main()
{
    int N, M, P, i;

    printf("Vedite N -> ");
    scanf("%d", &N);

    printf("\nVedite M -> ");
    scanf("%d", &M);
    do{
        printf("\nVedite P<10 -> ");
        scanf("%d", &P);
    }while(P>9 || P < 2);

    int A[M];   //hranim polu4ennye 4isla

    for(i=0; i != M; i++){
        A[i] = converting(N+i,P);
    }
    print(A,M,N,P);
    getchar();
    return 0;
}
int converting(int N, int P)
{
    int b, sum = 0, bit, cnt = 0, sw = 0;

    do{
        b = N%P;
        N = N/P;
        if(N == 0) sw++;
        if(b != 0){
            bit = stepen(cnt);
            sum = sum + b*bit;
            printf("\nsum = %d",sum);
        }
        cnt++;
    }while(N != 0 || sw != 1);
    return sum;
}
int stepen(int n) {
    int x = 10, sum = 1;
    if(n == 0) return sum;
    do{
        sum = sum*x;
        n--;
    }while(n != 0);
    return sum;
 }
void print(int A[], int lim, int N, int P)
{
    int i=0;

    printf("\n\nDecimal(N+i)          scale of notation P(%d) based",P);
    do{
        printf("\n%d                     %d",N+i,A[i]);
    i++;
    }while(i != lim);
}
