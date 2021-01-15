//
// Created by Xin Sun on 2021-01-15.
//

#include <iostream>
#include <algorithm>
using namespace std;
#define MAX_V 100000
int dp[MAX_V + 5];

int main()
{
    int n, V;
    cin >> V >> n;
    int v, w, s;
    for(int i = 1; i <= n; i++){
        cin >> v >> w >> s;
        for(int k = 1; k <= s; k++) {
            for (int j = V; j >= v; j--) {
                dp[j] = max(dp[j], dp[j - v] + w);
            }
        }
    }

    cout << dp[V] << endl;
}