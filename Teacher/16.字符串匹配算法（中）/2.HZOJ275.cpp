/*************************************************************************
	> File Name: 2.HZOJ275.cpp
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
#define MAX_N 1000000
#define P 9973
#define P1 100007
#define base 13
#define base1 103
long long H[MAX_N + 5];
long long H1[MAX_N + 5];
long long K[MAX_N + 5];
long long K1[MAX_N + 5];
long long inv[P];
long long inv1[P1];
char s[MAX_N + 5];

void init() {
    inv[1] = 1;
    inv1[1] = 1;
    for (long long i = 2; i < P; i++) {
        inv[i] = ((-(P / i) * inv[P % i]) % P + P) % P;
        inv1[i] = ((-(P1 / i) * inv1[P1 % i]) % P1 + P1) % P1;
    }
    K[0] = 1;
    K1[0] = 1;
    for (long long i = 1; i <= MAX_N; i++) {
        K[i] = (K[i - 1] * base) % P;
        K1[i] = (K1[i - 1] * base1) % P1;
    }
    H[0] = 0;
    H1[0] = 0;
    for (long long i = 1; s[i]; i++) {
        H[i] = (H[i - 1] + K[i] * s[i]) % P;
        H1[i] = (H1[i - 1] + K1[i] * s[i]) % P1;
    }
    return ;
}

long long getH(long long l, long long r) {
    return ((H[r] - H[l - 1]) % P * inv[K[l]] % P + P) % P;
}

long long getH1(long long l, long long r) {
    return ((H1[r] - H1[l - 1]) % P1 * inv1[K1[l]] % P1 + P1) % P1;
}

int main() {
    scanf("%s", s + 1);
    long long m, l1, l2, r1, r2;
    init();
    scanf("%lld", &m);
    for (long long i = 0; i < m; i++) {
        scanf("%lld%lld%lld%lld", &l1, &r1, &l2, &r2);
        if (getH(l1, r1) == getH(l2, r2) && getH1(l1, r1) == getH1(l2, r2)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}
