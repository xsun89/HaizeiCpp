/*************************************************************************
	> File Name: 3.HZOJ271.cpp
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

#define MAX_N 300000
int q[MAX_N + 5], head = 0, tail = 0;
int val[MAX_N + 5];

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    for (int i = 1; i <= n; i++) {
        while (tail - head && val[q[tail - 1]] > val[i]) --tail;
        q[tail++] = i;
        if (q[head] <= i - k) head++;
        if (i >= k) {
            i > k && cout << " ";
            cout << val[q[head]];
        }
    }
    cout << endl;
    head = tail = 0;
    for (int i = 1; i <= n; i++) {
        while (tail - head && val[q[tail - 1]] < val[i]) --tail;
        q[tail++] = i;
        if (q[head] <= i - k) head++;
        if (i >= k) {
            i > k && cout << " ";
            cout << val[q[head]];
        }
    }
    cout << endl;
    return 0;
}
