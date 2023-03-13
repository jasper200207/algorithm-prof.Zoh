#include<stdio.h>
#include<cmath>
using namespace std;

unsigned long long int sigmak(unsigned int n) {
    return (unsigned long long int)n*(n+1)/2;
}

unsigned long long int sigmak2(unsigned int n) {
    return (unsigned long long int)n*(n+1)*(2*n+1)/6;
}

int main() {
    unsigned int N, inp, min=12000, max=0;
    unsigned long long int sumV=0, sum2V=0;
    scanf("%d",&N);
    for(int i=0;i<N+2;i++) {
        scanf("%d",&inp);
        sumV += inp;
        sum2V += inp*inp;
        min = min < inp ? min : inp;
        max = max > inp ? max : inp;
    }
    sumV -= sigmak(max) - sigmak(min-1);
    sum2V -= sigmak2(max) - sigmak2(min-1);
    for(int i=min; i<=max;i++) {
        int j = sumV - i;
        if(i*i + j*j == sum2V) {
            printf("%d\n%d",i,j);
            break;
        }
    }
    return 0;
}