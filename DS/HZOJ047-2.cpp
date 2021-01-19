//
// Created by Xin Sun on 2021-01-13.
//
#include <iostream>
#include <algorithm>
using namespace std;

int dp[MAX_V + 5];

int main()
{
    int n, V;
    cin >> V >> n;
    int v, w;
    for(int i = 1; i <= n; i++){
        cin >> v >> w;
        for(int j = V; j >= v; j--){
            dp[j] = max(dp[j], dp[j - v] + w);
        }
    }

    cout << dp[V] << endl;
}