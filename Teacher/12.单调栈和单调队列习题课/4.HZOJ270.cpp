/*************************************************************************
	> File Name: 4.HZOJ270.cpp
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
#include <climits>
using namespace std;
#define MAX_N 300000
int s[MAX_N + 5], n, m;
int q[MAX_N + 5], head, tail;

void read() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] += s[i - 1];
    }
    return ;
}

int solve() {
    int ans = INT_MIN;
    head = tail = 0;
    q[tail++] = 0;
    for (int i = 1; i <= n; i++) {
        if (i - q[head] > m) head++;
        ans = max(ans, s[i] - s[q[head]]);
        while (tail - head && s[q[tail - 1]] > s[i]) --tail;
        q[tail++] = i;
    }
    return ans;
}

int main() {
    read();
    cout << solve() << endl;
    return 0;
}
