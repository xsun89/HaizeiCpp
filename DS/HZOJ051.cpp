//
// Created by Xin Sun on 2021-01-26.
//

#include <iostream>

using namespace std;
#define MAX_N 1000
#define MOD_NUM 100007
int m , n;
int s[MAX_N + 5], top;
int c[MAX_N + 5][MAX_N + 5];
int f[MAX_N + 5];

void read(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> c[i][j];
            if(c[i][j]) c[i][j] += c[i-1][j];
        }
    }
}

int solve(){
    long long ans = 0;
    for(int i = 1; i <= n; i++){
        top = -1;
        s[++top] = 0;
        c[i][0] = -1;
        f[0] = 0;
        for(int j = 1; j <= m; j++){
            while(top != -1 && c[i][s[top]] >= c[i][j]) top--;
            f[j] = c[i][j] * (j - s[top]) + f[s[top]];
            s[++top] = j;
            f[j] %= MOD_NUM;
            ans += f[j];
            ans %= MOD_NUM;
        }
    }

    return ans;
}
int main()
{
    read();
    cout << solve() << endl;
    return 0;
}