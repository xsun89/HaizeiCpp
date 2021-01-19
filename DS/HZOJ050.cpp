//
// Created by Xin Sun on 2021-01-14.
//

#include <iostream>
using namespace std;

#define MAX_N 32
#define MAX_M 1000000

int dp[MAX_N + 5][MAX_M + 5];

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) dp[1][i] = i;

    for (int i = 2; i <= n; i++){
        int k = 2;
        for(int j = 2; j <= m; j++){
            if(k < j && dp[i - 1][k - 1] < dp[i][j - k]){
                k++;
            }
            dp[i][j] = dp[i - 1][k - 1] + 1;
        }
    }

    cout << dp[n][m] << endl;
}