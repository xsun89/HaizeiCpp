/*************************************************************************
	> File Name: 1.HZOJ328.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 
 ************************************************************************/

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
long long n;
long long val[MAX_N + 5];
long long c[MAX_N + 5];

void add(long long i, long long x, long long n) {
    while (i <= n) {
        c[i] += x;
        i += lowbit(i);
    }
    return;
}

long long query(long long i) {
    long long sum = 0;
    while (i) {
        sum += c[i];
        i  -= lowbit(i);
    }
    return sum;
}

void read() {
    cin >> n;
    for (long long i = 1; i <= n; i++) {
        cin >> val[i];
    }     
    return;
}

void solve(long long &big, long long &small) {
    big = small = 0;
    for (long long i = 1; i <= n; i++) {
        long long small_pre = query(val[i]);
        long long small_post = val[i] - 1 - small_pre;
        long long big_pre = i - 1 - small_pre;
        long long big_post = n - val[i] - big_pre;
        big += big_pre * big_post;
        small += small_pre * small_post;
        add(val[i], 1, n);
    }
    return;
}

int main() {
    read();
    long long big, small;
    solve(big, small);
    cout << big << " " << small << endl;
    return 0;
}

