/*************************************************************************
	> File Name: 1.HZOJ328.cpp
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
#include<iostream>
using namespace std;

/* OJ328 楼兰图腾 树状数组 
 * 思路：
 * 1. 找^和找v思路相同，即遍历所有y坐标，将i位置前/后小于（或大于）val(i)的元素个数相乘，再累加
 * 2. 1~n中某个数字已出现则在标记数组中标记为1，否则为0
 * 3. i位置前小于val(i)的元素个数可用标记数组的树状数组（前缀和）来记录
 */
#define MAX_N 200000
#define lowbit(x) (x & -x)
int n;
int val[MAX_N + 5];
int c[MAX_N + 5];

void add(int i, int x, int n) {
    while (i <= n) {
        c[i] += x;
        i += lowbit(i);
    }
    return;
}

long long query(int i) {
    long long sum = 0;
    while (i) {
        sum += c[i];
        i  -= lowbit(i);
    }
    return sum;
}

void read() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }     
    return;
}

void solve(int &big, int &small) {
    big = small = 0;
    for (int i = 1; i <= n; i++) {
        int small_pre = query(val[i]);
        int small_post = val[i] - 1 - small_pre;
        int big_pre = i - 1 - small_pre;
        int big_post = n - val[i] - big_pre;
        big += big_pre * big_post;
        small += small_pre * small_post;
        add(val[i], 1, n);
    }
    return;
}

int main() {
    read();
    int big, small;
    solve(big, small);
    cout << big << " " << small << endl;
    return 0;
}

