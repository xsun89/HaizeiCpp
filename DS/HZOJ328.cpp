//
// Created by Xin Sun on 2021-02-10.
//

#include <iostream>

using namespace std;

#define MAX_N 200000
#define lowbit(x) (x & -x)

long long c[MAX_N + 5];
long long val[MAX_N + 5];

long long n, up, down;

void add(long long i, long long x, long long n){
    while (i <= n){
        c[i] += x;
        i += lowbit(i);
    }

    return ;
}

long long query(long long i){
    long long sum = 0;
    while (i){
        sum += c[i];
        i -= lowbit(i);
    }

    return sum;
}

void read()
{
    cin >> n;
    for (long long i = 1; i <= n; i++){
        cin >> val[i];
    }
}

void solve()
{
    long long largerLeft = 0;
    long long largerRight = 0;
    long long lowerLeft = 0;
    long long lowerRight = 0;
    for (long long i = 1; i <= n; i++){
        lowerLeft = query(val[i]);
        largerLeft = i - lowerLeft - 1;
        lowerRight = val[i] - lowerLeft - 1;
        largerRight = n - val[i] - largerLeft;
        up += largerLeft * largerRight;
        down += lowerLeft * lowerRight;
        add(val[i], 1, n);
    }
}

int main()
{
    read();
    solve();
    cout << up << " " << down << endl;
    return 0;
}