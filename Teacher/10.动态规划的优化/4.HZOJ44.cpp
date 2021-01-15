/*************************************************************************
	> File Name: 4.HZOJ44.cpp
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
#include <cstring>
using namespace std;
#define MAX_N 1000000
int dp[MAX_N + 5];
int len[MAX_N + 5];

int binary_search(int *arr, int n, int x) {
    int head = 0, tail = n, mid;
    while (head < tail) {
        mid = (head + tail) >> 1;
        if (arr[mid] < x) head = mid + 1;
        else tail = mid;
    }
    return head;
}

int main() {
    int n, ans = 0, a;
    cin >> n;
    memset(len, 0x3f, sizeof(len));
    len[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        dp[i] = binary_search(len, ans + 1, a);
        len[dp[i]] = a;
        ans = max(dp[i], ans);
    }
    cout << ans << endl;
    return 0;
}
