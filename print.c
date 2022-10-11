#include<stdio.h>
int main(){
    char str[50];
    scanf("%s", str);
    for(int i = 0; i < 24; i++) {
    printf("%d ", str[i]);
    }
    printf("\n");
}