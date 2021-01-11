//
// Created by Xin Sun on 2021-01-07.
//
#include <iostream>
using namespace std;
#define MAX_N 500000
int dp[MAX_N + 5];

bool isHunWen(string s, int ind, int cur) {
    int n = cur - ind;

    for (int i = 0; i < n; i++) {
        if (s[i] != s[cur - 1 - i])
            return false;
    }
    return true;
}

int main()
{
    string s;
    cin >> s;
    dp[0] = 1;
    int ind = 0;
    for (int i = 1; i < s.size(); i++){
        if(isHunWen(s, ind, i)){
            dp[i] = dp[ind] + 1;
            ind = i;
        }
    }
    return 0;
}
