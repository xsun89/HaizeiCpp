/*************************************************************************
	> File Name: 1.HZOJ46.cpp
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
#define MAX_N 500000
int dp[MAX_N + 5];

bool is_palindrome(string &s, int i, int j) {
    while (i < j) {
        if (s[i++] - s[j--]) return false;
        i++, j--;
    }
    return true;
}

int main() {
    string s;
    cin >> s;
    dp[0] = 0;
    for (int i = 1; i <= s.size(); i++) {
        dp[i] = dp[i - 1] + 1;
        for (int j = 0; j < i; j++) {
            if (is_palindrome(s, j, i - 1)) {
                dp[i] = min(dp[i], dp[j] + 1);
            }
        }
    }
    cout << dp[s.size()] - 1 << endl;
    return 0;
}
