/*************************************************************************
	> File Name: 5.HZOJ48.cpp
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
#define MAX_N 10000
int dp[MAX_N + 5];

int main() {
    int V, n, v, w;
    cin >> n >> V;
    for (int i = 1; i <= n; i++) {
        cin >> v >> w;
        for (int j = v; j <= V; j++) {
            dp[j] = max(dp[j], dp[j - v] + w);
        }
    }
    cout << dp[V] << endl;
    return 0;
}
