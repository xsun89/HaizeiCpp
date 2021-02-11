/*************************************************************************
	> File Name: 1.HZOJ369.cpp
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
#define max_num 50000000666LL
typedef long long LL;

int dp[20][2][2], pos[20];

int dfs(int i, int f0, int f1, int limit) {
    if (!limit && dp[i][f0][f1]) return dp[i][f0][f1];
    int up = limit ? pos[i] : 9;
    if (i == 1) {
        if (f0)
    }
    int ret = 0;
    for (int num = 0; num <= up; num++) {
        if (num == 6 && f0 == 0) continue;
        if (num != 6 && f0 != 0) continue;
        ret += dfs(i - 1, f1, 0, limit && num == up);
        if (num != 6 || f1 == 0) ret += dfs(i - 1, f1, 1, limit && num == up);
    }
    if (limit == 0) dp[i][f0][f1] = ret;
    return ret;
}

LL getNum(int n) {
    int cnt = 0;
    while (n) {
        pos[++cnt] = n % 10;
        n /= 10;
    }
    pos[cnt + 1] = pos[cnt + 2] = 0;
    return n - dfs(cnt + 2, 0, 0, 1);
}

LL bs(LL l, LL r, LL x) {
    if (l == r) return l;
    LL mid = (l + r) >> 1;
    if (getNum(mid) < x) return bs(mid + 1, r, x);
    return bs(l, mid, x);
}

void solve() {
    int n;
    cin >> n;
    cout << bs(1, max_num, n) << endl;
    return ;
}

int main() {
    pos[1] = pos[2] = pos[3] = pos[4] = 9;
    pos[5] = pos[6] = 0;
    cout << dfs(6, 0, 0, 1) << endl;
    cout << getNum(1000) << endl;
    int t;
    cin >> t;
    while (t--) solve();    
    return 0;
}
