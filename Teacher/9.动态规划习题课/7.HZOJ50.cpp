/*************************************************************************
	> File Name: 7.HZOJ50.cpp
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
#define MAX_N 32
#define MAX_M 1000000
int dp[MAX_N + 5][MAX_M + 5];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= m; i++) dp[1][i] = i;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = j;
            for (int k = 1; k <= j; k++) {
                dp[i][j] = min(dp[i][j], max(dp[i - 1][k - 1], dp[i][j - k]) + 1);
            }
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}
