//
// Created by Xin Sun on 2021-02-12.
//
#include <iostream>

using namespace std;
int brute_force(const char *input, const char *target)
{
    for (int i = 0; input[i]; i++){
        int flag = 0;
        for (int j = 0; target[j]; j++){
            if(input[i+j] == target[j]){
                continue;
            }else{
                flag = 1;
                break;
            }
        }
        if(flag == 0) {
            return i;
        }
    }
    return -1;
}

void getNext(const char *t, int *next){
    int j = -1;
    next[0] = -1;
    for(int i = 1; t[i]; i++){
        while(j != -1 && t[j + 1] != t[i]){
            j = next[j];
        }
        if(t[j + 1] == t[i]){
            j = j + 1;
        }
        next[i] = j;
    }

    return;
}

int kmp(const char *s, const char *t){
    int len = strlen(t);
    int *next = (int *)malloc(sizeof(int) * (len + 1));
    getNext(t, next);
    for(int i = 0, j = -1; s[i]; i++){
        while(j != -1 && s[i] != t[j + 1]){
            j = next[j];
        }
        if(s[i] == t[j + 1]) {
            j += 1;
        }
        if(t[j + 1] == 0) {
            free(next);
            return i - len + 1;
        }
    }
    free(next);
    return -1;
}

int main()
{
    char s[100], t[100];
    int flag = 1;
    flag = flag && 1 == 3;

    while (scanf("%s%s", s, t) != EOF) {
        printf("brute_force(%s, %s) = %d\n", s, t, brute_force(s, t));
        printf("kmp(%s, %s) = %d\n", s, t, kmp(s, t));
    }

    printf("\n");
    return 0;
}
