//
// Created by Xin Sun on 2021-01-07.
//
#include <iostream>
using namespace std;
#define MAX_N 500000

int dp[MAX_N + 5];

bool isHunWen(string s, int ind, int cur) {
    while(ind < cur) {
        if (s[ind++] != s[cur--])
            return false;
    }
    return true;
}

int main()
{
    string s;
    cin >> s;
    //dp[i] is for string ending with i, the minimum number of HeiWen
    dp[0] = 0;
    for (int i = 1; i <= s.size(); i++){
        dp[i] = dp[i-1] + 1;
        for (int j = 0; j < i; j++) {
            if (isHunWen(s, j, i - 1)) {
                dp[i] = min(dp[i], dp[j] + 1);
            }
        }
    }
    cout << dp[s.size()] - 1 << endl;
    return 0;
}
