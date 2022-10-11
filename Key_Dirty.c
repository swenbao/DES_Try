//
//  main.c
//  DES_Key
//
//  Created by 筍包 on 2022/10/8.
//

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void printCurrentKey(int *key);
void bits_56_to_64(int *key);
void kp(int *key);
void round_key(int *key);
void left_shift (int *key, int num);
void compressKey(int *key);
void printAA(int *key, int lenght, char *str);

int KP[] =
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
int CP[] =
{
    14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};
int SHIFTS[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

int main(){
    char key_txt[8] = {0};
    printf("enter your key : ");
    scanf("%7s", key_txt);
    int key[64] = {0};
    unsigned n = 0;
    for(int k = 0; k < 8; k++){
        int j = 1;
        j <<= 7;
        for(int i = 0; i < 8; i++) {
            if(key_txt[k] & j){
                printf("1");
                key[n] = 1;
                n++;
            } else { 
                printf("0");
                key[n] = 0;
                n++;
            }
            j >>= 1;
        }
        printf("\n");
    }
    printCurrentKey(key);
    bits_56_to_64(key);
    printCurrentKey(key);
    kp(key);
    printCurrentKey(key);
    round_key(key);

    return 0;
}

void printCurrentKey(int *key) {
    for(int i = 1; i <= 64; i++){
        printf("%d", key[i-1]);
        if(i % 8 == 0) printf("|");
    }
    printf("\n---------------------------\n");
}

void printAA(int *key, int lenght, char *str){
    printf("%s\n", str);
    for(int i = 1; i <= lenght; i++){ 
        printf("%d", key[i-1]);
        if(i % 8 == 0) printf("|");
    }
    printf("\n---------------------------\n");
}

void bits_56_to_64(int *key){
    int index = 62, dif = 7, count_1 = 0;
    for(; dif >= 1; index -= 8, dif --){
        for(int i = index; i >= index - 6; i--){
            key[i] = key[i - dif];
            if(key[i - dif] == 1){
                count_1++;
            }
        }
        if(count_1 % 2 == 0){
            key[index+1] = 1;
            count_1 = 0;
        } else { 
            key[index+1] = 0;
            count_1 = 0;
        }
    }
}
void kp(int *key){
    unsigned key_temp [56];
    for(int i = 0; i < 56; i++){
        key_temp[i] = key[KP[i]-1];
    }
    for(int i = 0; i < 64; i++){
        if(i < 56){
            key[i] = key_temp[i];
        } else {
            key[i] = -1;
        }
    }
}
void round_key(int *key){
    int left[28], right[28], combined[56];
    for(int i = 0; i < 56; i++){
        if(i < 28){
            left[i] = key[i];
        } else {
            right[i - 28] = key[i];
        }
    }
    left_shift(left, SHIFTS[0]);
    left_shift(right, SHIFTS[0]);
    printAA(left, 28, "Left");
    printAA(right, 28, "right");

    for(int i = 0; i < 56; i++){
        if(i < 28){
            combined[i] = left[i];
        } else {
            combined[i] = right[i-28];
        }
    }
    printAA(combined, 56, "combined");
    compressKey(combined);
    printAA(combined, 56, "compressed");
}
void left_shift (int *key, int num){
    if(num == 1){
        int temp[28];
        temp[27] = key[0];
        for(int i = 0; i < 27; i++){
            temp[i] = key[i+1];
        }
        for(int i = 0; i <28; i++){
            key[i] = temp[i];
        }
    } else if(num == 2){
        int temp[28];
        temp[26] = key[0];
        temp[27] = key[1];
        for(int i = 0; i < 26; i++){
            temp[i] = key[i+2];
        }
        for(int i = 0; i <28; i++){
            key[i] = temp[i];
        }
    } else {
        printf("error when shifting split key\n");
        exit(1);
    }
}
void compressKey(int *key){
    int temp[48];
    for(int i = 0; i < 48; i++){
        temp[i] = key[CP[i]-1];
    }
    for(int i = 0; i < 56; i++){
        if(i < 48){
            key[i] = temp[i];
        } else {
            key[i] = -1;
        }
    }
}