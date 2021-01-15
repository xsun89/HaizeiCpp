//
// Created by Xin Sun on 2021-01-15.
//

#include <iostream>
#include <algorithm>
using namespace std;
#define MAX_V 100000
int dp[MAX_V + 5];

int main()
{
    int n, V;
    cin >> V >> n;
    int v, w, s;
    for(int i = 1; i <= n; i++){
        cin >> v >> w >> s;
        /*2进制优化，因为采用2进制，可以得到和原来1个1个枚举得到的一样
            例如：s = 14 ==》 k = 1, 2, 4, 7
            take 3 == take 1 plus take 2
            take 4 == take 4
            take 8 == take 1, 3, and 4 can not be 4 + 4 because each case only can do once.
         */
        for(int k = 1; s; k *= 2) {
            if(s < k) k = s;
            s -= k;
            for (int j = V; j >= v * k; j--) {
                dp[j] = max(dp[j], dp[j - v * k] + w * k);
            }
        }
    }

    cout << dp[V] << endl;
}