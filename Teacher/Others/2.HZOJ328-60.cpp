/*************************************************************************
	> File Name: 2.HZOJ328-60.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 
 ************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;
#define max_n 200000
#define lowbit(x) ((x) & (-x))
int num[max_n + 5];

void add(int j, int v, int n) {
    while (j<=n) {
        num[j] += v;
        j += lowbit(j);
    }
    return ;
}
int alg(int j) {
    int sum = 0;
    while (j) {
        sum += num[j];
        j -= lowbit(j);
    }
    return sum;
}
int main() {
    long long n,a,x = 0, y = 0;
    cin>>n;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        add(a + 1, 1, n);
        int q = alg(a);
        int w = i - 1 - q;
        int e = n - a - w;
        int r = a - 1 - q;
        x +=  w * e;
        y +=  q * r;
    }
    cout << x << " " << y;
    return 0;
}
