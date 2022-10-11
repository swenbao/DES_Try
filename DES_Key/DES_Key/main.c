//
//  main.c
//  DES_Key
//
//  Created by 筍包 on 2022/10/8.
//

#include<stdio.h>
#include<math.h>

void printCurrentKey(unsigned *key);

int PC1[] =
{
    57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

int main(){
    char key_txt[8] = {0};
    printf("enter your key : ");
    scanf("%7s", key_txt);
    /*for(int k = 0; k < 7; k++){
        int j = 1;
        j <<= 7;
        for(int i = 0; i < 8; i++) {
            if(key_txt[k] & j){
                printf("1");
            } else { printf("0");}
            j >>= 1;
        }
        printf("\n");
    }*/
    //--------------------------------
    unsigned key[2] = {0,0};
    int standard = 7;
    for(int k = 0; k < 8; k++){
        unsigned keep = 0;
        int x = 0;
        if(k >= 4) x = 1;
        
        unsigned j = 1;
        j <<= 7;
        for(int i = 0; i < 8; i++) {
            if((i == 4 && k == 3) || (i == 0 && k == 7)){
                break;
            }
            if(i == 0 && k == 4){
                printCurrentKey(key);
                key[x] |= key_txt[3];
                key[x] <<= 1;
                printCurrentKey(key);
                standard = 3;
            }
            printf("i = %d, k = %d\n", i, k);
            if(i == standard){
                printf("x\n");
                printCurrentKey(key);
                key[x] <<= 1;
                printf("After x Shifting\n");
                printCurrentKey(key);
                standard--;
            }  // 問題出在這*/
            
            if(key_txt[k] & j){
                printf("1\n");
                printCurrentKey(key);
                key[x] |= 1;
                printf("After 1 Assigning\n");
                printCurrentKey(key);
                //printf("shift 前：%d\n", key[0]);
                if(!((i == 7 && k == 3)||(i==7&&k==7))){
                    key[x] <<= 1;
                }
                printf("After 1 Shifting\n");
                printCurrentKey(key);
                //printf("shift 後：%d\n", key[0]);
            } else {
                printf("0\n");
                //printf("shift 前：%d\n", key[0]);
                printCurrentKey(key);
                if(!((i == 7 && k == 3)||(i==7&&k==7))){
                    key[x] <<= 1;
                }
                printf("After 0 Shifting\n");
                printCurrentKey(key);
                //printf("shift 後：%d\n", key[0]);
            }
            j >>= 1;
        }
        printf("\n");
    }
    return 0;
}

void printCurrentKey(unsigned *key) {
    for(int k = 0; k < 2; k++){
        unsigned j = 1;
        j <<= 31;
        for(int i = 1; i <= 32; i++) {
            if(key[k] & j){
                printf("1");
            } else { printf("0");}
            j >>= 1;
            
            if(i % 8 == 0)printf("|");
        }
        printf("\n");
    }
    printf("\n---------------------------\n");
}
