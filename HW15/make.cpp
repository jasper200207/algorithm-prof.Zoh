#include<stdio.h>

int main() {
    printf("325\n");
    for(int i=0;i<26;i++) {
        for(int j=i+1;j<26;j++) {
            printf("%c %c 1\n",i+'a',j+'a');
        }
    }
}