//
// Created by Xin Sun on 2021-01-22.
//

#include <iostream>
#include <algorithm>
#define MAX_N 100000
using namespace std;

long long h[MAX_N + 5], top;
long long s[MAX_N + 5], n;
long long r[MAX_N + 5], l[MAX_N + 5];

void read()
{
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];

    return;
}

long long solve()
{
    h[0] = h[n + 1] = -1;
    top = -1;
    s[++top] = 0;
    for (long long i = 1; i <= n; i++){
        while (top != -1 && h[s[top]] >= h[i]) top--;
        l[i] = s[top];
        s[++top] = i;
    }

    top = -1;
    s[++top] = n + 1;
    for (long long i = n; i >= 1; i--){
        while (top != -1 && h[s[top]] >= h[i]) top--;
        r[i] = s[top];
        s[++top] = i;
    }
    long long ans = 0;
    for(long long i = 1; i <= n; i++)
    {
        ans = max(ans, h[i] * abs(r[i] - l[i] - 1));
    }
    return ans;
}
int main()
{
    read();
    cout << solve() << endl;
    return 0;
}