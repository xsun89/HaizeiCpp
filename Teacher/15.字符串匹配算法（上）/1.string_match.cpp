/*************************************************************************
	> File Name: 1.string_match.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

int brute_force(const char *s, const char *t) {
    for (int i = 0; s[i]; i++) {
        int flag = 1;
        for (int j = 0; t[j] && flag; j++) {
            flag = flag && (s[i + j] && s[i + j] == t[j]);
        }
        if (flag == 1) return i;
    }
    return -1;
}

int getNext(const char *t, int &j, char input, int *next) {
    while (j != -1 && t[j + 1] != input) j = next[j];
    if (t[j + 1] == input) j += 1;
    return j;
}

int kmp(const char *s, const char *t) {
    int n = strlen(t);
    int *next = (int *)malloc(sizeof(int) * n + 1);
    next[0] = -1;
    for (int i = 1, j = -1; t[i]; i++) next[i] = getNext(t, j, t[i], next);
    for (int i = 0, j = -1; s[i]; i++) {
        if (getNext(t, j, s[i], next) != n - 1) continue;
        return i - n + 1;
    }
    free(next);
    return -1;
}

int sunday(const char *s, const char *t) {
    int offset[256];
    int n = strlen(t), m = strlen(s);
    for (int i = 0; i < 256; i++) offset[i] = n + 1;
    for (int i = 0; t[i]; i++) offset[t[i]] = n - i;
    for (int i = 0; i + n <= m; i += offset[s[i + n]]) {
        int flag = 1;
        for (int j = 0; t[j] && flag; j++) {
            flag = flag && (s[i + j] == t[j]);
        }
        if (flag) return i;
    }
    return -1;
}

int main() {
    char s[100], t[100];
    while (scanf("%s%s", s, t) != EOF) {
        printf("brute_force(%s, %s) = %d\n", s, t, brute_force(s, t));
        printf("kmp(%s, %s) = %d\n", s, t, kmp(s, t));
        printf("sunday(%s, %s) = %d\n", s, t, sunday(s, t));
    }
    return 0;
}
